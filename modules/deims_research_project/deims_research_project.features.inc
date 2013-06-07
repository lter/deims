<?php
/**
 * @file
 * deims_research_project.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_research_project_ctools_plugin_api() {
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
 * Implements hook_node_info().
 */
function deims_research_project_node_info() {
  $items = array(
    'project' => array(
      'name' => t('Research project'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
