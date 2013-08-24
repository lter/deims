<?php

class EmlSubmissionQueue extends SystemQueue {
  public static function get($name = 'EmlSubmissionQueue') {
    return new EmlSubmissionQueue('EmlSubmissionQueue');
  }

  public function enqueue($node) {
    $data = array(
      'nid' => $node->nid,
      'created' => REQUEST_TIME,
      'attempts' => 0,
      'last_attempt' => 0,
    );
    $this->createItem($data);
  }

  public static function processData(&$data) {
    try {
      $node = node_load($data['nid']);
      // First we need to make sure we've performed the submission request and
      // have gotten back a valid transaction ID.
      if (empty($data['transaction'])) {
        $dataset = new EmlDataSet($node);
        if ($transaction = $dataset->submitEml()) {
          $data['transaction'] = $transaction;
        }
        static::get()->createItem($data);
      }
      else {
        // Fetch the evaluation report from the API.
        $transaction = $data['transaction'];
        $url = EmlDataSet::getApiUrl("error/eml/{$transaction}");
        $request = drupal_http_request($url, array('timeout' => 10));

        // The report API on success returns a 200 response with the report XML
        // in the response body.
        if ($request->code == 200 && !empty($request->data)) {
          watchdog('eml', $request->data);
          // Do not requeue.
        }
        elseif ($request->code == 401) {
          // A 401 respose means the report is not found, or is still being
          // generated. Requeue.
          $data['attempts']++;
          $data['last_attempt'] = time();
          static::get()->createItem($data);
        }
        elseif ($request->code == 404) {
          // No errors were found. Do not requeue.
          eml_action_dataset_update_doi($node);
        }
      }
    }
    catch (Exception $e) {
      watchdog_exception('eml', $e);
      static::get()->createItem($data);
    }
  }
}
