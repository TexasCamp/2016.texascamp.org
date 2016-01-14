<?php
/**
 * @file
 * common.inc
 *
 * Contains common functionality for the entire Project theme.
 */

/**
 * Helper function for including theme files.
 *
 * @param string $theme
 *   Name of the theme to use for base path.
 * @param string $path
 *   Path relative to $theme.
 */
function project_include($theme, $path) {
  static $themes = array();
  if (!isset($themes[$theme])) {
    $themes[$theme] = drupal_get_path('theme', $theme);
  }
  if ($themes[$theme] && ($file = DRUPAL_ROOT . '/' . $themes[$theme] . '/' . $path) && file_exists($file)) {
    include_once $file;
  }
}

/**
 * Theme a Bootstrap Glyphicon.
 *
 * @param string $name
 *   The icon name, minus the "glyphicon-" prefix.
 *
 * @return string
 *   The icon HTML markup.
 */
function _project_icon($name) {
  // Mimic the Icon API markup.
  $attributes = array(
    'class' => array('glyphicon', 'glyphicon-' . $name),
    'aria-hidden' => 'true',
  );
  
  return $output = '<i' . drupal_attributes($attributes) . '></i>';
}

/**
 * Colorize buttons based on the text value.
 *
 * @param string $text
 *   Button text to search against.
 *
 * @return string
 *   The specific button class to use or FALSE if not matched.
 */
function _project_colorize_button($text) {
  // Text values containing these specific strings, which are matched first.
  $specific_strings = array(
    'btn-primary' => array(
      t('Download feature'),
    ),
    'btn-success' => array(
      t('Add effect'),
      t('Add and configure'),
    ),
    'btn-info' => array(
      t('Save and add'),
      t('Add another item'),
      t('Update style'),
    ),
  );
  // Text values containing these generic strings, which are matches last.
  $generic_strings = array(
    'btn-primary' => array(
      t('Save'),
      t('Confirm'),
      t('Submit'),
      t('Search'),
    ),
    'btn-success' => array(
      t('Add'),
      t('Create'),
      t('Write'),
    ),
    'btn-warning' => array(
      t('Export'),
      t('Import'),
      t('Restore'),
      t('Rebuild'),
    ),
    'btn-info' => array(
      t('Apply'),
      t('Update'),
      t('Manage'),
    ),
    'btn-danger' => array(
      t('Delete'),
      t('Remove'),
    ),
  );
  // Specific matching first.
  foreach ($specific_strings as $class => $strings) {
    foreach ($strings as $string) {
      if (strpos(drupal_strtolower($text), drupal_strtolower($string)) !== FALSE) {
        return $class;
      }
    }
  }
  // Generic matching last.
  foreach ($generic_strings as $class => $strings) {
    foreach ($strings as $string) {
      if (strpos(drupal_strtolower($text), drupal_strtolower($string)) !== FALSE) {
        return $class;
      }
    }
  }
  return FALSE;
}

/**
 * Iconize buttons based on the text value.
 *
 * @param string $text
 *   Button text to search against.
 *
 * @return string
 *   The icon markup or FALSE if not matched.
 */
function _project_iconize_button($text) {
  // Text values containing these specific strings, which are matched first.
  $specific_strings = array();
  // Text values containing these generic strings, which are matches last.
  $generic_strings = array(
    'cog' => array(
      t('Manage'),
      t('Configure'),
    ),
    'download' => array(
      t('Download'),
    ),
    'export' => array(
      t('Export'),
    ),
    'import' => array(
      t('Import'),
    ),
    'pencil' => array(
      t('Edit'),
    ),
    'plus' => array(
      t('Add'),
      t('Write'),
    ),
    'trash' => array(
      t('Delete'),
      t('Remove'),
    ),
    'upload' => array(
      t('Upload'),
    ),
  );
  // Specific matching first.
  foreach ($specific_strings as $icon => $strings) {
    foreach ($strings as $string) {
      if (strpos(drupal_strtolower($text), drupal_strtolower($string)) !== FALSE) {
        return _project_icon($icon);
      }
    }
  }
  // Generic matching last.
  foreach ($generic_strings as $icon => $strings) {
    foreach ($strings as $string) {
      if (strpos(drupal_strtolower($text), drupal_strtolower($string)) !== FALSE) {
        return _project_icon($icon);
      }
    }
  }
  return FALSE;
}
