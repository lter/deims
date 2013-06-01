<?php

class EmlDataSet {

  private $node;

  public function __construct($node) {
    if ($node->type != 'data_set') {
      throw new Exception('Cannot create a EmlDataSet object using a node type != data_set.');
    }

    $this->node = $node;
  }

  /**
   * Render a data set into its EML.
   *
   * @return string
   *   A string containing the data set's EML/XML.
   */
  public function getEML() {
    $build = node_view($this->node, 'eml');
    $output = render($build);

    // Cleanup the XML output using the Tidy library.
    $config = array(
      'indent' => TRUE,
      'input-xml' => TRUE,
      'output-xml' => TRUE,
      'wrap' => FALSE,
    );
    $tidy = new tidy();
    $output = $tidy->repairString($output, $config);

    return $output;
  }

  /**
   * Calculate the package ID of the data set.
   *
   * @return string
   *   The package ID of the data set in the format of scope.identifier.revision.
   */
  public function getPackageID() {
    $pattern = variable_get('eml_package_id_pattern', 'knb-lter-[site:station-acronym].[node:field_data_set_id].[node:field_eml_revision_id]');
    return drupal_strtolower(token_replace($pattern, array('node' => $this->node), array('clear' => TRUE, 'callback' => 'eml_cleanup_package_id_tokens')));
  }

  public function getEMLHash() {
    return FieldHelper::getValue('node', $this->node, 'field_eml_hash', 'value');
  }

  public function setEMLHash($hash) {
    $this->node->field_eml_hash[LANGUAGE_NONE][0]['value'] = $hash;
  }

  public function calculateEMLHash($eml = NULL) {
    if (!isset($eml)) {
      $eml = $this->getEML();
    }

    // Remove the revision number from the EML so that we can 'truly' compare it.
    $eml = str_replace($this->getPackageID(), '', $eml);

    return hash('md5', $eml);
  }

  public function getEMLRevisionID() {
    return FieldHelper::getValue('node', $this->node, 'field_eml_revision_id', 'value');
  }

  public function setEMLRevisionID($id) {
    $this->node->field_eml_revision_id[LANGUAGE_NONE][0]['value'] = $id;
  }

  public function incrementEMLRevisionID() {
    $revision_id = $this->getEMLRevisionID();
    if (!empty($revision_id)) {
      $revision_id++;
    }
    else {
      $revision_id = 1;
    }
    $this->setEMLRevisionID($revision_id);
  }

  public function checkIfChanged($eml = NULL) {
    $current_hash = $this->calculateEMLHash($eml);
    $old_hash = $this->getEMLHash();

    if ($current_hash != $old_hash) {
      $original = clone $this->node;

      // Increment the revision ID and set the new hash.
      $this->incrementEMLRevisionID();
      $this->setEMLHash($current_hash);
      EntityHelper::updateFieldValues('node', $this->node);

      watchdog(
        'eml',
        'EML data set change detected. Updated EML revision ID and hash for !title.',
        array('!title' => $this->node->title),
        WATCHDOG_INFO,
        l(t('View data set'), 'node/' . $this->node->nid) . ' | ' . l(t('View EML'), 'node/' . $this->node->nid . '/eml')
      );
    }
  }

  /**
   * Fetch a data set's DOI (data object ID) from the LTER Data Manager API.
   *
   * @return string
   *   A DOI string from the PASTA API.
   *
   * @throws Exception
   * @ingroup eml_data_manager_api
   */
  public function fetchDOI() {
    $package_id = $this->getPackageID();

    // @todo Remove after testing.
    $package_id = 'knb-lter-sev.107.313449';

    if (!eml_dataset_is_valid_package_id($package_id)) {
      throw new Exception(t("Data set node @nid has an invalid package ID: @packagei.", array('@nid' => $this->node->nid, '@packageid' => $package_id)));
    }

    list($scope, $identifier, $revision) = explode('.', $package_id);

    $url = "https://pasta.lternet.edu/package/doi/eml/{$scope}/{$identifier}/{$revision}";
    $request = drupal_http_request($url, array('timeout' => 10));

    if (empty($request->error) && $request->code == 200 && !empty($request->data)) {
      if (preg_match('/doi:([\d.]+\/pasta\/[a-e0-9]+)/', $request->data, $matches)) {
        return $matches[1];
      }
      else {
        throw new Exception(t('DOI request to @url returned expected result %doi.', array('@url' => $url, '%doi' => $request->data)));
      }
    }
    elseif (!empty($response->error)) {
      throw new Exception(t('Unable to fetch EML DOI from @url: @error.', array('@url' => $url, '@error' => $response->error)));
    }
    else {
      throw new Exception(t('Unable to fetch EML DOI from @url.'));
    }
  }

