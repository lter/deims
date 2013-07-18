<?php

/**
 * @file
 * Page callbacks for the DEIMS Variable Field Search module.
 */

function deims_variable_search_autocomplete($field_name, $entity_type) {
  $term = $_GET['term'];
  $limit = 10;
  $matches = array();
  $field = field_info_field($field_name);
  $table = _field_sql_storage_tablename($field);
  $id_column = db_escape_field(_field_sql_storage_columnname($field_name, 'id'));

  // Build matching conditions
  $query = db_select('search_index', 'i', array('target' => 'slave'))->extend('SearchQuery')->extend('PagerDefault');
  $query->join($table, 'v', 'v.' . $id_column . ' = i.sid');
  $query->condition('v.deleted', 0);
  $query->condition('v.language', array(LANGUAGE_NONE, $GLOBALS['language']->language), 'IN');
  $query->searchExpression($term, $field_name);

  // Only continue if the first pass query matches.
  if ($query->executeFirstPass()) {
    $results = $query->limit($limit)->execute()->fetchAllAssoc('sid');
    $matches = array_keys($results);
  }

  //if (empty($matches) || count($matches) < $limit) {
  //  $query = db_select($table, 'v');
  //  $query->addField('v', $id_column);
  //  if (!empty($matches)) {
  //    $query->condition($id_column, $matches, 'NOT IN');
  //  }
  //  $or = db_or();
  //  $or->condition(_field_sql_storage_columnname($field_name, 'label'), '%' . db_like($term) . '%', 'LIKE');
  //  $or->condition(_field_sql_storage_columnname($field_name, 'name'), '%' . db_like($term) . '%', 'LIKE');
  //  $or->condition(_field_sql_storage_columnname($field_name, 'definition'), '%' . db_like($term) . '%', 'LIKE');
  //  $query->condition($or);
  //  $results = $query->execute()->fetchCol();
  //  $matches = array_merge($matches, $results);
  //}

  // Load and output results.
  $items = deims_variable_load_multiple($field_name, $matches);
  array_walk($items, '_deims_variable_search_prepare_summary');
  drupal_json_output(array_values($items));
}

function _deims_variable_search_prepare_summary(&$item) {
  $summary = check_plain($item['name']);
  if ($item['name'] != $item['label']) {
    $summary .= ' (' . check_plain($item['label']) . ')';
  }
  $summary .= ' - ' . deims_variable_type_label($item['type']);
  switch ($item['type']) {
    case DEIMS_VARIABLE_TYPE_NOMINAL:
      break;
    case DEIMS_VARIABLE_TYPE_PHYSICAL:
      $summary .= ' (' . check_plain($item['data']['unit']) . ')';
      break;
    case DEIMS_VARIABLE_TYPE_DATE:
      $summary .= ' (' . check_plain($item['data']['pattern']) . ')';
      break;
    case DEIMS_VARIABLE_TYPE_CODES:
      //$item['data']['codes'] = list_allowed_values_string($item['data']['codes']);
      $summary .= ' (' . implode(', ', array_slice(array_keys($item['data']['codes']), 0, 3));
      if (count($item['data']['codes']) > 3) {
        $summary .= ', ...';
      }
      $summary .= ')';
      $item['data']['codes_text'] = list_allowed_values_string($item['data']['codes']);
      break;
  }
  $item['missing_values_text'] = list_allowed_values_string($item['missing_values']);
  if (!empty($item['definition'])) {
    $summary .= ' - ' . truncate_utf8($item['definition'], 48, TRUE, TRUE);
  }
  $item['summary'] = $summary;
}
