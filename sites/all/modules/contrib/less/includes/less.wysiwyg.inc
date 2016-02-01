<?php

/**
 * @file
 * Contains functions that handle WYSIWYG module integration.
 */

/**
 * Implements hook_wysiwyg_editor_settings_alter().
 *
 * Check the CSS WYSIWYG setting for LESS files and replace with
 * generated CSS files where necessary.
 */
function less_wysiwyg_editor_settings_alter(&$settings, $context) {

  $wysiwyg = $context['editor']['name'];

  // Each editor has a different $settings array key for CSS files.
  $editors = array(
    'tinymce' => 'content_css',
    'fckeditor' => 'EditorAreaCSS',
    'ckeditor' => 'contentsCss',
  );

  if (!empty($editors[$wysiwyg]) && !empty($settings[$editors[$wysiwyg]])) {

    $stylesheets = $settings[$editors[$wysiwyg]];

    // Keep track if comma separated paths, or array of paths.
    $is_array = is_array($stylesheets);

    // $stylesheets is an array or comma separated list of file paths.
    $stylesheets = $is_array ? $stylesheets : explode(',', $stylesheets);

    // Create a 'value => value' array to preserve original stylesheet order.
    $stylesheets = drupal_map_assoc($stylesheets);

    // Do not attempt to process remote or regular CSS files.
    $local_stylesheets = array_filter(array_map('parse_url', $stylesheets), function ($value) {
      return empty($value['host']) && preg_match('/.*\.less$/i', $value['path']) == 1;
    });

    // Prepare an array that can be handled by normal LESS module processing.
    $items = array_map(function ($stylesheet) {
      return array(
        'data' => trim($stylesheet['path'], '/'),
      );
    }, $local_stylesheets);

    $processed_styles = _less_pre_render(array('#items' => $items));

    // Compiled path is in 'data' index of each sheet item.
    $compiled_sheets = array_map(function ($value) { return $value['data']; }, $processed_styles['#items']);

    // WYSIWYGs can't handle Drupal public:// paths, so get an accessible URL.
    $compiled_sheets = array_map('file_create_url', $compiled_sheets);

    // Replace paths to compiled output paths based on key (path) of original file.
    $processed_stylesheets = array_replace($stylesheets, $compiled_sheets);

    // Need a integer indexed array so JSON encoding doesn't attempt to make a object.
    $processed_stylesheets = array_values($processed_stylesheets);

    // Recombine file paths into comma separated list.
    $processed_stylesheets = $is_array ? $processed_stylesheets : implode(',', $processed_stylesheets);

    $settings[$editors[$wysiwyg]] = $processed_stylesheets;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * form_id = 'wysiwyg_profile'
 */
function less_form_wysiwyg_profile_form_alter(&$form, $form_state, $form_id) {
  $form['css']['css_path']['#description'] .= '<br />' . t('You may enter a path to a LESS file and it will be parsed automatically.');
}

/**
 * Implements hook_ckeditor_settings_alter().
 */
function less_ckeditor_settings_alter(&$settings) {

  $context = array(
    'editor' => array(
      'name' => 'ckeditor',
    ),
  );

  less_wysiwyg_editor_settings_alter($settings, $context);
}
