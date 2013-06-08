<?php
/**
 * @file
 * deims_data_source.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_data_source_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
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
function deims_data_source_node_info() {
  $items = array(
    'data_source' => array(
      'name' => t('Data source'),
      'base' => 'node_content',
      'description' => t('The description of the data file, usually, the physical properties of the file that contains the data. Name, delimiters, URL or resource locator, size, length, description, and the likes.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
