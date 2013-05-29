<?php

/**
 * @file
 * Definition of DeimsEntityOrganizationMigration.
 */

class DeimsEntityOrganizationMigration extends Migration {

  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('Entity'));

    $this->connection = Database::getConnection('default', 'drupal6');

    // Build the query for where this data is coming from.
    $query = $this->connection->select('content_type_person', 'ctp');
    $query->fields('ctp', array('nid', 'field_person_organization'));
    // Title of the organization must not be empty.
    $query->condition('ctp.field_person_organization', '', '<>');
    // Ensure that we only migrate duplicate organizations once by grouping.
    $query->groupBy('field_person_organization');

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationEntityAPI('organization', 'organization');

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
      'id',
      'type',
      'changed',
      'language',
      'field_url',
      'field_url:title',
      'field_url:attributes',
      'field_url:language',
    ));
  }
}
