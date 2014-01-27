<?php

/**
 * @file
 * Page callbacks for the DEIMS Data Explorer module.
 */

/**
 * @todo Document deims_data_explorer_page .
 *
 * @param $node
 *
 * @return int
 */
function deims_data_explorer_page($node) {
  // @todo Determine any other checks we need to do.
  if ($node->type != 'data_source') {
    return MENU_NOT_FOUND;
  }

  $connection = field_get_items('node', $node, 'field_deims_data_explorer');
  $variables  = field_get_items('node', $node, 'field_variables');

  if (!empty($connection) && !empty($variables)) {
    $form = drupal_get_form('deims_data_explorer_form', $variables, $connection[0], $node);
    return $form;
  }
  else {
    return MENU_NOT_FOUND;
  }
}

/**
 * [deims_data_explorer_download description]
 */
function deims_data_explorer_download($node, $file) {
  if (!isset($_GET['token']) || !drupal_valid_token($_GET['token'], $_GET['q'])) {
    return MENU_ACCESS_DENIED;
  }

  $output =  array(
    'header' => array(
      '#markup' => '<h2>' . t('File ready for download') . '</h2>',
    ),
    'info' => array(
      '#markup' => '<p>' . t('Your file is ready to be downloaded. It will be available for the next few hours. Please download it now.') . '</p><p>' . theme('file_entity_download_link', array('file' => $file)) . '</p>',
    ),
    'back' => array(
      '#type' => 'markup',
      '#markup' => '<p>' . l('Return to data set', "node/{$node->nid}") . '</p>',
    ),
  );
  return $output;
}

/**
 * @todo Document deims_data_explorer_form .
 *
 * @param $form
 * @param $form_state
 * @param $columns
 * @param $variables
 *
 * @return mixed
 */
