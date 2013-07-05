<?php
/**
 * @file
 * deims_site_details.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_site_details_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function deims_site_details_eck_bundle_info() {
  $items = array(
  'site_details_site_details' => array(
  'machine_name' => 'site_details_site_details',
  'entity_type' => 'site_details',
  'name' => 'site_details',
  'label' => 'Site Detail',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function deims_site_details_eck_entity_type_info() {
$items = array(
       'site_details' => array(
  'name' => 'site_details',
  'label' => 'Site Detail',
  'properties' => array(
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
