<?php

/**
 * @file
 * Enables modules and site configuration for a DEIMS site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function deims_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_element_info_alter().
 */
function deims_element_info_alter(&$info) {
  // Merge in some defaults to select or other elements.
  if (isset($info['select_or_other'])) {
    $info['select_or_other'] += array(
      '#other_unknown_defaults' => 'other',
      '#other_delimiter' => FALSE,
    );
  }
}

/**
 * Implements hook_entity_info().
 */
function deims_entity_info() {
  $info = array();

  // Expose the biblio_contributors_data table as an entity base table so that
  // we can make entity references to biblio authors.
  if (module_exists('biblio')) {
    $info['biblio_contributor'] = array(
      'label' => t('Biblio authors'),
      'base table' => 'biblio_contributor_data',
      'entity keys' => array(
        'id' => 'cid',
        'label' => 'name',
      ),
      'view modes' => array(
        'full' => array(
          'label' => t('Full content'),
          'custom settings' => TRUE,
        )
      )

    );
  }

  return $info;
}

function deims_calulate_maximum_timestamp($entity_type, $entity) {
  $references = _deims_gather_entity_references($entity_type, $entity);

  $timestamps = _deims_gather_entity_properties($entity_type, array($entity), 'changed');

  foreach ($references as $type => $type_ids) {
    $entities = entity_load($type, $type_ids);
    $timestamps = array_merge($timestamps, _deims_gather_entity_properties($type, $entities, 'changed'));
  }

  return max($timestamps);
}

function deims_calulate_sum_revision_ids($entity_type, $entity) {
  $references = _deims_gather_entity_references($entity_type, $entity);

  $revision_ids = _deims_gather_entity_properties($entity_type, array($entity), 'revision');

  foreach ($references as $type => $type_ids) {
    $entities = entity_load($type, $type_ids);
    $revision_ids = array_merge($revision_ids, _deims_gather_entity_properties($type, $entities, 'revision'));
  }

  return array_sum($revision_ids);
}

function _deims_gather_entity_references($entity_type, $entity, $found_references = array()) {
  list($entity_id, , $bundle) = entity_extract_ids($entity_type, $entity);

  // @todo Ensure that recursion protection works.
  if (isset($found_references[$entity_type]) && in_array($entity_id, $found_references[$entity_type])) {
    //return array();
  }

  $references = array();
  //$references[$entity_type][$entity_id] = $entity_id;

  $instances = field_info_instances($entity_type, $bundle);
  foreach ($instances as $instance) {
    if (!empty($entity->{$instance['field_name']}) && $items = field_get_items($entity_type, $entity, $instance['field_name'])) {
      $field = field_info_field($instance['field_name']);
      switch ($field['type']) {
        case 'entityreference':
          $ids = array();
          foreach ($items as $item) {
            if (!empty($item['target_id'])) {
              $ids[$item['target_id']] = $item['target_id'];
            }
          }
          $references += array($field['settings']['target_type'] => array());
          $references[$field['settings']['target_type']] += $ids;
          break;
      }
    }
  }

  if (!empty($references)) {
    foreach (array_keys($references) as $reference_type) {
      $entities = entity_load($reference_type, $references[$reference_type]);
      foreach ($entities as $id => $referenced_entity) {
        if ($reference_type != $entity_type && $id != $entity_id) {
          $references = drupal_array_merge_deep($references, _deims_gather_entity_references($reference_type, $referenced_entity, $references));
        }
      }
    }
  }

  return $references;
}

function _deims_gather_entity_properties($entity_type, array $entities, $key) {
  $timestamps = array();

  $entity_key = $key;
  $info = entity_get_info($entity_type);
  if (isset($info['entity keys'][$key])) {
    $entity_key = $info['entity keys'][$key];
  }

  foreach ($entities as $entity) {
    if (isset($entity->$entity_key) && is_scalar($entity->$entity_key)) {
      $timestamps[] = $entity->$entity_key;
    }
  }

  return $timestamps;
}

/**
 * Implements hook_preprocess_HOOK().
 *
 * Fix ECK entities to not display a title if they do not have title properies.
 */
function deims_preprocess_entity(&$variables) {
  $entity_type = $variables['elements']['#entity_type'];
  $info = entity_get_info($entity_type);
  if (strpos($info['base table'], 'eck') !== FALSE && empty($info['entity keys']['label'])) {
    $variables['page'] = TRUE;
  }
}

/**
 * Implements hook_field_widget_form_alter().
 */
function deims_field_widget_form_alter(&$element, &$form_state, $context) {
  // @todo Remove when elements module can provide a widget for fields.
  if ($context['field']['type'] == 'email' && $context['instance']['widget']['type'] == 'email_textfield') {
    $element['email']['#type'] = 'emailfield';
  }
  if ($context['field']['type'] == 'number_integer' && $context['instance']['widget']['type'] == 'number') {
    $element['value']['#type'] = 'numberfield';
    if (drupal_strlen($context['instance']['settings']['min'])) {
      $element['value']['#min'] = $context['instance']['settings']['min'];
    }
    if (drupal_strlen($context['instance']['settings']['max'])) {
      $element['value']['#max'] = $context['instance']['settings']['max'];
    }
  }
}
