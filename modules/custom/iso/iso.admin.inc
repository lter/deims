<?php

/**
 * @file
 * Administrative page callbacks for the ISO module.
 */

function iso_settings_form() {

  $form['iso_data_policies'] = array(
    '#type' => 'textarea',
    '#title' => t('Data policies text'),
    '#default_value' => variable_get('iso_data_policies', ''),
  );

  return system_settings_form($form);
}
