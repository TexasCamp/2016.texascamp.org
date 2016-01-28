<?php
/**
 * @file
 * Contains eventBriteUser.
 *
 * This class contains all of the API calls for users
 */

class eventBriteUser {

  private $userID;
  private $email;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($userID = NULL, $email = NULL, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($userID)) {
      $this->userID = $userID;
    }
    if (!empty($email)) {
      $this->email = $email;
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

  /**
   * Function userListEvents.
   *
   * Get a list of events for the currently authenticated user. You can pass in
   * new app_key and user_key values to override the defaults provided here if
   * you want to list private events for the user you pass in
   *
   * @param  array   $userParams   [description]
   * @param  boolean $forceNoCache [description]
   *
   * @return object
   *   either an array from the JSON output or a SimpleXML Object
   */
  public function userListEvents($userParams = array(), $forceNoCache = FALSE, $dataOverride = '') {

    $result = new eventBriteCommon('user_list_events',
      'get',
      $dataOverride,
      $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    // $userParams['user'] = $this->email;
    // $result->params = $userParams;
    return $result->processJSONRequest();
  }

  public function userListTickets($type = 'public', $dataOverride = '', $forceNoCache = FALSE) {

    $result = new eventBriteCommon(
      'user_list_tickets',
      'get',
      $dataOverride,
      $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('type' => $type);
    return $result->processJSONRequest();
  }

  public function userListVenues($forceNoCache = FALSE, $dataOverride = '') {
    $result = new eventBriteCommon('user_list_venues',
      'get',
      $dataOverride,
      $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    return $result->processJSONRequest();
  }

  public function userListOrganizers($forceNoCache = FALSE, $dataOverride = '') {
    $result = new eventBriteCommon(
      'user_list_organizers',
      'get',
      $dataOverride,
      $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    return $result->processJSONRequest();
  }

  public function userGet($forceNoCache = FALSE, $dataOverride = '', $userKey = NULL) {
    if (!$this->userID && !$this->email) {
      drupal_set_message(t('You haven\'t picked a user!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('user_get', 'get', $dataOverride, $forceNoCache, $userKey);
    $result->params = array(
      'user_id' => $this->userID,
      'email' => $this->email
    );
    return $result->processJSONRequest();
  }

  public function userGetMaster($forceNoCache = FALSE, $dataOverride = '', $userKey = NULL) {
    $result = new eventBriteCommon('user_get', 'get', $dataOverride, $forceNoCache, $userKey);
    $result->params = array(
      'user_id' => $this->userID,
      'email' => $this->email
    );
    return $result->processJSONRequest();
  }

  public function userGetMasterV3($forceNoCache = FALSE, $dataOverride = 'https://www.eventbriteapi.com/v3/users/', $userKey = NULL) {
    $result = new eventBriteCommon('me', 'get', $dataOverride, $forceNoCache, $userKey, NULL, $this->accessToken);
    return $result->processJSONRequest(TRUE);
  }

  public function userNew($password, $dataOverride = '') {
    if (!$this->email) {
      drupal_set_message(t('You must enter an email address!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('user_new', 'create', $dataOverride, TRUE);
    $result->params = array(
      'password' => $password,
      'email' => $this->email
    );
    return $result->processJSONRequest();
  }

  public function userUpdate($dataOverride = '', $password) {
    if (!$this->email) {
      drupal_set_message(t('You haven\'t picked a user!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('user_update',
      'update',
      $dataOverride,
      TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array(
      'password' => $password,
      'email' => $this->email
    );
    return $result->processJSONRequest();
  }

}
