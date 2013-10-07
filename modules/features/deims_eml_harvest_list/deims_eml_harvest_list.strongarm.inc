<?php
/**
 * @file
 * deims_eml_harvest_list.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function deims_eml_harvest_list_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'harvest_list_doc_type';
  $strongarm->value = 'eml://ecoinformatics.org/eml-2.0.1';
  $export['harvest_list_doc_type'] = $strongarm;

  return $export;
}
