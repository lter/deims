<?php

/**
 * @file
 * Definition of DeimsContentDataSetMigration.
 */

class DeimsContentDataSetMigration extends DrupalNode6Migration {
  protected $dependencies = array('DeimsContentDataFile', 'DeimsContentPerson', 'DeimsContentResearchSite');

  public function __construct(array $arguments) {
    $arguments += array(
      'description' => '',
      'group_name' => t('Content'),
      'source_connection' => 'drupal6',
      'source_version' => 6,
      'source_type' => 'data_set',
      'destination_type' => 'data_set',
      'user_migration' => 'DeimsUser',
    );

    parent::__construct($arguments);

    // This content type does not have a body field.
    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
    $this->addUnmigratedSources(array('body', 'teaser', 'format'));

    $this->addFieldMapping('field_data_sources', 'field_dataset_datafile_ref')
      ->sourceMigration(array('DeimsContentDataFile'))
      ->description('Possibly overridden in prepareRow().');
    $this->addFieldMapping('field_data_set_id', 'field_dataset_id');
    $this->addFieldMapping('field_abstract', 'field_dataset_abstract');
    $this->addFieldMapping('field_abstract:format', 'field_dataset_abstract:format')
      ->callbacks(array($this, 'mapFormat'));
    //$this->addFieldMapping('field_core_areas', '1');
    $this->addFieldMapping('field_short_name', 'field_dataset_short_name');
    //$this->addFieldMapping('field_keywords', '9');
    $this->addFieldMapping('field_purpose', 'field_dataset_purpose');
    $this->addFieldMapping('field_purpose:format', 'field_dataset_purpose:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_additional_information', 'field_dataset_add_info');
    $this->addFieldMapping('field_additional_information:format', 'field_dataset_add_info:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_related_links', 'field_dataset_related_links');
    $this->addFieldMapping('field_related_links:title', 'field_dataset_related_links:title');
    $this->addFieldMapping('field_related_links:attributes', 'field_dataset_related_links:attributes');
    //$this->addFieldMapping('field_related_publications', 'field_dataset_biblio_ref')
    //  ->sourceMigration(array('DeimsContentBiblioMigration'));
    $this->addFieldMapping('field_maintenance', 'field_dataset_maintenance');
    $this->addFieldMapping('field_maintenance:format', 'field_dataset_maintenance:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_related_sites', 'field_dataset_site_ref')
      ->sourceMigration(array('DeimsContentResearchSite'));
    $this->addFieldMapping('field_methods', 'field_methods');
    $this->addFieldMapping('field_methods:format', 'field_methods:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_instrumentation', 'field_instrumentation');
    $this->addFieldMapping('field_instrumentation:format', 'field_instrumentation:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_quality_assurance', 'field_quality');
    $this->addFieldMapping('field_quality_assurance:format', 'field_quality:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_project_roles')
      ->description('Handled in prepare().');
    $this->addFieldMapping('field_date_range', 'field_beg_end_date');
    $this->addFieldMapping('field_date_range:value2', 'field_beg_end_date:value2');
    $this->addFieldMapping('field_publication_date', 'field_dataset_publication_date');
    $this->addFieldMapping('field_person_creator', 'field_dataset_owner_ref')
      ->sourceMigration(array('DeimsContentPerson'));
    $this->addFieldMapping('field_person_contact', 'field_dataset_contact_ref')
      ->sourceMigration(array('DeimsContentPerson'));

    $this->addUnmigratedSources(array(
      'field_dataset_datamanager_ref', // Handled in prepare()
      'field_dataset_fieldcrew_ref', // Handled in prepare()
      'field_dataset_labcrew_ref', // Handled in prepare()
      'field_dataset_ext_assoc_ref', // Handled in prepare()
    ));

    $this->addUnmigratedDestinations(array(
      'field_data_set_id:language',
      'field_abstract:language',
      'field_short_name:language',
      'field_purpose:language',
      'field_additional_information:language',
      'field_related_links:language',
      'field_maintenance:language',
      'field_methods:language',
      'field_instrumentation:language',
      'field_quality_assurance:language',
      'field_doi',
      'field_doi:language',
      'field_eml_hash',
      'field_eml_hash:language',
      'field_eml_link',
      'field_eml_revision_id',
      'field_eml_valid',
      // No actual source field for these destinations. It is assumed that
      // individual sites will add support for these.
      'field_person_metadata_provider',
      'field_person_publisher',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    // The more reliable field for relating a data set to its data sources
    // is actually on the data source itself, linking back to this data set,
    // rather than the data source reference field on this data set. If this
    // backreference field has a value, use it instead.
    $connection = Database::getConnection('default', $this->sourceConnection);
    $query = $connection->select('content_type_data_file', 'c');
    $query->addField('c', 'nid');
    $query->condition('field_data_file_data_set_nid', $row->nid);
    $query->distinct();
    $results = $query->execute()->fetchCol();
    if (!empty($results)) {
      $row->field_dataset_datafile_ref = $results;
    }
  }

  public function prepare($node, $row) {
    // Fetch and prepare the variables field.
    $node->field_project_roles[LANGUAGE_NONE] = $this->getProjectRoles($node, $row);

    // Remove any empty or illegal delta field values.
    EntityHelper::removeInvalidFieldDeltas('node', $node);
    EntityHelper::removeEmptyFieldValues('node', $node);
  }

  public function getProjectRoles($node, $row) {
    $field_values = array();

    $roles = array(
      'field_dataset_datamanager_ref' => 'data manager',
      'field_dataset_fieldcrew_ref' => 'field crew',
      'field_dataset_labcrew_ref' => 'lab crew',
      'field_dataset_ext_assoc_ref' => 'associated researcher',
    );

    foreach ($roles as $field => $role) {
      if (!empty($row->{$field}) && $source_ids = array_filter($row->{$field})) {
        if ($user_ids = $this->handleSourceMigration('DeimsContentPerson', $source_ids)) {
          if (!is_array($user_ids)) {
            $user_ids = array($user_ids);
          }
          foreach ($user_ids as $user_id) {
            $entity = entity_create('project_role', array('type' => 'project_role', 'language' => $node->language));
            $wrapper = entity_metadata_wrapper('project_role', $entity);
            $wrapper->field_project_role = $role;
            $wrapper->field_related_person = $user_id;
            entity_save('project_role', $entity);
            $field_values[] = array('target_id' => $entity->id);
          }
        }
      }
    }

    return $field_values;
  }
}
