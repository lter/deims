<?php
/**
 * @file
 * deims_image.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_image_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}
