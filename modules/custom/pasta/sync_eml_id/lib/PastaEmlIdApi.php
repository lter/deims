<?php

class PastaEmlIdApi {
  protected $dataSet;

  public function __construct(EmlDataSet $dataSet) {
    $this->dataSet = $dataSet;
  }

  public function getDataSet() {
    return $this->dataSet();
  }

  public static function getApiUrl($path, array $options = array()) {
    $base_url = variable_get('eml_pasta_base_url', 'https://pasta.lternet.edu');
    return url($base_url . '/' . $path, $options);
  }

  /**
   * Fetch a data set's Eml revision ID (data object version) from the LTER PASTA Data Manager API.
   *
   * @return int
   *   An integer from the PASTA API.
   *
   * @throws Exception
   * @ingroup eml_data_manager_api
   */
  public function fetchEMLID() {
    list($scope, $identifier, $revision) = $this->dataSet->getPackageIDParts();

    $url = static::getApiUrl("package/eml/{$scope}/{$identifier}?filter=newest");
    $request = drupal_http_request($url, array('timeout' => 10));

    if (empty($request->error) && $request->code == 200 && !empty($request->data)) {
        return $request->data;
    }
    elseif (!empty($request->error)) {
      throw new Exception(t('Unable to fetch EML ID from @url: @error.', array('@url' => $url, '@error' => $request->error)));
    }
    else {
      throw new Exception(t('Unable to fetch EML Revision ID from @url.'));
    }
  }
}
