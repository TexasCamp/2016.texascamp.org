<?php

/**
 * @file
 * Eventbrite forms file.
 */

/**
 * Admin configiguration form.
 */
function eventbrite_api_config_form($form, &$form_state) {
  $form = array();

  $numaccts = 0;
  $functions = module_load_include('inc', 'eventbrite_api', 'includes/eventbrite_api.functions');
  drupal_add_css(drupal_get_path('module', 'eventbrite_api') . '/css/eventbrite_api.css');
  $defaultacct = variable_get('eventbrite_api_defaultacct', array('api_userkey' => '', 'api_appkey' => '', 'api_oauth' => '', 'api_name' => ''));
  // Load the details.
  $ukey = $defaultacct['api_userkey'];
  $akey = $defaultacct['api_appkey'];
  $oauth = $defaultacct['api_oauth'];
  $defaultacctname = $defaultacct['api_name'];

  // Create the div wrapper that get's recreated by ajax
  $form['forms'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#prefix' => '<div id="eventbrite_api_accounts"><table class="eventbrite_accounts">',
    '#suffix' => '</table></div>',
  );

  $accounts = _eventbrite_api_list_accounts();
  $options = array();
  $defaultval = -1;
  $header = array(
    'eventbrite_api_name' => 'Account Name',
    'eventbrite_api_userkey' => 'User Key',
    'eventbrite_api_appkey' => 'App Key',
    'eventbrite_api_oauth' => 'OAuth Key',
    'eventbrite_api_delete' => 'Delete',
  );

  if (count($accounts)) {
    foreach ($accounts as $account) {
      $options[$account->acid] = array(
        //'eventbrite_api_name' => $account->name,
        'eventbrite_api_name' => array('data' => array(
          '#type' => 'textfield',
          '#value' => $account->name,
          '#size' => 15,
          '#name' => 'eventbrite_api_name[' . $account->acid . ']'),
        ),
        'eventbrite_api_userkey' => array('data' => array(
          '#type' => 'textfield',
          '#value' => $account->api_userkey,
          '#size' => 20,
          '#name' => 'eventbrite_api_userkey[' . $account->acid . ']'),
        ),
        'eventbrite_api_appkey' => array('data' => array(
          '#type' => 'textfield',
          '#value' => $account->api_appkey,
          '#size' => 20,
          '#name' => 'eventbrite_api_appkey[' . $account->acid . ']'),
        ),
        'eventbrite_api_oauth' => array('data' => array(
          '#type' => 'textfield',
          '#value' => $account->api_oauth,
          '#size' => 20,
          '#name' => 'eventbrite_api_oauth[' . $account->acid . ']'),
        ),
        'eventbrite_api_delete' => array('data' => array(
          '#type' => 'checkbox',
          '#value' => FALSE,
          '#size' => 20,
          '#name' => 'eventbrite_api_delete[' . $account->acid . ']'),
        ),
        'eventbrite_api_update' => array('data' => array(
          '#type' => 'checkbox',
          '#value' => TRUE,
          '#size' => 20,
          '#name' => 'eventbrite_api_update[' . $account->acid . ']'),
        ),
      );
      $defaultval = $account->is_default ? $account->acid : $defaultval;
      $numaccts += 1;
    }
  }

  $options[-1] = array(
    //'eventbrite_api_name' => $account->name,
    'eventbrite_api_name' => array('data' => array(
      '#type' => 'textfield',
      '#value' => '',
      '#size' => 15,
      '#name' => 'eventbrite_api_name[-1]'),
    ),
    'eventbrite_api_userkey' => array('data' => array(
      '#type' => 'textfield',
      '#value' => '',
      '#size' => 20,
      '#name' => 'eventbrite_api_userkey[-1]'),
    ),
    'eventbrite_api_appkey' => array('data' => array(
      '#type' => 'textfield',
      '#value' => '',
      '#size' => 20,
      '#name' => 'eventbrite_api_appkey[-1]'),
    ),
    'eventbrite_api_oauth' => array('data' => array(
      '#type' => 'textfield',
      '#value' => '',
      '#size' => 20,
      '#name' => 'eventbrite_api_oauth[-1]'),
    ),
    'eventbrite_api_delete' => array('data' => array(
      '#type' => 'checkbox',
      '#value' => FALSE,
      '#access' => FALSE,
      '#size' => 20,
      '#name' => 'eventbrite_api_delete[-1]'),
    ),
    'eventbrite_api_update' => array('data' => array(
      '#type' => 'checkbox',
      '#value' => TRUE,
      '#size' => 20,
      '#name' => 'eventbrite_api_update[-1]'),
    ),
  );

  $form['forms']['auth'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#multiple' => FALSE,
    '#default_value' => $defaultval,
  );
  $form['eventbrite_api_name'] = array( '#type' => 'value', );
  $form['eventbrite_api_userkey'] = array( '#type' => 'value', );
  $form['eventbrite_api_appkey'] = array( '#type' => 'value', );
  $form['eventbrite_api_oauth'] = array( '#type' => 'value', );
  $form['eventbrite_api_delete'] = array( '#type' => 'value', );
  $form['eventbrite_api_update'] = array( '#type' => 'value', );

  // The add more button TODO
  $form['add_account'] = array(
    '#type' => 'button',
    '#value' => t('Add Account'),
    '#href' => '',
    '#ajax' => array(
      'callback' => '_eventbrite_api_ajax_add_account',
      'wrapper' => 'eventbrite_api_accounts',
    ),
  );

  // The remove button
  $form['remove_account'] = array(
    '#type' => 'button',
    '#value' => t('Remove Selected'),
    '#href' => '',
    '#ajax' => array(
      'callback' => '_eventbrite_api_ajax_remove_account',
      'wrapper' => 'eventbrite_api_accounts',
    ),
  );

  // The user v3 and v1 ids are used in some places, so they get set here
  $form['eventbrite_user_id_v1'] = array(
    '#type' => 'hidden',
    '#default_value' => variable_get('eventbrite_user_id_v1',NULL),
  );
  $form['eventbrite_user_id_v3'] = array(
    '#type' => 'hidden',
    '#default_value' => variable_get('eventbrite_user_id_v3',NULL),
  );

  // Display the rest of the form only when the Eventbrite details are correct.
  if (!empty($ukey) && !empty($akey)) {
    $form['import'] = array(
      '#type' => 'fieldset',
      '#title' => t('Eventbrite data import'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['import']['import_all'] = array(
      '#type' => 'submit',
      '#value' => t('Import all Eventbrite event data'),
      '#submit' => array('_eventbrite_api_import_all_wrapper'),
    );
    $form['import']['import_all_help'] = array(
      '#markup' => '<div>' . t('If you already have Eventbrite data imported,
      this will delete that data before importing the new data. This
      cannot be undone.') . '</div>',
    );
    $form['import_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Event import settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['import_settings']['eventbrite_api_import_delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete all existing data before import.'),
      '#default_value' => variable_get('eventbrite_api_import_delete', 1),
    );
    $form['import_settings']['eventbrite_api_cron_import'] = array(
      '#type' => 'checkbox',
      '#title' => t('Import events from Eventbrite during cron runs'),
      '#default_value' => variable_get('eventbrite_api_cron_import', 1),
    );
    $form['import_settings']['eventbrite_api_cron_delay'] = array(
      '#type' => 'select',
      '#title' => t('How often should we run cron'),
      '#default_value' => variable_get('eventbrite_api_cron_delay', 360),
      '#options' => array(
        3600 => 'Every hour',
        7200 => 'Every 2 hours',
        10800 => 'Every 3 hours',
        14400 => 'Every 4 hours',
        18000 => 'Every 5 hours',
        43200 => 'Every 12 hours',
        86400 => 'Once per day',
        172800 => 'Every 2 days',
        259200 => 'Every 3 days',
        432000 => 'Every 5 days',
        604800 => 'Once per week',
        1209600 => 'Every 2 weeks',
      ),
      '#description' => t('Select the gap in hours between each cron run. Remember that syncronising with the server requires resources, so set this value to as high as you believe is feasible to keep your site up to date.', array()),
    );
    $form['import_settings']['eventbrite_api_import_strip'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip HTML code from the event description (recommended)'),
      '#default_value' => variable_get('eventbrite_api_import_strip', 1),
    );
    $form['general'] = array(
      '#type' => 'fieldset',
      '#title' => t('General settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['general']['eventbrite_api_currency'] = array(
      '#type' => 'select',
      '#title' => t('Default currency'),
      '#default_value' => variable_get('eventbrite_api_currency', 'USD'),
      '#options' => _eventbrite_api_currencies(),
    );
    $form['general']['eventbrite_api_country_code'] = array(
      '#type' => 'select',
      '#title' => t('Default country code'),
      '#default_value' => variable_get('eventbrite_api_country_code', 'US'),
      '#options' => _eventbrite_api_countries(),
    );
  }
  $form['eventbrite_api_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['#validate'][] = 'eventbrite_api_config_form_validate';

  return $form;
}

/**
 * Validation function for the admin configiguration form.
 * Essentially, we're testing to see if the keys work.
 */
function eventbrite_api_config_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Submit') {
    // test out the key pair
    foreach ($form_state['values']['eventbrite_api_appkey'] as $key => $acct) {
      $akey = $form_state['values']['eventbrite_api_appkey'][$key];
      $ukey = $form_state['values']['eventbrite_api_userkey'][$key];
      $oauth = $form_state['values']['eventbrite_api_oauth'][$key];
      $defaultacctname = $form_state['values']['eventbrite_api_name'][$key];
      $eventbrite = new eventBriteEvents(NULL, $ukey, $akey);
      $events = $eventbrite->eventSearch();
      if (isset($events['error']) && isset($events['error']['error_message'])) {
        $error = $events['error']['error_type'] . ': ' . $events['error']['error_message'];
        if (strpos($error, 'user_key') !== FALSE) {
          $element = 'eventbrite_api_userkey';
        }
        // If it's the app key.
        elseif (strpos($error, 'application key') !== FALSE) {
          $element = 'eventbrite_api_appkey';
        }
        form_set_error($element, t('Connection to Eventbrite failed for the account ' . $defaultacctname . ' with the following error: @error', array('@error' => $error)));
      }
      else {
        $obj = new eventBriteUser(NULL, NULL,NULL, NULL, $form_state['values']['eventbrite_api_oauth'][$key]);
        $user = $obj->userGetMaster();
        if (isset($user['error']) && isset($user['error']['error_message'])) {
          $error = $user['error']['error_type'] . ': ' . $user['error']['error_message'];
          drupal_set_message(t('Connection to Eventbrite failed to retrieve the v1 user id for the account ' . $defaultacctname . ' : @error', array('@error' => $error)), 'warning');
        }
        else {
          $form_state['values']['eventbrite_user_id_v1'] = $user['user']['user_id'];
        }
        $user = $obj->userGetMasterV3();
        if (isset($user['error']) && isset($user['error']['error_message'])) {
          $error = $user['error']['error_type'] . ': ' . $user['error']['error_message'];
          drupal_set_message(t('The OAuth token is invalid for the account ' . $defaultacctname . ' : @error', array('@error' => $error)), 'warning');
        }
        $form_state['values']['eventbrite_user_id_v3'] = $user['id'];
      }
    }
  }
}

function eventbrite_api_config_form_submit($form, &$form_state) {
  foreach ($form_state['values']['eventbrite_api_appkey'] as $key => $acct) {
    $akey = $form_state['values']['eventbrite_api_appkey'][$key];
    $ukey = $form_state['values']['eventbrite_api_userkey'][$key];
    $oauth = $form_state['values']['eventbrite_api_oauth'][$key];
    $acctname = $form_state['values']['eventbrite_api_name'][$key];
    if ($acctname <> '') {
      $defaultacct = $form_state['values']['forms']['auth'] == $key ? 1 : 0;
      if ($form_state['values']['forms']['auth'] == $key) {
        $defaultacct = 1;
        variable_set('eventbrite_api_defaultacct', array('api_userkey' => $ukey, 'api_appkey' => $akey, 'api_oauth' => $oauth, 'api_name' => $acctname));
      }
      else {
        $defaultacct = 0;
      }
      if ($key > 0) {
        $num_updated = db_update('eventbrite_api_accounts') // Table name no longer needs {}
          ->fields(array(
            'name' => $acctname,
            'api_userkey' => $ukey,
            'api_appkey' => $akey,
            'api_oauth' => $oauth,
            'is_default' => $defaultacct,
          ))
          ->condition('acid', $key)
          ->execute();
      }
      else {
        $acid = db_insert('eventbrite_api_accounts') // Table name no longer needs {}
          ->fields(array(
            'name' => $acctname,
            'api_userkey' => $ukey,
            'api_appkey' => $akey,
            'api_oauth' => $oauth,
            'is_default' => $defaultacct,
          ))
          ->execute();
      }
    }
  }
  variable_set('eventbrite_api_import_delete', $form_state['values']['eventbrite_api_import_delete']);
  variable_set('eventbrite_api_cron_import', $form_state['values']['eventbrite_api_cron_import']);
  variable_set('eventbrite_api_cron_delay', $form_state['values']['eventbrite_api_cron_delay']);
  variable_set('eventbrite_api_import_strip', $form_state['values']['eventbrite_api_import_strip']);
  variable_set('eventbrite_api_currency', $form_state['values']['eventbrite_api_currency']);
  variable_set('eventbrite_api_country_code', $form_state['values']['eventbrite_api_country_code']);
}

function _eventbrite_api_ajax_add_account($form, &$form_state) {
  $num = - (count($form['eventbrite_api_name']['#value']) + 1);
  $form['forms']['auth'][$num] = $form['forms']['auth'][-1];
  $form['forms']['auth']['#options'][$num] = $form['forms']['auth']['#options'][-1];
  $form['eventbrite_api_name']['#value'][$num] = '';
  return $form['forms'];
}

function _eventbrite_api_ajax_remove_account($form, &$form_state) {
  foreach ($form_state['values']['eventbrite_api_delete'] as $key => $value) {
    unset($form['forms']['auth'][$key]);
    db_delete('eventbrite_api_accounts')
      ->condition('acid', $key)
      ->execute();
  }
  return $form['forms'];
}

/**
 * Event add form.
 */
function event_add_form($form, &$form_state, $event) {
  $functions = module_load_include('inc', 'eventbrite_api', 'includes/eventbrite_api.functions');
  $form['details'] = array(
    '#type' => 'fieldset',
    '#title' => t('General information'),
  );

  $form['details']['eid'] = array(
    '#type' => 'hidden',
    '#title' => t('Event ID'),
    '#default_value' => isset($event->eid) ? $event->eid : '',
  );

  $form['details']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Event title'),
    '#default_value' => isset($event->title) ? $event->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['details']['new_vid'] = array(
    '#type' => 'checkbox',
    '#default_value' => FALSE,
    '#title' => t('Create New Venue'),
  );

  $form['details']['vid'] = array(
    '#title' => t('Venue'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'eventbrite/venue/autocomplete',
    '#default_value' => isset($event->vid) ? eventbrite_api_autocomplete_build($event->vid, 'venue') : '',
    '#states' => array(
      'invisible' => array(
        ':input[name="new_vid"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['details']['venue'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create New Venue'),
    '#states' => array(
      'visible' => array(
        ':input[name="new_vid"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['details']['venue']['venname'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#maxlength' => 255,
    '#states' => array(
        'required' => array(
            ':input[name="new_vid"]' => array('checked' => TRUE),
        ),
    ),
  );

  $form['details']['venue']['venaddress'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#maxlength' => 255,
  );

  $form['details']['venue']['venaddress_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
    '#maxlength' => 255,
  );

  $form['details']['venue']['vencity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#maxlength' => 255,
  );

  $form['details']['venue']['venregion'] = array(
    '#type' => 'textfield',
    '#title' => t('Region'),
    '#maxlength' => 255,
    '#description' => t('Please note that if your event is in the US, this field is mandatory and requires a 2 digit US state code. You can find a list of US state codes at !url.', array('!url' => l('https://en.wikipedia.org/wiki/List_of_U.S._state_abbreviations', 'https://en.wikipedia.org/wiki/List_of_U.S._state_abbreviations'))),
  );

  $form['details']['venue']['venpostal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#maxlength' => 255,
  );

  $form['details']['venue']['vencountry_code'] = array(
    '#type' => 'select',
    '#title' => t('Country code'),
    '#options' => _eventbrite_api_countries(),
  );

  $form['details']['dates'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date information'),
  );

  $form['details']['dates']['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start date'),
    '#default_value' => isset($event->start_date) ? $event->start_date : '',
    '#required' => TRUE,
  );

  $form['details']['dates']['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End date'),
    '#default_value' => isset($event->end_date) ? $event->end_date : '',
    '#required' => TRUE,
  );

  $form['details']['dates']['date_default_timezone'] = array(
    '#type' => 'select',
    '#title' => t('Default time zone'),
    '#default_value' => variable_get('date_default_timezone', date_default_timezone_get()),
    '#options' => system_time_zones(),
    '#required' => TRUE,
  );

  $form['details']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($event->description) ? $event->description : '',
  );

  $form['details']['new_org'] = array(
    '#type' => 'checkbox',
    '#default_value' => FALSE,
    '#title' => t('Create New Organization'),
  );

  $form['details']['oid'] = array(
    '#title' => t('Organizer'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'eventbrite/organizer/autocomplete',
    '#default_value' => isset($event->oid) ? eventbrite_api_autocomplete_build($event->oid, 'organizer') : '',
    '#states' => array(
      'invisible' => array(
        ':input[name="new_org"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['details']['org'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create New Organization'),
    '#states' => array(
      'visible' => array(
        ':input[name="new_org"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['details']['org']['orgname'] = array(
    '#type' => 'textfield',
    '#title' => t('Organizer name'),
    '#default_value' => isset($organizer->name) ? $organizer->name : '',
    '#maxlength' => 255,
    '#states' => array(
        'required' => array(
            ':input[name="new_org"]' => array('checked' => TRUE),
        ),
    ),
  );

  $form['details']['org']['orgdescription'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($organizer->description) ? $organizer->description : '',
  );

  $form['details']['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#default_value' => isset($event->currency) ? $event->currency : variable_get('eventbrite_api_currency', 'USD'),
    '#options' => _eventbrite_api_currencies(),
  );

  $form['details']['status'] = array(
    '#type' => 'select',
    '#title' => t('Event status'),
    '#default_value' => isset($event->status) ? $event->status : 'draft',
    '#options' => array(
      'draft' => t('Draft'),
      'live' => t('Live'),
    ),
  );

  $form['tickets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tickets'),
  );

  $form['tickets']['tixcapacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Total Capacity'),
    '#default_value' => isset($event->capacity) ? $event->capacity : '',
    '#size' => 5,
  );

  // Create the div wrapper that get's recreated by ajax
  $form['tickets']['forms'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#prefix' => '<div id="eventbrite_api_tix_forms">',
    '#suffix' => '</div>',
  );

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'ticket')
    ->propertyCondition('eid', $event->eid)
    ->addMetaData('account', user_load(1)); // Run the query as user 1.

  $result = $query->execute();

  $numtix = 0;
  $curtix = array();

  if (!empty($result['ticket'])) {
    $numtix = count($result['ticket']);
    foreach ($result['ticket'] as $entity_obj) {
      $curtix[] = ticket_load($entity_obj->tid);
    }
  }

  // Set the number of saved forms value
  if ($numtix > 0) {
    $form_state['tickets']['forms'] = $numtix;
  }
  else {
    $form_state['tickets']['forms'] = isset($form_state['tickets']['forms']) ? $form_state['tickets']['forms'] : 1;
  }

  // Allow the user to create 1 to n tickest for this event.
  for ($count = 1; $count <= $form_state['tickets']['forms']; $count++) {
    $form['tickets']['forms'][$count] = array(
      '#type' => 'fieldset',
      '#title' => 'Ticket ' . $count,
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['tickets']['forms'][$count]['tid'] = array(
      '#type' => 'hidden',
      '#title' => t('Ticket ID'),
      '#default_value' => isset($curtix[$count -1]->tid) ? $curtix[$count -1]->tid : '',
    );

    $form['tickets']['forms'][$count]['tixname'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#maxlength' => 255,
      '#required' => TRUE,
      '#default_value' => isset($curtix[$count -1]->name) ? $curtix[$count -1]->name : '',
    );

    $form['tickets']['forms'][$count]['tixtype'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#options' => array(
        0 => 'Fixed price',
        1 => 'Donation',
      ),
      '#default_value' => isset($curtix[$count -1]->type) ? $curtix[$count -1]->type : 0,
      '#required' => TRUE,
    );

    $form['tickets']['forms'][$count]['tixmin'] = array(
      '#type' => 'textfield',
      '#title' => t('Min'),
      '#description' => t('The minimum number of this ticket a person can purchase. The default is 1.'),
      '#default_value' => !empty($curtix[$count -1]->min) ? $curtix[$count -1]->min : 1,
      '#required' => TRUE,
      '#maxlength' => 255,
    );

    $form['tickets']['forms'][$count]['tixmax'] = array(
      '#type' => 'textfield',
      '#title' => t('Max'),
      '#description' => t('The maximum number of this ticket a person can purchase. This is optional and if left blank, the default will be whatever value is entered into the "Quantity available" field.'),
      '#default_value' => (!empty($curtix[$count -1]->max) ? $curtix[$count -1]->max : (isset($curtix[$count -1]->quantity_available) ? $curtix[$count -1]->quantity_available : '')),
      '#maxlength' => 255,
    );

    $form['tickets']['forms'][$count]['tixprice'] = array(
      '#type' => 'textfield',
      '#title' => t('Price'),
      '#prefix' => '$',
      '#default_value' => isset($curtix[$count -1]->price) ? $curtix[$count -1]->price : '0.00',
    );

    $form['tickets']['forms'][$count]['tixquantity_available'] = array(
      '#type' => 'textfield',
      '#title' => t('Quantity available'),
      '#description' => t('The number of this ticket available.'),
      '#default_value' => isset($curtix[$count -1]->quantity_available) ? $curtix[$count -1]->quantity_available : 100,
    );

    $form['tickets']['forms'][$count]['tixcurrency'] = array(
      '#type' => 'select',
      '#title' => t('Currency'),
      '#options' => _eventbrite_api_currencies(),
      '#default_value' => !empty($curtix[$count -1]->currency) ? $curtix[$count -1]->currency : variable_get('eventbrite_api_currency', 'USD'),
      '#required' => TRUE,
    );

    $form['tickets']['forms'][$count]['tixdescription'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => isset($curtix[$count -1]->description) ? $curtix[$count -1]->description : '',
    );

    $form['tickets']['forms'][$count]['tixstart_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('Start date'),
      '#default_value' => isset($curtix[$count -1]->start_date) ? $curtix[$count -1]->start_date : '',
      '#required' => TRUE,
    );

    $form['tickets']['forms'][$count]['tixend_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('End date'),
      '#default_value' => isset($curtix[$count -1]->end_date) ? $curtix[$count -1]->end_date : '',
      '#required' => TRUE,
    );

    $form['tickets']['forms'][$count]['tixinclude_fee'] = array(
      '#type' => 'select',
      '#title' => t('Include fee'),
      '#description' => t('Should the Eventbrite fee be added onto the ticket price or included as part of the ticket price.'),
      '#options' => array(
        0 => 'Add to ticket price',
        1 => 'Include in ticket price',
      ),
      '#default_value' => isset($curtix[$count -1]->include_fee) ? $curtix[$count -1]->include_fee : 0,
      '#required' => TRUE,
    );

    $form['tickets']['forms'][$count]['tixvisible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide this ticket type'),
      '#default_value' => !empty($curtix[$count -1]->visible) ? $curtix[$count -1]->visible : false,
    );

    if (!empty($ticket->eid)) {
      $form['tickets']['forms'][$count]['tixhide'] = array(
        '#type' => 'select',
        '#title' => t('Show or hide'),
        '#description' => t('Display this ticket on the Eventbrite booking page or hide it from view.'),
        '#options' => array(
          'n' => 'Show',
          'y' => 'Hide',
        ),
        '#default_value' => isset($curtix[$count -1]->hide) ? $curtix[$count -1]->hide : 'n',
        '#required' => TRUE,
      );
    }
  }

  // The add more button
  $form['tickets']['forms']['add_ticket'] = array(
    '#type' => 'button',
    '#value' => t('Add Another Ticket'),
    '#href' => '',
    '#limit_validation_errors' => array(),
    '#states' => array(
      // Here visibility requires that two separate conditions be true.
      'invisible' => array(
        ':input[name="forms[' . $form_state['tickets']['forms'] . '][tixname]"]' => array('value' => ''),
      ),
    ),
    '#ajax' => array(
      'callback' => 'eventbrite_api_ajax_add_tix',
      'wrapper' => 'eventbrite_api_tix_forms',
    ),
  );

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('event_add_form_submit'),
  );

  if (!empty($event->title)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete event'),
      '#suffix' => l(t('Cancel'), 'admin/config/services/eventbrite/events'),
      '#submit' => $submit + array('event_form_submit_delete'),
      '#weight' => 45,
    );
  }
  $form['#validate'][] = 'event_add_form_validate';
  // Add the field related form elements.
  $form_state['event'] = $event;
  $form_state['eid'] = $event->eid;

  field_attach_form('event', $event, $form, $form_state);

  $form_state['tickets']['forms']++;

  return $form;
}

function eventbrite_api_ajax_add_tix($form, $form_state) {
  return $form['tickets']['forms'];
}

/**
 * Validation function for event add form.
 */
function event_add_form_validate($form, &$form_state) {
  $capacity = 0;
  $values = $form_state['values'];
  // validate teh new venue if required
  if ($values['new_vid']) {
    if ($values['venname'] == '') {
      form_set_error('venname', t('If you create a new venue, you must enter a venue name!'));
    }
  }
  if ($values['new_org']) {
    if ($values['orgname'] == '') {
      form_set_error('orgname', t('If you create a new organization, you must enter an organization name!'));
    }
  }
  if ($values['start_date'] == '' && strtotime($values['start_date']) <= time()) {
    form_set_error('start_date', t('The start date must be later than today'));
  }
  if ($values['start_date'] > $values['end_date']) {
    form_set_error('end_date', t('The end date must be later than start date'));
  }
  foreach ($values['forms'] as $key => $ticket) {
    if (is_numeric($key)) {
      if ($ticket['tixstart_date'] > $values['end_date']) {
        form_set_error('tixstart_date', t('The ticket start date cannot be later than event end date'));
      }
      if ($ticket['tixend_date'] > $values['end_date']) {
        form_set_error('tixstart_date', t('The ticket end date cannot be later than event end date'));
      }
      if ($ticket['tixstart_date'] > $ticket['tixend_date']) {
        form_set_error('tixstart_date', t('The ticket end date must be later than ticket start date'));
      }
      $capacity += $ticket['tixquantity_available'];
    }
  }
  if ($values['tixcapacity'] != '' && $values['tixcapacity'] != 0 && $values['tixcapacity'] < $capacity) {
    form_set_error('tixcapacity', t('The total quantity across all of the tickets is greater than the max capacity for the  event'));
  }
}

/**
 * Submit function for event add form.
 */
function event_add_form_submit($form, &$form_state) {
  $functions = module_load_include('inc', 'eventbrite_api', 'includes/eventbrite_api.functions');
  $values = $form_state['values'];
  // Get the organisation id from the autcomplete or create a new one
  if ($values['new_org']) {
    // Save the new venue and get the id
    $neworg = array(
      'name' => $values['orgname'],
      'description' => $values['orgdescription'],
    );
    $orgobj = new eventBriteOrganizer();
    $neworg = $orgobj->organiserNew($neworg);
    if (isset($neworg['error']) && isset($neworg['error']['error_message'])) {
      $error = $neworg['error']['error_type'] . ': ' . $neworg['error']['error_message'];
      drupal_set_message(t('We couldn\'t create the organisation: @error', array('@error' => $error)), 'error');
      return;
    }
    // Create a new org then save it to the drupal db
    $neworgdb = eventBriteOrganizer::organizer_create();
    $neworgdb->oid = $neworg['process']['id'];
    $neworgdb->name = $values['orgname'];
    $neworgdb->description = $values['orgdescription'];
    // Write the record.
    if ($write = eventBriteOrganizer::organizer_save($neworgdb)) {
      $values['oid'] = $neworgdb->oid;
    }
  }
  else {
    $values['oid'] = eventbrite_api_autocomplete_filter($values['oid']);
  }

  // Get the venue id from the autcomplete or create a new one
  if ($values['new_vid']) {
    $newvenuedb = array();
    // Save the new venue and get the id
    $newvenue = array(
      'organizer_id' => $values['oid'],
      'name' => $values['venname'],
      'address' => $values['venaddress'],
      'address_2' => $values['venaddress_2'],
      'city' => $values['vencity'],
      'region' => $values['venregion'],
      'postal_code' => $values['venpostal_code'],
      'country_code' => $values['vencountry_code'],
    );
    $venueobj = new eventBriteVenues();
    $newvenue = $venueobj->venueNew($newvenue);

    if (isset($newvenue['error']) && isset($newvenue['error']['error_message'])) {
      $error = $newvenue['error']['error_type'] . ': ' . $newvenue['error']['error_message'];
      drupal_set_message(t('We couldn\'t create the venue: @error', array('@error' => $error)), 'error');
      return;
    }
    // Create a new org then save it to the drupal db
    _eventbrite_api_import_venues($newvenue['process']['id'], $newvenuedb);
    $record = (object) array_merge((array) eventbrite_api_entity_prepare('venues'), (array) $newvenuedb[$newvenue['process']['id']]);
    // Write the record.
    $write = drupal_write_record('eventbrite_api_venues', $record);
  }
  else {
    $values['vid'] = eventbrite_api_autocomplete_filter($values['vid']);
  }

  // Now save the event
  $newevent = array(
    'oid' => eventbrite_api_autocomplete_filter($values['oid']),
    'vid' => eventbrite_api_autocomplete_filter($values['vid']),
    'is_new' => TRUE,
    'timezone' => $values['date_default_timezone'],
    'capacity' => $values['tixcapacity'],
    'title' => $values['title'],
    'start_date' => _eventbrite_api_datef($values['start_date']),
    'status' => $values['status'],
    'description' => $values['description'],
    'end_date' => _eventbrite_api_datef($values['end_date']),
    'created' => date('Y-m-d H:i:00'),
    'modified' => date('Y-m-d H:i:00'),
  );

  if (empty($values['eid'])) {
    $eventobj = new eventBriteEvents();
    $newevent = $eventobj->eventNew($newevent);
    if (isset($newevent['error']) && isset($newevent['error']['error_message'])) {
      $error = $newevent['error']['error_type'] . ': ' . $newevent['error']['error_message'];
      drupal_set_message(t('We couldn\'t create the event: @error', array('@error' => $error)), 'error');
      return;
    }
  }
  else {
    $newevent['eid'] = $values['eid'];
    $eventobj = new eventBriteEvents($values['eid']);
    $newevent = $eventobj->eventUpdate($newevent);
    if (isset($newevent['error']) && isset($newevent['error']['error_message'])) {
      $error = $newevent['error']['error_type'] . ': ' . $newevent['error']['error_message'];
      drupal_set_message(t('We couldn\'t update the event: @error', array('@error' => $error)), 'error');
      return;
    }
    $num_deleted = db_delete('eventbrite_api_events')
      ->condition('eid', $newevent['process']['id'])
      ->execute();
  }

  $neweventdb = array();
  // Create a new event then save it to the drupal db
  _eventbrite_api_import_event($newevent['process']['id'], $neweventdb);
  $record = (object) array_merge((array) eventbrite_api_entity_prepare('events'), (array) $neweventdb[$newevent['process']['id']]);

  // Write the record.
  if ($write = drupal_write_record('eventbrite_api_events', $record)) {
    $newticketdb = array();
    // now add the tickets
    unset($values['forms']['add_ticket']);
    foreach ($values['forms'] as $ticket) {
      $newticketdb = array();
      // Save the new tickets and get the id
        $newticket = array(
          'event_id' => $newevent['process']['id'],
          'name' => $ticket['tixname'],
          'type' => $ticket['tixtype'],
          'description' => $ticket['tixdescription'],
          'start_date' => _eventbrite_api_datef($ticket['tixstart_date']),
          'end_date' => _eventbrite_api_datef($ticket['tixend_date']),
          'min' => $ticket['tixmin'],
          'max' => $ticket['tixmax'],
          'price' => $ticket['tixprice'],
          'visible' => !$ticket['tixvisible'],
          'currency' => $ticket['tixcurrency'],
          'quantity_available' => $ticket['tixquantity_available'],
          'is_new' => TRUE,
        );
      if (empty($values['eid'])) {
        $tixobj = new eventBriteTickets($newevent['process']['id']);
        $newticket = $tixobj->ticketNew($newticket);
        if (isset($newticket['error']) && isset($newticket['error']['error_message'])) {
          $error = $newticket['error']['error_type'] . ': ' . $newticket['error']['error_message'];
          drupal_set_message(t('We couldn\'t create the ticket: @error', array('@error' => $error)), 'error');
          return;
        }
      }
      else {
        $newticket['tid'] = $ticket['tid'];
        $tixobj = new eventBriteTickets($ticket['tid'], $newevent['process']['id']);
        $newticket = $tixobj->ticketUpdate($newticket);
        if (isset($newticket['error']) && isset($newticket['error']['error_message'])) {
          $error = $newticket['error']['error_type'] . ': ' . $newticket['error']['error_message'];
          drupal_set_message(t('We couldn\'t update the ticket: @error', array('@error' => $error)), 'error');
          return;
        }
        $num_deleted = db_delete('eventbrite_api_tickets')
          ->condition('tid', $ticket['tid'])
          ->execute();
      }

    }
    // Create a new ticket then save it to the drupal db
    _eventbrite_api_import_tickets($newevent['process']['id'], $newticketdb);
    foreach ($newticketdb as $record) {
      // Make sure all records have the correct keys.
      $record = (object) array_merge((array) eventbrite_api_entity_prepare('tickets'), (array) $record);
      // Write the record.
      $write = drupal_write_record('eventbrite_api_tickets', $record);
    }
  }

  if ($write) {
    drupal_set_message(t('Event !title saved to Eventbrite and cached locally.', array('!title' => '<em>' . check_plain($newevent['process']['id']['title']) . '</em>')));
    $form_state['redirect'] = 'admin/config/services/eventbrite/event';
  }
}

/**
 * Form API submit callback for the event delete button.
 */
function event_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/config/services/eventbrite/event/' . $form_state['eid'] . '/delete';
}

/**
 * Event delete form.
 */
function event_delete_form($form, &$form_state, $event) {
  $form_state['event'] = $event;

  $form['#submit'][] = 'event_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete event "@title"?', array('@title' => $event->title)),
    'admin/content/events/event',
    '<p>' . t('This will cancel the event on Eventbrite and delete it locally. This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for event_delete_form
 */
function event_delete_form_submit($form, &$form_state) {
  $event = $form_state['event'];
  eventBriteEvents::event_delete($event);
  drupal_set_message(t('The event %name has been deleted.', array('%name' => (!empty($event->name) ? $event->name : ''))));
  $form_state['redirect'] = 'admin/config/services/eventbrite/event';
}

/**
 * Submit callback for event_delete_form
 */
function organizer_delete_form_submit($form, &$form_state) {
  $organizer = $form_state['organizer'];
  organizer_delete($organizer);
  drupal_set_message(t('The organizer %name has been deleted.', array('%name' => $organizer->name)));
  $form_state['redirect'] = 'admin/config/services/eventbrite/organizer';
}

function event_add_wrapper() {
  $event = eventBriteEvents::event_create();
  return drupal_get_form('event_add_form', $event);
}

function event_edit_wrapper($event) {
  return drupal_get_form('event_add_form', $event);
}

function event_delete_wrapper($event) {
  return drupal_get_form('event_delete_form', $event);
}

/**
 * Organizer add form.
 */
function organizer_add_form($form, &$form_state, $organizer) {
  // Add the OID into the $form_state array.
  $form_state['oid'] = !empty($organizer->oid) ? $organizer->oid : '';

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Organizer name'),
    '#default_value' => isset($organizer->name) ? $organizer->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($organizer->description) ? $organizer->description : '',
  );

  $form['long_description'] = array(
    '#markup' => '<label>Long Description</label><p>' . (isset($organizer->long_description) ? $organizer->long_description : '') . '</p></br>',
  );

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('organizer_add_form_submit'),
  );
  $form['#validate'][] = 'organizer_add_form_validate';
  // Add the field related form elements.
  $form_state['organizer'] = $organizer;
  $form_state['oid'] = $organizer->oid;

  field_attach_form('organizer', $organizer, $form, $form_state);
  return $form;
}

