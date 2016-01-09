<?php

/**
 * @file
 * Webform module Mailchimp component.
 */

/**
 * Implementation of _webform_defaults_component().
 */
function _webform_defaults_mailchimp() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(
      'title_display' => 0,
      'field_prefix' => '',
      'field_suffix' => '',
      'description' => '',
      'attributes' => array(),
      'mailchimp_list' => '',
      'use_existing_email_field' => '',
      'private' => FALSE,
    ),
  );
}

/**
 * Implementation of _webform_theme_component().
 */
function _webform_theme_mailchimp() {
  return array(
    'webform_display_mailchimp' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * Implementation of _webform_edit_component().
 */
function _webform_edit_mailchimp($component) {
  drupal_add_js(drupal_get_path('module', 'webform_mailchimp') . '/webform_mailchimp.js');

  $node = node_load($component['nid']);
  $form = array();

  $options = array('none' => 'Select list');
  $q = mailchimp_get_api_object();
  if ($q) {
    $lists = mailchimp_get_lists();
    if (!empty($lists)) {
      foreach ($lists as $key => $list) {
        $options[$list['id']] = $list['name'];
      }
    }
    else {
      drupal_set_message(t('You do not have any Mailchimp lists defined.'), 'error');
    }
  }
  else {
    drupal_set_message(t('Could not get valid Mailchimp API object'), 'error');
  }

  $form['extra']['mailchimp_list'] = array(
    '#type' => 'select',
    '#title' => t('Choose list'),
    '#default_value' => !empty($component['extra']['mailchimp_list']) ? $component['extra']['mailchimp_list'] : 0,
    '#description' => t('Choose which list that the user can subscribe to.'),
    '#options' => $options,
    '#element_validate' => array('_webform_mailchimp_list_validate'),
  );

  $form['user_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('User email as default'),
    '#default_value' => $component['value'] == '%useremail' ? 1 : 0,
    '#description' => t('Set the default value of this field to the user email, if he/she is logged in.'),
    '#weight' => 0,
    '#element_validate' => array('_webform_mailchimp_user_email_validate'),
  );

  $options = array('mailchimp_field' => 'Create field');

  // Fetches existing components, checks if any of them are e-mail fields.
  // Let's the user choose which field to use for the newsletter e-mail address.
  if (!empty($node->webform['components'])) {
    foreach ($node->webform['components'] AS $field) {
      if ($field['type'] == 'email') {
        $options[$field['form_key']] = $field['name'];
      }
    }
  }

  $form['extra']['use_existing_email_field'] = array(
    '#type' => 'select',
    '#title' => t('Select an existing e-mail field, or create one'),
    '#default_value' => !empty($component['extra']['use_existing_email_field']) ? $component['extra']['use_existing_email_field'] : 'create',
    '#description' => t('If you select an existing email field, that fields input will be used. If not, a field will be shown to the user.'),
    '#weight' => 1,
    '#options' => $options,
  );

  $form['extra']['checkbox_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Checkbox label'),
    '#default_value' => !empty($component['extra']['checkbox_label']) ? $component['extra']['checkbox_label'] : t('Subscribe to newsletter'),
    '#description' => t('If using an existing field you can edit the default label that\'s printed here.'),
    '#weight' => 2,
    '#prefix' => '<div id="field_settings" style="display:none;">',
  );

  $form['extra']['checkbox_checked_by_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Checked by default.'),
    '#description' => t('If using an existing field, make the checkbox checked by default.'),
    '#default_value' => !empty($component['extra']['checkbox_checked_by_default']) ? $component['extra']['checkbox_checked_by_default'] : 0,
    '#weight' => 3,
  );

  $form['extra']['checkbox_hidden'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the checkbox.'),
    '#description' => t('Check this if users do not need to be able to set or unset wether they want to subscribe. Note that you still need to check wether the checkbox should be checked by default.'),
    '#default_value' => !empty($component['extra']['checkbox_hidden']) ? $component['extra']['checkbox_hidden'] : 0,
    '#weight' => 4,
    '#suffix' => '</div>',
  );

  $form['extra']['mergefields'] = array(
    '#type' => 'textarea',
    '#title' => t('Mailchimp merge fields'),
    '#description' => t('Enter one key|value pair per line. Use the MailChimp field tag as the key and the webform field key as the value. For example "FNAME|firstname"'),
    '#default_value' => !empty($component['extra']['mergefields']) ? $component['extra']['mergefields'] : '',
    '#weight' => 5,
  );

  $form['extra']['interestfields'] = array(
    '#type' => 'textarea',
    '#title' => t('Mailchimp interests fields'),
    '#description' => t('Enter one key|value pair per line. Use the MailChimp group name as the key and the webform field (checkboxes or dropdown) key as the value. For example "FOOD|types_of_food_you_like"'),
    '#default_value' => !empty($component['extra']['interestfields']) ? $component['extra']['interestfields'] : '',
    '#weight' => 6,
  );

  return $form;
}

/**
 * Validation function for the email edit form.
 */
function _webform_mailchimp_user_email_validate($element, &$form_state) {
  if ($form_state['values']['user_email']) {
    $form_state['values']['value'] = '%useremail';
  }
}

function _webform_mailchimp_list_validate($element, &$form_state) {
  if ($form_state['values']['extra']['mailchimp_list'] == 'none') {
    form_error($element, t('You need to select a Mailchimp list.'));
  }
}

/**
 * Implementation of _webform_render_component().
 */
