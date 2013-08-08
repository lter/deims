<?php

/**
 * @file
 * Definition of DeimsContentOrganizationMigration.
 */

class DeimsContentOrganizationMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->connection = Database::getConnection('default', 'drupal6');

    // Build the query for where this data is coming from.
    $query = $this->connection->select('content_type_person', 'ctp');
    $query->fields('ctp', array('nid', 'field_person_organization'));
    // Title of the organization must not be empty.
    $query->condition('ctp.field_person_organization', '', '<>');
    // Ensure that we only migrate duplicate organizations once by grouping.
    $query->groupBy('field_person_organization');

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('organization');

    // Tell Migrate where the IDs for this migration live, and
    // where they should go.
    $source_key_schema = array(
      'nid' => array(
        'type' => 'int',
        'length' => 10,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $source_key_schema, $this->destination->getKeySchema());

    $this->addFieldMapping('title', 'field_person_organization');

    $this->addUnmigratedDestinations(array(
      'uid',
      'created',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'field_url',
      'field_url:title',
      'field_url:attributes',
      'path',
      'comment',
      'pathauto',
    ));
  }
}