/**
 * Validation function for event add form.
 */
function organizer_add_form_validate($form, &$form_state) {
  $organizer_submit = (object) $form_state['values'];
  field_attach_form_validate('event', $organizer_submit, $form, $form_state);
}

/**
 * Submit function for organizer add form.
 */
function organizer_add_form_submit($form, &$form_state) {
  $organizer_submit = (object) $form_state['values'];
  // Assign them to an array to send to Eventbrite.
  $eventbrite = $form_state['values'];

  // Add extra fields.
  field_attach_submit('organizer', $organizer_submit, $form, $form_state);

  // Should we update an existing organizer or add a new one?
  if (!empty($form_state['oid'])) {
    // Add the id with the correct key.
    $eventbrite['id'] = $form_state['oid'];
    $orgobj = new eventBriteOrganizer($form_state['oid']);
    $neworg = $orgobj->organiserUpdate($eventbrite);
    // If the event is updated.
    if (isset($neworg['error']) && isset($neworg['error']['error_message'])) {
      $error = $neworg['error']['error_type'] . ': ' . $neworg['error']['error_message'];
      drupal_set_message(t('We couldn\'t update the organizer: @error', array('@error' => $error)), 'error');
      return;
    }
    // Set the organizer entity values.
    $organizer = (object) array_merge((array) $form_state['organizer'], (array) $form_state['values']);
  }
  else {
    $orgobj = new eventBriteOrganizer();
    $neworg = $orgobj->organiserNew($eventbrite);
    if (isset($neworg['error']) && isset($neworg['error']['error_message'])) {
      $error = $neworg['error']['error_type'] . ': ' . $neworg['error']['error_message'];
      drupal_set_message(t('We couldn\'t create the organizer: @error', array('@error' => $error)), 'error');
      return;
    }
    // Set the organizer entity values.
    $organizer = (object) array_merge((array) $form_state['organizer'], (array) $form_state['values']);
    $organizer->oid = $neworg['process']['id'];
  }

  $save = eventBriteOrganizer::organizer_save($organizer);
  if (!empty($save)) {
    drupal_set_message(t('Organizer !name saved to Eventbrite and cached locally.', array('!name' => '<em>' . $organizer->name . '</em>')));
    $form_state['redirect'] = 'admin/config/services/eventbrite/organizer';
  }
}

