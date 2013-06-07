<?php
/**
 * @file
 * deims_research_site.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_research_site_ctools_plugin_api() {
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
function deims_research_site_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function deims_research_site_node_info() {
  $items = array(
    'research_site' => array(
      'name' => t('Research site'),
      'base' => 'node_content',
      'description' => t('The description of a location where research is conducted. Includes a site name and identifier, lat-lon pairs, elevation and other descriptors.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
