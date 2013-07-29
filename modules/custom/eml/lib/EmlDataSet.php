<?php

/**
 * @file
 * Contains EmlDataSet.
 */

/**
 * Utility and API functions for interacting with data sets and their EML.
 */
class EmlDataSet {

  private $node;

  protected $eml = NULL;

  public function __construct($node) {
    if ($node->type != 'data_set') {
      throw new Exception('Cannot create a EmlDataSet object using a node type != data_set.');
    }

    $this->node = $node;
  }

  public static function getInstance($node) {
    $instances = &drupal_static('EmlDataSet_instances', array());
    if ($node->type != 'data_set') {
      throw new InvalidArgumentException('Cannot create a EmlDataSet object using a node type != data_set.');
    }
    if (empty($node->nid)) {
      return new self($node);
    }
    elseif (!isset($instances[$node->nid])) {
      $instances[$node->nid] = new self($node);
    }

    return $instances[$node->nid];
  }

  public static function getApiUrl($path, array $options = array()) {
    $base_url = variable_get('eml_pasta_base_url', 'https://pasta.lternet.edu');
    return url($base_url . '/' . $path, $options);
  }

  /**
   * Render a data set into its EML.
   *
   * @return string
   *   A string containing the data set's EML/XML.
   */
  public function getEML($reset = FALSE) {
    if (empty($this->eml) || $reset) {
      $build = node_view($this->node, 'eml');
      $this->eml = render($build);
      $this->eml = $this->tidyXml($this->eml);
    }
    return $this->eml;
  }

  /**
   * Cleanup XML output using the Tidy library
   *
   * @param string $xml
   *   A string containing XML.
   *
   * @return string
   *   The XML after being repaired with Tidy.
   */
  private function tidyXml($xml) {
    if (extension_loaded('tidy')) {
      $config = array(
        'indent' => TRUE,
        'input-xml' => TRUE,
        'output-xml' => TRUE,
        'wrap' => FALSE,
      );
      $tidy = new tidy();
      return $tidy->repairString($xml, $config);
    }
    else {
      // If the Tidy library isn't found, then we can pretty much duplicate
      // the whitespace and indentation cleanup using the PHP DOM library.

      // Need to convert encoded spaces to character encoding.
      $xml = str_replace('&nbsp;', '&#160;', $xml);

      $dom = new DOMDocument();
      $dom->preserveWhiteSpace = FALSE;
      $dom->loadXML($xml);
      $xpath = new DOMXPath($dom);
      foreach ($xpath->query('//text()') as $domNode) {
        $domNode->data = trim($domNode->nodeValue);
      }
      $dom->formatOutput = TRUE;
      return $dom->saveXML($dom->documentElement, LIBXML_NOEMPTYTAG);
    }
  }

  /**
   * Get the package ID of the data set.
   *
   * @return string
   *   The package ID of the data set in the format of
   *   scope.identifier.revision.
   */
  public function getPackageID() {
    $pattern = variable_get('eml_package_id_pattern', 'knb-lter-[site:station-acronym].[node:field_data_set_id].[node:field_eml_revision_id]');
    return drupal_strtolower(token_replace($pattern, array('node' => $this->node), array('clear' => TRUE, 'callback' => 'eml_cleanup_package_id_tokens')));
  }

  public function getPackageIDParts() {
    $package_id = $this->getPackageID();
    return explode('.', $package_id, 3);
  }

  public function getEMLHash() {
    return FieldHelper::getValue('node', $this->node, 'field_eml_hash', 'value');
  }

  public function setEMLHash($hash) {
    $this->node->field_eml_hash[LANGUAGE_NONE][0]['value'] = $hash;
  }