/**
 * Form API submit callback for the organizer delete button.
 */
function organizer_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/config/services/eventbrite/organizer/' . $form_state['oid'] . '/delete';
}

/**
 * Organizer delete form.
 */
function organizer_delete_form($form, &$form_state, $organizer) {
  $form_state['organizer'] = $organizer;

  $form['#submit'][] = 'organizer_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete organizer "@name"?', array('@name' => $organizer->name)),
    'admin/content/events/event',
    '<p>' . t('This will delete the organizer on Eventbrite and delete it locally. This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

function organizer_add_wrapper() {
  $organizer = eventBriteOrganizer::organizer_create();
  return drupal_get_form('organizer_add_form', $organizer);
}

function organizer_edit_wrapper($organizer) {
  return drupal_get_form('organizer_add_form', $organizer);
}

function organizer_delete_wrapper($organizer) {
  return drupal_get_form('organizer_delete_form', $organizer);
}

/**
 * Ticket add form.
 */
function ticket_add_form($form, &$form_state, $ticket) {
  $functions = module_load_include('inc', 'eventbrite_api', 'includes/eventbrite_api.functions');
  // Ability to clone the ticket to another event.
  $arg = arg(5);
  if (empty($ticket->tid) && !empty($arg)) {
    $entity = entity_load('ticket', array($arg));
    if (!empty($entity)) {
      $ticket = array_shift($entity);
      // Get rid of the event and ticket IDs.
      $ticket->tid = $ticket->eid = '';
    }
  }
  // Add the TID into the $form_state array.
  $form_state['tid'] = $ticket->tid;

  $form['eid'] = array(
    '#type' => 'textfield',
    '#title' => t('Event'),
    '#description' => t('A ticket can only be associated with one event so once chosen, the associated event cannot be changed.'),
    '#default_value' => isset($ticket->eid) ? eventbrite_api_autocomplete_build($ticket->eid, 'event') : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  // If we're editing an event we can't edit the event ID.
  if (!empty($ticket->eid)) {
    $form['eid']['#disabled'] = TRUE;
  }
  // If it's not being edited, add autocomplete to the field.
  else {
    $form['eid']['#autocomplete_path'] = 'eventbrite/event/autocomplete';
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($ticket->name) ? $ticket->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array(
      0 => 'Fixed price',
      1 => 'Donation',
    ),
    '#default_value' => isset($ticket->type) ? $ticket->type : 0,
    '#required' => TRUE,
  );

  $form['min'] = array(
    '#type' => 'textfield',
    '#title' => t('Min'),
    '#description' => t('The minimum number of this ticket a person can purchase. The default is 1.'),
    '#default_value' => !empty($ticket->min) ? $ticket->min : 1,
    '#required' => TRUE,
    '#maxlength' => 255,
  );

  $form['max'] = array(
    '#type' => 'textfield',
    '#title' => t('Max'),
    '#description' => t('The maximum number of this ticket a person can purchase. This is optional and if left blank, the default will be whatever value is entered into the "Quantity available" field.'),
    '#default_value' => (!empty($ticket->max) ? $ticket->max : (isset($ticket->quantity_available) ? $ticket->quantity_available : '')),
    '#maxlength' => 255,
  );

  $form['price'] = array(
    '#type' => 'textfield',
    '#title' => t('Price'),
    '#default_value' => isset($ticket->price) ? $ticket->price : '',
  );

  $form['quantity_available'] = array(
    '#type' => 'textfield',
    '#title' => t('Quantity available'),
    '#description' => t('The number of this ticket available.'),
    '#default_value' => isset($ticket->quantity_available) ? $ticket->quantity_available : '',
  );

  $form['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#options' => _eventbrite_api_currencies(),
    '#default_value' => !empty($ticket->currency) ? $ticket->currency : variable_get('eventbrite_api_currency', 'USD'),
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($ticket->description) ? $ticket->description : '',
  );

  $form['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start date'),
    '#default_value' => isset($ticket->start_date) ? $ticket->start_date : '',
    '#required' => TRUE,
  );

  $form['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End date'),
    '#default_value' => isset($ticket->end_date) ? $ticket->end_date : '',
    '#required' => TRUE,
  );

  $form['include_fee'] = array(
    '#type' => 'select',
    '#title' => t('Include fee'),
    '#description' => t('Should the Eventbrite fee be added onto the ticket price or included as part of the ticket price.'),
    '#options' => array(
      0 => 'Add to ticket price',
      1 => 'Include in ticket price',
    ),
    '#default_value' => isset($ticket->include_fee) ? $ticket->include_fee : 0,
    '#required' => TRUE,
  );

  if (!empty($ticket->eid)) {
    $form['hide'] = array(
      '#type' => 'select',
      '#title' => t('Show or hide'),
      '#description' => t('Display this ticket on the Eventbrite booking page or hide it from view.'),
      '#options' => array(
        'n' => 'Show',
        'y' => 'Hide',
      ),
      '#default_value' => isset($ticket->hide) ? $ticket->hide : 'n',
      '#required' => TRUE,
    );
  }

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('ticket_add_form_submit'),
  );
  $form['#validate'][] = 'ticket_add_form_validate';
  // Add the field related form elements.
  $form_state['ticket'] = $ticket;
  $form_state['tid'] = $ticket->tid;

  field_attach_form('ticket', $ticket, $form, $form_state);
  return $form;
}

