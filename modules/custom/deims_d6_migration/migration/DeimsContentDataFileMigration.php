<?php

/**
 * @file
 * Definition of DeimsContentDataFileMigration.
 */

class DeimsContentDataFileMigration extends DrupalNode6Migration {
  protected $dependencies = array('DeimsFile', 'DeimsContentResearchSite');

  public function __construct(array $arguments) {
    $arguments += array(
      'description' => '',
      'source_connection' => 'drupal6',
      'source_version' => 6,
      'source_type' => 'data_file',
      'destination_type' => 'data_source',
      'user_migration' => 'DeimsUser',
    );

    parent::__construct($arguments);

    // This content type does not have a body field.
    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
    $this->addUnmigratedSources(array('body', 'teaser', 'format'));

    $this->addFieldMapping('field_data_source_file', 'field_data_file')
      ->sourceMigration('DeimsFile');
    $this->addFieldMapping('field_data_source_file:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_data_source_file:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_methods', 'field_methods');
    $this->addFieldMapping('field_methods:format', 'field_methods:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_instrumentation', 'field_instrumentation');
    $this->addFieldMapping('field_instrumentation:format', 'field_instrumentation:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_quality_assurance', 'field_quality');
    $this->addFieldMapping('field_quality_assurance:format', 'field_quality:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('field_related_sites', 'field_datafile_site_ref')
      ->sourceMigration('DeimsContentResearchSite');
    $this->addFieldMapping('field_variables')
      ->description('Handled in prepare().');
    $this->addFieldMapping('field_description', 'field_datafile_description');
    $this->addFieldMapping('field_csv_header_lines', 'field_num_header_line');
    $this->addFieldMapping('field_csv_footer_lines', 'field_num_footer_lines');
    $this->addFieldMapping('field_csv_orientation', 'field_orientation');
    $this->addFieldMapping('field_csv_quote_character', 'field_quote_character');
    $this->addFieldMapping('field_csv_field_delimiter', 'field_delimiter');
    $this->addFieldMapping('field_csv_record_delimiter', 'field_record_delimiter');
    $this->addFieldMapping('field_date_range', 'field_beg_end_date');
    $this->addFieldMapping('field_date_range:to', 'field_beg_end_date:value2');

    $this->addUnmigratedSources(array(
      'field_datafile_variable_ref', // Handled in prepare()
      'field_data_file_data_set', // Handled in DeimsContentDataSet
    ));

    $this->addUnmigratedDestinations(array(
      'field_data_source_file:language',
      'field_data_source_file:destination_dir',
      'field_data_source_file:destination_file',
      'field_data_source_file:file_replace',
      'field_data_source_file:source_dir',
      'field_data_source_file:urlencode',
      'field_data_source_file:description',
      'field_data_source_file:display',
      'field_methods:language',
      'field_instrumentation:language',
      'field_quality_assurance:language',
      'field_variables:name',
      'field_variables:type',
      'field_variables:definition',
      'field_variables:data',
      'field_variables:missing_values',
      'field_description:format',
      'field_description:language',
      'field_csv_quote_character:language',
      'field_csv_field_delimiter:language',
      'field_csv_record_delimiter:language',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
  }

  public function prepare($node, $row) {
    // Fetch and prepare the variables field.
    $node->field_variables[LANGUAGE_NONE] = $this->getVariables($node, $row);

    // Remove any empty or illegal delta field values.
    EntityHelper::removeInvalidFieldDeltas('node', $node);
    EntityHelper::removeEmptyFieldValues('node', $node);

    // Perform field validation and check for debugging information.
    if (empty($node->field_variables[LANGUAGE_NONE])) {
      $this->saveMessage('Empty variable field in data file node.', MigrationBase::MESSAGE_INFORMATIONAL);
    }
  }

  /**
   * Convert code definition strings from a 'key = value' format to 'key|value'.
   */
  protected function getKeyValueFromString($code) {
    // Convert code definitions from '=' to '|' as the key/value separator
    $parts = explode('=', $code, 2);
    // Remove any surrounding whitespace from the key or value.
    array_walk($parts, 'trim');
    return count($parts) == 2 ? $parts : $parts + array(0 => '', 1 => '');
  }

  public function getVariables($node, $row) {
    // We already have the array of referenced variable nodes in this row variable.
    // First filter out any NULL or empty values before proceeding.
    $variable_nids = array_filter($row->field_datafile_variable_ref);
    if (empty($variable_nids)) {
      return array();
    }

    $field_values = array();

    $connection = Database::getConnection('default', $this->sourceConnection);
    $query = $connection->select('node', 'n');
    $query->fields('n', array('title'));
    $query->condition('n.nid', $variable_nids, 'IN');
    $query->innerJoin('content_type_variable', 'ctv', 'n.vid = ctv.vid');
    $query->fields('ctv');
    $variables = $query->execute()->fetchAllAssoc('nid');

    // Collect the VID values for the variable nodes, so that we can fetch
    // their multiple field values.
    $vids = array();
    foreach ($variables as $variable) {
      $vids[] = $variable->vid;
    }

    // Next get the variables' code definitions.
    $code_values = array();
    if (!empty($variables)) {
      $query = $connection->select('content_field_code_definition', 'c');
      $query->fields('c', array('nid', 'field_code_definition_value'));
      $query->condition('vid', $vids, 'IN');
      $query->isNotNull('field_code_definition_value');
      $query->orderBy('nid');
      $query->orderBy('delta');
      $results = $query->execute()->fetchAll();
      foreach ($results as $result) {
        list($key, $value) = $this->getKeyValueFromString($result->field_code_definition_value);
        $code_values[$result->nid][$key] = $value;
      }
    }

    // Next get the variables' missing values.
    $missing_values = array();
    if (!empty($variables)) {
      $query = $connection->select('content_field_var_missingvalues', 'c');
      $query->fields('c', array('nid', 'field_var_missingvalues_value'));
      $query->condition('vid', $vids, 'IN');
      $query->isNotNull('field_var_missingvalues_value');
      $query->orderBy('nid');
      $query->orderBy('delta');
      $results = $query->execute()->fetchAll();
      foreach ($results as $result) {
        list($key, $value) = $this->getKeyValueFromString($result->field_var_missingvalues_value);
        $missing_values[$result->nid][$key] = $value;
      }
    }

    // Rather than looping through $variables, we need to loop using
    // $variable_nids, which has preserved the actual order of the variables.
    foreach ($variable_nids as $nid) {
      if (!isset($variables[$nid])) {
        throw new Exception('Unable to load variable node ' . $nid);
      }
      $variable = $variables[$nid];

      $value = array();

      // The label value is not required, but node title is.
      $value['name'] = isset($variable->field_attribute_label_value) ? $variable->field_attribute_label_value : $variable->title;
      $value['label'] = $variable->title;
      $value['definition'] = $variable->field_var_definition_value;
      $value['data'] = array();
      if (!empty($variable->field_attribute_unit_value)) {
        $value['type'] = DEIMS_VARIABLE_TYPE_PHYSICAL;
        $value['data']['unit'] = $variable->field_attribute_unit_value;
        $value['data']['minimum'] = $variable->field_attribute_minimum_value;
        $value['data']['maximum'] = $variable->field_attribute_maximum_value;
        $value['data']['precision'] = $variable->field_attribute_precision_value;
      }
      elseif (!empty($variable->field_attribute_formatstring_value)) {
        $value['type'] = DEIMS_VARIABLE_TYPE_DATE;
        $value['data']['pattern'] = $variable->field_attribute_formatstring_value;
      }
      elseif (!empty($code_values[$variable->nid])) {
        $value['type'] = DEIMS_VARIABLE_TYPE_CODES;
        $value['data']['codes'] = $code_values[$variable->nid];
      }
      else {
        $value['type'] = DEIMS_VARIABLE_TYPE_NOMINAL;
      }
      $value['missing_values'] = isset($missing_values[$variable->nid]) ? $missing_values[$variable->nid] : array();
      $field_values[] = $value;
    }

    return $field_values;
  }
}
