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


/**
 * Implements hook_field_widget_form_alter().
 *
 * Make some visiual tweaks to the inline entity form and it's subforms.
 */
function deims_admin_field_widget_form_alter(&$element, &$form_state, $context) {
  if ($context['instance']['widget']['module'] == 'inline_entity_form') {
    $info = entity_get_info($element['entities']['#entity_type']);

    // If there is ony one bundle available to use, change the wording in the
    // buttons to be more helpful and reference that bundle only, rather than
    // the entity type.
    if (!empty($element['actions']['bundle']['#value']) && $element['actions']['bundle']['#type'] == 'value') {
      $bundle = drupal_strtolower($info['bundles'][$element['actions']['bundle']['#value']]['label']);
      $bundle_lowercase = drupal_strtolower($bundle);
      if (isset($element['actions']['ief_add']['#value'])) {
        $element['actions']['ief_add']['#value'] = t('Add @bundle', array('@bundle' => $bundle_lowercase));
      }
      if (isset($element['actions']['ief_add_existing']['#value'])) {
        $element['actions']['ief_add_existing']['#value'] = t('Use existing @bundle', array('@bundle' => $bundle_lowercase));
      }
    }

    $state = $form_state['inline_entity_form'][$element['#ief_id']];
    if (!empty($element['form'])) {
      $bundle = $info['bundles'][$state['form settings']['bundle']]['label'];
      $bundle_lowercase = drupal_strtolower($bundle);
      if ($state['form'] == 'add') {
        // For empty IEF widgets, don't lose the field title and description
        // when using the add form, by forcing the widget to still use a
        // fieldset rather than a container.
        if (empty($state['entitites'])) {
          $element['#type'] = 'fieldset';
        }

        $element['form']['#title'] = t('Add @bundle', array('@bundle' => $bundle_lowercase));
        $element['form']['actions']['ief_add_save']['#value'] = t('Save @bundle', array('@bundle' => $bundle_lowercase));
      }
      elseif ($state['form'] == 'ief_add_existing') {
        // For empty IEF widgets, don't lose the field title and description
        // when using the add form, by forcing the widget to still use a
        // fieldset rather than a container.
        if (empty($state['entitites'])) {
          $element['#type'] = 'fieldset';
        }

        $element['form']['#title'] = t('Use existing @bundle', array('@bundle' => $bundle_lowercase));
        $element['form']['entity_id']['#title'] = t('Select an existing @bundle', array('@bundle' => $bundle_lowercase));
        $element['form']['actions']['ief_reference_save']['#value'] = t('Select @bundle', array('@bundle' => $bundle_lowercase));
      }
      elseif ($element['form']['#op'] == 'clone') {
        $element['form']['#title'] = t('Clone @bundle', array('@bundle' => $bundle_lowercase));
        $element['form']['actions']['ief_clone_save']['#value'] = t('Save @bundle', array('@bundle' => $bundle_lowercase));
      }
    }

    if (!empty($state['entities'])) {
      foreach ($state['entities'] as $delta => $entity_state) {
        if ($entity_state['form'] == 'edit') {
          $bundle = $info['bundles'][$element['entities'][$delta]['form']['#bundle']]['label'];
          $bundle_lowercase = drupal_strtolower($bundle);
          $element['entities'][$delta]['form']['actions']['ief_edit_save']['#value'] = t('Save @bundle', array('@bundle' => $bundle_lowercase));
        }
      }
    }

    // Add support for the field help text.
    if (!empty($context['instance']['description'])) {
      $element['#description'] = field_filter_xss($context['instance']['description']);
    }
    else {
      $element['#description'] = '';
    }

    // Only re-add the cardinality description if you can add more than one
    // value, and this isn't an unlimited-value field.
    if ($context['field']['cardinality'] != FIELD_CARDINALITY_UNLIMITED && $context['field']['cardinality'] > 1) {
      if (!empty($element['#description'])) {
        $element['#description'] .= ' ';
      }
      $element['#description'] = t('You have added @entities_count out of @cardinality_count allowed.', array(
        '@entities_count' => count($state['entities']),
        '@cardinality_count' => $context['field']['cardinality'],
      ));
    }
  }
}
