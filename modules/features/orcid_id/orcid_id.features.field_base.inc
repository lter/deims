<?php
/**
 * @file
 * orcid_id.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function orcid_id_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_orcid_id'.
  $field_bases['field_orcid_id'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_orcid_id',
    'field_permissions' => array(
      'type' => 0,
    ),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'url',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'url',
  );

  return $field_bases;
}
