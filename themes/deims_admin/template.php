<?php

/**
 * @file
 * Process theme data.
 *
 * Use this file to run your theme specific implimentations of theme functions,
 * such preprocess, process, alters, and theme function overrides.
 */

/**
 * Override the date combo theme to remove the fieldset
 */
function deims_admin_date_combo($variables) {
  return theme('form_element', $variables);
}

/**
 * Implements hook_preprocess_views_exposed_form().
 *
 * Stuff an empty label above buttons so they line up if another widget in the
 * same row also has a label.
 */
function deims_admin_preprocess_views_exposed_form(&$vars) {
  $wrap_button = false;

  foreach ($vars['widgets'] as $widget) {
    if (!is_null($widget->label)) { $wrap_button = true; }
  }

  if ($wrap_button) {
    $button = $vars['button'];
    $vars['button'] = '<label>&nbsp;</label>'
      . '<div>' . $button . '</div>';
  }
}

/**
 * Implements hook_views_bulk_operations_form_alter().
 *
 * Tweaks the appearance of the VBO selector.
 */
function deims_admin_views_bulk_operations_form_alter(&$form, &$form_state, $vbo) {
  if ($form_state['step'] == 'views_form_views_form') {
    $form['select']['#title'] = '';
    $form['select']['#collapsible'] = FALSE;
    $form['select']['submit']['#value'] = t('Apply');
    $form['select']['operation']['#options'][0] = t('Bulk operations');
    $form['select']['#weight'] = 49;
  }
}
