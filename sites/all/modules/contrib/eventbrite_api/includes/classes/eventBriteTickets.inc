<?php
/**
 * @file
 * Contains eventBriteTickets.
 *
 * This class contains all of the API calls for tickets
 */

class eventBriteTickets {

  private $ticketID;
  private $eventID;
  private $userKey;
  private $appKey;
  private $accessToken;

  function __construct($ticketID = NULL, $eventID = NULL, $userKey = NULL, $appKey = NULL, $accessToken = NULL) {
    if (!empty($ticketID)) {
      $this->ticketID = $ticketID;
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

  public static function ticket_create() {
    $ticket = (object) array(
      'tid' => '',
      'eid' => '',
      'name' => '',
      'type' => '',
      'description' => '',
      'start_date' => '',
      'end_date' => '',
      'min' => '',
      'max' => '',
      'price' => '',
      'quantity_sold' => '',
      'visible' => '',
      'currency' => '',
      'quantity_available' => '',
      'display_price' => '',
      'is_new' => TRUE,
    );
    return $ticket;
  }

  public static function ticket_save(&$ticket) {
    return entity_save('ticket', $ticket);
  }

  public static function ticket_delete($entity) {
    entity_delete('ticket', $entity->tid);
    // MAKE THIS CANCEL EVENT WITH EVENTBRITE.
  }

  public function ticketNew($ticketParams, $dataOverride = '') {
    if (is_null($this->eventID)) {
      drupal_set_message(t('You haven\'t picked an event.'), 'error');
      return FALSE;
    }
    $ticketParams['event_id'] = $this->eventID;
    $result = new eventBriteCommon('ticket_new', 'create', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $result->params = $ticketParams;
    return $result->processJSONRequest();
  }

  public function ticketUpdate($ticketParams, $dataOverride = '') {
    if (!$this->ticketID) {
      drupal_set_message(t('You haven\'t picked a ticket.'), 'error');
      return FALSE;
    }
    $result = new eventBriteCommon('ticket_update', 'update', $dataOverride, TRUE, $this->userKey, $this->appKey, $this->accessToken);
    $ticketParams['id'] = $this->ticketID;
    $result->params = $ticketParams;
    return $result->processJSONRequest();
  }

}