function deims_data_explorer_form($form, &$form_state, $variables, $connection, $node) {
  // Get the allowed columns from the data source variable definitions.
  $allowed_column_variables = _deims_de_get_allowed_columns($variables);
  // Get allowed filters from the data source variable definitions.
  $allowed_filters_variables = _deims_de_get_allowed_filters($variables);

  // Flatten the array of columns & filters to just the name value.
  $allowed_columns = _deims_de_flatten_allowed($allowed_column_variables);
  $allowed_filters = _deims_de_flatten_allowed($allowed_filters_variables);

  // Validate these columns actually exist.
  $schema = schema_reference_get_schema_info($connection['connection']);
  //$allowed_columns = array_intersect($allowed_columns, array_keys($schema[$connection['table']]));
  //$allowed_filters = array_intersect($allowed_columns, array_keys($schema[$connection['table']]));

  foreach ($allowed_filters_variables as $index => $variable) {
    if (!empty($schema[$connection['table']]['fields'][$variable['name']])) {
      $allowed_filters_variables[$index]['schema'] = $schema[$connection['table']]['fields'][$variable['name']];
    }
  }

  // Check if the form has been submitted.
  if (isset($form_state['values']['op'])) {
    // Get columns submitted in the form.
    $submitted_columns = _deims_de_get_submitted_columns($form_state['values']['columns_table']);

    // Take only the columns submitted AND are allowed.
    $columns = array_intersect($allowed_columns, $submitted_columns);

    // Get filters submitted in the form.
    $submitted_filters = _deims_de_get_submitted_filters($form_state['values']['filters_table']);

    // Take only the filters submitted AND are allowed.
    $filters = array_intersect_key($form_state['input']['filters'], drupal_map_assoc($allowed_filters), drupal_map_assoc(array_filter($submitted_filters)));
    foreach ($allowed_filters_variables as $variable) {
      if (!empty($filters[$variable['name']])) {
        $filters[$variable['name']]['variable'] = $variable;
      }
    }

    $query = deims_data_explorer_get_query_from_data_source($node, $columns, $filters);
    $total_rows = $query->countQuery()->execute()->fetchField();

    if (empty($total_rows)) {
      $form['results'] = array(
        '#markup' => t('No results found.'),
      );
      return $form;
    }

    switch ($form_state['values']['op']) {
      case 'Web Preview':
        $query->range(0, DEIMS_PREVIEW_COUNT);
        $data = $query->execute()->fetchAll(PDO::FETCH_ASSOC);

        $form['results'] = array(
          '#markup' => deims_data_explorer_generate_preview($columns, $data, $total_rows),
        );

        return $form;
        break;

      case 'Download':
        // Add logic for download button disable and warning.
        if (deims_data_explorer_get_row_count($connection, $filters) >= DEIMS_DOWNLOAD_COUNT) {
           drupal_set_message('This is a very large data set. Please ' . l('contact us', 'contact') .
             ' to obtain a copy.', 'warning', FALSE);
        } else {
          $file = file_save_data('', file_create_filename($connection['table'] . '.csv', variable_get('deims_data_explorer_dir', 'public://data-downloads/')));

          // Set up the batch process.
          $batch = array(
            'title' => 'Processing Data Set',
            'operations' => array(
              array('_fetch_row_batch', array($query, $file, $columns)),
              array('_process_file_for_download', array($file, $connection['table'], $form_state['values']['nid'])),
            ),
            'finished' => '_show_download_link',
            'file' => drupal_get_path('module', 'deims_data_explorer') . '/deims_data_explorer.batch.inc'
          );

          batch_set($batch);
          // This can be left blank because we're setting it in the finished
          // callback hackery magic.
          batch_process();
        }
        break;

      default:
        return MENU_ACCESS_DENIED;
    }
  }

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );

  // START: Create the table to select columns.
  $form['columns_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please select what columns you would like to include.'),
  );

  $header  = array(
    'name' => t('Column'),
    'label' => t('Label'),
    'type' => t('Type'),
    'definition' => t('Definition'),
  );
  $options = array();
  foreach ($allowed_column_variables as $variable) {
    $options[$variable['name']] = array(
      'name' => $variable['name'],
      'label' => $variable['label'],
      'type' => deims_variable_type_label($variable['type']),
      'definition' => $variable['definition'],
    );
  }
  $form['columns_set']['columns_table'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No columns found'),
    '#required' => TRUE,
  );
  // END: Create the table to select columns.


  // START: Create the table to select filters.
  $form['filter_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please choose any filters you would like to add.'),
  );

  $header = array(
    'name' => t('Column'),
    'choice' => t('Filter'),
  );
  $options = array();
  foreach ($allowed_filters_variables as $variable) {
    if ($element = _deims_de_prep_variable($variable, $form_state)) {
      $options[$variable['name']] = array(
        'name' => $variable['name'],
        'choice' => drupal_render($element),
      );
    }
  }
  $form['filter_set']['filters_table'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No filters found'),
  );
  // END: Create the table to select filters.

  //deims_de_prep_variables($variables, $form);

  $form['preview'] = array(
    '#type' => 'submit',
    '#value' => 'Web Preview',
  );

  $form['download'] = array(
    '#type' => 'submit',
    '#value' => 'Download',
  );

  // Commented out by means of patch 18357-download-validation (Luke Wertz)
  // Add logic for download button disable and warning.
  //if (deims_data_explorer_get_row_count($connection) >= DEIMS_DOWNLOAD_COUNT) {
  //  drupal_set_message('This is a very large data set. Please ' . l('contact us', 'contact') .
  //    ' to obtain a copy.', 'warning', FALSE);
  //  unset($form['download']);
  //}
  return $form;
}

function deims_data_explorer_form_validate($form, &$form_state) {
  if (!array_filter($form_state['values']['columns_table'])) {
    drupal_set_message(t('You must select at least one column.'), 'error');
  }
}

