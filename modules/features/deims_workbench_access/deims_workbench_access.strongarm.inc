<?php
/**
 * @file
 * deims_workbench_access.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function deims_workbench_access_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_access';
  $strongarm->value = 'taxonomy';
  $export['workbench_access'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_access_custom_form';
  $strongarm->value = 0;
  $export['workbench_access_custom_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_access_taxonomy';
  $strongarm->value = array(
    'section' => 'section',
    'core_areas' => 0,
    'lter_controlled_vocabulary' => 0,
    'station_keywords' => 0,
    'tags' => 0,
  );
  $export['workbench_access_taxonomy'] = $strongarm;

  return $export;
}
