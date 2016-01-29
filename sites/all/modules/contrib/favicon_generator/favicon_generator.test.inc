<?php
/**
 * @file
 * Favicon generator testing functions.
 *
 * These will not be available unless this file is included and should not be
 * included on a live site.
 *
 * To use:
 * Place in the top of favicon_generator.module
 * <code>include_once DRUPAL_ROOT . '/' . drupal_get_path('module',
 * 'favicon_generator') . "/favicon_generator.test.inc";</code>
 * In favicon_generator_menu(), before the return:
 * <code>$items = array_merge($items, favicon_generator_test_menu());</code>
 * Change drupal_http_request in _favicon_generator_download_and_save_icons() to
 * <code>'http://localhost/api/favicon', </code>
 *
 * NOTE: This file will be removed. Do not depend on it.
 */

/**
 * Creates testing url.
 *
 * Using for testing other functions. Should not be accessible on live sites.
 */
function favicon_generator_test_menu() {
  $items = array();

  $items['api/favicon'] = array(
    'title' => 'favicon_generator',
    'page callback' => 'favicon_generator_json_return',
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );

  return $items;
}

/**
 * Callback for testing url.
 */
function favicon_generator_json_return() {
  $r = json_decode('{"favicon_generation_result":{"result":{"status":"success","error_message":"Invalid API key"},"favicon":{"package_url":"http:\/\/localhost\/favicons.zip","html_code":"<link rel=\"shortcut icon\" href=\"\/sites\/default\/files\/favicon\/favicon.ico\">\n<link rel=\"apple-touch-icon\" sizes=\"57x57\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-57x57.png\">\n<link rel=\"apple-touch-icon\" sizes=\"114x114\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-114x114.png\">\n<link rel=\"apple-touch-icon\" sizes=\"72x72\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-72x72.png\">\n<link rel=\"apple-touch-icon\" sizes=\"144x144\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-144x144.png\">\n<link rel=\"apple-touch-icon\" sizes=\"60x60\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-60x60.png\">\n<link rel=\"apple-touch-icon\" sizes=\"120x120\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-120x120.png\">\n<link rel=\"apple-touch-icon\" sizes=\"76x76\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-76x76.png\">\n<link rel=\"apple-touch-icon\" sizes=\"152x152\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-152x152.png\">\n<link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"\/sites\/default\/files\/favicon\/apple-touch-icon-180x180.png\">\n<link rel=\"icon\" type=\"image\/png\" href=\"\/sites\/default\/files\/favicon\/favicon-192x192.png\" sizes=\"192x192\">\n<link rel=\"icon\" type=\"image\/png\" href=\"\/sites\/default\/files\/favicon\/favicon-160x160.png\" sizes=\"160x160\">\n<link rel=\"icon\" type=\"image\/png\" href=\"\/sites\/default\/files\/favicon\/favicon-96x96.png\" sizes=\"96x96\">\n<link rel=\"icon\" type=\"image\/png\" href=\"\/sites\/default\/files\/favicon\/favicon-16x16.png\" sizes=\"16x16\">\n<link rel=\"icon\" type=\"image\/png\" href=\"\/sites\/default\/files\/favicon\/favicon-32x32.png\" sizes=\"32x32\">\n<meta name=\"msapplication-TileColor\" content=\"#00aba9\">\n<meta name=\"msapplication-TileImage\" content=\"\/sites\/default\/files\/favicon\/mstile-144x144.png\">\n<meta name=\"msapplication-config\" content=\"\/sites\/default\/files\/favicon\/browserconfig.xml\">\n<link rel=\"manifest\" href=\"\/sites\/default\/files\/favicon\/android_chrome_manifest.json\">","compression":"true"},"files_location":{"type":"path","path":"\/sites\/default\/files\/favicon"},"preview_picture_url":"http:\/\/localhost\/favicon_preview.png","versions":"0.9"}}');
  drupal_json_output($r);
}
