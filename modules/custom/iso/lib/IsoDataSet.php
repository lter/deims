<?php

/**
 * @file
 * Contains IsoDataSet.
 */

/**
 * Utility and API functions for interacting with data sets and their ISO.
 */
class IsoDataSet {

  private $node;

  protected $iso = NULL;

  public function __construct($node) {
    if ($node->type != 'data_set') {
      throw new Exception('Cannot create a IsoDataSet object using a node type != data_set.');
    }
    $this->node = $node;
  }

  public function getNode() {
    return $this->node;
  }

  public static function getInstance($node) {
    $instances = &drupal_static('IsoDataSet_instances', array());
    if ($node->type != 'data_set') {
      throw new InvalidArgumentException('Cannot create a IsoDataSet object using a node type != data_set.');
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
   * Render a data set into its ISO
   *
   * @return string
   *   A string containing the data set's ISO/XML.
   */
  public function getISO($reset = FALSE) {
    if (empty($this->iso) || $reset) {
      $build = node_view($this->node, 'iso');
      $this->iso = render($build);
      $this->iso = $this->tidyXml($this->iso);
    }
    return $this->iso;
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
