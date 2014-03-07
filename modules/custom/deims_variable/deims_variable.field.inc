<?php

/**
 * @file
 * Field integration for the DEIMS Variable Field module.
 */

/**
 * Implements hook_field_info().
 */
function deims_variable_field_info() {
  $info['deims_variable'] = array(
    'label' => t('Variable'),
    'description' => '',
    'default_widget' => 'deims_variable_default',
    'default_formatter' => 'deims_variable_default',
  );

  return $info;
}

/**
 * Implements hook_field_load().
 */
function deims_variable_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    foreach ($items[$id] as $delta => $item) {
      foreach ($item as $column => $value) {
        if (!empty($field['columns'][$column]['serialize'])) {
          if (empty($value)) {
            $items[$id][$delta][$column] = isset($field['columns'][$column]['unserialized default']) ? $field['columns'][$column]['unserialized default'] : NULL;
          }
          else {
            $unserialized_value = @unserialize($value);
            if ($unserialized_value !== FALSE || $value == 'b:0;') {
              $items[$id][$delta][$column] = $unserialized_value;
            }
          }
        }
      }
    }
  }
}

/**
 * Implements hook_field_is_empty().
 */
function deims_variable_field_is_empty($item, $field) {
  return empty($item['name'])
      && empty($item['label'])
      && empty($item['definition'])
      && empty($item['missing_values'])
      && empty($item['type'])
      && empty($item['data']['unit'])
      && empty($item['data']['pattern'])
      && empty($item['data']['codes']);
}

/**
 * Implements hook_field_validate().
 */
function deims_variable_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $delta => $item) {
    if (!deims_variable_field_is_empty($item, $field)) {
      if (empty($item['name'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => 'deims_variable_name_empty',
          'message' => t('Please provide a <strong>name</strong> for this variable.'),
          'element' => array('name'),
        );
      }

      if (empty($item['definition'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => 'deims_variable_definition_empty',
          'message' => t('Please provide a <strong>definition</strong> for this variable.'),
          'element' => array('definition'),
        );
      }

      switch ($item['type']) {
        case DEIMS_VARIABLE_TYPE_NOMINAL:
          // Nominal variables have no detailed options.
          break;

        case DEIMS_VARIABLE_TYPE_PHYSICAL:
          /*if ($item['data']['minimum'] >= $item['data']['maximum']) {
            $errors[$field['field_name']][$langcode][$delta][] = array(
              'error' => 'deims_variable_minimum_error',
              'message' => t('%name: the minimum value must be smaller than the maximum value.', array('%name' => $instance['label'])),
            );
          }
          if ($item['data']['maximum'] <= $item['data']['minimum']) {
            $errors[$field['field_name']][$langcode][$delta][] = array(
              'error' => 'deims_variable_maximum_error',
              'message' => t('%name: the maximum value must be larger than the minimum value.', array('%name' => $instance['label'])),
            );
          }*/
          break;

        case DEIMS_VARIABLE_TYPE_DATE:
          break;

        case DEIMS_VARIABLE_TYPE_CODES:
          if (empty($items[$delta]['data']['codes'])) {
            $errors[$field['field_name']][$langcode][$delta][] = array(
              'error' => 'deims_variable_codes_empty',
              'message' => t('Code type variables must not have an empty code list.'),
              'element' => array('data', 'codes'),
            );
          }
          break;
      }
    }
  }
}

/**
 * Implements hook_field_presave().
 */
function deims_variable_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  foreach ($items as $delta => &$item) {
    // Force nominal variables to save an empty missing values array.
    if ($item['type'] == DEIMS_VARIABLE_TYPE_NOMINAL) {
      $item['missing_values'] = array();
    }

    if (empty($item['id']) && array_key_exists('id', $item)) {
      unset($item['id']);
    }

    unset($item['field_remove_item']);

    // Serialize all columns that are flagged as such in hook_field_schema().
    foreach ($item as $column => $value) {
      if (!empty($field['columns'][$column]['serialize'])) {
        if (!empty($value)) {
          $items[$delta][$column] = serialize($value);
        }
        else {
          $items[$delta][$column] = isset($field['columns'][$column]['unserialized default']) ? serialize($field['columns'][$column]['unserialized default']) : NULL;
        }
      }
    }
  }
}