function deims_data_explorer_form_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  //unset($form_state['values']['submit'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);

  foreach ($form_state['values'] as $key => $value) {
    // drupal_set_message(t('%name has value %value', array('%name' => $key, '%value' => print_r($value, TRUE))));
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * @todo Document
 *
 * @param array $item
 *
 * @return string
 */
function deims_data_explorer_generate_preview($columns_array, $rows_array, $total_rows = 0) {
  $count = null;
  if ($total_rows >= DEIMS_PREVIEW_COUNT) {
    $count = '<div class="deims-row-count">Showing <strong>' . DEIMS_PREVIEW_COUNT . '</strong>
    of <strong>'. $total_rows . '</strong> records';
  }

  $markup = $count . theme('table', array(
    'header' => $columns_array,
    'rows'   => $rows_array,
  )) . $count;

  return $markup;
}

/**
 * @todo Document _deims_de_get_allowed_columns .
 *
 * @param $variables
 *
 * @return array
 */
function _deims_de_get_allowed_columns($variables) {
  return array_filter($variables, function($variable) {
    return !empty($variable['data']['data_explorer_settings']['expose']);
  });
}

/**
 * @todo Document _deims_de_get_allowed_filters .
 *
 * @param $variables
 *
 * @return array
 */
function _deims_de_get_allowed_filters($variables) {
  return array_filter($variables, function($variable) {
    return !empty($variable['data']['data_explorer_settings']['filter']);
  });
}

function _deims_de_get_submitted_columns($columns) {
  $return = array();
  foreach ($columns as $key => $value) {
     if ($key == $value) {
       $return[] = $value;
     }
  }
  return $return;
}

function _deims_de_get_submitted_filters($columns) {
  $return = array();
  foreach ($columns as $key => $value) {
    if ($key == $value) {
      $return[] = $value;
    }
  }
  return $return;
}

function _deims_de_flatten_allowed($variables) {
  // @todo Change these to return the full variables and use the array map only where needed.
  // @todo Change to only include checked columns.
  return array_map(function ($value) { return $value['name']; }, $variables);
}

/**
 * [deims_data_explorer_get_row_count description]
 * @param  [type] $connection [description]
 * @return [type]             [description]
 */
function deims_data_explorer_get_row_count($connection, array $filters = array()) {
  $db = Database::getConnection('default', $connection['connection']);
  $query = $db->select($connection['table']);
  deims_data_explorer_filters_apply($query, $filters);
  return $query->countQuery()->execute()->fetchField();
}

/**
 * @todo Document deims_data_explorer_get_rows .
 *
 * @param $connection
 * @param array $columns
 * @param array $conditions
 * @param int $limit
 *
 * @return array
 */
function deims_data_explorer_get_rows($connection, array $columns = array(), array $filters = array(), $limit = 20, $from = 0) {
  $db = Database::getConnection('default', $connection['connection']);
  $query = $db->select($connection['table'], 't');
  $query->fields('t', $columns);
  deims_data_explorer_filters_apply($query, $filters);
  $query->range($from, $limit);
  return $query->execute()->fetchAll(PDO::FETCH_ASSOC);
}

function _deims_de_prep_variable($variable, $form_state) {
  if ($variable['type'] == '') {
    $variable['type'] = 'nominal';
  }
  $function = '_deims_de_prep_' . $variable['type'];
  if (function_exists($function)) {
    // Add to form.
    return $function($variable, $form_state);
  }
}

/**
 * @todo Document _deims_prep_list .
 *
 * @param $variable
 */
function _deims_de_prep_codes($variable) {
  $options = array();

  foreach ($variable['data']['codes'] as $key => $value) {
    $options[$key] = $value;
    if ($key != $value) {
      $options[$key] .= ' (' . $key . ')';
    }
  }

  return array(
    '#type' => 'select',
    '#title' => t('Limit by search codes:'),
    '#options' => $options,
    '#name' => 'filters[' . $variable['name'] . '][values][]',
    '#multiple' => TRUE,
    '#attributes' => array('multiple' => 'multiple'),
  );
}

/**
 * @todo Document _deims_de_prep_nominal .
 *
 * @param $variable
 */
function _deims_de_prep_nominal($variable) {
  return array(
    '#type' => 'textfield',
    '#title' => t('Limit by search term:'),
    '#name' => 'filters[' . $variable['name'] . '][value]',
  );
}

/**
 * @todo Document _deims_de_prep_physical .
 *
 * @param $variable
 */
function _deims_de_prep_physical($variable) {
  $element = array();
  $name = $variable['name'];
  $unit = $variable['data']['unit'];

  if (drupal_strlen($variable['data']['minimum']) && drupal_strlen($variable['data']['maximum'])) {
    $minimum = $variable['data']['minimum'];
    $maximum = $variable['data']['maximum'];
    $precision = $variable['data']['precision'];
    $options = array();
    foreach (range($minimum, $maximum, $precision) as $number) {
      $options[$number] = $number;
    }
    $element['min'] = array(
      '#type'          => 'select',
      '#title'         => t("Choose a minimum $unit:"),
      '#options'       => array('' => t('- NA -')) + $options,
      '#default_value' => $minimum,
      '#name' => 'filters[' . $variable['name'] . '][min]',
    );
    $element['max'] = array(
      '#type'          => 'select',
      '#title'         => t("Choose a maximum $unit:"),
      '#options'       => array('' => t('- NA -')) + $options,
      '#default_value' => $maximum,
      '#name' => 'filters[' . $variable['name'] . '][max]',
    );
  }
  else {
    $element['min'] = array(
      '#type'          => 'textfield',
      '#title'         => t("Choose a minimum $unit:"),
      '#name' => 'filters[' . $variable['name'] . '][min]',
      '#size' => 10,
    );
    $element['max'] = array(
      '#type'          => 'textfield',
      '#title'         => t("Choose a maximum $unit:"),
      '#name' => 'filters[' . $variable['name'] . '][max]',
      '#size' => 10,
    );
  }

  return $element;
}

/**
 * @todo Document _deims_de_prep_date .
 *
 * @param $variable
 * @param $
 */
function _deims_de_prep_date($variable, $form_state) {
  switch ($variable['schema']['type']) {
    case 'date':
    case 'datetime':
      $type = $variable['schema']['type'];
      break;
  }
  $element['min'] = array(
    '#prefix' => '<div class="form-item form-type-datetime"><label>' . t('Choose a minimum date') . '</label>',
    '#markup' => '<input type="' . $type . '" name="filters[' . $variable['name'] . '][min]" />',
    '#suffix' => '</div>',
  );
  $element['max'] = array(
    '#prefix' => '<div class="form-item form-type-datetime"><label>' . t('Choose a maximum date') . '</label>',
    '#markup' => '<input type="' . $type . '" name="filters[' . $variable['name'] . '][max]" />',
    '#suffix' => '</div>',
  );
  $element['#attached']['library'][] = array('system', 'ui.datepicker');
  //if ($type == 'datetime') {
    $element['#attached']['js'][] = libraries_get_path('jquery-ui-timepicker') . '/jquery-ui-timepicker-addon.js';
    $element['#attached']['css'][] = libraries_get_path('jquery-ui-timepicker') . '/jquery-ui-timepicker-addon.css';
  //}
  $element['#attached']['js'][] = drupal_get_path('module', 'deims_data_explorer') . '/deims_data_explorer.js';

  return $element;
}

/**
 * @todo Document _deims_de_array2csv .
 *
 * @param array $array
 *
 * @return null|string
 */
function _deims_de_array2csv(array &$array) {
  if (count($array) == 0) {
    return NULL;
  }
  ob_start();
  $df = fopen("php://output", 'w');
  fputcsv($df, array_keys(reset($array)));
  foreach ($array as $row) {
    fputcsv($df, $row);
  }
  fclose($df);

  return ob_get_clean();
}
