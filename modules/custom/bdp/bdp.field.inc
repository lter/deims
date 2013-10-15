<?php

/**
 * @file
 * Field integration for the BDP module.
 */

/**
 * Implements hook_field_formatter_info().
 */
function bdp_field_formatter_info() {
  $info['taxonomy_bdp_keywordset'] = array(
    'label' => t('BDP keywordSet'),
    'field types' => array('taxonomy_term_reference'),
    'settings' => array(
      'thesaurus_value' => '[term:vocabulary]',
      'keyword_value' => '[term:name]',
    ),
  );
  $info['entityreference_bdp_element'] = array(
    'label' => t('BDP element'),
    'field types' => array('entityreference'),
    'settings' => array(
      'element' => '',
      'multiple' => 0,
    ),
  );
  $info['name_bdp_individualName'] = array(
    'label' => t('BDP individualName'),
    'field types' => array('name'),
  );
  $info['name_bdp_publisherName'] = array(
    'label' => t('BDP publisherName'),
    'field types' => array('name'),
  );
  $info['addressfield_bdp_address'] = array(
    'label' => t('BDP address'),
    'field types' => array('addressfield'),
  );
  $info['addressfield_bdp_pubplace'] = array(
    'label' => t('BDP PubPlace'),
    'field types' => array('addressfield'),
  );
  $info['bdp_electronicMailAddress'] = array(
    'label' => t('BDP electronicMailAddress'),
    'field types' => array('email'),
  );
  $info['telephone_bdp_phone'] = array(
    'label' => t('BDP phone'),
    'field types' => array('telephone'),
    'settings' => array(
      'phonetype' => 'voice',
    ),
  );
  $info['date_bdp_temporalCoverage'] = array(
    'label' => t('BDP temporalCoverage'),
    'field types' => array('date', 'datestamp', 'datetime'),
  );
  $info['geofield_bdp_boundingCoordinates'] = array(
    'label' => t('BDP boundingCoordinates'),
    'field types' => array('geofield'),
  );
  $info['bdp_onlineUrl'] = array(
    'label' => t('BDP onlineUrl'),
    'field types' => array('link_field', 'url'),
  );
  // not used (not working either, we took away nested elements)
  $info['bdp_text'] = array(
    'label' => t('BDP text'),
    'field types' => array('text', 'text_long', 'text_with_summary'),
  );

  // Add a low weight to each formatter so that it isn't assigned as the
  // defaul formatter for new fields.
  foreach ($info as &$formatter) {
    $formatter['weight'] = 110;
  }

  return $info;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function bdp_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  switch ($display['type']) {
    case 'taxonomy_bdp_keywordset':
      $summary[] = t('Thesaurus value: @value', array('@value' => $settings['thesaurus_value']));
      $summary[] = t('Keyword value: @value', array('@value' => $settings['keyword_value']));
      break;

    case 'entityreference_bdp_element':
      $summary[] = t('Element name: @value', array('@value' => !empty($settings['element']) ? $settings['element'] : t('None')));
      $summary[] = empty($settings['multiple']) ? t('Output multiple values inside one tag.') : t('Output multiple values as individual tags.');
      break;

    case 'telephone_bdp_phone':
      $summary[] = t('Type: @value', array('@value' => $settings['phonetype']));
      break;
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function bdp_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  switch ($display['type']) {
    case 'taxonomy_bdp_keywordset':
      $element['thesaurus_value'] = array(
        '#title' => t('Thesaurus element value'),
        '#type' => 'textfield',
        '#default_value' => $settings['thesaurus_value'],
        '#element_validate' => array('token_element_validate'),
        '#token_types' => array('term'),
        '#required' => TRUE,
      );
      $element['keyword_value'] = array(
        '#title' => t('Keyword element value'),
        '#type' => 'textfield',
        '#default_value' => $settings['keyword_value'],
        '#element_validate' => array('token_element_validate'),
        '#token_types' => array('term'),
        '#required' => TRUE,
      );
      break;

    case 'entityreference_bdp_element':
      $element['element'] = array(
        '#title' => t('BDP element name'),
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

    case 'telephone_bdp_phone':
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
function bdp_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  switch ($display['type']) {
    case 'taxonomy_bdp_keywordset':
      $tids = array();
      foreach ($items as $item) {
        $tids[] = $item['tid'];
      }

      $terms = taxonomy_term_load_multiple($tids);
      $keywords = array();
      $keywords[] = array(
        'key' => 'themekt',
        'value' => token_replace($settings['thesaurus_value'], array('term' => reset($terms)))
      );
      foreach ($items as $delta => $item) {
        $keywords[] = array(
          'key' => 'themekey',
          'value' => token_replace($settings['keyword_value'], array('term' => $terms[$item['tid']])),
        );
      }
      if (!empty($keywords)) {
        $element = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array('keywords' => $keywords),
        );
      }
      break;

    case 'entityreference_bdp_element':
      $ids = array();
      foreach ($items as $item) {
        $ids[] = $item['target_id'];
      }
      if (!empty($ids) && $entities = entity_load($field['settings']['target_type'], $ids)) {
        $entities = entity_load($field['settings']['target_type'], $ids);
        $results = entity_view($field['settings']['target_type'], $entities, 'bdp', $langcode, FALSE);
        if (!empty($settings['element']) && !empty($settings['multiple'])) {
          $element = array(
            '#theme' => 'bdp_tags',
            '#tag' => $settings['element'],
          ) + $results[$field['settings']['target_type']];
        }
        else {
          foreach ($results[$field['settings']['target_type']] as $delta => $result) {
            if (!empty($settings['element'])) {
              $element[$delta] = array(
                '#theme' => 'bdp_tag',
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

    case 'name_bdp_individualName':
      foreach ($items as $delta => $item) {
        $name = array(
          'cntper' => $item['given'].' '.$item['family'],
        );
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array('cntperp' => $name),
        );
      }
      break;

    case 'name_bdp_publisherName':
      foreach ($items as $delta => $item) {
        $name =  $item['given'].' '.$item['family'];
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array('publish' => $name),
        );
      }
      break;

    case 'addressfield_bdp_address':
      foreach ($items as $delta => $item) {
        $address = array();
        $address['addrtype']='Physical Address';
        if (!empty($item['thoroughfare'])) {
          $address['address'] = $item['thoroughfare'];
        }
        if (!empty($item['locality'])) {
          $address['city'] = $item['locality'];
        }
        if (!empty($item['administrative_area'])) {
          $address['state'] = $item['administrative_area'];
        }
        if (!empty($item['postal_code'])) {
          $address['postal'] = $item['postal_code'];
        }
        if (!empty($item['country'])) {
          $address['country'] = $item['country'];
        }
        // if all address-related elements, dont print an <address> group
        if (!empty($address)) {
           $element[$delta] = array(
             '#theme' => 'bdp_elements',
             '#bdp' => array('cntaddr' => $address),
           );
        }
      }
      break;
    case 'addressfield_bdp_pubplace':
      foreach ($items as $delta => $item) {
        $address = array();
        if (!empty($item['locality'])) {
          $address['pubplace'] = $item['locality'];
        }
        if (!empty($item['administrative_area'])) {
          $address['pubplace'] .= ' '. $item['administrative_area'];
        }
        if (!empty($item['country'])) {
          $address['pubplace'] .= $item['country'];
        }
        // if all address-related elements, dont print an <address> group
        if (!empty($address)) {
           $element[$delta] = array(
             '#theme' => 'bdp_elements',
             '#bdp' => array('pubplace' => $address),
           );
        }
      }
      break;

    case 'date_bdp_temporalCoverage':
      $values = array();
      foreach ($items as $item) {
        $display['settings']['format_type'] = 'iso_8601';
        $dates = date_formatter_process('date_default', $entity_type, $entity, $field, $instance, $langcode, $item, $display);
        $granularity = date_granularity($field);
        if ($dates['value']['formatted'] != $dates['value2']['formatted']) {
          $value = array('key' => 'rngdates', 'value' => array(
            'begdate' => _bdp_date_value($dates['value'], $granularity),
            'enddate' => _bdp_date_value($dates['value2'], $granularity),
          ));
        }
        else {
          $value = array('key' => 'sngdate', 'value' => _bdp_date_value($dates['value'], $granularity));
        }
        $values[] = $value;
      }

      if (!empty($values)) {
        $element = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array('timeinfo' => $values),
        );
      }
      break;

    case 'geofield_bdp_boundingCoordinates':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array(
            'westbc' => $item['right'],
            'eastbc' => $item['left'],
            'northbc' => $item['top'],
            'southbc' => $item['bottom'],
          ),
        );
      }
      break;

    case 'telephone_bdp_phone':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array(array(
            'key' => 'cntvoice',
            'value' => $item['value'],
          )),
        );
      }
      break;

    case 'telephone_bdp_fax':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array(array(
            'key' => 'cntfax',
            'value' => $item['value'],
          )),
        );
      }
      break;

    case 'bdp_electronicMailAddress':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array(
            'cntemail' => $item['email'],
          ),
        );
      }
      break;

    case 'bdp_onlineUrl':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => array(
            'onlink' => $field['type'] == 'url' ? $item['value'] : $item['url'],
          ),
        );
      }
      break;

    case 'bdp_text':
      foreach ($items as $delta => $item) {
        $text = _text_sanitize($instance, $langcode, $item, 'value');
        $element[$delta] = array(
          '#theme' => 'bdp_elements',
          '#bdp' => strip_tags($text),
        );
      }
      break;
  }

  return $element;
}

function _bdp_date_value($date, $granularity) {
  $value = array('caldate' => $date['formatted_date']);
  if (!empty($granularity['hour']) || !empty($granularity['minute']) || !empty($granularity['second'])) {
    $value['time'] = $date['formatted_time'] . $date['formatted_timezone'];
  }
  return $value;
}
