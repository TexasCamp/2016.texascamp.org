<?php

/**
 * @file
 *   drush integration for stellarjs.
 */

/**
 * The stellarjs plugin URI.
 */
define('STELLARJS_DOWNLOAD_URI', 'https://github.com/markdalgleish/stellar.js/archive/master.zip');
define('STELLARJS_UNZIP_PREFIX', 'stellar.js-');

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function stellarjs_drush_command() {
  $items = array();

  // the key in the $items array is the name of the command.
  $items['install-stellarjs'] = array(
    'callback' => 'drush_stellarjs_install',
    'description' => dt('Download and install the Stellar.js library.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap.
    'arguments' => array(
      'path' => dt('Optional. A path where to install the stellarjs plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('stellarjsplugin'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function stellarjs_drush_help($section) {
  switch ($section) {
    case 'drush:install-stellarjs':
      return dt('Download and install the stellarjs plugin from markdalgleish.com/projects/stellar.js, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the stellarjs plugin.
 */
function drush_stellarjs_install() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive
  if ($filepath = drush_download_file(STELLARJS_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = basename($filepath, '.zip');
    $unzipname = STELLARJS_UNZIP_PREFIX . basename($filepath, '.zip');
    
    // Remove any existing stellarjs plugin directory
    if (is_dir($dirname) || is_dir('stellarjs')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir($unzipname, TRUE);
      drush_delete_dir('stellarjs', TRUE);
      drush_log(dt('A existing stellarjs plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive
    drush_tarball_extract($filename);

    // Change the directory name to "stellarjs" if needed.
    if ($dirname != 'stellarjs' || $unzipname != 'stellarjs' ) {
      drush_move_dir($dirname, 'stellarjs', TRUE);
      drush_move_dir($unzipname, 'stellarjs', TRUE);
      $dirname = 'stellarjs';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('stellarjs plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the stellarjs plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}
