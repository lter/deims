<?php

/**
 * Alter the deims_variable widget.
 */
function deims_data_explorer_field_widget_deims_variable_default_form_alter(&$element, &$form_state, $context) {
  $element['data']['data_explorer_settings'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Data Explorer Settings',
    '#options' => array('expose' => 'Expose this variable', 'filter' => 'Allow users to filter on this variable'),
    '#default_value' => array(),
    '#weight' => '-1',
  );

  // Set up default values.
  if (!empty($context['items'][$element['#delta']]['data']['data_explorer_settings'])) {
    foreach ($context['items'][$element['#delta']]['data']['data_explorer_settings'] as $field => $value) {
      if ($field == $value) {
        $element['data']['data_explorer_settings']['#default_value'][] = $value;
      }
    }
  }
}
