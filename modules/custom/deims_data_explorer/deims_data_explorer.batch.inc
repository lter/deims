<?php

function _fetch_row_batch($options,&$context) {
  // Set up our batch configuration information.
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $options['total_rows'];
  }

  // Get the batched rows.
  $from = $options['limit'] * $context['sandbox']['progress'];
  $rows = deims_data_explorer_get_rows($options['connection'],$options['columns'],$options['filters'],$options['limit'],$options['from']);

  // Write out the CSV
  $fp = fopen(drupal_realpath($options['file']->uri), 'a'));
  foreach ($rows as $row) {
    fputcsv($fp, $row);
  }
  fclose($fp);

  $context['sandbox']['progress'] = $from;
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    $context['sandbox']['progress']++;
  } else {
    $context['results'][] = $options['file'];
  }
}

function _show_download_link($success, $results, $operations) {
  dpm(date('H:i:s'), 'time');
  dpm($results, 'results');
}
