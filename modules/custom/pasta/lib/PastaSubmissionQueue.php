<?php

class PastaSubmissionQueue extends SystemQueue {
  public static function get($name = 'PastaSubmissionQueue') {
    return new PastaSubmissionQueue($name);
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
      if ($node = node_load($data['nid'])) {
        $dataset = new EmlDataSet($node);
        $pasta = new PastaApi($dataset);
        // First we need to make sure we've performed the submission request and
        // have gotten back a valid transaction ID.
        if (empty($data['transaction'])) {
          if ($transaction = $pasta->submitEml()) {
            $data['transaction'] = $transaction;
          }
          static::get()->createItem($data);
          // At this point we are unsure if the EML is valid or not, so update
          // the field to reflect that.
          $dataset->setEmlValidationStatus(NULL);
        }
        else {
          // Fetch the evaluation report from the API.
          $transaction = $data['transaction'];
          $url = PastaApi::getApiUrl("error/eml/{$transaction}");
          $request = drupal_http_request($url, array('timeout' => 10));

          // The report API on success returns a 200 response with the report XML
          // in the response body.
          if ($request->code == 200 && !empty($request->data)) {
            // EML was not valid if there were errors.
            $dataset->setEmlValidationStatus(FALSE);
            watchdog('pasta', $request->data);
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
            // No errors were found, so assumed that this EML is valid.
            $dataset->setEmlValidationStatus(TRUE);
            // Fetch the (possibly) new DOI.
            if ($doi = $pasta->fetchDOI()) {
              $dataset->saveDOI($doi);
            }
          }
        }
      }
    }
    catch (Exception $e) {
      watchdog_exception('pasta', $e);
      static::get()->createItem($data);
    }
  }
}
