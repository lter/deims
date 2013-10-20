<?php

/**
 * @file
 * Page callbacks for the BDP module.
 */

/**
 * Output a node as BDP.
 *
 * Sets the content header for xml, renders the bdp, and returns nothing in
 * order to not have render actions take place on the bdp.
 * When nothing is returned from a page callback Drupal will not render anything
 * and still call the rest of the proper hooks including necessary exit hooks.
 * For a similar usage example see:
 * @see http://api.drupal.org/api/drupal/modules%21node%21node.module/function/node_feed/7
 */
function bdp_output_node($node) {
  if ($node->type != 'data_set') {
    return MENU_NOT_FOUND;
  }

  try {
    // Get the BDP as a string and output it.
    $dataset = new BdpDataSet($node);
    $bdp = $dataset->getBDP();
    drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
    print $bdp;
  }
  catch (Exception $exception) {
    watchdog_exception('bdp', $exception);
    return MENU_NOT_FOUND;
  }
}
