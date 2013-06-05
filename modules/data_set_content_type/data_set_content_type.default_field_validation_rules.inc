<?php
/**
 * @file
 * data_set_content_type.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function data_set_content_type_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'data_set_id_unique';
  $rule->name = 'data_set_id_unique';
  $rule->field_name = 'field_data_set_id';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'data_set';
  $rule->validator = 'field_validation_unique_validator';
  $rule->settings = array(
    'data' => 'global',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      6 => 0,
      4 => 0,
      5 => 0,
      7 => 0,
      3 => 0,
    ),
    'errors' => 1,
  );
  $rule->error_message = 'The data set ID must be unique: [value] has already been used by [existing-entity-link].';
  $export['data_set_id_unique'] = $rule;

  return $export;
}
