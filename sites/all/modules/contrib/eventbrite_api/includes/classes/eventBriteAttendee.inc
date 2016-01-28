<?php
/**
 * @file
 * Contains eventBriteAttendee.
 *
 * This class contains all of the API calls for attendees
 */

class eventBriteAttendee {

  private $eventID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($eventID = null, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
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

  public function attendeeList($forceNoCache = FALSE, $dataOverride = '') {
    if (!$this->eventID) {
      drupal_set_message(t('You haven\'t picked an event!'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('event_list_attendees', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('event_id' => $this->eventID);
    return $result->processJSONRequest();
  }

}
