<?php

class EmlValidationReportQueue extends SystemQueue {
  public static function get($name = 'EmlValidationQueue') {
    return new EmlValidationReportQueue('EmlValidationQueue');
  }

  public function enqueue($node) {
    $dataset = new EmlDataSet($node);
    if ($transaction = $dataset->fetchValidationReportTransaction()) {
      $data = array(
        'nid' => $node->nid,
        'transaction' => $transaction,
        'created' => REQUEST_TIME,
      );
      $this->createItem($data);
    }
  }

  public static function processData($data) {
    $seen_nids = &drupal_static('eml_validation_report_queue_process', array());

    // Ensure that on the same request we don't try to fetch the validation
    // report for the same node more than once.
    if (!empty($seen_nids[$data['nid']])) {
      return;
    }
    else {
      $seen_nids[$data['nid']] = TRUE;
    }

    $data += array('attempts' => 0);
    $time = time();
    $interval = ($time - $data['created']);

    if ($interval > 604800) {
      watchdog('eml', 'Failed to fetch EML validation results for node @nid. Made @attempts attempts in !interval.', array('@nid' => $data['nid'], '@attempts' => $data['attempts'], '!interval' => format_interval($interval)), WATCHDOG_ERROR);
      // drupal_cron_run() takes care of removing this item from the queue now.
      return;
    }

    $report = EmlDataSet::fetchValidationReport($data['transaction']);
    if (empty($report)) {
      // If the report is not yet available, increment the number of recorded
      // attempts, and re-queue the this data set to be checked later.
      $data['attempts']++;
      $data['last_checked'] = $time;
      static::get()->createItem($data);
    }

    // This loads the most recent published revision of the node.
    $node = node_load($data['nid']);
    if (!empty($report)) {
      // Boolean $valid here will convert to a 0 or 1 field value on save.
      $node->field_eml_valid[LANGUAGE_NONE][0]['value'] = empty($report['error']) ? 'yes' : 'no';
      EntityHelper::updateFieldValues('node', $node);
    }
    else {
      // A NULL value means we were unable to fetch validation results. Set
      // the validation field to empty.
      $node->field_eml_valid = array();
      EntityHelper::updateFieldValues('node', $node);
    }
  }
}
