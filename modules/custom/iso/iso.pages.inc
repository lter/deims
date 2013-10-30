<?php

/**
 * @file
 * Page callbacks for the ISO module.
 */

/**
 * Output a node as ISO.
 *
 * Sets the content header for xml, renders the iso, and returns nothing in
 * order to not have render actions take place on the iso.
 * When nothing is returned from a page callback Drupal will not render anything
 * and still call the rest of the proper hooks including necessary exit hooks.
 * For a similar usage example see:
 * @see http://api.drupal.org/api/drupal/modules%21node%21node.module/function/node_feed/7
 */
function iso_output_node($node) {
  if ($node->type != 'data_set') {
    return MENU_NOT_FOUND;
  }

  try {
    // Get the ISO as a string and output it.
    $dataset = new IsoDataSet($node);
    $iso = $dataset->getISO();
    drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
    print $iso;
  }
  catch (Exception $exception) {
    watchdog_exception('iso', $exception);
    return MENU_NOT_FOUND;
  }
}
