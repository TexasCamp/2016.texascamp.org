<?php
/**
 * @file
 * Contains eventBriteAccessCodes.
 *
 * This class contains all of the API calls for accessCodes
 */

class eventBriteAccessCodes {

  private $accessCodeID;
  private $eventID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($accessCodeID = NULL, $eventID = NULL, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($accessCodeID)) {
      $this->accessCodeID = $accessCodeID;
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

  public function accessCodeList($forceNoCache, $dataOverride = '') {
    if (!$this->eventID) {
      drupal_set_message(t('You haven\'t picked an event!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('event_list_access_codes', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('eventID' => $this->eventID);
    return $result->processJSONRequest();
  }

  public function accessCodeNew($accessParams, $dataOverride = '') {
    if (!$accessParams['event_id']) {
      drupal_set_message(t('You haven\'t picked an event!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('access_code_new', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $accessParams;
    return $result->processJSONRequest();
  }

  public function accessCodeUpdate($accessParams, $dataOverride = '') {
    if (!$this->accessCodeID) {
      drupal_set_message(t('You haven\'t picked an access code.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('access_code_update', 'update', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $accessParams['id'] = $this->accessCodeID;
    $result->params = $accessParams;
    return $result->processJSONRequest();
  }

}
