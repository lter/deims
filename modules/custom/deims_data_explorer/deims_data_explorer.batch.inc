<?php
/**
 * @file
 * Contains Data Explorer batch operations.
 */

/**
 * Batch process description for _fetch_row_batch.
 *
 * @param array $options 
 *   Array of options passed by the init.
 * @param array $context 
 *   Context passed back to the function.
 */

function _fetch_row_batch($query, $file, $columns, &$context) {
  // Set up our batch configuration information.
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $query->countQuery()->execute()->fetchField();
  }

  // May be set to DEIMS_BATCH_LIMIT) perhaps.
  $query->range($context['sandbox']['progress'], 5); 
  $result = $query->execute();

  // Write out the CSV.
  $fhp = fopen(drupal_realpath($file->uri), 'a');

  // Add the header row if we're on our first pass.
  if ($context['sandbox']['progress'] == 0 && !empty($columns)) {
    fputcsv($fhp, $columns);
  }

  while ($row = $result->fetchAssoc()) {
    fputcsv($fhp, $row);
    $context['sandbox']['progress']++;
  }
  fclose($fhp);

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

/**
 * Description for _process_file_for_download.
 *
 * @param object $file
 *   The file object that is being acted upon.
 * @param string $table
 *   The name of the table that was queried.
 * @param array $context
 *   Context passed back to function.
 */
function _process_file_for_download($file, $table, $nid, &$context) {
  // Setting status = 0 marks the file as temporary which means it'll get
  // cleaned up automatically within 6 hours by Drupal.

  // Do we need to compress the file?
  if (($file->filesize / DRUPAL_KILOBYTE) > (DRUPAL_KILOBYTE * DEIMS_COMPRESSION_THRESHOLD)) {
    $uncompressed = $file;
    $file = file_save_data('');
    $fhp = gzopen(drupal_realpath($file->uri), 'w9');
    gzwrite($fhp, file_get_contents(drupal_realpath($uncompressed->uri)));
    gzclose($fhp);
    file_delete($uncompressed);

    // Re-save the file to compute size.
    $file->status = 0;
    $file = file_move($file, file_create_filename($table . '_csv.gz', variable_get('deims_data_explorer_dir', 'public://data-downloads/')));
  }
  else {
    $file->status = 0;
    file_save($file);
  }
  $context['results']['file'] = $file;
  $context['results']['nid'] = $nid;
}

/**
 * Description for _show_download_link.
 * @param  boolean $success
 *   True when succeeded.
 * @param  object $results
 *   Results of data query file packaging.
 * @param  array $operations
 *   Operations related to the download packaging process.
 */
function _show_download_link($success, $results, $operations) {
  $batch = &batch_get();

  if ($success) {
    $path = "node/{$results['nid']}/data/download/{$results['file']->fid}";
    $batch['redirect'] = array(
      $path,
      array(
        'query' => array(
          'token' => drupal_get_token($path),
        ),
      ),
    );
  }
  else {
    $message = 'There was an error processing your request. Please try again and '
      . l('contact us', '/contact') . ' if you have repeated errors.';
    drupal_set_message($message);
    $batch['redirect'] = 'node/' . $results['nid'] . '/data';
  }

}
