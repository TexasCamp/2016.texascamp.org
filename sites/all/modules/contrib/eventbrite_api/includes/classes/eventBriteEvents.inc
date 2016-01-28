<?php
/**
 * @file
 * Contains eventBriteEvents.
 *
 * This class contains all of the API calls for events
 */

class eventBriteEvents {

  private $eventID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($eventID = NULL, $userKey = null, $appKey = null, $accessToken = null) {
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

  public static function event_create() {
    $event = (object) array(
      'eid' => '',
      'oid' => '',
      'acid' => '',
      'vid' => '',
      'is_new' => TRUE,
      'locale' => '',
      'timezone' => '',
      'category' => '',
      'capacity' => '',
      'num_attendee_rows' => '',
      'title' => '',
      'start_date' => '',
      'status' => '',
      'description' => '',
      'end_date' => '',
      'tags' => '',
      'timezone_offset' => '',
      'password' => '',
      'created' => '',
      'url' => '',
      'privacy' => '',
      'modified' => '',
      'repeats' => '',
    );
    return $event;
  }

  public static function event_save(&$event) {
    return entity_save('event', $event);
  }

  public static function event_delete($entity) {
    entity_delete('event', $entity->eid);
    $eventbrite = new self($entity->eid);
    $response = $eventbrite->eventUpdate(array('id' => $entity->eid, 'status' => 'deleted'));
  }

  /**
   * Autocomplete results for the ticket form event field.
   */
  public static function _eventbrite_event_autocomplete($string) {
    $matches = array();
    // Select the organizers table.
    $query = db_select('eventbrite_api_events', 'e');
    // Select rows that match the string.
    $return = $query
      ->fields('e', array('eid', 'title'))
      ->condition('e.title', '%' . db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    // Add matches to $matches .
    foreach ($return as $row) {
      $matches[$row->eid] = check_plain($row->title);
    }
    // Return for JS.
    drupal_json_output($matches);
  }

  public function eventSearch($searchArray = array(), $forceNoCache = FALSE, $dataOverride = '') {
    $result = new eventBriteCommon('event_search', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $searchArray;
    return $result->processJSONRequest();
  }

  public function eventGet($forceNoCache = FALSE, $dataOverride = '') {
    if (!$this->eventID) {
      drupal_set_message(t('You haven\'t picked an event.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('event_get', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('id' => $this->eventID);
    return $result->processJSONRequest();
  }

  public function eventNew($eventArray, $dataOverride = '') {
    $result = new eventBriteCommon('event_new', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $eventArray;
    return $result->processJSONRequest();
  }

  public function eventCopy($eventTitle, $dataOverride = '') {
    if (!$this->eventID) {
      drupal_set_message(t('You haven\'t picked an event to copy.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('event_copy', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('id' => $this->eventID, 'event_name' => $eventTitle);
    return $result->processJSONRequest();
  }

  public function eventUpdate($eventArray, $opType = 'update', $dataOverride = '') {
    if (!$this->eventID) {
      drupal_set_message(t('You haven\'t picked an event to update.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('event_update', $opType, $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $eventArray['id'] = $this->eventID;
    $result->params = $eventArray;
    return $result->processJSONRequest();
  }

}
