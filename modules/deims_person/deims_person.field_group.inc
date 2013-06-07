<?php
/**
 * @file
 * deims_person.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function deims_person_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact|node|person|form';
  $field_group->group_name = 'group_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Contact information',
    'weight' => '16',
    'children' => array(
      0 => 'field_address',
      1 => 'field_phone',
      2 => 'field_fax',
      3 => 'field_email',
      4 => 'field_url',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-contact field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_contact|node|person|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|person|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '5',
    'children' => array(
      0 => 'group_records',
      1 => 'group_contact',
      2 => 'group_organization',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => ' group-details field-group-htabs',
      ),
    ),
  );
  $export['group_details|node|person|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_organization|node|person|form';
  $field_group->group_name = 'group_organization';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Organization',
    'weight' => '17',
    'children' => array(
      0 => 'field_organization',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-organization field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_organization|node|person|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_records|node|person|form';
  $field_group->group_name = 'group_records';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Records',
    'weight' => '18',
    'children' => array(
      0 => 'field_user_account',
      1 => 'field_person_id',
      2 => 'field_associated_biblio_author',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-records field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_records|node|person|form'] = $field_group;

  return $export;
}
