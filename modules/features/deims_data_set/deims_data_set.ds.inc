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
    'links' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_data_set_id' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'ID',
        ),
      ),
    ),
    'field_abstract' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_purpose' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_additional_information' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_related_links' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Links',
        ),
      ),
    ),
    'field_related_publications' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Publications',
        ),
      ),
    ),
    'field_maintenance' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_related_sites' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Sites',
        ),
      ),
    ),
    'field_methods' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_instrumentation' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_quality_assurance' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_project_roles' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h3',
          'lb-col' => TRUE,
        ),
      ),
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
      'header' => array(
        0 => 'group_summary',
        19 => 'field_short_name',
        20 => 'field_abstract',
        22 => 'field_doi',
        24 => 'field_data_set_id',
      ),
      'left' => array(
        1 => 'group_categories',
        2 => 'field_project_roles',
        3 => 'group_dates',
        4 => 'group_people',
        6 => 'field_core_areas',
        10 => 'field_keywords',
        26 => 'field_date_range',
        27 => 'field_publication_date',
      ),
      'right' => array(
        5 => 'field_related_publications',
        7 => 'group_related',
        8 => 'group_downloads',
        9 => 'field_eml_link',
        11 => 'field_related_links',
        14 => 'field_related_sites',
        15 => 'field_data_sources',
        17 => 'links',
      ),
      'footer' => array(
        12 => 'field_purpose',
        13 => 'group_methodology',
        16 => 'field_methods',
        18 => 'field_instrumentation',
        21 => 'field_maintenance',
        23 => 'field_quality_assurance',
        25 => 'field_additional_information',
      ),
    ),
    'fields' => array(
      'group_summary' => 'header',
      'group_categories' => 'left',
      'field_project_roles' => 'left',
      'group_dates' => 'left',
      'group_people' => 'left',
      'field_related_publications' => 'right',
      'field_core_areas' => 'left',
      'group_related' => 'right',
      'group_downloads' => 'right',
      'field_eml_link' => 'right',
      'field_keywords' => 'left',
      'field_related_links' => 'right',
      'field_purpose' => 'footer',
      'group_methodology' => 'footer',
      'field_related_sites' => 'right',
      'field_data_sources' => 'right',
      'field_methods' => 'footer',
      'links' => 'right',
      'field_instrumentation' => 'footer',
      'field_short_name' => 'header',
      'field_abstract' => 'header',
      'field_maintenance' => 'footer',
      'field_doi' => 'header',
      'field_quality_assurance' => 'footer',
      'field_data_set_id' => 'header',
      'field_additional_information' => 'footer',
      'field_date_range' => 'left',
      'field_publication_date' => 'left',
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
