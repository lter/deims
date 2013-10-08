<?php

/**
 * @file
 * Contains EmlHarvestList
 */

/**
 * Utility and API functions for interacting with data sets and their EML.
 */
class EmlHarvestList {

  private $node;

  public function __construct($node) {
    if ($node->type != 'data_set') {
      throw new Exception('Cannot create a EmlHLDataSet object using a node type != data_set.');
    }

    $this->node = $node;
  }

  public function getNode() {
    return $this->node;
  }

  public static function getInstance($node) {
    $instances = &drupal_static('EmlHarvestList_instances', array());
    if ($node->type != 'data_set') {
      throw new InvalidArgumentException('Cannot create a EmlHarvestList object using a node type != data_set.');
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
   * Render a data set into its EML Harvest list form.
   *
   * @return string
   *   A string containing the data set's EML harvest list format.
   */
  public function getEMLHL($reset = FALSE) {
    if (empty($this->eml_hl) || $reset) {
      $build = node_view($this->node, 'eml_hl');
      $this->eml_hl = render($build);
      $this->eml_hl = $this->tidyXml($this->eml_hl);
    }
    return $this->eml_hl;
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

}