/**
 * Validation function for event add form.
 */
function ticket_add_form_validate($form, &$form_state) {
  $ticket_submit = (object) $form_state['values'];
  field_attach_form_validate('event', $ticket_submit, $form, $form_state);
}

/**
 * Submit function for ticket add form.
 */
function ticket_add_form_submit($form, &$form_state) {
  // Extract IDs from autocomplete fields.
  $form_state['values']['eid'] = eventbrite_api_autocomplete_filter($form_state['values']['eid']);

  $ticket_submit = (object) $form_state['values'];
  // Assign them to an array to send to Eventbrite.
  $eventbrite = $form_state['values'];

  // Add extra fields.
  field_attach_submit('ticket', $ticket_submit, $form, $form_state);

  $eventbrite['start_date'] = _eventbrite_api_datef($eventbrite['start_date']);
  $eventbrite['end_date'] = _eventbrite_api_datef($eventbrite['end_date']);
  if (empty($eventbrite['max'])) {
    $eventbrite['max'] = $eventbrite['quantity_available'];
  }

  // Should we update an existing ticket or add a new one?
  if (!empty($form_state['tid'])) {
    // Add the id with the correct key.
    $eventbrite['id'] = $form_state['tid'];
    $tixobj = new eventBriteTickets($form_state['tid']);
    $newtix = $tixobj->ticketUpdate($eventbrite);
    // If the event is updated.
    if (isset($newtix['error']) && isset($newtix['error']['error_message'])) {
      $error = $newtix['error']['error_type'] . ': ' . $newtix['error']['error_message'];
      drupal_set_message(t('We couldn\'t update the ticket: @error', array('@error' => $error)), 'error');
      return;
    }
  }
  else {
    $tixobj = new eventBriteTickets(NULL, $form_state['values']['eid']);
    $newtix = $tixobj->ticketNew($eventbrite);
    if (isset($newtix['error']) && isset($newtix['error']['error_message'])) {
      $error = $newtix['error']['error_type'] . ': ' . $newtix['error']['error_message'];
      drupal_set_message(t('We couldn\'t create the ticket: @error', array('@error' => $error)), 'error');
      return;
    }
    $form_state['tid'] = $newtix['process']['id'];
  }

  // Set the ticket entity values.
  // The ticket prices need to be pulled back from the event
  $eventobj = new eventBriteEvents($form_state['values']['eid']);
  $getEvent = $eventobj->eventGet(TRUE);
  foreach ($getEvent['event']['tickets'] as $curticket) {
    if ($curticket['ticket']['id'] == $form_state['tid']) {
      $ticket = $curticket['ticket'];
    }
  }

  //$save = eventBriteTickets::ticket_save($ticket);
  if (!empty($save)) {
    drupal_set_message(t('Ticket !name saved to Eventbrite and cached locally.', array('!name' => '<em>' . $ticket->name . '</em>')));
    $form_state['redirect'] = 'admin/config/services/eventbrite/ticket';
  }
}

