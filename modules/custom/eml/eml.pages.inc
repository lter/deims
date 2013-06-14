<?php

/**
 * @file
 * Page callbacks for the EML module.
 */

/**
 * Output a node as EML.
 *
 * Sets the content header for xml, renders the eml, and returns nothing in
 * order to not have render actions take place on the eml.
 * When nothing is returned from a page callback Drupal will not render anything
 * and still call the rest of the proper hooks including necessary exit hooks.
 * For a similar usage example see:
 * @see http://api.drupal.org/api/drupal/modules%21node%21node.module/function/node_feed/7
 */
function eml_output_node($node) {
  if ($node->type != 'data_set') {
    return MENU_NOT_FOUND;
  }

  try {
    // Get the EML as a string and output it.
    $dataset = new EMLDataSet($node);
    $eml = $dataset->getEML();
    drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
    print $eml;
  }
  catch (Exception $exception) {
    watchdog_exception('eml', $exception);
    return MENU_NOT_FOUND;
  }
}
