<?php

/**
 * @file
 * Contains the theme function override for 'textarea'.
 */

/**
 * Implements theme_textarea().
 */
function md_leaders_textarea($variables) {
  $element = $variables['element'];
  $element['#attributes'] = array('placeholder' => $element['#title']);
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-control'));

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    $wrapper_attributes['class'][] = 'resizable';
    $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
    $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
    $output .= '</div>';
    return $output;
  }
  else {
    $output = '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
    return $output;
  }
}
