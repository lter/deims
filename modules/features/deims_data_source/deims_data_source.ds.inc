<?php
/**
 * @file
 * deims_data_source.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function deims_data_source_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|data_source|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'data_source';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'links' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_data_source_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Download',
        ),
      ),
    ),
    'field_methods' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h3',
        ),
      ),
    ),
    'field_instrumentation' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h3',
        ),
      ),
    ),
    'field_quality_assurance' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h3',
        ),
      ),
    ),
    'field_related_sites' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h3',
        ),
      ),
    ),
  );
  $export['node|data_source|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function deims_data_source_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|data_source|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'data_source';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_date_range',
        1 => 'field_description',
        2 => 'field_data_source_file',
      ),
      'left' => array(
        3 => 'group_variables',
        4 => 'field_variables',
      ),
      'right' => array(
        5 => 'field_csv_header_lines',
        6 => 'group_data_source_details',
        7 => 'field_csv_footer_lines',
        10 => 'field_csv_orientation',
        11 => 'field_csv_quote_character',
        14 => 'field_csv_field_delimiter',
        15 => 'field_csv_record_delimiter',
      ),
      'footer' => array(
        8 => 'field_related_sites',
        9 => 'field_methods',
        12 => 'field_instrumentation',
        13 => 'field_quality_assurance',
        16 => 'links',
      ),
    ),
    'fields' => array(
      'field_date_range' => 'header',
      'field_description' => 'header',
      'field_data_source_file' => 'header',
      'group_variables' => 'left',
      'field_variables' => 'left',
      'field_csv_header_lines' => 'right',
      'group_data_source_details' => 'right',
      'field_csv_footer_lines' => 'right',
      'field_related_sites' => 'footer',
      'field_methods' => 'footer',
      'field_csv_orientation' => 'right',
      'field_csv_quote_character' => 'right',
      'field_instrumentation' => 'footer',
      'field_quality_assurance' => 'footer',
      'field_csv_field_delimiter' => 'right',
      'field_csv_record_delimiter' => 'right',
      'links' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'hide_sidebars' => 1,
  );
  $export['node|data_source|full'] = $ds_layout;

  return $export;
}
