<?php

/**
 * @file
 * Definition of DeimsContentResearchSiteMigration.
 */

class DeimsContentResearchSiteMigration extends DrupalNode6Migration {
  protected $dependencies = array();

  public function __construct(array $arguments) {
    $arguments += array(
      'description' => '',
      'group_name' => t('Content'),
      'source_connection' => 'drupal6',
      'source_version' => 6,
      'source_type' => 'research_site',
      'destination_type' => 'research_site',
      'user_migration' => 'DeimsUser',
    );

    parent::__construct($arguments);

    // This content type does not have a body field.
    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
    $this->addUnmigratedSources(array('teaser'));

    $this->addFieldMapping('field_description', 'body');
    $this->addFieldMapping('field_description:format', 'format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_site_id', 'field_research_site_siteid');
    $this->addFieldMapping('field_elevation', 'field_research_site_elevation');

    $this->addFieldMapping('field_images')
      ->sourceMigration('DeimsFile')
      ->arguments(array(
          'file_class' => 'MigrateFileFid',
          'preserve_files' => TRUE,
        ));

    $this->addFieldMapping('field_site_details')
      ->description('Handled in prepare().');
    $this->addFieldMapping('field_coordinates')
      ->description('Handled in prepare().');

    $this->addUnmigratedSources(array(
      'field_research_site_landform',
      'field_research_site_geology',
      'field_research_site_soils',
      'field_research_site_hydrology',
      'field_research_site_vegetation',
      'field_research_site_climate',
      'field_research_site_history',
      'field_research_site_legacynid',
      'field_research_site_core',
    ));

    $this->addUnmigratedDestinations(array(
      'field_images:file_class',
      'field_images:language',
      'field_images:destination_dir',
      'field_images:destination_file',
      'field_images:file_replace',
      'field_images:preserve_files',
      'field_images:source_dir',
      'field_description:language',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
  }

  public function prepare($node, $row) {
    $node->field_site_details[LANGUAGE_NONE] = $this->getSiteDetails($node, $row);
    $node->field_coordinates[LANGUAGE_NONE] = $this->getCoordinates($node, $row);

    // Remove any empty or illegal delta field values.
    EntityHelper::removeInvalidFieldDeltas('node', $node);
    EntityHelper::removeEmptyFieldValues('node', $node);
  }

  public function getSiteDetails($node, $row) {
    $details = array(
      'landform' => 'Landform',
      'geology' => 'Geology',
      'soils' => 'Soils',
      'hydrology' => 'Hydrology',
      'vegetation' => 'Vegetation',
      'climate' => 'Climate',
      'history' => 'History',
    );
    $field_values = array();

    foreach ($details as $detail => $label) {
      $detail_value = trim($row->{'field_research_site_' . $detail});
      if (!empty($detail_value)) {
        $entity = entity_create('site_details', array('type' => 'site_details', 'language' => $node->language));
        $wrapper = entity_metadata_wrapper('site_details', $entity);
        $wrapper->field_label = $label;
        $wrapper->field_description->value = $detail_value;
        entity_save('site_details', $entity);
        $field_values[] = array('target_id' => $entity->id);
      }
    }

    return $field_values;
  }

  public function getCoordinates($node, $row) {
    $field_values = array();

    // Because the coordinates field in Drupal 6 is stored as binary WKT, we
    // have to use MySQL's asText() function to convert the field back to a
    // readable WKT value for us to process in prepare().
    if (!empty($row->field_research_site_pt_coords)) {
      $wkt = db_query("SELECT AsText(:binary)", array(':binary' => $row->field_research_site_pt_coords))->fetchField();

      //$connection = Database::getConnection('default', $this->sourceConnection);
      //$query = $connection->select('content_type_research_site');
      //$query->addExpression('AsText(field_research_site_pt_coords_geo)');
      //$query->condition('nid', $row->nid);
      //$query->condition('vid', $row->vid);
      //$wkt = $query->execute()->fetchField();

      // @todo Investigate if $row->field_research_site_pt_coords can be unpacked rather than needing a new SQL query.
      //dpm(unpack('Lpadding/corder/Lgtype/dlongitude/dlatitude', $row->field_research_site_pt_coords));

      // Force the geo module to accept our field value as WKT.
      $field_values[] = array(
        'geo_type' => 'Point',
        'wkt' => $wkt,
        'master_column' => 'wkt',
      );
    }

    return $field_values;
  }
}
