<?php

/**
 * @file
 * Definition of DeimsContentPersonMigration.
 */

class DeimsContentPersonMigration extends DrupalNode6Migration {
  protected $dependencies = array('DeimsEntityOrganization');

  public function __construct(array $arguments) {
    $arguments += array(
      'description' => '',
      'group_name' => t('Content'),
      'source_connection' => 'drupal6',
      'source_version' => 6,
      'source_type' => 'person',
      'destination_type' => 'person',
      'user_migration' => 'DeimsUser',
    );

    parent::__construct($arguments);

    // This content type does not have a body field.
    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
    $this->addUnmigratedSources(array('body', 'teaser', 'format'));

    // Add our mappings.
    $this->addFieldMapping('field_phone', 'field_person_phone');
    $this->addFieldMapping('field_email', 'field_person_email');
    $this->addFieldMapping('field_fax', 'field_person_fax');
    $this->addFieldMapping('field_user_account', 'field_person_uid')
      ->sourceMigration(array('Users'));
    $this->addFieldMapping('field_list_in_directory', 'field_person_list');
    $this->addFieldMapping('field_person_id', 'field_person_personid');
    $this->addFieldMapping('field_person_role', 'field_person_role');
    $this->addFieldMapping('field_person_title', 'field_person_title');

    $this->addFieldMapping('field_name', 'field_person_first_name')
      ->arguments(array(
        'family' => array('source_field' => 'field_person_last_name'),
      ));

    $this->addFieldMapping('field_address', 'field_person_country')
      ->arguments(array(
        'administrative_area' => array('source_field' => 'field_person_state'),
        'locality' => array('source_field' => 'field_person_city'),
        'postal_code' => array('source_field' => 'field_person_zipcode'),
        'thoroughfare' => array('source_field' => 'field_person_address'),
      ));

    // Values for field_organization provided in prepare()).
    $this->addFieldMapping('field_organization', NULL)
      ->description('Provided in prepare().');

    $this->addUnmigratedSources(array(
      'field_person_last_name', // Migrated with field_name.
      'field_person_organization', // Migrated in prepare().
      'field_person_address', // Migrated with field_address
      'field_person_city', // Migrated with field_address
      'field_person_state', // Migrated with field_address
      'field_person_zipcode', // Migrated with field_address
      'field_person_fullname',
      'field_person_pubs',
    ));
    $this->addUnmigratedDestinations(array(
      'field_address:administrative_area', // Migrated with field_address
      'field_address:sub_administrative_area',
      'field_address:locality', // Migrated with field_address
      'field_address:dependent_locality',
      'field_address:postal_code', // Migrated with field_address
      'field_address:thoroughfare', // Migrated with field_address
      'field_address:premise',
      'field_address:sub_premise',
      'field_address:organisation_name',
      'field_address:name_line',
      'field_address:first_name',
      'field_address:last_name',
      'field_address:data',
      'field_person_title:language',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    // Convert values from 'Yes' and 'No' to integers 1 and 0, respectively.
    $row->field_person_list = (!empty($row->field_person_list) && $row->field_person_list == 'Yes' ? 1 : 0);

    // Fix empty email values.
    switch ($row->field_person_email) {
      case 'none@none.com':
      case 'not@known.edu':
      case 'unknown.email@unknown.edu':
        $row->field_person_email = NULL;
    }

    // Fix country values.
    switch ($row->field_person_country) {
      case 'USA':
      case 'United States of America':
        $row->field_person_country = 'United States';
        break;
    }

    // Convert a country name into a country code for addressfield.
    if (!empty($row->field_person_country)) {
      $country_code = $this->getCountryCode($row->field_person_country);
      if (!$country_code) {
        // Default the country to the US to ensure that this field is saved.
        $this->queueMessage('Invalid country value ' . $row->field_person_country . ' for person node ' . $row->nid . '. Country has been set to US so that the address field will save.', MigrationBase::MESSAGE_INFORMATIONAL);
        $country_code = 'US';
      }
      $row->field_person_country = $country_code;
    }
    elseif (!empty($row->field_person_address) || !empty($row->field_person_city) || !empty($row->field_person_state)) {
      // Default the country to the US to ensure that this field is saved.
      $this->queueMessage('Empty country value with non-empty address for person node ' . $row->nid . '. Country has been set to US so that the address field will save.', MigrationBase::MESSAGE_INFORMATIONAL);
      $row->field_person_country = 'US';
    }

    if ($row->field_person_zipcode == 0) {
      $row->field_person_zipcode = NULL;
    }
  }

  public function prepare($node, $row) {
    $node->field_organization[LANGUAGE_NONE] = $this->getOrganization($node, $row);

    // Force the auto_entitylabel module to leave $node->title alone.
    $node->auto_entitylabel_applied = TRUE;

    // Remove any empty or illegal delta field values.
    EntityHelper::removeInvalidFieldDeltas('node', $node);
    EntityHelper::removeEmptyFieldValues('node', $node);
  }

  public function getOrganization($node, $row) {
    $field_values = array();

    // Search for an already migrated organization entity with the same title
    // and link value.
    if (!empty($row->field_person_organization)) {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'organization');
      $query->propertyCondition('title', $row->field_person_organization);
      //}
      $results = $query->execute();
      if (!empty($results['organization'])) {
        $field_values[] = array('target_id' => reset($results['organization'])->id);
      }
    }

    return $field_values;
  }

  /**
   * Convert a country name to it's country two-character code.
   *
   * @param string $country_name
   *   The country name.
   *
   * @return string
   *   The two-letter country code if found, or FALSE if the country was not
   *   found.
   */
  public function getCountryCode($country_name) {
    include_once DRUPAL_ROOT . '/includes/locale.inc';
    $countries = country_get_list();
    if (isset($countries[$row->field_person_country])) {
      // Do nothing. Country is already a valid code.
      return $country_name;
    }
    elseif ($code = array_search($row->field_person_country, $countries)) {
      return $code;
    }
    else {
      return FALSE;
    }
  }
}