  public function calculateEMLHash() {
    $eml = $this->getEML();

    // Remove the package ID (which contains the revision) from the EML so that
    // we can truly compare it against the previous version.
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

  /**
   * Detect if any of the EML output changed since it was generated last.
   */
  public function detectEmlChanges($check_unpublished = TRUE) {
    if ($check_unpublished && $this->node->status != NODE_PUBLISHED) {
      eml_debug("Skipping detectEmlChanges() since node @nid is not published.", array('@nid' => $this->node->nid));
      return FALSE;
    }

    $old_hash = $this->getEMLHash();
    $current_hash = $this->calculateEMLHash();

    if ($current_hash != $old_hash) {
      // Get the current/old package ID so that we can change it in the EML
      // string after the revision ID has been incremented.
      $original_package_id = $this->getPackageID();

      // Increment the revision ID and set the new hash.
      $this->incrementEMLRevisionID();
      $this->setEMLHash($current_hash);
      EntityHelper::updateFieldValues('node', $this->node);

      // Only trigger a watchdog message if the node isn't new. In cases of
      // migrations this would flood the message log with unnecessary noise.
      if (empty($this->node->is_new)) {
        watchdog(
          'eml',
          'EML data set change detected. Updated EML revision ID and hash for !title.',
          array('!title' => $this->node->title),
          WATCHDOG_INFO,
          l(t('View data set'), 'node/' . $this->node->nid) . ' | ' . l(t('View EML'), 'node/' . $this->node->nid . '/eml')
        );
      }

      // Update the EML output if neccessary.
      // @todo Should this code move to incrementEMLRevisionID or setEMLRevisionID?
      if (!empty($this->eml)) {
        $this->eml = str_replace($original_package_id, $this->getPackageID(), $this->eml);
      }

      // Allow other modules to respond to the changed EML.
      module_invoke_all('eml_changed', $this);

      // Enqueue the data set to be submitted to PASTA.
      EmlSubmissionQueue::get()->enqueue($this->node);

      eml_debug("Changes detected in data set @nid.", array('@nid' => $this->node->nid));
      return TRUE;
    }
    else {
      eml_debug("No changes detected in data set @nid.", array('@nid' => $this->node->nid));
      return FALSE;
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
    list($scope, $identifier, $revision) = $this->getPackageIDParts();

    $url = static::getApiUrl("package/doi/eml/{$scope}/{$identifier}/{$revision}");
    $request = drupal_http_request($url, array('timeout' => 10));

    if (empty($request->error) && $request->code == 200 && !empty($request->data)) {
      if (preg_match('/doi:([\d.]+\/pasta\/[a-e0-9]+)/', $request->data, $matches)) {
        return $matches[1];
      }
      else {
        throw new Exception(t('DOI request to @url returned expected result %doi.', array('@url' => $url, '%doi' => $request->data)));
      }
    }
    elseif (!empty($request->error)) {
      throw new Exception(t('Unable to fetch EML DOI from @url: @error.', array('@url' => $url, '@error' => $request->error)));
    }
    else {
      throw new Exception(t('Unable to fetch EML DOI from @url.'));
    }
  }

  public static function addApiAuthentication(array &$options) {
    $auth = token_replace(variable_get('eml_pasta_user', 'uid=[site:station-acronym],o=LTER,dc=ecoinformatics,dc=org'));
    $options['headers']['Authorization'] = 'Basic ' . base64_encode($auth);
  }

  public function submitEml() {
    $url = static::getApiUrl("package/eml");
    $options = array(
      'method' => 'POST',
      'data' => $this->getEML(),
      'headers' => array(
        'Content-Type' => 'application/xml',
      ),
    );
    static::addApiAuthentication($options);
    $request = drupal_http_request($url, $options);
    dpm($request);

    // The API call to /package/eml returns a 202 on success with a transaction
    // ID which is used to fetch the actual evalution report from
    // /error/eml/{transaction}.
    if ($request->code == 202 && !empty($request->data)) {
      return $request->data;
    }
    elseif (!empty($request->error)) {
      throw new Exception(t('Unable to submit EML to @url: @error.', array('@url' => $url, '@error' => $request->error)));
    }
    else {
      throw new Exception(t('Unable to submit EML to @url.'));
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
    $url = static::getApiUrl('package/evaluate/eml');
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
    $url = static::getApiUrl("package/evaluate/report/eml/{$transaction}");
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
    $nids = FieldHelper::getValues('node', $this->node, 'field_data_sources', 'target_id');
    $sources = node_load_multiple($nids);

    $custom_units = array();
    foreach ($sources as $source) {
      if ($items = field_get_items('node', $source, 'field_variables')) {
        foreach ($items as $item) {
          if ($item['type'] == DEIMS_VARIABLE_TYPE_PHYSICAL && !LterUnitHelper::isUnitStandard($item['data']['unit'])) {
            $custom_units[] = $item['data']['unit'];
          }
        }
      }
    }

    $custom_units = array_unique($custom_units);
    if (!empty($custom_units) && $stmml = LterUnitStmmlHelper::getUnitsStmml($custom_units)) {
      return array(
        '#theme' => NULL,
        '#markup' => $stmml,
      );
    }
  }
}
