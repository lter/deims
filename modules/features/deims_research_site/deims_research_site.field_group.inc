<?php
/**
 * @file
 * deims_research_site.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function deims_research_site_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|research_site|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'research_site';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '14',
    'children' => array(
      0 => 'field_site_details',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-details field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_details|node|research_site|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_geo_temporal|node|research_site|form';
  $field_group->group_name = 'group_geo_temporal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'research_site';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Geospatial',
    'weight' => '16',
    'children' => array(
      0 => 'field_elevation',
      1 => 'field_coordinates',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Geospatial',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-geo-temporal field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_geo_temporal|node|research_site|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|research_site|form';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'research_site';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '15',
    'children' => array(
      0 => 'field_images',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-images field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_images|node|research_site|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tabs|node|research_site|form';
  $field_group->group_name = 'group_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'research_site';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '3',
    'children' => array(
      0 => 'group_details',
      1 => 'group_images',
      2 => 'group_taxonomy',
      3 => 'group_geo_temporal',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'classes' => 'form-item',
      ),
    ),
  );
  $export['group_tabs|node|research_site|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_taxonomy|node|research_site|form';
  $field_group->group_name = 'group_taxonomy';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'research_site';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Taxonomy',
    'weight' => '18',
    'children' => array(
      0 => 'field_core_areas',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-taxonomy field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_taxonomy|node|research_site|form'] = $field_group;

  return $export;
}
