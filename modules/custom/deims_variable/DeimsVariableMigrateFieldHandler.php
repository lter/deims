<?php

/**
 * @file
 * Defintiion of DeimsVariableMigrateFieldHandler.
 */

/**
 *
 * Primary value passed to this field must be the variable label.
 *
 * Arguments are used to specify all the other values:
 *  - name: The human-readable name of the variable.
 *  - type: The type of variable (measurment, date, list).
 *  - definition: The description of the variable.
 *  - data: An array of data about the variable, depending on its type.
 *  - missing_values: An array of key/value pairs considered to be empty or
 *    missing.
 *
 * Add the source field mappings to the argument array then add NULL mappings
 * to avoid having fields flagged as as unmapped:
 * @code
 *   $variable_arguments = array(
 *     'name' => array('source_field' => 'source_field_variable_name'),
 *     'type' => array('source_field' => 'source_field_variable_type'),
 *   );
 *   // The variable label should be passed in as the primary value.
 *   $this->addFieldMapping('field_geofield_dest', 'source_field_variable_label')
 *        ->arguments($variable_arguments);
 *   // Since the excerpt is mapped via an argument, add a NULL mapping so it's
 *   // not flagged as unmapped.
 *   $this->addFieldMapping(NULL, 'source_field_variable_name');
 *   $this->addFieldMapping(NULL, 'source_field_variable_type');
 * @endcode
 */
class DeimsVariableMigrateFieldHandler extends MigrateFieldHandler {
  public function __construct() {
    $this->registerTypes(array('deims_variable'));
  }

  /**
   * Provide subfields for the addressfield columns.
   */
  public function fields() {
    // Declare our arguments to also be available as subfields.
    $fields = array(
      'name' => t('The human-readable name of the variable.'),
      'type' => t('The type of variable (measurment, date, list).'),
      'definition' => t('The description of the variable.'),
      'data' => t('An array of data about the variable, depending on its type.'),
      'missing_values' => t('An array of key/value pairs considered to be empty or missing.'),
    );
    return $fields;
  }

  public function prepare($entity, array $field_info, array $instance, array $values) {
    $arguments = array();

    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      if ($value == 'nominal') {
        $value = '';
      }
      $return[$language][$delta] = array('type' => $value) + array_intersect_key($arguments, $field_info['columns']);
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }
}