/**
 * Ticket clone form.
 */
function ticket_clone_form($form, &$form_state, $ticket) {
  $form_state['ticket'] = $ticket;

  $form['#submit'][] = 'ticket_clone_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to clone ticket "@name"?', array('@name' => $ticket->name)),
    'admin/content/events/event',
    '<p>' . t('This will clone the ticket on Eventbrite and clone it locally.') . '</p>',
    t('Clone'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

function ticket_add_wrapper() {
  $ticket = eventBriteTickets::ticket_create();
  return drupal_get_form('ticket_add_form', $ticket);
}

function ticket_edit_wrapper($ticket) {
  return drupal_get_form('ticket_add_form', $ticket);
}

function ticket_delete_wrapper($ticket) {
  return drupal_get_form('ticket_delete_form', $ticket);
}

function ticket_clone_wrapper($ticket) {
  return drupal_get_form('ticket_clone_form', $ticket);
}

/**
 * Submit function for ticket clone form.
 */
function ticket_clone_form_submit($form, &$form_state) {
  // Assign them to an array to send to Eventbrite.
  $eventbrite = (array) $form_state['ticket'];
  // Ensure empty max field doesn't cause an error.
  if (empty($eventbrite['max'])) {
    $eventbrite['max'] = $eventbrite['quantity_available'];
  }
  // Connect to Eventbrite.
  if (($library = libraries_load('eventbrite')) && !empty($library['loaded'])) {
    $auth = array('app_key'  => variable_get('eventbrite_api_appkey', ''), 'user_key' => variable_get('eventbrite_api_userkey', ''));
    $eb_client = new Eventbrite($auth);
    try {
      // Add the event id.
      $eventbrite['event_id'] = $eventbrite['eid'];
      $response = $eb_client->ticket_new($eventbrite);
      // If the event is added.
      if ($response->process->status == 'OK') {
        // Ticket ID.
        $tid = $response->process->id;
        // We have to call the actual event to get the full ticket details.
        $response = $eb_client->event_get(array('id' => $eventbrite['eid']));
        // Get the list of tickets.
        $tickets = $response->event->tickets;
        // Add some IDs.
        $ticket = array('tid' => $tid, 'eid' => $eventbrite['eid']);
        // Find the ticket we just added.
        foreach ($tickets as $t) {
          if ($t->ticket->id == $tid) {
            $ticket = $ticket + (array) $t->ticket;
            break;
          }
        }
        // Set the ticket.
        $ticket = (object) array_merge((array) $form_state['ticket'], (array) $ticket);
      }
    }
    catch (Exception $e) {
      $response = $e->getMessage();
      form_set_error('form', $response);
    }
    // Save the entity.
    $save = ticket_save($ticket);
    if (!empty($save)) {
      drupal_set_message(t('Ticket !name saved to Eventbrite and cached locally.', array('!name' => '<em>' . $ticket->name . '</em>')));
      $form_state['redirect'] = 'admin/config/services/eventbrite/ticket';
    }
  }
  else {
    drupal_set_message(t('Please install the Eventbrite API library. Check the !readme for further information.', array('!readme' => l(t('README'), 'admin/help/eventbrite_api'))), 'error');
  }
}

/**
 * Venue add form.
 */
function venue_add_form($form, &$form_state, $venue) {
  $functions = module_load_include('inc', 'eventbrite_api', 'includes/eventbrite_api.functions');
  // Add the VID into the $form_state array.
  $form_state['vid'] = !empty($venue->vid) ? $venue->vid : '';

  // If we're editing an event we don't show the organizer ID.
  if (empty($venue->name)) {
    $form['oid'] = array(
      '#type' => 'textfield',
      '#title' => t('Organizer'),
      '#default_value' => isset($venue->oid) ? $venue->oid : '',
      '#maxlength' => 255,
      '#required' => TRUE,
      '#autocomplete_path' => 'eventbrite/organizer/autocomplete',
    );
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($venue->name) ? $venue->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#default_value' => isset($venue->address) ? $venue->address : '',
    '#maxlength' => 255,
  );

  $form['address_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
    '#default_value' => isset($venue->address_2) ? $venue->address_2 : '',
    '#maxlength' => 255,
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => isset($venue->city) ? $venue->city : '',
    '#maxlength' => 255,
  );

  $form['region'] = array(
    '#type' => 'textfield',
    '#title' => t('Region'),
    '#default_value' => isset($venue->region) ? $venue->region : '',
    '#maxlength' => 255,
    '#description' => t('Please note that if your event is in the US, this field is mandatory and requires a 2 digit US state code. You can find a list of US state codes at !url.', array('!url' => l('https://en.wikipedia.org/wiki/List_of_U.S._state_abbreviations', 'https://en.wikipedia.org/wiki/List_of_U.S._state_abbreviations'))),
  );

  $form['postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => isset($venue->postal_code) ? $venue->postal_code : '',
    '#maxlength' => 255,
  );

  $form['country_code'] = array(
    '#type' => 'select',
    '#title' => t('Country code'),
    '#default_value' => !empty($venue->country) ? $venue->country : variable_get('eventbrite_api_country_code', 'US'),
    '#options' => _eventbrite_api_countries(),
  );

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('venue_add_form_submit'),
  );

  $form['#validate'][] = 'venue_add_form_validate';
  // Add the field related form elements.
  $form_state['venue'] = $venue;
  $form_state['vid'] = $venue->vid;

  field_attach_form('venue', $venue, $form, $form_state);
  return $form;
}

