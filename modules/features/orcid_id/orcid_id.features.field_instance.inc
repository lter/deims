<?php
/**
 * @file
 * orcid_id.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function orcid_id_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-person-field_orcid_id'.
  $field_instances['node-person-field_orcid_id'] = array(
    'bundle' => 'person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'bdp' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'url',
        'settings' => array(
          'nofollow' => FALSE,
          'trim_length' => 80,
        ),
        'type' => 'url_default',
        'weight' => 30,
      ),
      'eml' => array(
        'label' => 'hidden',
        'module' => 'eml',
        'settings' => array(),
        'type' => 'eml_onlineUrl',
        'weight' => 7,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'iso' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_orcid_id',
    'label' => 'ORCID ID',
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
        'size' => 60,
      ),
      'type' => 'url_external',
      'weight' => 16,
    ),
    'workbench_access_field' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('ORCID ID');

  return $field_instances;
}
