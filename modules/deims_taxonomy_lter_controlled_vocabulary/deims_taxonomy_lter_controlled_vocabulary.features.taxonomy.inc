<?php
/**
 * @file
 * deims_taxonomy_lter_controlled_vocabulary.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function deims_taxonomy_lter_controlled_vocabulary_taxonomy_default_vocabularies() {
  return array(
    'lter_controlled_vocabulary' => array(
      'name' => 'LTER Controlled Vocabulary',
      'machine_name' => 'lter_controlled_vocabulary',
      'description' => '',
      'hierarchy' => '1',
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
