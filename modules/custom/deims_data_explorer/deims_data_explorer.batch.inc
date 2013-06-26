<?php

/**
 * _fetch_row_batch description
 * @param  array $options Array of options passed by the init.
 * @param  array $context Context passed back to the function.
 */
function _fetch_row_batch($options,&$context) {
  // Set up our batch configuration information.
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $options['total_rows'];
  }

  // Get the batched rows.
  $rows = deims_data_explorer_get_rows($options['connection'],$options['columns'],$options['filters'],$options['limit'],$context['sandbox']['progress']);

  // Write out the CSV.
  $fp = fopen(drupal_realpath($options['file']->uri), 'a');
  foreach ($rows as $row) {
    fputcsv($fp, $row);
    $context['sandbox']['progress']++;
  }
  fclose($fp);

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

/**
 * _process_file_for_download description
 * @param  object $file    The file object that is being acted upon.
 * @param  string $table   The name of the table that was queried.
 * @param  array  $context Context passed back to function.
 */
function _process_file_for_download($file,$table,&$context) {
  // Setting status = 0 marks the file as temporary which means it'll get
  // cleaned up automatically within 6 hours by Drupal.
  $file->status = 0;
  $file = file_move($file, file_create_filename($table . '.csv', 'public://'));

  // Do we need to compress the file?
  if (($file->filesize / DRUPAL_KILOBYTE) > (DRUPAL_KILOBYTE * DEIMS_COMPRESSION_THRESHOLD)) {
    $uncompressed = $file;
    $file = file_save_data('');
    $fp = gzopen(drupal_realpath($file->uri), 'w9');
    gzwrite($fp, file_get_contents(drupal_realpath($uncompressed->uri)));
    gzclose($fp);
    file_delete($uncompressed);

    // Re-save the file to compute size.
    $file->status = 0;
    $file = file_move($file, file_create_filename($table . '_csv.gz', 'public://'));
  }
  $context['results']['file'] = $file;
}

/**
 * _show_download_link
 * @param  [type] $success    [description]
 * @param  [type] $results    [description]
 * @param  [type] $operations [description]
 * @return [type]             [description]
 */
function _show_download_link($success, $results, $operations) {

  if ($success) {
    $uri = file_entity_download_uri($results['file']);
    $message = 'Your data set has been processed. You can download the file by '
      . l('clicking here', $uri['path'], $uri['options']) . '.';
  }
  else {
    $message = 'There was an error processing your request. Please try again and '
      . l('contact us', '/contact') . ' if you have repeated errors.';
  }

  drupal_set_message($message, 'status', FALSE);
}
