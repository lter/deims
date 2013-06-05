<?php
/**
 * @file
 * data_source_content_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function data_source_content_type_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_data_source_details|node|data_source|full';
  $field_group->group_name = 'group_data_source_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Data Source Details',
    'weight' => '5',
    'children' => array(
      0 => 'field_csv_header_lines',
      1 => 'field_csv_footer_lines',
      2 => 'field_csv_orientation',
      3 => 'field_csv_quote_character',
      4 => 'field_csv_field_delimiter',
      5 => 'field_csv_record_delimiter',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_data_source_details|node|data_source|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|data_source|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '2',
    'children' => array(
      0 => 'group_source',
      1 => 'group_temporal',
      2 => 'group_methods',
      3 => 'group_related',
      4 => 'group_variables',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'classes' => 'form-item',
      ),
    ),
  );
  $export['group_details|node|data_source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_methods|node|data_source|form';
  $field_group->group_name = 'group_methods';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Methods',
    'weight' => '9',
    'children' => array(
      0 => 'field_methods',
      1 => 'field_instrumentation',
      2 => 'field_quality_assurance',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-methods field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_methods|node|data_source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_related|node|data_source|form';
  $field_group->group_name = 'group_related';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Related Information',
    'weight' => '10',
    'children' => array(
      0 => 'field_related_sites',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Related Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-related field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_related|node|data_source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_source|node|data_source|form';
  $field_group->group_name = 'group_source';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Source',
    'weight' => '5',
    'children' => array(
      0 => 'field_data_source_file',
      1 => 'field_csv_header_lines',
      2 => 'field_csv_footer_lines',
      3 => 'field_csv_orientation',
      4 => 'field_csv_quote_character',
      5 => 'field_csv_field_delimiter',
      6 => 'field_csv_record_delimiter',
      7 => 'field_connection',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Source',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-source field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_source|node|data_source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_temporal|node|data_source|form';
  $field_group->group_name = 'group_temporal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Temporal Coverage',
    'weight' => '7',
    'children' => array(
      0 => 'field_date_range',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-temporal field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_temporal|node|data_source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_variables|node|data_source|form';
  $field_group->group_name = 'group_variables';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Variables',
    'weight' => '6',
    'children' => array(
      0 => 'field_variables',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-variables field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_variables|node|data_source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_variables|node|data_source|full';
  $field_group->group_name = 'group_variables';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_source';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Variables',
    'weight' => '3',
    'children' => array(
      0 => 'field_variables',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_variables|node|data_source|full'] = $field_group;

  return $export;
}
