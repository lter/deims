<?php

/**
 * @file
 * Administrative page callbacks for the BDP module.
 */

function bdp_settings_form() {

  $form['bdp_data_policies'] = array(
    '#type' => 'textarea',
    '#title' => t('Data policies text'),
    '#default_value' => variable_get('bdp_data_policies', ''),
  );

  return system_settings_form($form);
}
