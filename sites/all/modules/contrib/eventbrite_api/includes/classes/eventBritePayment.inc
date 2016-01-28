<?php
/**
 * @file
 * Contains eventBritePayment.
 *
 * This class contains all of the API calls for payments
 */

class eventBritePayment {

  private $paymentID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($paymentID = null, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($paymentID)) {
      $this->paymentID = $paymentID;
    }
    if (!empty($userKey)) {
      $this->userKey = $userKey;
    }
    if (!empty($appKey)) {
      $this->appKey = $appKey;
    }
    if (!empty($accessToken)) {
      $this->accessToken = $accessToken;
    }
  }

  public function paymentUpdate($paymentParams, $dataOverride = '') {
    if (!$this->paymentID) {
      drupal_set_message(t('You haven\'t picked a payment.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('payment_update', 'update', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $ticketParams['id'] = $this->paymentID;
    $result->params = $paymentParams;
    return $result->processJSONRequest();
  }

}
