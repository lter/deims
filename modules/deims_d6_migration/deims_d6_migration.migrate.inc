<?php

/**
 * @file
 * Migrate module integration with the DEIMS D6 Migration module.
 */

/**
 * Implements hook_migrate_api().
 */
function deims_d6_migration_migrate_api() {
  $info = array(
    'api' => 2,
    'groups' => array(
      DEIMS_D6_MIGRATION_GROUP => array(
        'title' => t('DEIMS Drupal 6 migration'),
      ),
    ),
    'migrations' => array(
      'DeimsFile' => array(
        'class_name' => 'DeimsFileMigration',
      ),
      'DeimsContentPage' => array(
        'class_name' => 'DeimsContentPageMigration',
      ),
      'DeimsContentStory' => array(
        'class_name' => 'DeimsContentStoryMigration',
      ),
      'DeimsContentResearchSite' => array(
        'class_name' => 'DeimsContentResearchSiteMigration',
      ),
      'DeimsContentPerson' => array(
        'class_name' => 'DeimsContentPersonMigration',
      ),
      'DeimsEntityOrganization' => array(
        'class_name' => 'DeimsEntityOrganizationMigration',
      ),
      'DeimsContentDataSet' => array(
        'class_name' => 'DeimsContentDataSetMigration',
      ),
      'DeimsContentDataFile' => array(
        'class_name' => 'DeimsContentDataFileMigration',
      ),
      'DeimsContentBook' => array(
        'class_name' => 'DeimsContentBookMigration',
      ),
      'DeimsTaxonomyCategories' => array(
        'class_name' => 'DrupalTerm6Migration',
        'description' => "Taxonomy migration for the 'Categories' vocabulary.",
        'source_connection' => 'drupal6',
        'source_version' => 6,
        // @todo Make this vocabulary source ID automatic from the D6 database.
        'source_vocabulary' => '5',
        'destination_vocabulary' => 'categories',
      ),
      'DeimsTaxonomyCoreAreas' => array(
        'class_name' => 'DrupalTerm6Migration',
        'description' => "Taxonomy migration for the 'Core areas' vocabulary.",
        'source_connection' => 'drupal6',
        'source_version' => 6,
        // @todo Make this vocabulary source ID automatic from the D6 database.
        'source_vocabulary' => '1',
        'destination_vocabulary' => 'categories',
      ),
      'DeimsTaxonomyLTERControlled' => array(
        'class_name' => 'DrupalTerm6Migration',
        'description' => "Taxonomy migration for the 'LTER Controlled' vocabulary.",
        'source_connection' => 'drupal6',
        'source_version' => 6,
        // @todo Make this vocabulary source ID automatic from the D6 database.
        'source_vocabulary' => '9',
        'destination_vocabulary' => 'lter_controlled_vocabulary',
      ),
      'DeimsUser' => array(
        'class_name' => 'DrupalUser6Migration',
        'description' => 'User migration',
        'source_connection' => 'drupal6',
        'source_version' => 6,
      ),
    ),
  );

  foreach ($info['migrations'] as &$migration) {
    $migration['group_name'] = DEIMS_D6_MIGRATION_GROUP;
  }

  // Allow other modules to alter our migration classes.
  $overrides = module_invoke_all('deims_migration_overrides');
  foreach ($overrides as $machine_name => $class_name) {
    if (isset($info['migrations'][$machine_name])) {
      $info['migrations'][$machine_name]['class_name'] = $class_name;
    }
  }

  return $info;
}
