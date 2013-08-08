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

  public function prepare($file, $row) {
    // Hack to make migration work as we expect.
    $file->value = 'public://' . $file->value;

    if (!file_exists($file->value)) {
      throw new MigrateException("The file at {$file->value} does not exist.");
    }
  }
}
