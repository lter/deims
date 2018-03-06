<?php

/**
 * @file
 * Contains EmlDataSet.
 */

/**
 * Utility and API functions for interacting with data sets and their EML.
 * Nov 2017 Added utf8 option to tidy statement at line 80, i.e. $tidy->repairString($xml, $config,'utf8') for &nbsp problem.
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

  public function getNode() {
    return $this->node;
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
   * Cleanup XML output using the Tidy library.
   *
   * @param string $xml
   *   A string containing XML.
   *
   * @return string
   *   The XML after being repaired with Tidy.
   *  Added utf8 encoding to the tidy statment
   *  This takes care of the &nbsp; coding.
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
      return $tidy->repairString($xml, $config, 'utf8');
    }
    else {
      // If the Tidy library isn't found, then we can pretty much duplicate
      // the whitespace and indentation cleanup using the PHP DOM library.

      // Need to convert encoded spaces to character encoding. Added additional conversions.
      $xml = preg_replace ('/[^\x{0009}\x{000a}\x{000d}\x{0020}-\x{D7FF}\x{E000}-\x{FFFD}]+/u', ' ', $xml);
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

      eml_debug("Changes detected in data set @nid.", array('@nid' => $this->node->nid));
      return TRUE;
    }
    else {
      eml_debug("No changes detected in data set @nid.", array('@nid' => $this->node->nid));
      return FALSE;
    }
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

  public function setEmlValidationStatus($status = NULL) {
    if (isset($status)) {
      // Boolean $valid here will convert to a 0 or 1 field value on save.
      $this->node->field_eml_valid[LANGUAGE_NONE][0]['value'] = $status ? 'yes' : 'no';
      EntityHelper::updateFieldValues('node', $this->node);
    }
    else {
      // A NULL value means we were unable to fetch validation results. Set
      // the validation field to empty.
      $this->node->field_eml_valid = array();
      EntityHelper::updateFieldValues('node', $this->node);
    }
  }

  public function getDOI() {
    return FieldHelper::getValue('node', $this->node, 'field_doi', 'value');
  }

  public function saveDOI($doi) {
    $this->node->field_doi[LANGUAGE_NONE][0]['value'] = $doi;
    EntityHelper::updateFieldValues('node', $this->node);
    $uri = entity_uri('node', $this->node);
    $link = l(t('View data set'), $uri['path'], $uri['options']);
    watchdog('pasta', 'Updated DOI for %title to @doi.', array('%title' => $this->node->title, '@doi' => $doi), WATCHDOG_INFO, $link);

  }

}
