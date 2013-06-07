<?php

/**
 * @file
 * Definition of DeimsMigration.
 */

/**
 * Define the abstract DEIMS Migration group.
 */
abstract class DeimsMigration extends Migration {
  /**
   * Connection object to be used later in each migration class.
   */
  public $connection;

  public function __construct($group = NULL) {
    // Always call the parent constructor first for basic setup
    parent::__construct($group);

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    $this->team = array(
      new MigrateTeamMember('Inigo San Gil', 'isangil@lternet.edu', t('Technical contact')),
    );

    // Set up a connection for the migration database. This is used later
    // in each
    $this->connection = Database::getConnection('default', 'drupal6');
  }

  /**
   * Return an array of unmigrated destinations as field mapping objects.
   */
  public function getUnmigratedDestinations() {
    $results = array();
    foreach ($this->getFieldMappings() as $key => $mapping) {
      if ($mapping->getIssueGroup() == t('DNM')) {
        $results[$key] = $mapping;
      }
    }
    return $results;
  }

  public function prepare($object, $row) {
    // Note there is no parent::prepare($object, $row) here since there is no
    // parent to call.

    // Apply entity-generic alterations before the entity object is saved.
    if ($this->destination instanceof MigrateDestinationEntity) {
      $entity_type = $this->destination->getEntityType();

      // Any field API fields must be defined on the entity object, even if they
      // are unchanged. If a field is left out, and a the object is a new node
      // that will have a new revision saved, the field that is left out will
      // not be 'saved' along with the new revision, which may result in data
      // loss.
      list($id, , $bundle) = entity_extract_ids($entity_type, $object);
      if (!empty($id) && $original = entity_load_unchanged($entity_type, $id)) {
        $instances = field_info_instances($entity_type, $bundle);
        // Compare the keys of field instances against the keys of unmigrated
        // field destinations to get the list of fields we need to manually set.
        $fields = array_intersect_key($instances, $this->getUnmigratedDestinations());
        foreach (array_keys($fields) as $field) {
          $object->$field = $original->$field;
        }
      }

      // Remove empty field values.
      $this->removeEmptyEntityFieldValues($entity_type, $object);

      if (module_exists('entity_translation')) {
        $this->prepareEntityTranslations($entity_type, $object);
      }

      if ($entity_type == 'node') {
        $this->preserveValues($object);
      }
    }
  }

  public function preserveValues($node) {
    if (!empty($node->nid)) {
      // Ensure that certain values are not overridden when updating exsiting
      // migrated content.
      $original = entity_load_unchanged('node', $node->nid);
      foreach (array('language', 'created', 'status', 'promote', 'sticky', 'uid') as $key) {
        $node->$key = $original->$key;
      }
    }
  }

  /**
   * Remove the empty field values from an entity.
   *
   * We run this on migrations because empty field values are only removed when
   * an entity is submitted via the UI and forms, and not programmatically.
   *
   * @param string $entity_type
   *   An entity type.
   * @param object $entity
   *   An entity object.
   */
  public function removeEmptyEntityFieldValues($entity_type, $entity) {
    // Invoke field_default_submit() which will filter out empty field values.
    $form = $form_state = array();
    _field_invoke_default('submit', $entity_type, $entity, $form, $form_state);
  }

  public function prepareEntityTranslations($entity_type, $entity) {
    if (entity_translation_enabled($entity_type)) {
      if ($handler = entity_translation_get_handler($entity_type, $entity)) {

        // Fetch all the languages that have field data for this entity.
        $translation_langcodes = $this->getEntityFieldLangcodes($entity_type, $entity);
        // Remove language-neutral from the array.
        $translation_langcodes = array_diff($translation_langcodes, array(LANGUAGE_NONE, $handler->getLanguage()));
        // Remove any language codes that already have translations.
        $translation_langcodes = array_diff($translation_langcodes, array_keys($handler->getTranslations()->data));

        // Before saving any translations, ensure
        list($id) = entity_extract_ids($entity_type, $entity);
        if (empty($id) && !empty($translation_langcodes)) {
          //$handler->initTranslations();
        }

        if (!empty($translation_langcodes)) {
          foreach ($translation_langcodes as $langcode) {
            $translation = array(
              'language' => $langcode,
              'source' => ($langcode != $handler->getLanguage() ? $handler->getLanguage() : ''),
              'uid' => 1,
              'status' => 1, // Set translations to published by default.
            );
            $handler->setTranslation($translation);
          }
        }
      }
    }
  }

  public function getEntityFieldLangcodes($entity_type, $entity) {
    list(, , $bundle) = entity_extract_ids($entity_type, $entity);
    $instances = field_info_instances($entity_type, $bundle);
    $langcodes = array();
    foreach (array_keys($instances) as $field) {
      if (!empty($entity->{$field})) {
        foreach (array_keys($entity->{$field}) as $field_langcode) {
          $langcodes[] = $field_langcode;
        }
      }
    }
    return array_unique($langcodes);
  }
}
