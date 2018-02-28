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
      'multiple' => 0,
    ),
  );
  $info['name_eml_individualName'] = array(
    'label' => t('EML individualName'),
    'field types' => array('name'),
  );
  $info['addressfield_eml_address'] = array(
    'label' => t('EML address'),
    'field types' => array('addressfield'),
  );
  $info['eml_electronicMailAddress'] = array(
    'label' => t('EML electronicMailAddress'),
    'field types' => array('email'),
  );
  $info['telephone_eml_phone'] = array(
    'label' => t('EML phone'),
    'field types' => array('telephone'),
    'settings' => array(
      'phonetype' => 'voice',
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
  $info['eml_onlineUrl'] = array(
    'label' => t('EML onlineUrl'),
    'field types' => array('link_field', 'url'),
  );
  $info['eml_text'] = array(
    'label' => t('EML text'),
    'field types' => array('text', 'text_long', 'text_with_summary'),
  );

  // Add a low weight to each formatter so that it isn't assigned as the
  // defaul formatter for new fields.
  foreach ($info as &$formatter) {
    $formatter['weight'] = 100;
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
      $summary[] = t('Element name: @value', array('@value' => !empty($settings['element']) ? $settings['element'] : t('None')));
      $summary[] = empty($settings['multiple']) ? t('Output multiple values inside one tag.') : t('Output multiple values as individual tags.');
      break;

    case 'telephone_eml_phone':
      $summary[] = t('Type: @value', array('@value' => $settings['phonetype']));
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
        '#description' => t('If blank, will not output a root XML element and only output the contents from the template.'),
      );
      $element['multiple'] = array(
        '#type' => 'checkbox',
        '#title' => t('Output multiple values as individual tags.'),
        '#default_value' => $settings['multiple'],
      );
      break;

    case 'telephone_eml_phone':
      $element['phonetype'] = array(
        '#title' => t('Type'),
        '#type' => module_exists('select_or_other') ? 'select_or_other' : 'select',
        '#options' => drupal_map_assoc(array('voice', 'facsimile', 'tdd')),
        '#default_value' => $settings['phonetype'],
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
        $element = array(
          '#theme' => 'eml_elements',
          '#eml' => array('keywordSet' => $keywords),
        );
      }
      break;

    case 'entityreference_eml_element':
      $ids = array();
      foreach ($items as $item) {
        $ids[] = $item['target_id'];
      }
      if (!empty($ids) && $entities = entity_load($field['settings']['target_type'], $ids)) {
        $entities = entity_load($field['settings']['target_type'], $ids);
        $results = entity_view($field['settings']['target_type'], $entities, 'eml', $langcode, FALSE);
        if (!empty($settings['element']) && !empty($settings['multiple'])) {
          $element = array(
            '#theme' => 'eml_tags',
            '#tag' => $settings['element'],
          ) + $results[$field['settings']['target_type']];
        }
        else {
          foreach ($results[$field['settings']['target_type']] as $delta => $result) {
            if (!empty($settings['element'])) {
              $element[$delta] = array(
                '#theme' => 'eml_tag',
                '#tag' => $settings['element'],
                '#value' => render($result),
              );
            }
            else {
              $element[$delta] = array(
                '#markup' => render($result),
              );
            }
          }
        }
      }
      break;

    case 'name_eml_individualName':
      foreach ($items as $delta => $item) {
        $name = array(
          'givenName' => $item['given'],
          'surName' => $item['family'],
        );
        $element[$delta] = array(
          '#theme' => 'eml_elements',
          '#eml' => array('individualName' => $name),
        );
      }
      break;

    case 'addressfield_eml_address':
      foreach ($items as $delta => $item) {
        $address = array();
        if (!empty($item['thoroughfare'])) {
          $address['deliveryPoint'] = $item['thoroughfare'];
        }
        if (!empty($item['premise'])) {
          $address['deliveryPoint'] = $address['deliveryPoint'].", ".$item['premise'];  
        }        
        if (!empty($item['locality'])) {
          $address['city'] = $item['locality'];
        }
        if (!empty($item['administrative_area'])) {
          $address['administrativeArea'] = $item['administrative_area'];
        }
        if (!empty($item['postal_code'])) {
          $address['postalCode'] = $item['postal_code'];
        }
        if (!empty($item['country'])) {
          $address['country'] = $item['country'];
        }

        if (!empty($address)) {
          $element[$delta] = array(
            '#theme' => 'eml_elements',
            '#eml' => array('address' => $address),
          );
        }
      }
      break;

    case 'date_eml_temporalCoverage':
      $values = array();
      foreach ($items as $item) {
        $display['settings']['format_type'] = 'iso_8601';
        $dates = date_formatter_process('date_default', $entity_type, $entity, $field, $instance, $langcode, $item, $display);
        $granularity = date_granularity($field);
        if ($dates['value']['formatted'] != $dates['value2']['formatted']) {
          $value = array(
            'key' => 'rangeOfDates', 'value' => array(
              'beginDate' => _eml_date_value($dates['value'], $granularity),
              'endDate' => _eml_date_value($dates['value2'], $granularity),
             )
          );
        }
        else {
          $value = array(
            'key' => 'singleDateTime', 
            'value' => _eml_date_value($dates['value'], $granularity)
          );
        }
        $values[] = $value;
      }

      if (!empty($values)) {
        $element = array(
          '#theme' => 'eml_elements',
          '#eml' => array('temporalCoverage' => $values),
        );
      }
      break;

    case 'geofield_eml_boundingCoordinates':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'eml_elements',
          '#eml' => array(
            'westBoundingCoordinate' => $item['left'],
            'eastBoundingCoordinate' => $item['right'],
            'northBoundingCoordinate' => $item['top'],
            'southBoundingCoordinate' => $item['bottom'],
          ),
        );
      }
      break;

    case 'telephone_eml_phone':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'eml_elements',
          '#eml' => array(array(
            'key' => 'phone',
            'attributes' => array('phonetype' => $settings['phonetype']),
            'value' => $item['value'],
          )),
        );
      }
      break;

    case 'eml_electronicMailAddress':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'eml_elements',
          '#eml' => array(
            'electronicMailAddress' => $item['email'],
          ),
        );
      }
      break;

    case 'eml_onlineUrl':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'eml_elements',
          '#eml' => array(
            'onlineUrl' => $field['type'] == 'url' ? $item['value'] : $item['url'],
          ),
        );
      }
      break;

    case 'eml_text':
      foreach ($items as $delta => $item) {
        $text = _text_sanitize($instance, $langcode, $item, 'value');
        $element[$delta] = array(
          '#theme' => 'eml_elements',
          '#eml' => array(
            'para' => array('literalLayout' => strip_tags($text)),
          ),
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
