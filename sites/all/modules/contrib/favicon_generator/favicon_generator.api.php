<?php
/**
 * @file
 * Hooks provided by Favicon Generator.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Add sub-module fields to admin UI.
 *
 * @return array
 *   A Form API array containing the form elements of the sub-module.
 */
function hook_favicon_generator_admin() {
  return array();
}

/**
 * Create the RFG sub-spec for the platform.
 *
 * @param array $settings
 *   An array of global settting.
 *   Includes color and margin.
 *
 * @return array
 *   A nest array of the settings required by RFG.
 */
function hook_favicon_generator_spec(array $settings) {
  return array(
    'platform' => array(
      'setting1' => 'xxx',
    ),
  );
}

/**
 * Get the minimum size for the icon file in px.
 *
 * @return int
 *   The minimum size for the icon file.
 */
function hook_favicon_generator_min_size() {
  return 80;
}

/**
 * Get the recommended minimum size for the icon file in px.
 *
 * @return int
 *   The recommended size for the icon file.
 */
function hook_favicon_generator_rec_size() {
  return 260;
}

/**
 * @} End of "addtogroup hooks".
 */
