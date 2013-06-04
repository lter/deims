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
            $items[$id][$delta][$column] = unserialize($value);
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
  return !isset($item['label']) || $item['label'] === '';
}

/**
 * Implements hook_field_validate().
 */
function deims_variable_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {

  // Work-around for required fields.
  // Forcing some fields to be required puts empty rows on nodes when they are
  // being edited which then throw an error. The empty rows were needing to be
  // manually removed, so this way we can do a smoke-check for if a row is
  // sane before passing it on.
  foreach ($entity->field_variables[LANGUAGE_NONE] as $key => $field_instance) {
    if (empty($field_instance['label']) || empty($field_instance['name']) || empty($field_instance['definition'])) {
      $fields = array(
        'label' => $field_instance['label'],
        'name' => $field_instance['name'],
        'definition' => $field_instance['definition']
      );

      $partial = array();

      foreach ($fields as $field_partial) {
        if (!empty($field_partial)) {
          array_push($partial, $field_partial);
        }
      }

      foreach (array_intersect($fields, $partial) as $empty_field => $value) {
        $errors[$field['field_name']][$langcode][$key][] = array(
          'error' => 'deims_variable_required_field',
          'message' => 'Please provide a Label, Name, and Definition for each variable.'
        );
      }
    }
  }

  foreach ($items as $delta => $item) {
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
        break;
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
  if ($delta > 0 && !isset($items[$delta]) && empty($form_state['input'])) {
    // Do not add an 'extra' field value if this is not the first delta field
    // item.
    return FALSE;
  }

  // We need to actually track the form parents of our widget since it may be
  // used with inline entity forms.
  $field_name = $element['#field_name'];
  $langcode = $element['#language'];
  $parents = array_merge($element['#field_parents'], array($field_name, $langcode, $delta));
  $state_parent = $parents[0] . '[' . implode('][', array_slice($parents, 1));

  if ($field['cardinality'] == 1) {
    $element['#type'] = 'fieldset';
  }

  $element['#attached']['css'][] = drupal_get_path('module', 'deims_variable') . '/deims_variable.field.css';

  $element['label'] = array(
    '#prefix' => '<div class="variable-left-column form-wrapper">',
    '#type' => 'textfield',
    '#title' => t('Label') . ' <span class="form-required">*</span>',
    '#description' => t('The label of the actual column in the source file.'),
    '#default_value' => isset($items[$delta]['label']) ? $items[$delta]['label'] : '',
    '#required' => FALSE,
    '#maxlength' => 255,
    '#size' => 30,
  );
  $element['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name') . ' <span class="form-required">*</span>',
    '#description' => t('The human-readable name of the variable.'),
    '#default_value' => isset($items[$delta]['name']) ? $items[$delta]['name'] : '',
    '#required' => FALSE,
    '#maxlength' => 255,
  );
  $element['definition'] = array(
    '#type' => 'textarea',
    '#title' => t('Definition') . ' <span class="form-required">*</span>',
    '#description' => t('The definition of the variable (column). Example: The air temperature collected at 2 meters above the ground. Other example: The set of codes used to categorize the sub-plots where the census studies were conducted.'),
    '#default_value' => isset($items[$delta]['definition']) ? $items[$delta]['definition'] : '',
    '#required' => FALSE,
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
        ':input[name="' . $state_parent . '][type]"]' => array('value' => DEIMS_VARIABLE_TYPE_NOMINAL),
      ),
    ),
  );

  if ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
    $element['field_remove_item'] = array(
      '#type' => 'button',
      '#value' => t('Remove'),
      '#ajax' => array(
        'callback' => 'deims_variable_remove_item_ajax_callback',
      ),
      '#execute_submit_handlers' => FALSE,
      '#limit_validation_errors' => array(),
      '#attributes' => array(
        'class' => array('remove-button'),
      ),
    );
  }

  $element['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('What type of variable is this?'),
    '#options' => _deims_variable_types(),
    '#default_value' => isset($items[$delta]['type']) ? $items[$delta]['type'] : DEIMS_VARIABLE_TYPE_NOMINAL,
    '#ajax' => array(
      'wrapper' => 'edit-' . drupal_clean_css_identifier(implode('-', $parents)) . '-data',
      'callback' => 'deims_variable_variable_type_select_callback'
    ),
  );

  $element['data'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#weight' => 50,
    '#suffix' => '</div>',
  );

  // Check if the type value has been submitted.
  $type = drupal_array_get_nested_value($form_state, array_merge(array('values'), $parents, array('type')));
  if (empty($type) && !empty($element['type']['#default_value'])) {
    $type = $element['type']['#default_value'];
  }

  switch ($type) {
    case DEIMS_VARIABLE_TYPE_NOMINAL:
      // Nominal variables have no detailed options.
      break;
    case DEIMS_VARIABLE_TYPE_PHYSICAL:
      $element['data']['unit'] = array(
        '#type' => 'textfield',
        '#title' => t('Unit of measure'),
        '#description' => t('The unit reference to quantify a measurement. Usually these are well know standard units with reference to one of the many reference systems (metric systems) such as the centimeter-gram-second (cgs) or the international system (SI), or the units typically used in the US (inch, mile, pound, gallon, etc).'),
        // Use NULL as a default value here instead of an empty string, to
        // prevent 'Illegal choice' errors if this element is converted to a
        // select_or_other type below.
        '#default_value' => isset($items[$delta]['data']['unit']) ? $items[$delta]['data']['unit'] : NULL,
        '#required' => TRUE,
        '#maxlength' => 128,
        '#size' => 40,
        '#autocomplete_path' => 'lter-unit/autocomplete',
      );
      if (module_exists('select_or_other')) {
        $element['data']['unit']['#type'] = 'select_or_other';
        $element['data']['unit']['#options'] = lter_unit_get_unit_options(1);
      }
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
      );
      break;
  }

  return $element;
}

/**
 * Ajax callback to remove a variable field item.
 */
function deims_variable_remove_item_ajax_callback(&$form, $form_state) {
  $wrapper = '.' . $form['#field_remove_item']['wrapper'];
  $field_name = $form['#field_remove_item']['field_name'];

  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace($wrapper, render($form[$field_name])),
    ),
  );
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
 * Implements hook_field_widget_error().
 */
function deims_variable_field_widget_error($element, $error, $form, &$form_state) {
  form_error($element, $error['message']);
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
        $attribute['attributeLabel'] = $item['label'];
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
            if (lter_unit_is_unit_standard($item['data']['unit'])) {
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
