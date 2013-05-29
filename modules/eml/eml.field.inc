<?php

/**
 * @file
 * Field integration for the EML module.
 */

/**
 * Implements hook_field_formatter_info().
 */
function eml_field_formatter_info() {
  $info['taxonomy_eml_keywordset'] = array(
    'label' => t('EML keywordSet'),
    'field types' => array('taxonomy_term_reference'),
    'settings' => array(
      'keyword_value' => '[term:name]',
      'thesaurus_value' => '[term:vocabulary]',
    ),
  );
  $info['entityreference_eml_element'] = array(
    'label' => t('EML element'),
    'field types' => array('entityreference'),
    'settings' => array(
      'element' => '',
    ),
  );
  $info['entityreference_eml_people'] = array(
    'label' => t('EML people'),
    'field types' => array('entityreference'),
    'settings' => array(
      'element' => '',
    ),
  );
  $info['name_eml_individualName'] = array(
    'label' => t('EML individualName'),
    'field types' => array('name'),
  );
  $info['addressfield_eml_address'] = array(
    'label' => t('EML individualName'),
    'field types' => array('addressfield'),
  );
  $info['email_eml_electronicMailAddress'] = array(
    'label' => t('EML electronicMailAddress'),
    'field types' => array('email'),
  );
  $info['telephone_eml_phone'] = array(
    'label' => t('EML phone'),
    'field types' => array('telephone'),
    'settings' => array(
      'type' => 'voice',
    ),
  );
  $info['date_eml_temporalCoverage'] = array(
    'label' => t('EML temporalCoverage'),
    'field types' => array('date', 'datestamp', 'datetime'),
  );
  $info['geofield_eml_boundingCoordinates'] = array(
    'label' => t('EML boundingCoordinates'),
    'field types' => array('geofield'),
  );

  // Add a low weight to each formatter so that it isn't assigned as the
  // defaul formatter for new fields.
  foreach ($info as &$field) {
    $field['weight'] = 100;
  }

  return $info;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function eml_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  switch ($display['type']) {
    case 'taxonomy_eml_keywordset':
      $summary[] = t('Keyword value: @value', array('@value' => $settings['keyword_value']));
      $summary[] = t('Thesaurus value: @value', array('@value' => $settings['thesaurus_value']));
      break;

    case 'entityreference_eml_element':
      $summary[] = t('Element name: @value', array('@value' => $settings['element']));
      break;

    case 'telephone_eml_phone':
      $summary[] = t('Type: @value', array('@value' => $settings['type']));
      break;
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function eml_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  switch ($display['type']) {
    case 'taxonomy_eml_keywordset':
      $element['keyword_value'] = array(
        '#title' => t('Keyword element value'),
        '#type' => 'textfield',
        '#default_value' => $settings['keyword_value'],
        '#element_validate' => array('token_element_validate'),
        '#token_types' => array('term'),
        '#required' => TRUE,
      );
      $element['thesaurus_value'] = array(
        '#title' => t('Thesaurus element value'),
        '#type' => 'textfield',
        '#default_value' => $settings['thesaurus_value'],
        '#element_validate' => array('token_element_validate'),
        '#token_types' => array('term'),
        '#required' => TRUE,
      );
      break;

    case 'entityreference_eml_element':
      $element['element'] = array(
        '#title' => t('EML element name'),
        '#type' => 'textfield',
        '#default_value' => $settings['element'],
        '#required' => TRUE,
      );
      break;

    case 'telephone_eml_phone':
      $element['type'] = array(
        '#title' => t('Type'),
        '#type' => 'select',
        '#options' => array(
          'voice' => t('Voice'),
          'fax' => t('Fax'),
        ),
        '#default_value' => $settings['type'],
      );
      break;
  }

  return $element;
}

/**
 * Implements hook_field_formatter_view().
 */
function eml_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  switch ($display['type']) {
    case 'taxonomy_eml_keywordset':
      $tids = array();
      foreach ($items as $item) {
        $tids[] = $item['tid'];
      }
      $terms = taxonomy_term_load_multiple($tids);
      $keywords = array();
      foreach ($items as $delta => $item) {
        $keywords[] = array(
          'key' => 'keyword',
          'value' => token_replace($settings['keyword_value'], array('term' => $terms[$item['tid']])),
        );
      }
      if (!empty($keywords)) {
        $keywords[] = array(
          'key' => 'keywordThesaurus',
          'value' => token_replace($settings['thesaurus_value'], array('term' => reset($terms)))
        );
        $entity->eml_elements['keywordSet'] = $keywords;
      }
      break;

    case 'entityreference_eml_element':
      $ids = array();
      foreach ($items as $item) {
        $ids[] = $item['target_id'];
      }
      $entities = entity_load($field['settings']['target_type'], $ids);
      $results = entity_view($field['settings']['target_type'], $entities, 'eml', $langcode, FALSE);
      foreach ($results[$field['settings']['target_type']] as $result) {
        if (!empty($result['#entity']->eml_elements)) {
          $entity->eml_elements[] = array(
            'key' => $settings['element'],
            'value' => $result['#entity']->eml_elements,
          );
        }
        elseif (!empty($result['#node']->eml_elements)) {
          $entity->eml_elements[] = array(
            'key' => $settings['element'],
            'value' => $result['#node']->eml_elements,
          );
        }
      }
      break;

    case 'entityreference_eml_people':
      $ids = array();
      foreach ($items as $item) {
        $ids[] = $item['target_id'];
      }
      $entities = entity_load($field['settings']['target_type'], $ids);

      foreach ($entities as $result) {
        $person = array();
        $person_entity = node_load($result->field_related_person[LANGUAGE_NONE][0]['target_id']);

        $person['individualName'] = array();
        $person['individualName']['givenName'] = $person_entity->field_name[LANGUAGE_NONE][0]['given'];
        $person['individualName']['surName'] = $person_entity->field_name[LANGUAGE_NONE][0]['family'];
        $person['address'] = array();
        $person['address']['deliveryPoint'] = $person_entity->field_address[LANGUAGE_NONE][0]['thoroughfare'];
        $person['address']['city'] = $person_entity->field_address[LANGUAGE_NONE][0]['locality'];
        $person['address']['administrativeArea'] = $person_entity->field_address[LANGUAGE_NONE][0]['administrative_area'];
        $person['address']['postalCode'] = $person_entity->field_address[LANGUAGE_NONE][0]['postal_code'];
        $person['electronicMailAddress'] = $person_entity->field_email[LANGUAGE_NONE][0]['email'];


        $key = 'associatedParty';
        switch ($result->field_project_role[LANGUAGE_NONE][0]['value']) {
          case 'creator':
          case 'contact':
          case 'publisher':
          case 'metadataProvider':
            $key = $result->field_project_role[LANGUAGE_NONE][0]['value'];
            break;
          default:
            $person['role'] = drupal_strtolower($result->field_project_role[LANGUAGE_NONE][0]['value']);
            break;
        }

        $entity->eml_elements[] = array(
          'key' => $key,
          'value' => $person,
        );
      }
      break;

    case 'name_eml_individualName':
      foreach ($items as $item) {
        $name = array(
          'givenName' => $item['given'],
          'surName' => $item['family'],
        );
        $entity->eml_elements[] = array(
          'key' => 'individualName',
          'value' => $name,
        );
      }
      break;

    case 'addressfield_eml_address':
      foreach ($items as $item) {
        $address = array();
        $address['deliveryPoint'] = $item['thoroughfare'];
        $address['city'] = $item['locality'];
        $address['administrativeArea'] = $item['administrative_area'];
        $address['postalCode'] = $item['postal_code'];
        $entity->eml_elements[] = array(
          'key' => 'address',
          'value' => $address,
        );
      }
      break;

    case 'date_eml_temporalCoverage':
      $values = array();
      foreach ($items as $item) {
        $display['settings']['format_type'] = 'iso_8601';
        $dates = date_formatter_process($formatter, $entity_type, $entity, $field, $instance, $langcode, $item, $display);
        $granularity = date_granularity($field);
        if ($dates['value']['formatted'] != $dates['value2']['formatted']) {
          $value = array('key' => 'rangeOfDates', 'value' => array(
            'beginDate' => _eml_date_value($dates['value'], $granularity),
            'endDate' => _eml_date_value($dates['value2'], $granularity),
          ));
        }
        else {
          $value = array('key' => 'singleDateTime', 'value' => _eml_date_value($dates['value'], $granularity));
        }
        $values[] = $value;
      }

      if (!empty($values)) {
        $entity->eml_elements[] = array(
          'key' => 'temporalCoverage',
          'value' => $dates,
        );
      }
      break;

    case 'geofield_eml_boundingCoordinates':
      $values = array();
      foreach ($items as $item) {
        $value = array(
          'westBoundingCoordinate' => $item['right'],
          'eastBoundingCoordinate' => $item['left'],
          'northBoundingCoordinate' => $item['top'],
          'southBoundingCoordinate' => $item['bottom'],
        );
        // @todo <boundingAltitudes> value needs to be inside this element.
        $entity->eml_elements[] = array(
          'key' => 'boundingCoordinates',
          'value' => $value,
        );
      }
      break;
  }

  return $element;
}

function _eml_date_value($date, $granularity) {
  $value = array('calendarDate' => $date['formatted_date']);
  if (!empty($granularity['hour']) || !empty($granularity['minute']) || !empty($granularity['second'])) {
    $value['time'] = $date['formatted_time'] . $date['formatted_timezone'];
  }
  return $value;
}
