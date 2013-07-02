<?php

/**
 * @file
 * Contains LterUnitHelper.
 */

class LterUnitHelper {

  /**
   * Definte the default unit scope for requests to the service. 2 = EML-2.1.0.
   */
  const UNIT_SCOPE = 2;

  /**
   * Fetch an array of all EML standard units.
   */
  public static function getUnits() {
    $units = &drupal_static(__FUNCTION__);

    if (!isset($units)) {
      $cid = 'units:scope=2';
      if ($cache = cache_get($cid, 'cache_lter_unit')) {
        $units = $cache->data;
      }
      else {
        $units = array();
        $url = 'http://unit.lternet.edu/services/unitregistry/unit/(scopeId=' . static::UNIT_SCOPE . ')';
        $request = drupal_http_request($url, array('headers' => array('Accept' => 'application/json')));
        if (empty($request->error) && $request->code == 200 && !empty($request->data)) {
          if ($data = json_decode($request->data)) {
            foreach ($data as $entity) {
              $unit = array(
                'singular' => $entity->name,
                'plural' => $entity->name,
                'symbol' => $entity->abbreviation,
                'kind' => $entity->quantity->name,
                'source' => $url,
              );
              if (!empty($entity->deprecatedTo)) {
                $unit['deprecated'] = $entity->deprecatedTo->name;
              }
              $units[$entity->name] = $unit;
            }
          }
          else {
            trigger_error('Error parsing JSON data from ' . $url);
          }
        }
        cache_set($cid, $units, 'cache_lter_unit');
      }
    }

    return $units;
  }

  /**
   * Generate a list of options from lter_unit_get_units() for a select list.
   */
  public static function getUnitOptions($category_minimum = 0) {
    $results = &drupal_static(__FUNCTION__);

    if (!isset($results)) {
      $cid = 'unit-options:' . $GLOBALS['language']->language;
      if ($cache = cache_get($cid, 'cache_lter_unit')) {
        $results = $cache->data;
      }
      else {
        $results = array();
        $units = static::getUnits();
        foreach ($units as $unit) {
          $label = t($unit['singular']);
          if (!empty($unit['symbol']) && $unit['singular'] != $unit['symbol']) {
            $label .= ' (' . $unit['symbol'] . ')';
          }
          if (!empty($unit['kind'])) {
            $category = t($unit['kind']);
            if (!isset($results[$category])) {
              $results[$category] = array();
            }
            $results[$category][$unit['singular']] = $label;
          }
          else {
            $results[$unit['singular']] = $label;
          }
        }

        cache_set($cid, $results, 'cache_lter_unit');
      }
    }

    $return = $results;
    foreach ($return as $category => $option) {
      if (is_array($option)) {
        // Flatten categories if neccessary.
        if (!$category_minimum || count($option) < $category_minimum) {
          unset($return[$category]);
          $return += $option;
        }
        else {
          ksort($return[$category]);
        }
      }
    }

    ksort($return);
    return $return;
  }

  public static function isUnitStandard($unit) {
    $units = static::getUnits();
    return !empty($units[$unit]);
  }
}
