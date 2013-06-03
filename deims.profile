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
    );
  }

  return $info;
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
