<?php

/**
 * @file
 * Definition of DeimsFileMigration.
 */

class DeimsFileMigration extends DrupalFile6Migration {
  protected $dependencies = array();

  public function __construct(array $arguments) {
    $arguments += array(
      'description' => '',
      'source_connection' => 'drupal6',
      'source_version' => 6,
      'source_dir' => 'public://',
      'user_migration' => 'DeimsUser',
      'file_class' => 'MigrateFileUriAsIs',
    );

    parent::__construct($arguments);

    $this->addUnmigratedSources(array(
      'origname',
    ));
  }
}
