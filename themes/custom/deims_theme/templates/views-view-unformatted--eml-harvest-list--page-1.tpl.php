<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

 drupal_add_http_header("Content-Type", "application/xml; charset=utf-8");
 $baseurl = $GLOBALS['base_url'];
 $xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";  
 $xml .= "<hrv:harvestList xmlns:hrv=\"eml://ecoinformatics.org/harvestList\">\n";
 foreach ($rows as $row){
   $xml .=  $row;
 }
 $xml .= "</hrv:harvestList>\n";
 print $xml;
 exit;

?>


