<?php

/**
 * @file
 * Contains LterUnitStmmlHelper.
 */

class LterUnitStmmlHelper {

  /**
   * Fetch the STMML XML of a custom unit.
   *
   * @param string $unit
   *   The name of the unit.
   *
   * @param bool $use_cache
   *
   * @return DOMElement
   *   A DOMElement of the <stmml:unit> tag for the unit.
   *
   * @todo Sean document this process.
   * @see http://www.w3schools.com/dom/dom_element.asp
   * @see http://www.php.net/manual/en/domxpath.query.php
   * @see http://www.php.net/manual/en/class.domdocument.php
   *
   *
   */
  public static function getUnitStmml($unit, $use_cache = FALSE) {
    $stmml = NULL;
    $dom = new DOMDocument();

    try {
      // Fetch the STMML data from the Unit API.
      $url = 'http://unit.lternet.edu/services/unitformat/stmml/unit/(name=' . $unit . ')';
      $options = array();
      $options['headers']['Accept'] = 'text/xml';
      $options['timeout'] = 10;
      $options['cache']['cid'] = 'stmml:' . $unit;
      $options['cache']['bin'] = 'cache_lter_unit';
      $request = CacheHelper::httpRequest($url, $options);

      if (empty($request->error) && !empty($request->data) && strpos($request->data, $unit) !== FALSE) {
        // Load and parse the STMML for modification.
        $dom->loadXML($request->data);
        $xpath = new DOMXpath($dom);

        // Inspect all the child elements of stmml:unitList
        foreach ($xpath->query('/stmml:unitList/node()') as $node) {

          // Skip any elements that are not actually stmml:unit.
          if ($node->tagName != 'stmml:unit') {
            continue;
          }

          if ($node->getAttribute('id') == $unit) {
            // We found the first stmml:unit element with an ID value that
            // matches our unit name. Store this DOMElement as the result and
            // skip to the end of the function.
            $stmml = $node;
            break;
          }
        }
      }
    }
    catch (Exception $e) {
      // Do nothing. Always fall through to default stmml:unit creation.
    }

    // If the unit was not found in the results, create a default stmml:unit
    // DOMElement required for EML validation.
    if (!isset($stmml)) {
      $stmml = $dom->createElementNS('http://www.xml-cml.org/schema/stmml-1.1', 'stmml:unit');
      $stmml->setAttribute('id', $unit);
      $description = $dom->createElement('stmml:description');
      $stmml->appendChild($description);
    }

    return $stmml;
  }

  /**
   * Return the STMML output for an array of units.
   *
   * @param array $units
   *   An array of unit names.
   *
   * @return string
   *   The raw XML of the <stmml:unitList> containing the unit defintions.
   */
  public static function getUnitsStmml(array $units) {
    $dom = new DOMDocument();
    $unitList = $dom->createElementNS('http://www.xml-cml.org/schema/stmml-1.1', 'stmml:unitList');
    $unitList->setAttribute('xmlns:sch', 'http://www.ascc.net/xml/schematron');
    $unitList->setAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
    $unitList->setAttribute('xmlns', 'http://www.xml-cml.org/schema/stmml');
    $unitList->setAttribute('xsi:schemaLocation', 'http://www.xml-cml.org/schema/stmml-1.1 http://nis.lternet.edu/schemas/EML/eml-2.1.0/stmml.xsd');

    foreach ($units as $unit) {
      $result = static::getUnitStmml($unit);
      // Because the unit STMML is generated seperately than the DOM being
      // generated here, it has to be 'imported' into the DOM here in order to
      // be appended.
      $node = $dom->importNode($result, TRUE);
      $unitList->appendChild($node);
    }

    return $dom->saveXML($unitList, LIBXML_NOXMLDECL);
  }
}
