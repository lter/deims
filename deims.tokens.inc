<?php

/**
 * Implements hook_token_info().
 */
function deims_token_info() {
  $info['tokens']['node']['maximum-timestamp'] = array(
    'name' => t('Maximum timestamp'),
    'description' => '',
    'type' => 'date',
  );
  $info['tokens']['node']['revision-sum'] = array(
    'name' => t('Timestamp sum'),
    'description' => '',
  );
  $info['tokens']['node']['source-data-set'] = array(
    'name' => t('Data set that references this data source'),
    'description' => '',
    'type' => 'node',
  );

  $info['tokens']['site']['station-acronym'] = array(
    'name' => t('Station acronym'),
    'description' => '',
  );


  return $info;
}

/**
 * Implements hook_tokens().
 */
function deims_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $langcode = !empty($options['lanuage']) ? $options['language']->language : NULL;
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Simple key values on the node.
        case 'maximum-timestamp':
          $timestamp = deims_calulate_maximum_timestamp('node', $node);
          $replacements[$original] = format_date($timestamp, 'medium', '', NULL, $langcode);
          break;

        case 'revision-sum':
          $replacements[$original] = deims_calulate_sum_revision_ids('node', $node);
          break;

        case 'source-data-set':
          if ($node->type == 'data_source' && $data_set = _deims_data_source_get_data_set($node)) {
            $label = entity_label('node', $data_set);
            $replacements[$original] = $sanitize ? check_plain($label) : $label;
          }
          break;
      }
    }

    if ($max_timestamp_tokens = token_find_with_prefix($tokens, 'maximum-timestamp')) {
      $timestamp = deims_calulate_maximum_timestamp('node', $node);
      $replacements += token_generate('date', $max_timestamp_tokens, array('date' => $timestamp), $options);
    }
    if ($source_data_set_tokens = token_find_with_prefix($tokens, 'source-data-set')) {
      if ($node->type == 'data_source' && $data_set = _deims_data_source_get_data_set($node)) {
        $replacements += token_generate('node', $source_data_set_tokens, array('node' => $data_set), $options);
      }
    }
  }

  if ($type == 'site') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'station-acronym':
          $acronym = variable_get('station_acronym', 'STATION');
          $replacements[$original] = $sanitize ? check_plain($acronym) : $acronym;
          break;
      }
    }
  }

  return $replacements;
}

function entity_get_back_references($entity_type, $entity, $field_name) {

}

function _deims_data_source_get_data_set($node) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'data_set');
  $query->fieldCondition('field_data_sources', 'target_id', $node->nid);
  $results = $query->execute();
  if (!empty($results['node'])) {
    $data_set_id = reset($results['node'])->nid;
    return node_load($data_set_id);
  }
}
