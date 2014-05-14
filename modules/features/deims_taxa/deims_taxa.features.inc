<?php
/**
 * @file
 * deims_taxa.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function deims_taxa_eck_bundle_info() {
  $items = array(
  'taxa_taxa' => array(
  'machine_name' => 'taxa_taxa',
  'entity_type' => 'taxa',
  'name' => 'taxa',
  'label' => 'Taxa',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function deims_taxa_eck_entity_type_info() {
$items = array(
       'taxa' => array(
  'name' => 'taxa',
  'label' => 'Taxa',
  'properties' => array(),
),
  );
  return $items;
}
