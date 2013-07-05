<?php
/**
 * @file
 * deims_project_role.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_project_role_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function deims_project_role_eck_bundle_info() {
  $items = array(
  'project_role_project_role' => array(
  'machine_name' => 'project_role_project_role',
  'entity_type' => 'project_role',
  'name' => 'project_role',
  'label' => 'Project role',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function deims_project_role_eck_entity_type_info() {
$items = array(
       'project_role' => array(
  'name' => 'project_role',
  'label' => 'Project role',
  'properties' => array(
    'changed' => array(
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
  ),
),
  );
  return $items;
}
