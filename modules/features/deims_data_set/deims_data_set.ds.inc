<?php
/**
 * @file
 * deims_data_set.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function deims_data_set_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|data_set|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'data_set';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'data_links' => array(
      'weight' => '0',
      'label' => 'inline',
      'format' => 'default',
    ),
    'data_set_services_icons' => array(
      'weight' => '1',
      'label' => 'inline',
      'format' => 'default',
    ),
    'links' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|data_set|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|data_set|search_result';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'data_set';
  $ds_fieldsetting->view_mode = 'search_result';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => '',
        'ft' => array(),
      ),
    ),
  );
  $export['node|data_set|search_result'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function deims_data_set_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'data_links';
  $ds_field->label = 'Data Links';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|0f9c160e1311a62ef70e6d629058a208',
    'block_render' => '3',
  );
  $export['data_links'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'data_set_services_icons';
  $ds_field->label = 'Data Set Services Links';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|268cc4f74fc2cd31eb0fe71658685dd9',
    'block_render' => '3',
  );
  $export['data_set_services_icons'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function deims_data_set_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|data_set|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'data_set';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'data_links',
        2 => 'data_set_services_icons',
        5 => 'links',
        11 => 'group_downloads',
        13 => 'field_person_creator',
        15 => 'field_person_contact',
        17 => 'field_project_roles',
        19 => 'field_short_name',
        20 => 'field_doi',
        21 => 'field_data_set_id',
      ),
      'left' => array(
        1 => 'field_abstract',
        3 => 'field_related_sites',
        4 => 'group_methodology',
        6 => 'group_quality_assurance',
        7 => 'group_maintenance',
        8 => 'group_additional_info',
        9 => 'group_keywords',
        10 => 'field_methods',
        12 => 'field_instrumentation',
        14 => 'field_quality_assurance',
        16 => 'field_maintenance',
        18 => 'field_additional_information',
        24 => 'field_keywords',
        25 => 'field_core_areas',
      ),
      'footer' => array(
        22 => 'field_related_publications',
        23 => 'field_data_sources',
      ),
    ),
    'fields' => array(
      'data_links' => 'right',
      'field_abstract' => 'left',
      'data_set_services_icons' => 'right',
      'field_related_sites' => 'left',
      'group_methodology' => 'left',
      'links' => 'right',
      'group_quality_assurance' => 'left',
      'group_maintenance' => 'left',
      'group_additional_info' => 'left',
      'group_keywords' => 'left',
      'field_methods' => 'left',
      'group_downloads' => 'right',
      'field_instrumentation' => 'left',
      'field_person_creator' => 'right',
      'field_quality_assurance' => 'left',
      'field_person_contact' => 'right',
      'field_maintenance' => 'left',
      'field_project_roles' => 'right',
      'field_additional_information' => 'left',
      'field_short_name' => 'right',
      'field_doi' => 'right',
      'field_data_set_id' => 'right',
      'field_related_publications' => 'footer',
      'field_data_sources' => 'footer',
      'field_keywords' => 'left',
      'field_core_areas' => 'left',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['node|data_set|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|data_set|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'data_set';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_abstract',
        1 => 'field_data_set_id',
        8 => 'field_short_name',
      ),
      'right' => array(
        2 => 'field_project_roles',
        3 => 'field_related_publications',
        9 => 'field_related_links',
        10 => 'field_related_sites',
        13 => 'field_data_sources',
      ),
      'left' => array(
        4 => 'field_core_areas',
        5 => 'field_publication_date',
        6 => 'field_date_range',
        7 => 'field_keywords',
      ),
      'footer' => array(
        11 => 'field_purpose',
        12 => 'field_methods',
        14 => 'field_instrumentation',
        15 => 'field_maintenance',
        16 => 'field_quality_assurance',
        17 => 'field_additional_information',
        18 => 'field_restricted',
      ),
    ),
    'fields' => array(
      'field_abstract' => 'header',
      'field_data_set_id' => 'header',
      'field_project_roles' => 'right',
      'field_related_publications' => 'right',
      'field_core_areas' => 'left',
      'field_publication_date' => 'left',
      'field_date_range' => 'left',
      'field_keywords' => 'left',
      'field_short_name' => 'header',
      'field_related_links' => 'right',
      'field_related_sites' => 'right',
      'field_purpose' => 'footer',
      'field_methods' => 'footer',
      'field_data_sources' => 'right',
      'field_instrumentation' => 'footer',
      'field_maintenance' => 'footer',
      'field_quality_assurance' => 'footer',
      'field_additional_information' => 'footer',
      'field_restricted' => 'footer',
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
  $export['node|data_set|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|data_set|search_result';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'data_set';
  $ds_layout->view_mode = 'search_result';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_doi',
        2 => 'field_data_set_id',
        3 => 'field_abstract',
        4 => 'field_publication_date',
        5 => 'field_date_range',
        6 => 'field_core_areas',
        7 => 'field_keywords',
        8 => 'field_related_sites',
        9 => 'field_data_sources',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_doi' => 'ds_content',
      'field_data_set_id' => 'ds_content',
      'field_abstract' => 'ds_content',
      'field_publication_date' => 'ds_content',
      'field_date_range' => 'ds_content',
      'field_core_areas' => 'ds_content',
      'field_keywords' => 'ds_content',
      'field_related_sites' => 'ds_content',
      'field_data_sources' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'hide_sidebars' => 0,
  );
  $export['node|data_set|search_result'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function deims_data_set_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'map';
  $ds_view_mode->label = 'Map';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['map'] = $ds_view_mode;

  return $export;
}
