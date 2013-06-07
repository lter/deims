<?php
/**
 * @file
 * deims_taxonomy_section.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function deims_taxonomy_section_taxonomy_default_vocabularies() {
  return array(
    'section' => array(
      'name' => 'Section',
      'machine_name' => 'section',
      'description' => 'Used by Workbench to manage sections for articles and like content.',
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
