<?php

/**
 * @file
 * Theme callbacks for the DEIMS Variable Field module.
 */

function deims_variable_get_data_summary(array $variable) {
  $summary = array();

  switch ($variable['type']) {
    case DEIMS_VARIABLE_TYPE_NOMINAL:
      // Nominal variables have no detailed options.
      break;
    case DEIMS_VARIABLE_TYPE_PHYSICAL:
      $summary[t('Unit')] = check_plain($variable['data']['unit']);
      $summary[t('Maximum')] = is_numeric($variable['data']['maximum']) ? check_plain($variable['data']['maximum']) : t('Not specified');
      $summary[t('Minimum')] = is_numeric($variable['data']['minimum']) ? check_plain($variable['data']['minimum']) : t('Not specified');
      $summary[t('Precision')] = is_numeric($variable['data']['precision']) ? check_plain($variable['data']['precision']) : t('Not specified');
      break;
    case DEIMS_VARIABLE_TYPE_DATE:
      $summary[t('Date format')] = check_plain($variable['data']['pattern']);
      break;
    case DEIMS_VARIABLE_TYPE_CODES:
      $summary[t('Codes')] = theme('deims_variable_codes_list', array('codes' => $variable['data']['codes']));
      break;
  }

  return $summary;
}

function template_preprocess_deims_variable_summary(array &$variables) {
  $variable = $variables['variable'];

  $variables['label'] = check_plain($variable['label']);
  $variables['name'] = check_plain($variable['name']);
  $variables['type'] = deims_variable_type_label($variable['type']);

  $details = array();
  $details[t('Label')] = check_plain($variable['label']);
  $details[t('Definition')] = check_plain($variable['definition']);
  $details[t('Type')] = check_plain(deims_variable_type_label($variable['type']));
  $details += deims_variable_get_data_summary($variable);
  $details[t('Missing values')] = !empty($variable['missing_values']) ? theme('deims_variable_codes_list', array('codes' => $variable['missing_values'])) : t('None specified');

  $variables['details'] = $details;
}

function theme_deims_variable_codes_list(array &$variables) {
  $options = &$variables['codes'];

  $variables['items'] = array();
  foreach ($options as $key => $value) {
    $variables['items'][] = check_plain($key) . ' = ' . check_plain($value);
  }

  return theme_item_list($variables);
}
