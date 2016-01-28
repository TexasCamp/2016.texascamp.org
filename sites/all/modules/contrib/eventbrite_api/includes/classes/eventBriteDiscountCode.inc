<?php
/**
 * @file
 * Contains eventBriteDiscountCodes.
 *
 * This class contains all of the API calls for discountCodes
 */

class eventBriteDiscountCodes {

  private $discountCodeID;
  private $eventID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($discountCodeID = NULL, $eventID = NULL, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($discountCodeID)) {
      $this->discountCodeID = $discountCodeID;
    }
    if (!empty($eventID)) {
      $this->eventID = $eventID;
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

  public function discountCodeList($forceNoCache, $dataOverride = '') {
    if (!$this->eventID) {
      drupal_set_message(t('You haven\'t picked an event!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('event_list_discounts', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('event_id' => $this->eventID);
    return $result->processJSONRequest();
  }

  public function discountCodeNew($discountParams, $dataOverride = '') {
    if (!$discountParams['event_id']) {
      drupal_set_message(t('You haven\'t picked an event!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('discount_new', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $discountParams;
    return $result->processJSONRequest();
  }

  public function discountCodeUpdate($discountParams, $dataOverride = '') {
    if (!$this->discountCodeID) {
      drupal_set_message(t('You haven\'t picked a discount.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('discount_update', 'update', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $discountParams['id'] = $this->discountCodeID;
    $result->params = $discountParams;
    return $result->processJSONRequest();
  }

}
