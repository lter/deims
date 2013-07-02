<?php

/**
 * @file
 * Administrative page callbacks for the EML module.
 */

function eml_settings_form() {
  $form['station_acronym'] = array(
    '#type' => 'textfield',
    '#title' => t('Station acronym'),
    '#default_value' => variable_get('station_acronym', 'STATION'),
    '#required' => TRUE,
    '#size' => 10,
    '#maxlength' => 20,
  );
  $form['eml_package_id_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Package ID pattern'),
    '#description' => t('This field supports tokens.'),
    '#default_value' => variable_get('eml_package_id_pattern', 'knb-lter-[site:station-acronym].[node:field_data_set_id].[node:field_eml_revision_id]'),
    '#required' => TRUE,
    '#element_validate' => array('token_element_validate'),
    '#token_types' => array('node'),
    '#attributes' => array('style' => 'width: 100%;'),
  );
  $form['eml_data_policies'] = array(
    '#type' => 'textarea',
    '#title' => t('Data policies text'),
    '#default_value' => variable_get('eml_data_policies', ''),
    '#required' => TRUE,
  );

  $form['tokens'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node'),
    '#dialog' => TRUE,
  );

  $form['pasta'] = array(
    '#type' => 'fieldset',
    '#title' => t('PASTA API'),
  );

  $form['pasta']['eml_pasta_user'] = array(
    '#type' => 'textfield',
    '#title' => t('PASTA API user'),
    '#description' => t('This field supports tokens.'),
    '#default_value' => variable_get('eml_pasta_user', 'uid=[site:station-acronym],o=LTER,dc=ecoinformatics,dc=org:password'),
    '#required' => TRUE,
    '#element_validate' => array('token_element_validate'),
    '#attributes' => array('style' => 'width: 100%;'),
  );
  $form['pasta']['eml_paste_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('PASTA API URL'),
    '#default_value' => variable_get('eml_pasta_base_url', 'https://pasta.lternet.edu'),
  );
  $form['pasta']['tokens'] = array(
    '#theme' => 'token_tree',
    '#dialog' => TRUE,
  );

  return system_settings_form($form);
}
