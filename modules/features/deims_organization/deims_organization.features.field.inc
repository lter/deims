<?php
/**
 * @file
 * deims_organization.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function deims_organization_field_default_fields() {
  $fields = array();

  // Exported field: 'node-organization-field_url'.
  $fields['node-organization-field_url'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_url',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'url',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'url',
    ),
    'field_instance' => array(
      'bundle' => 'organization',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'hidden',
          'module' => 'bdp',
          'settings' => array(),
          'type' => 'bdp_onlineUrl',
          'weight' => '1',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'url',
          'settings' => array(
            'nofollow' => FALSE,
            'trim_length' => 80,
          ),
          'type' => 'url_default',
          'weight' => '1',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(),
          'type' => 'eml_onlineUrl',
          'weight' => '1',
        ),
        'iso' => array(
          'label' => 'hidden',
          'module' => 'iso',
          'settings' => array(),
          'type' => 'iso_onlineUrl',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_url',
      'label' => 'URL',
      'required' => 0,
      'settings' => array(
        'title_fetch' => 0,
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'url',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'url_external',
        'weight' => '1',
      ),
      'workbench_access_field' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('URL');

  return $fields;
}
