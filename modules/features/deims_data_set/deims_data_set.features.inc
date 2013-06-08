<?php
/**
 * @file
 * deims_data_set.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_data_set_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function deims_data_set_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function deims_data_set_node_info() {
  $items = array(
    'data_set' => array(
      'name' => t('Data set'),
      'base' => 'node_content',
      'description' => t('Basic information about a data set. The information collected here enables the associated data to be discovered on the web. Here we capture the Data Set title, abstract, geo-temporal references and other high level details. These information pieces are all part of the basics of a metadata collection.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
