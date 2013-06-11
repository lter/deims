<?php
/**
 * @file
 * deims_person.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_person_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function deims_person_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function deims_person_node_info() {
  $items = array(
    'person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('Identification and contact details for a person involved with the organization. I.e; The name and contact of a researcher, field technician, data manager, etc.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
