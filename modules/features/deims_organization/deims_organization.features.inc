<?php
/**
 * @file
 * deims_organization.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_organization_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function deims_organization_eck_bundle_info() {
  $items = array(
  'organization_organization' => array(
  'machine_name' => 'organization_organization',
  'entity_type' => 'organization',
  'name' => 'organization',
  'label' => 'Organization',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function deims_organization_eck_entity_type_info() {
$items = array(
       'organization' => array(
  'name' => 'organization',
  'label' => 'Organization',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'changed' => array(
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
    'language' => array(
      'label' => 'Entity language',
      'type' => 'language',
      'behavior' => 'language',
    ),
  ),
),
  );
  return $items;
}