/**
 * Implements hook_field_widget_info().
 */
function deims_variable_field_widget_info() {
  $info['deims_variable_default'] = array(
    'label' => t('Default'),
    'field types' => array('deims_variable'),
  );

  return $info;
}

/**
 * Implements hook_field_widget_form().
 */
function deims_variable_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // We need to actually track the form parents of our widget since it may be
  // used with inline entity forms.
  $field_name = $element['#field_name'];
  $langcode = $element['#language'];
  $parents = array_merge($element['#field_parents'], array($field_name, $langcode, $delta));

  $element['#state_parent'] = $parents[0] . '[' . implode('][', array_slice($parents, 1)) . ']';
  $element['#attached']['css'][] = drupal_get_path('module', 'deims_variable') . '/deims_variable.field.css';
  $element['#attached']['js'][] = drupal_get_path('module', 'deims_variable') . '/deims_variable.field.js';

  if ($field['cardinality'] == 1) {
    $element['#type'] = 'fieldset';
  }
  else {
    $details_attributes = array('class' => array('variable-entry'));
    if (empty($items[$delta])) {
      $details_attributes['open'] = 'open';
    }
    $element['details_start'] = array(
      '#markup' => '<details' . drupal_attributes($details_attributes) . '>',
      '#weight' => -200,
    );
    $element['summary'] = array(
      '#markup' => '<summary title="' . t('Click to expand or collapse the variable entry form.') . '">' . t('Unnamed variable') . '</summary>',
      '#weight' => -195,
    );
    $element['details_end'] = array(
      '#markup' => '</details>',
      '#weight' => 200,
    );
  }

  $element['actions'] = array(
    '#type' => 'actions',
    // Ensure that the actions element is output inbetween the <details> and
    // the <summary> elements.
    '#weight' => -205,
    '#access' => $field['cardinality'] == FIELD_CARDINALITY_UNLIMITED,
  );

  $element['id'] = array(
    '#type' => 'value',
    '#value' => isset($items[$delta]['id']) ? $items[$delta]['id'] : NULL,
  );
  $element['name'] = array(
    '#prefix' => '<div class="variable-left-column form-wrapper">',
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('The name of the actual column in the source file.'),
    '#default_value' => isset($items[$delta]['name']) ? $items[$delta]['name'] : '',
    '#required' => $instance['required'],
    '#maxlength' => 255,
    '#size' => 30,
    '#attributes' => array('class' => array('variable-name')),
  );
  $element['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#description' => t('The human-readable label of the variable.'),
    '#default_value' => isset($items[$delta]['label']) ? $items[$delta]['label'] : '',
    '#maxlength' => 255,
    '#attributes' => array('class' => array('variable-label')),
  );
  $element['definition'] = array(
    '#type' => 'textarea',
    '#title' => t('Definition'),
    '#description' => t('The definition of the variable (column). Example: The air temperature collected at 2 meters above the ground. Other example: The set of codes used to categorize the sub-plots where the census studies were conducted.'),
    '#default_value' => isset($items[$delta]['definition']) ? $items[$delta]['definition'] : '',
    '#required' => $instance['required'],
    '#rows' => 2,
  );

  $element['missing_values'] = array(
    '#type' => 'textarea',
    '#title' => t('Missing values'),
    '#description' => t("Any missing value codes should be described here. Use a pipe character to separate the code from the explanation of the code used for the missing value. For example: -9999|Instrument Failed, NA|Not Applies, -77777|Out of calibration Range, BLANK|Not sure, but no good."),
    '#default_value' => isset($items[$delta]['missing_values']) ? list_allowed_values_string($items[$delta]['missing_values']) : '',
    '#placeholder' => "-9999|Instrument Failed",
    '#rows' => 2,
    '#element_validate' => array('list_allowed_values_setting_validate'),
    '#field_has_data' => FALSE,
    '#field' => array('type' => 'list_text'),
    '#suffix' => '</div><div class="variable-right-column">',
    '#states' => array(
      'invisible' => array(
        // Nominal variables do not have missing values, so hide this field.
        ':input[name="' . $element['#state_parent'] . '[type]"]' => array('value' => DEIMS_VARIABLE_TYPE_NOMINAL),
      ),
    ),
    '#attributes' => array('class' => array('variable-missing-values')),
  );

  if ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
    $element['actions']['remove_button'] = array(
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#name' => implode('_', $parents) . '_remove_button',
      '#delta' => $delta,
      '#submit' => array('deims_variable_remove_submit'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'path' => 'deims-variable/field-remove-item/ajax',
        'effect' => 'fade',
      ),
      '#attributes' => array(
        'class' => array('remove-button'),
      ),
    );
  }

  // Set up a trackable target ID so the ajax system knows what content to
  // replace.
  $target_id = 'edit-' . drupal_clean_css_identifier(implode('-', $parents)) . '-data-values';

  $element['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('What type of variable is this?'),
    '#options' => _deims_variable_types(),
    '#default_value' => isset($items[$delta]['type']) ? $items[$delta]['type'] : DEIMS_VARIABLE_TYPE_NOMINAL,
    '#ajax' => array(
      'wrapper' => $target_id,
      'callback' => 'deims_variable_variable_type_select_callback',
    ),
    '#attributes' => array('class' => array('variable-type')),
  );

  $element['data'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#weight' => 50,
    '#prefix' => '<div id="' . $target_id . '">',
    '#suffix' => '</div></div>',
  );

  // Check if the type value has been submitted.
  $type_exists = FALSE;
  $type = drupal_array_get_nested_value($form_state, array_merge(array('values'), $parents, array('type')), $type_exists);
  if (!$type_exists && !empty($element['type']['#default_value'])) {
    $type = $element['type']['#default_value'];
  }

  switch ($type) {
    case DEIMS_VARIABLE_TYPE_NOMINAL:
      // Nominal variables have no detailed options.
      break;

    case DEIMS_VARIABLE_TYPE_PHYSICAL:
      $element['data']['unit'] = array(
        '#type' => 'select_or_other',
        '#title' => t('Unit of measure'),
        '#description' => t('The unit reference to quantify a measurement. Usually these are well know standard units with reference to one of the many reference systems (metric systems) such as the centimeter-gram-second (cgs) or the international system (SI), or the units typically used in the US (inch, mile, pound, gallon, etc).'),
        // Use NULL as a default value here instead of an empty string, to
        // prevent 'Illegal choice' errors if this element is converted to a
        // select_or_other type below.
        '#default_value' => isset($items[$delta]['data']['unit']) ? $items[$delta]['data']['unit'] : NULL,
        '#options' => LterUnitHelper::getUnitOptions(1),
        '#required' => TRUE,
        '#attributes' => array(
          'data-create_option_text' => t('Use other unit'),
          'class' => array('chosen-enabled'),
        ),
      );
      $element['data']['maximum'] = array(
        '#type' => 'numberfield',
        '#title' => t('Maximum value'),
        '#description' => t('The maximum value attainable by this variable or measurement.'),
        '#default_value' => isset($items[$delta]['data']['maximum']) ? $items[$delta]['data']['maximum'] : '',
        '#size' => 5,
        '#step' => 'any',
      );
      $element['data']['minimum'] = array(
        '#type' => 'numberfield',
        '#title' => t('Minimum value'),
        '#description' => t('The mininum value attainable by this variable or measurement.'),
        '#default_value' => isset($items[$delta]['data']['minimum']) ? $items[$delta]['data']['minimum'] : '',
        '#size' => 5,
        '#step' => 'any',
      );
      $element['data']['precision'] = array(
        '#type' => 'numberfield',
        '#title' => t('Precision'),
        '#description' => t('The precision value of this variable or measurement.'),
        '#default_value' => isset($items[$delta]['data']['precision']) ? $items[$delta]['data']['precision'] : '',
        '#size' => 5,
        '#step' => 'any',
      );
      break;

    case DEIMS_VARIABLE_TYPE_DATE:
      $element['data']['pattern'] = array(
        '#type' => 'textfield',
        '#title' => t('Date and/or time pattern'),
        '#description' => t('This is the format in which the date is expressed.'),
        '#default_value' => isset($items[$delta]['data']['pattern']) ? $items[$delta]['data']['pattern'] : '',
        '#required' => TRUE,
        '#size' => 30,
        '#placeholder' => 'DD/MM/YYYY',
      );
      break;

    case DEIMS_VARIABLE_TYPE_CODES:
      $element['data']['codes'] = array(
        '#type' => 'textarea',
        '#title' => t('Codes'),
        '#description' => t('The possible codes this variable can contain. Enter one code per line, in the format code|label. The label is optional: if a line contains a single string, it will be used as both code and label.'),
        '#default_value' => isset($items[$delta]['data']['codes']) ? list_allowed_values_string($items[$delta]['data']['codes']) : '',
        '#required' => TRUE,
        '#placeholder' => "L|Larvae",
        '#rows' => 9,
        '#element_validate' => array('list_allowed_values_setting_validate'),
        '#field_has_data' => FALSE,
        '#field' => array('type' => 'list_text'),
        '#attributes' => array('class' => array('variable-data-codes')),
      );
      break;
  }
  return $element;
}