function _webform_render_mailchimp($component, $value = NULL, $filter = TRUE) {
  if ($value[0]) {
    $default_value = $value[0];
  }
  else {
    $default_value = _webform_filter_values($component['value']);
  }

  $element = array();

  // Creates a field if the user hasn't chosen another email field.
  if ($component['extra']['use_existing_email_field'] == 'mailchimp_field') {
    $element['mailchimp_email_address'] = array(
      '#type'              => 'textfield',
      '#title'             => $filter ? _webform_filter_xss($component['name']) : $component['name'],
      '#title_display'     => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
      '#required'          => $component['mandatory'],
      '#description'       => $filter ? _webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
      '#default_value'     => _webform_filter_values($component['value']),
      '#theme_wrappers'    => array('webform_element'),
      '#webform_component' => $component,
      '#weight'            => $component['weight'],
    );
  }
  else {
    // Creates a checkbox to subscribe, or a hidden form element if configured
    if ($component['extra']['checkbox_hidden'] == 1) {
      $element['mailchimp_signup'] = array(
        '#type'              => 'hidden',
        '#default_value'     => !empty($component['extra']['checkbox_checked_by_default']) ? $component['extra']['checkbox_checked_by_default'] : 0,
      );
    }
    else {
      $element['mailchimp_signup'] = array(
        '#type'              => 'checkbox',
        '#title'             => !empty($component['extra']['checkbox_label']) ? _webform_filter_xss($component['extra']['checkbox_label']) : t('Subscribe to newsletter'),
        '#default_value'     => !empty($component['extra']['checkbox_checked_by_default']) ? $component['extra']['checkbox_checked_by_default'] : 0,
        '#description'       => $filter ? _webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
        '#theme_wrappers'    => array('webform_element'),
        '#webform_component' => $component,
        '#weight'            => $component['weight'],
      );
    }
  }

  $mailchimp_list = $component['extra']['mailchimp_list'];
  $element['mailchimp_list'] = array(
    '#prefix' => '',
    '#type' => 'value',
    '#value' => $mailchimp_list,
  );

  $element['#weight'] = $component['weight'];
  return $element;
}

/**
 * A Drupal Forms API Validation function. Validates the entered values from
 * email components on the client-side form.
 * @param $form_element
 *   The e-mail form element.
 * @param $form_state
 *   The full form state for the webform.
 * @return
 *   None. Calls a form_set_error if the e-mail is not valid.
 */
function _webform_validate_mailchimp_email($form_element, $form_state) {
  $component = $form_element['#webform_component'];
  if (!empty($form_element['mailchimp_email_address']['#value']) && !valid_email_address($form_element['mailchimp_email_address']['#value'])) {
    form_error($form_element, t('%value is not a valid email address.', array('%value' => $form_element['mailchimp_email_address']['#value'])));
  }
  elseif (empty($form_element['mailchimp_email_address']['#value']) && $form_element['#required']) {
    form_error($form_element, t('E-mail address for newsletter "%name" is required.', array('%name' => $component['name'])));
  }
}

/**
 * Implementation of _webform_display_component().
 */
function _webform_display_mailchimp($component, $value, $format = 'html') {
  return array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_mailchimp',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#format' => $format,
    '#value' => isset($value[0]) ? $value[0] : '',
    '#webform_component' => $component,
  );
}

/**
 * Format the output of data for this component.
 */
function theme_webform_display_mailchimp($variables) {
  $element = $variables['element'];
  $element['#value'] = empty($element['#value']) ? ' ' : $element['#value'];
  return $element['#format'] == 'html' ? check_plain($element['#value']) : $element['#value'];
}

/**
 * Implementation of _webform_submit_component().
 */
function _webform_submit_mailchimp($component, $value) {
  $return_val = NULL;

  if (!empty($value['mailchimp_signup'])){
    $return_val = array(0 => $value['mailchimp_signup']);
  }

  if (!empty($value['mailchimp_signup'])){
    $return_val = array(0 => $value['mailchimp_signup']);
  }
  if (!empty($value['mailchimp_email_address'])) {
    $return_val = array(0 => $value['mailchimp_email_address']);
  }

  return $return_val;
}

/**
 * Implementation of _webform_analysis_component().
 */
function _webform_analysis_mailchimp($component, $sids = array()) {
  $query = db_select('webform_submitted_data', 'wsd', array('fetch' => PDO::FETCH_ASSOC))
    ->fields('wsd', array('data'))
    ->condition('nid', $component['nid'])
    ->condition('cid', $component['cid']);

  if (count($sids)) {
    $query->condition('sid', $sids, 'IN');
  }

  $nonblanks = 0;
  $submissions = 0;
  $wordcount = 0;

  $result = $query->execute();
  foreach ($result as $data) {
    if (drupal_strlen(trim($data['data'])) > 0) {
      $nonblanks++;
      $wordcount += str_word_count(trim($data['data']));
    }
    $submissions++;
  }

  $rows[0] = array(t('Left Blank'), ($submissions - $nonblanks));
  $rows[1] = array(t('User entered value'), $nonblanks);
  $rows[2] = array(t('Average submission length in words (ex blanks)'), ($nonblanks != 0 ? number_format($wordcount/$nonblanks, 2) : '0'));
  return $rows;
}

/**
 * Implementation of _webform_table_component().
 */
function _webform_table_mailchimp($component, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}

/**
 * Implementation of _webform_csv_headers_component().
 */
function _webform_csv_headers_mailchimp($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $component['name'];
  return $header;
}

/**
 * Implementation of _webform_csv_data_component().
 */
function _webform_csv_data_mailchimp($component, $export_options, $value) {
  return !isset($value[0]) ? '' : $value[0];
}
