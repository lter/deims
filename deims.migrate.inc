<?php

/**
 * @file
 * Migrate module integration with the DEIMS install profile.
 */

/**
 * Implements hook_migrate_api().
 */
function deims_migrate_api() {
  return array(
    'api' => 2,
    'migrations' => array(
      'DeimsFile' => array('class_name' => 'DeimsFileMigration'),
      'DeimsContentPage' => array('class_name' => 'DeimsContentPageMigration'),
      'DeimsContentStory' => array('class_name' => 'DeimsContentStoryMigration'),
      'DeimsContentResearchSite' => array('class_name' => 'DeimsContentResearchSiteMigration'),
      'DeimsContentPerson' => array('class_name' => 'DeimsContentPersonMigration'),
      'DeimsEntityOrganization' => array('class_name' => 'DeimsEntityOrganizationMigration'),
      'DeimsContentDataSet' => array('class_name' => 'DeimsContentDataSetMigration'),
      'DeimsContentDataFile' => array('class_name' => 'DeimsContentDataFileMigration'),
      'DeimsContentBook' => array('class_name' => 'DeimsContentBookMigration'),

      'DeimsTaxonomyCategories' => array(
        'class_name' => 'DrupalTerm6Migration',
        'description' => "Taxonomy migration for the 'Categories' vocabulary.",
        'group_name' => t('Taxonomy'),
        'source_connection' => 'drupal6',
        'source_version' => 6,
        // @todo Make this vocabulary source ID automatic from the D6 database.
        'source_vocabulary' => '5',
        'destination_vocabulary' => 'categories',
      ),
      'DeimsTaxonomyCoreAreas' => array(
        'class_name' => 'DrupalTerm6Migration',
        'description' => "Taxonomy migration for the 'Core areas' vocabulary.",
        'group_name' => t('Taxonomy'),
        'source_connection' => 'drupal6',
        'source_version' => 6,
        // @todo Make this vocabulary source ID automatic from the D6 database.
        'source_vocabulary' => '1',
        'destination_vocabulary' => 'categories',
      ),
      'DeimsTaxonomyLTERControlled' => array(
        'class_name' => 'DrupalTerm6Migration',
        'description' => "Taxonomy migration for the 'LTER Controlled' vocabulary.",
        'group_name' => t('Taxonomy'),
        'source_connection' => 'drupal6',
        'source_version' => 6,
        // @todo Make this vocabulary source ID automatic from the D6 database.
        'source_vocabulary' => '9',
        'destination_vocabulary' => 'lter_controlled_vocabulary',
      ),
      'DeimsUser' => array(
        'class_name' => 'DrupalUser6Migration',
        'description' => 'User migration',
        'group_name' => t('User'),
        'source_connection' => 'drupal6',
        'source_version' => 6,
      ),
    ),
  );
}
