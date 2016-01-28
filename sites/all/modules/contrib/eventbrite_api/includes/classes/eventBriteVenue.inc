<?php
/**
 * @file
 * Contains eventBriteVenues.
 *
 * This class contains all of the API calls for venues
 */

class eventBriteVenues {

  private $venueID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($venueID = null, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($venueID)) {
      $this->venueID = $venueID;
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

  public static function venue_create() {
    $venue = (object) array(
      'vid' => '',
      'oid' => '',
      'name' => '',
      'address' => '',
      'address_2' => '',
      'city' => '',
      'region' => '',
      'postal_code' => '',
      'country_code' => '',
      'is_new' => TRUE,
    );
    return $venue;
  }

  public static function venue_save(&$venue) {
    return entity_save('venue', $venue);
  }

  public static function venue_delete($entity) {
    entity_delete('venue', $entity->tid);
    // MAKE THIS CANCEL EVENT WITH EVENTBRITE.
  }

  /**
   * Autocomplete results for the event form venue field.
   */
  public static function _eventbrite_venue_autocomplete($string) {
    $matches = array();
    // Select the organizers table.
    $query = db_select('eventbrite_api_venues', 'v');
    // Select rows that match the string.
    $return = $query
      ->fields('v', array('vid', 'name'))
      ->condition('v.name', '%' . db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    // Add matches to $matches .
    foreach ($return as $row) {
      $matches[$row->vid] = check_plain($row->name);
    }
    // Return for JS.
    drupal_json_output($matches);
  }
  public function venueGet($forceNoCache = FALSE, $dataOverride = '') {
    if (!$this->venueID) {
      drupal_set_message(t('You haven\'t picked a venue.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('venue_get', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('id' => $this->venueID);
    return $result->processJSONRequest();
  }

  public function venuesList($user_id, $forceNoCache = FALSE, $dataOverride = 'https://www.eventbriteapi.com/v3/users/') {
    $result = new eventBriteCommon('venues', 'get', $dataOverride, $forceNoCache, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = array('id' => $user_id);
    return $result->processJSONRequest(TRUE);
  }

  public function venueNew($venueArray, $dataOverride = '') {
    $result = new eventBriteCommon('venue_new', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $venueArray;
    return $result->processJSONRequest();
  }

  public function venueUpdate($venueArray, $dataOverride = '') {
    if (!$this->venueID) {
      drupal_set_message(t('You haven\'t picked a venue.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('venue_update', 'update', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $venueArray['id'] = $this->venueID;
    $result->params = $venueArray;
    return $result->processJSONRequest();
  }

  public function set_venueID($invenueID) {
    $this->venueID = $invenueID;
  }

}
