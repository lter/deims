<?php
/**
 * @file
 * deims_workbench_access.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_workbench_access_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
