<?php

/**
 * Filter by order status.
 */
class eventbrite_api_handler_filter_event_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = array();
      $this->value_options['draft'] = 'Draft';
      $this->value_options['live'] = 'Live';
    }
  }
}