/**
 * Validation function for event add form.
 */
function venue_add_form_validate($form, &$form_state) {
  $venue_submit = (object) $form_state['values'];
  field_attach_form_validate('event', $venue_submit, $form, $form_state);
}

/**
 * Submit function for venue add form.
 */
function venue_add_form_submit($form, &$form_state) {
  // Extract IDs from autocomplete fields.
  $form_state['values']['oid'] = eventbrite_api_autocomplete_filter($form_state['values']['oid']);
  $venue_submit = (object) $form_state['values'];
  // Assign them to an array to send to Eventbrite.
  $eventbrite = $form_state['values'];

  // The oid is organizer_id in the api
  $eventbrite['organizer_id'] = $form_state['values']['oid'];

  // Add extra fields.
  field_attach_submit('venue', $venue_submit, $form, $form_state);

  // Should we update an existing venue or add a new one?
  if (!empty($form_state['vid'])) {
    // Add the id with the correct key.
    $eventbrite['id'] = $form_state['vid'];
    $venueobj = new eventBriteVenues($form_state['vid']);
    $newvenue = $venueobj->venueUpdate($eventbrite);
    // If the event is updated.
    if (isset($newvenue['error']) && isset($newvenue['error']['error_message'])) {
      $error = $newvenue['error']['error_type'] . ': ' . $newvenue['error']['error_message'];
      drupal_set_message(t('We couldn\'t update the venue: @error', array('@error' => $error)), 'error');
      return;
    }
  }
  else {
    $venueobj = new eventBriteVenues();
    $newvenue = $venueobj->venueNew($eventbrite);
    if (isset($newvenue['error']) && isset($newvenue['error']['error_message'])) {
      $error = $newvenue['error']['error_type'] . ': ' . $newvenue['error']['error_message'];
      drupal_set_message(t('We couldn\'t create the venue: @error', array('@error' => $error)), 'error');
      return;
    }
    $form_state['vid'] = $newvenue['process']['id'];
  }

  // Set the venue entity values.
  // The venue needs to be pulled back from eventbrite with the long / lat
  $venueobj->set_venueID($form_state['vid']);
  $getvenue = $venueobj->venueGet(TRUE);
  $venue = $getvenue['venue'][0];

  $save = eventBriteVenues::venue_save($venue);
  if (!empty($save)) {
    drupal_set_message(t('Organizer !name saved to Eventbrite and cached locally.', array('!name' => '<em>' . $venue->name . '</em>')));
    $form_state['redirect'] = 'admin/config/services/eventbrite/venue';
  }
}

/**
 * Form API submit callback for the venue delete button.
 */
function venue_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/config/services/eventbrite/venue/' . $form_state['vid'] . '/delete';
}

/**
 * Organizer delete form.
 */
function venue_delete_form($form, &$form_state, $venue) {
  $form_state['venue'] = $venue;

  $form['#submit'][] = 'venue_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete venue "@name"?', array('@name' => $venue->name)),
    'admin/content/events/event',
    '<p>' . t('This will delete the venue on Eventbrite and delete it locally. This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

function venue_add_wrapper() {
  $venue = eventBriteVenues::venue_create();
  return drupal_get_form('venue_add_form', $venue);
}

function venue_edit_wrapper($venue) {
  return drupal_get_form('venue_add_form', $venue);
}

function venue_delete_wrapper($venue) {
  return drupal_get_form('venue_delete_form', $venue);
}