  /**
   * Fetch an EML validation report transaction from the LTER Data Manager API.
   *
   * To evaluate an data set and its EML for validation:
   * - Upload the EML to https://pasta.lternet.edu/package/evaluate/eml
   * - The response from the API request should return a 202 HTTP status code
   *   on success, with the report transaction in the response body.
   * - The Data Package Manager API takes the EML and queues a report to be
   *   generated, which evaluates many different factors of the EML, including
   *   downloading the data files in the EML.
   * - Once the report has been finished, it can be fetched using
   *   EmlDataSet::fetchValidationReport().
   *
   * @throws Exception
   * @see EmlDataSet::fetchValidationReport()
   * @ingroup eml_data_manager_api
   */
  public function fetchValidationReportTransaction() {
    // First we need to send the EML to the evaluation API.
    $url = "https://pasta.lternet.edu/package/evaluate/eml";
    $options = array(
      'method' => 'POST',
      'data' => $this->getEML(),
      'headers' => array(
        'Content-Type' => 'application/xml',
      ),
      'timeout' => 30,
    );
    $response = drupal_http_request($url, $options);

    // The API call to /evaluate/eml returns a 202 on success with a transaction
    // ID which is used to fetch the actual evalution report from
    // /evaluate/report/eml/{transaction}.
    if ($response->code == 202 && !empty($response->data)) {
      return $response->data;
    }
    elseif (!empty($response->error)) {
      throw new Exception(t('Unable to fetch EML validation report transaction from @url: @error.', array('@url' => $url, '@error' => $response->error)));
    }
    else {
      throw new Exception(t('Unable to fetch EML validation report transaction from @url.'));
    }
  }

  /**
   * Fetch an EML validation report from the LTER Data Manager API.
   *
   *
   * @throws Exception
   * @see EmlDataSet::fetchValidationReportTransaction()
   * @ingroup eml_data_manager_api
   */
  public static function fetchValidationReport($transaction) {
    // Fetch the evaluation report from the API.
    $transaction = $request->data;
    $url = "https://pasta.lternet.edu/package/evaluate/report/eml/{$transaction}";
    $request = drupal_http_request($url, array('timeout' => 10));

    // The report API on success returns a 200 response with the report XML
    // in the response body.
    if ($request->code == 200 && !empty($request->data)) {
      return static::parseEvaluationSummary($request->data);
    }
    elseif ($request->code == 401) {
      // A 401 respose means the report is not found, or is still being
      // generated.
      return array();
    }

    // Do not return anything if we could not fetch validity. We need to be able
    // to distinguish between valid (TRUE), invalid (FALSE), and unknown (NULL).
  }

  /**
   * Parse an EML evalution report into a summary.
   *
   * @param string $report_xml
   *   An EML evalution report XML in string form.
   *
   * @return array
   *   An array of the summary of the report, keyed by the strings 'valid',
   *   'info', 'warn', and 'error', and the values being the number of checks
   *   that were info valid, information, warnings, or errors, repsectively.
   */
  public static function parseEvaluationSummary($xml) {
    $results = array_fill_keys(array('valid', 'info', 'warn', 'error'), 0);
    $report = simplexml_load_string($xml);
    foreach ($report->datasetReport->qualityCheck as $check) {
      $results[(string) $check->status]++;
    }
    foreach ($report->entityReport->qualityCheck as $check) {
      $results[(string) $check->status]++;
    }
    return $results;
  }

  public function getCustomUnitMetadata() {
    $nids = array();
    if ($items = field_get_items('node', $this->node, 'field_data_sources')) {
      foreach ($items as $item) {
        if (!empty($item['target_id'])) {
          $nids[] = $item['target_id'];
        }
      }
    }
    $sources = node_load_multiple($nids);

    $custom_units = array();
    foreach ($sources as $source) {
      if ($items = field_get_items('node', $source, 'field_variables')) {
        foreach ($items as $item) {
          if ($item['type'] == DEIMS_VARIABLE_TYPE_PHYSICAL && !lter_unit_is_unit_standard($item['data']['unit'])) {
            $custom_units[] = $item['data']['unit'];
          }
        }
      }
    }

    $custom_units = array_unique($custom_units);
    if (!empty($custom_units) && $stmml = lter_unit_get_units_stmml($custom_units)) {
      return array(
        '#theme' => NULL,
        '#markup' => $stmml,
      );
    }
  }
}
