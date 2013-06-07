<?php
/**
 * @file
 * deims_taxonomy_station_keywords.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function deims_taxonomy_station_keywords_taxonomy_default_vocabularies() {
  return array(
    'station_keywords' => array(
      'name' => 'Station Keywords',
      'machine_name' => 'station_keywords',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
