<?php
/**
 * @file
 * data_set_content_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_set_content_type_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function data_set_content_type_node_info() {
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
