<?php

/**
 * @file
 * Contains \Drupal\eventbrite_attendees\AttendeeList.
 *
 * or would if the Drupal 7 autoloader handled namespaces.
 */

class EventbriteAttendeeList implements \Countable, \Iterator {
  private $position = 0;
  protected $list = array();
  protected $status;

  function __construct(array $list, $status) {
    $this->list = array_values($list);
    $this->status = $status;
  }

  public static function fromJsonData($data, $status) {
    $list = array();
    foreach ($data as $a) {
      $attendee = $a->attendee;
      $answers = is_array($attendee->answers) ? $attendee->answers : array();
      $attendee->answers = array();
      foreach ($answers as $ans) {
        $attendee->answers[$ans->answer->question_id] = $ans->answer;
        $attendee->answers[$ans->answer->question_id]->attendee_id = $attendee->id;
      }
      $list[] = $attendee;
    }
    return new EventbriteAttendeeList($list, $status);
  }

  /**
   * Implements \Iterator::rewind()
   */
  function rewind() {
    $this->position = 0;
  }

  /**
   * Implements Iterator::current()
   *
   * @return object
   *   Data for one attendee.
   */
  function current() {
    return $this->list[$this->position];
  }

  /**
   * Implements \Iterator::key()
   *
   * @return int
   */
  function key() {
    return $this->position;
  }

  /**
   * Implements \Iterator::next()
   */
  function next() {
    ++$this->position;
  }

  /**
   * Implements \Iterator::valid()
   *
   * @return bool
   */
  function valid() {
    return isset($this->list[$this->position]);
  }

  /**
   * @return int
   */
  public function count() { 
    return count($this->list); 
  }

  public function status() {
    return $this->status;
  }
}