function deims_variable_variable_type_select_callback($form, $form_state) {
  $parents = $form_state['triggering_element']['#array_parents'];
  // The type element triggered this, so remove it from parents.
  array_pop($parents);
  // We want the data part of the form.
  $parents[] = 'data';
  return drupal_array_get_nested_value($form, $parents);
}

/**
 * Page callback to handle AJAX for removing a field collection item.
 *
 * Copied from field_collection_remove_js().
 *
 * This is a direct page callback. The actual job of deleting the item is
 * done in the submit handler for the button, so all we really need to
 * do is process the form and then generate output. We generate this
 * output by doing a replace command on the id of the entire form element.
 */
function deims_variable_remove_js() {
  require_once DRUPAL_ROOT . '/includes/form.inc';

  // drupal_html_id() very helpfully ensures that all html IDS are unique
  // on a page. Unfortunately what it doesn't realize is that the IDs
  // we are generating are going to replace IDs that already exist, so
  // this actually works against us.
  if (isset($_POST['ajax_html_ids'])) {
    unset($_POST['ajax_html_ids']);
  }

  list($form, $form_state) = ajax_get_form();
  drupal_process_form($form['#form_id'], $form, $form_state);

  // Get the information on what we're removing.
  $button = $form_state['triggering_element'];
  // Go two levels up in the form, to the whole widget.
  $element = drupal_array_get_nested_value($form, array_slice($button['#array_parents'], 0, -4));
  // Now send back the proper AJAX command to replace it.
  $return = array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace('#' . $element['#id'], drupal_render($element))
    ),
  );

  // Because we're doing this ourselves, messages aren't automatic. We have
  // to add them.
  $messages = theme('status_messages');
  if ($messages) {
    $return['#commands'][] = ajax_command_prepend('#' . $element['#id'], $messages);
  }

  return $return;
}

