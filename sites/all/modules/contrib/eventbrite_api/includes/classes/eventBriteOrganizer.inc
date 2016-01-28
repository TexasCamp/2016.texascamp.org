<?php
/**
 * @file
 * Contains eventBriteOrganizer.
 *
 * This class contains all of the API calls for organisers
 */

class eventBriteOrganizer {

  private $organiserID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($organiserID = null, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($organiserID)) {
      $this->organiserID = $organiserID;
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

  public static function organizer_create() {
    $organizer = (object) array(
      'oid' => '',
      'acid' => '',
      'name' => '',
      'description' => '',
      'long_description' => '',
      'url' => '',
      'is_new' => TRUE,
    );
    return $organizer;
  }

  public static function organizer_save(&$organizer) {
    return entity_save('organizer', $organizer);
  }

  public static function organizer_delete($entity) {
    entity_delete('organizer', $entity->oid);
    // MAKE THIS DELETE ORGANIZER WITH EVENTBRITE.
  }

  /**
   * Autocomplete results for the event form organizer field.
   */
  public static function _eventbrite_organizer_autocomplete($string) {
    $matches = array();
    // Select the organizers table.
    $query = db_select('eventbrite_api_organizers', 'o');
    // Select rows that match the string.
    $return = $query
      ->fields('o', array('oid', 'name'))
      ->condition('o.name', '%' . db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    // Add matches to $matches .
    foreach ($return as $row) {
      $matches[$row->oid] = check_plain($row->name);
    }
    // Return for JS.
    drupal_json_output($matches);
  }

  public function organiserListEvents($orgParams = array(), $forceNoCache = FALSE, $dataOverride = '') {
    if (!$this->organiserID) {
      drupal_set_message(t('You haven\'t picked an organiser!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('organizer_list_events', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $orgParams['id'] = $this->organiserID;
    $result->params = $orgParams;
    return $result->processJSONRequest();
  }

  public function organisersList($user_id, $forceNoCache = FALSE, $dataOverride = 'https://www.eventbriteapi.com/v3/users/') {
    $result = new eventBriteCommon('organizers', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('id' => $user_id);
    return $result->processJSONRequest(TRUE);
  }

  public function organiserGet($forceNoCache = FALSE, $dataOverride = '') {
    if (!$this->organiserID) {
      drupal_set_message(t('You haven\'t picked an organiser!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('organizer_get', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('id' => $this->organiserID);
    return $result->processJSONRequest();
  }

  public function organiserNew($orgParams, $dataOverride = '') {
    $result = new eventBriteCommon('organizer_new', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $orgParams;
    return $result->processJSONRequest();
  }

  public function organiserUpdate($orgParams, $forceNoCache = FALSE, $dataOverride = '') {
    if (!$this->organiserID) {
      drupal_set_message(t('You haven\'t picked an organiser!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('organizer_update', 'update', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $orgParams['id'] = $this->organiserID;
    $result->params = $orgParams;
    return $result->processJSONRequest();
  }

}
