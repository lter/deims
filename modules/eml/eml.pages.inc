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

  drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
  $build = node_view($node, 'eml');
  $output = render($build);

  // Cleanup the XML output using the Tidy library.
  if (extension_loaded('tidy')) {
    $config = array(
      'indent' => TRUE,
      'input-xml' => TRUE,
      'output-xml' => TRUE,
      'wrap' => FALSE,
    );
    $tidy = new tidy();
    $output = $tidy->repairString($output, $config);
  }
  print $output;

  // @todo Convert to use the helper function.
  //$dataset = new EMLDataSet($node);
  //print $dataset->getEML();

  drupal_page_footer();
}