/**
 * Submit callback to remove an item from the field UI multiple wrapper.
 *
 * Copied from field_collection_remove_submit()
 *
 * When a remove button is submitted, we need to find the item that it
 * referenced and delete it. Since field UI has the deltas as a straight
 * unbroken array key, we have to renumber everything down. Since we do this
 * we *also* need to move all the deltas around in the $form_state['values']
 * and $form_state['input'] so that user changed values follow. This is a bit
 * of a complicated process.
 */
function deims_variable_remove_submit($form, &$form_state) {
  $button = $form_state['triggering_element'];
  $delta = $button['#delta'];

  // Where in the form we'll find the parent element.
  $address = array_slice($button['#array_parents'], 0, -3);

  // Go one level up in the form, to the widgets container.
  $parent_element = drupal_array_get_nested_value($form, $address);
  $field_name = $parent_element['#field_name'];
  $langcode = $parent_element['#language'];
  $parents = $parent_element['#field_parents'];

  $field_state = field_form_get_state($parents, $field_name, $langcode, $form_state);

  // Go ahead and renumber everything from our delta to the last
  // item down one. This will overwrite the item being removed.
  for ($i = $delta; $i <= $field_state['items_count']; $i++) {
    $old_element_address = array_merge($address, array($i + 1));
    $new_element_address = array_merge($address, array($i));

    $moving_element = drupal_array_get_nested_value($form, $old_element_address);
    $moving_element_value = drupal_array_get_nested_value($form_state['values'], $old_element_address);
    $moving_element_input = drupal_array_get_nested_value($form_state['input'], $old_element_address);

    // Tell the element where it's being moved to.
    $moving_element['#parents'] = $new_element_address;

    // Move the element around.
    form_set_value($moving_element, $moving_element_value, $form_state);
    drupal_array_set_nested_value($form_state['input'], $moving_element['#parents'], $moving_element_input);
  }

  // Then remove the last item. But we must not go negative.
  if ($field_state['items_count'] > 0) {
    $field_state['items_count']--;
  }

  // Fix the weights. Field UI lets the weights be in a range of
  // (-1 * item_count) to (item_count). This means that when we remove one,
  // the range shrinks; weights outside of that range then get set to
  // the first item in the select by the browser, floating them to the top.
  // We use a brute force method because we lost weights on both ends
  // and if the user has moved things around, we have to cascade because
  // if I have items weight weights 3 and 4, and I change 4 to 3 but leave
  // the 3, the order of the two 3s now is undefined and may not match what
  // the user had selected.
  $input = drupal_array_get_nested_value($form_state['input'], $address);
  // Sort by weight
  uasort($input, '_field_sort_items_helper');

  // Reweight everything in the correct order.
  $weight = -1 * $field_state['items_count'];
  foreach ($input as $key => $item) {
    if ($item) {
      $input[$key]['_weight'] = $weight++;
    }
  }

  drupal_array_set_nested_value($form_state['input'], $address, $input);
  field_form_set_state($parents, $field_name, $langcode, $form_state, $field_state);

  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_field_widget_error().
 */
function deims_variable_field_widget_error($element, $error, $form, &$form_state) {
  $error_element = $element;
  if (!empty($error['element'])) {
    $error_element = drupal_array_get_nested_value($element, $error['element']);
  }
  if ($error_element) {
    form_error($error_element, $error['message']);
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function deims_variable_field_formatter_info() {
  $info['deims_variable_summary'] = array(
    'label' => t('Summary with details'),
    'field types' => array('deims_variable'),
  );
  $info['deims_variable_table'] = array(
    'label' => t('Table'),
    'field types' => array('deims_variable'),
  );
  $info['eml_attribute_list'] = array(
    'label' => t('EML attributeList'),
    'field types' => array('deims_variable'),
  );
  $info['bdp_attribute_list'] = array(
    'label' => t('BDP attributeList'),
    'field types' => array('deims_variable'),
  );
  $info['iso_attribute_list'] = array(
    'label' => t('ISO attributeList'),
    'field types' => array('deims_variable'),
  );

  return $info;
}

/**
 * Implements hook_field_formatter_view().
 */
function deims_variable_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {
    case 'deims_variable_summary':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'deims_variable_summary',
          '#variable' => $item,
        );
      }
      break;

    case 'deims_variable_table':
      if (!empty($items)) {
        // Display all values in a single element.
        $element[0] = array(
          '#theme' => 'deims_variable_table',
          '#variables' => $items,
        );
      }
      break;

    case 'eml_attribute_list':
      $attributes = array();

      foreach ($items as $delta => $item) {
        $attribute = array();
        $attribute['attributeName'] = $item['name'];
        $attribute['attributeLabel'] = !empty($item['label']) ? $item['label'] : $item['name'];
        $attribute['attributeDefinition'] = $item['definition'];

        switch ($item['type']) {
          case DEIMS_VARIABLE_TYPE_NOMINAL:
            $attribute['storageType'] = 'string';
            $attribute['measurementScale']['nominal'] = array();
            $attribute['measurementScale']['nominal']['nonNumericDomain'] = array();
            $attribute['measurementScale']['nominal']['nonNumericDomain']['textDomain']['definition'] = $item['definition'];
            break;
          case DEIMS_VARIABLE_TYPE_PHYSICAL:
            $attribute['measurementScale']['ratio'] = array();
            $attribute['measurementScale']['ratio']['unit'] = array();
            if (LterUnitHelper::isUnitStandard($item['data']['unit'])) {
              $attribute['measurementScale']['ratio']['unit']['standardUnit'] = $item['data']['unit'];
            }
            else {
              $attribute['measurementScale']['ratio']['unit']['customUnit'] = $item['data']['unit'];
            }
            if (drupal_strlen($item['data']['precision'])) {
              $attribute['measurementScale']['ratio']['precision'] = $item['data']['precision'];
            }
            $attribute['measurementScale']['ratio']['numericDomain'] = array();
            $attribute['measurementScale']['ratio']['numericDomain']['numberType'] = 'real';
            if (drupal_strlen($item['data']['minimum'])) {
              $attribute['measurementScale']['ratio']['numericDomain']['bounds'][] = array(
                'key' => 'minimum',
                'attributes' => array('exclusive' => 'false'),
                'value' => $item['data']['minimum'],
              );
            }
            if (drupal_strlen($item['data']['maximum'])) {
              $attribute['measurementScale']['ratio']['numericDomain']['bounds'][] = array(
                'key' => 'maximum',
                'attributes' => array('exclusive' => 'false'),
                'value' => $item['data']['maximum'],
              );
            }
            break;
          case DEIMS_VARIABLE_TYPE_DATE:
            $attribute['storageType'] = 'date';
            $attribute['measurementScale']['dateTime'] = array();
            $attribute['measurementScale']['dateTime']['formatString'] = $item['data']['pattern'];
            break;
          case DEIMS_VARIABLE_TYPE_CODES:
            $attribute['storageType'] = 'string';
            $attribute['measurementScale']['nominal'] = array();
            $attribute['measurementScale']['nominal']['nonNumericDomain'] = array();
            $attribute['measurementScale']['nominal']['nonNumericDomain']['enumeratedDomain'] = array();
            foreach ($item['data']['codes'] as $key => $value) {
              $attribute['measurementScale']['nominal']['nonNumericDomain']['enumeratedDomain'][] = array(
                'key' => 'codeDefinition',
                'value' => array(
                  'code' => $key,
                  'definition' => $value,
                ),
              );
            }
            break;
        }

        foreach ($item['missing_values'] as $key => $value) {
           $attribute[] = array(
              'key' => 'missingValueCode',
              'value' => array(
                 'code' => $key,
                 'codeExplanation' => $value,
               ),
           );
        }

        $attributes[] = array(
          'key' => 'attribute',
          'value' => $attribute,
        );
      }

      if (!empty($attributes)) {
        $element = array(
          '#theme' => 'eml_elements',
          '#eml' => $attributes,
        );
      }

      break;

    case 'bdp_attribute_list':
      $attributes = array();

      foreach ($items as $delta => $item) {
        $attribute = array();
        $attribute['attrlabl'] = !empty($item['label']) ? $item['label'] : $item['name']; 
        $attribute['attrdef'] = $item['definition'];
        $attribute['attrdefs'] = 'The data provider';

        switch ($item['type']) {
          case DEIMS_VARIABLE_TYPE_NOMINAL:
            $attribute['attrdomv']['udom'] = $item['definition'];
            break;
          case DEIMS_VARIABLE_TYPE_PHYSICAL:
            $attribute['attrdomv']['rdom'] = array();
            if (drupal_strlen($item['data']['minimum'])) {
              $attribute['attrdomv']['rdom']['rdommin']= $item['data']['minimum'];
            }
            if (drupal_strlen($item['data']['maximum'])) {
              $attribute['attrdomv']['rdom']['rdommax'] = $item['data']['maximum'];
            }
            $attribute['attrdomv']['rdom']['attrunit'] = $item['data']['unit'];
            if (drupal_strlen($item['data']['precision'])) {
              $attribute['attrdomv']['rdom']['attrmres'] = $item['data']['precision'];
            }
            break;
          case DEIMS_VARIABLE_TYPE_DATE:
            $attribute['attrdomv']['edom'] = array();
            $attribute['attrdomv']['edom']['edomv'] = 'calendar date/time';
            $attribute['attrdomv']['edom']['edomvd'] = $item['data']['pattern'];
            $attribute['attrdomv']['edom']['edomvds'] = 'gregorian calendar';
            break;
          case DEIMS_VARIABLE_TYPE_CODES:
            $attribute['attrdomv'] = array();
            foreach ($item['data']['codes'] as $key => $value) {
              $attribute['attrdomv'][] = array(
                'key' => 'edom',
                'value' => array(
                  'edomv' => $key,
                  'edomvd' => $value,
                  'edomvds' => 'The data provider',
                ),
              );
            }
            break;
        }

        $attributes[] = array(
          'key' => 'attr',
          'value' => $attribute,
        );
      }

      if (!empty($attributes)) {
        $element = array(
          '#theme' => 'bdp_elements',
          '#bdp' => $attributes,
        );
      }

      break;

    case 'iso_attribute_list':
//    ISO 19110 is not yet part of ISO19115, it is in the DIS stage (Draft)
      $attributes = array();

      foreach ($items as $delta => $item) {
        $attribute = array();
        $attribute['gfc:FC_FeatureAttribute'] = array();       
        $attribute['gfc:FC_FeatureAttribute']['gfc:memberName'] = array();
        $attribute['gfc:FC_FeatureAttribute']['gfc:memberName']['gco:LocalName'] = $item['name'];
        $attribute['gfc:FC_FeatureAttribute']['gfc:definition']['gco:CharacterString'] = $item['definition'];
        $attribute['gfc:FC_FeatureAttribute']['gfc:cardinality']['gco:Multiplicity gco:nilreason=unknown']='';
 
        switch ($item['type']) {

          case DEIMS_VARIABLE_TYPE_PHYSICAL:
   
            $unitmetadata = array();
            if (drupal_strlen($item['data']['precision'])) {
              $unitmetadata['precision'] = $item['data']['precision'];
            }
            if (drupal_strlen($item['data']['minimum'])) {
              $unitmetatada['minimum'] =  $item['data']['minimum'];
            }
            if (drupal_strlen($item['data']['maximum'])) {
              $unitmetadata['maximum'] = $item['data']['maximum'];
            }
            $unitname = "gml:unitDefinition gml:id=" . $item['data']['unit']; 

            $attribute['gfc:FC_FeatureAttribute']['gfc:valueMeasurementUnit'] = array();
            $attribute['gfc:FC_FeatureAttribute']['gfc:valueMeasurementUnit'][$unitname] = array();
            if( !$unitmetadata) {
              $attribute['gfc:FC_FeatureAttribute']['gfc:valueMeasurementUnit'][$unitname]['gml:metadataProperty']['GenericMetadata'] = $unitmetadata;
            } 
            $attribute['gfc:FC_FeatureAttribute']['gfc:valueMeasurementUnit'][$unitname]['gml:identifier codeSpace=http://unit.lternet.edu']='';
                     
            break;
     
          case DEIMS_VARIABLE_TYPE_DATE:
            $attribute['gfc:FC_FeatureAttribute']['gfc:code']['gco:CharacterString'] = 'Date Time Format: '. $item['data']['pattern'];
            break;
     
          case DEIMS_VARIABLE_TYPE_CODES:
            foreach ($item['data']['codes'] as $key => $value) {
              $attribute['gfc:FC_FeatureAttribute'][] = array(
                'key' => 'gfc:listedValue',
                'value' => array(
                  'gfc:FC_ListedValue' => array(
                     'gfc:label' => array('gco:CharacterString' => $key),
                     'gfc:definition' => array('gco:CharacterString' => $value),
                  ),
                ),
              );
            }

            break;
        }

        $attributes[] = array(
          'key' => 'gfc:carrierOfCharacteristics',
          'value' => $attribute,
        );
      
      }
      
      if (!empty($attributes)) {
        $element = array(
          '#theme' => 'iso_elements',
          '#iso' => $attributes,
        );
      }

      break;

  }
  
  return $element;
}

/**
 * Implements hook_field_widget_WIDGET_TYPE_form_alter() on behalf of options_element module.
 */
function options_element_field_widget_deims_variable_default_form_alter(&$element, &$form_state, $context) {
  // @todo What's the intention of usage here?
  $items = $context['items'];
  $delta = $context['delta'];

  deims_variable_convert_select_to_options_element($element['missing_values']);
  if (isset($element['data']['codes'])) {
    deims_variable_convert_select_to_options_element($element['data']['codes']);
  }
}

function deims_variable_convert_select_to_options_element(array &$element) {
  $options = list_extract_allowed_values($element['#default_value'], array('type' => 'list_text'), FALSE);
  $element['#type'] = 'options';
  $element['#key_type'] = 'custom';
  $element['#key_type_toggled'] = TRUE;
  $element['#options'] = !empty($options) ? $options : array();
  $element['#default_value_allowed'] = FALSE;
  $element['#element_validate'] = array_merge(element_info_property('options', '#element_validate'), array('deims_variable_convert_options_value_to_array'));
}

function deims_variable_convert_options_value_to_array($element, &$form_state) {
  form_set_value($element, $element['#value']['options'], $form_state);
}
