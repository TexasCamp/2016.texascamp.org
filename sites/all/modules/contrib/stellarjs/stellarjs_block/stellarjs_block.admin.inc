<?php

/**
 * @file
 * Admin page callbacks for the StellarJS Block module.
 */

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function stellarjs_block_admin_settings_form() {
  $form['stellarjs_block_image_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Stelalr block image directory'),
    '#description' => t('Subdirectory in the file upload directory where images will be stored.'),
    '#default_value' => variable_get('stellarjs_block_image_path', 'stellarjs_block'),
    '#maxlength' => 255,
  );
  $form['stellarjs_block_max_file_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum file size'),
    '#description' => t('Specify the size limit that applies to each image. Enter a value like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes) in order to restrict the allowed file size. If you leave this empty the file sizes will be limited only by PHP\'s maximum post and file upload sizes (current limit <strong>%limit</strong>).', array('%limit' => format_size(file_upload_max_size()))),
    '#default_value' => variable_get('stellarjs_block_max_file_size', 0),
    '#maxlength' => 15,
  );
  $form['stellarjs_block_max_dimensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum dimensions'),
    '#description' => t('The maximum allowed image size expressed as WIDTHxHEIGHT (e.g. 640x480). Set to 0 for no restriction. If a larger image is uploaded, it will be resized to reflect the given width and height.'),
    '#default_value' => variable_get('stellarjs_block_max_dimensions', 0),
    '#maxlength' => 15,
  );
  return system_settings_form($form);
}

/**
 * Implements hook_admin_settings_form_validate().
 */
function stellarjs_block_admin_settings_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  foreach (array('stellarjs_block_max_file_size') as $size) {
    if (!empty($values[$size]) && !is_numeric(parse_size($values[$size]))) {
      form_error($size, t('The "@field" option must contain a valid value. You can either leave the text field empty or enter a string like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes).', array('@field' => t('Maximum upload size per file'))));
    }
  }
  foreach (array('stellarjs_block_max_dimensions') as $resolution) {
    if (!empty($values[$resolution]) && !preg_match('/^[0-9]+x[0-9]+$/', $values[$resolution])) {
      form_set_error($resolution, t('Please specify a resolution in the format WIDTHxHEIGHT (e.g. 640x480).'));
    }
  }
}

/**
 * Form constructor for the add block form.
 *
 * @see stellarjs_block_configure_form_validate()
 * @see stellarjs_block_add_block_form_submit()
 * @ingroup forms
 */
function stellarjs_block_add_block_form() {
  module_load_include('inc', 'block', 'block.admin');
  $form = block_admin_configure($form = array(), $form_state, 'stellarjs_block', NULL);

  // Other modules should be able to use hook_form_block_add_block_form_alter()
  // to modify this form, so add a base form ID.
  $form_state['build_info']['base_form_id'] = 'block_add_block_form';

  // Prevent block_add_block_form_validate/submit() from being automatically
  // added because of the base form ID by providing these handlers manually.
  $form['#validate'] = array('stellarjs_block_add_block_form_validate');
  $form['#submit'] = array('stellarjs_block_add_block_form_submit');
  return $form;
}

/**
 * Form validate handler for the add Stellar block form.
 *
 * @see stellarjs_block_add_block_form()
 * @see stellarjs_block_add_block_form_submit()
 */
function stellarjs_block_add_block_form_validate($form, &$form_state) {
  $custom_block_exists = (bool) db_query_range('SELECT 1 FROM {stellarjs_block} WHERE info = :info', 0, 1, array(':info' => $form_state['values']['info']))->fetchField();

  if (empty($form_state['values']['info']) || $custom_block_exists) {
    form_set_error('info', t('Ensure that each block description is unique.'));
  }
}

/**
 * Form submission handler for stellarjs_block_add_block_form().
 *
 * Saves the new custom StellarJS block.
 *
 * @see stellarjs_block_add_block_form()
 * @see stellarjs_block_add_block_form_validate()
 */
function stellarjs_block_add_block_form_submit($form, &$form_state) {
  // Save the block configuration.
  $delta = db_insert('stellarjs_block')
    ->fields(array(
      'body' => $form_state['values']['body']['value'],
      'info' => $form_state['values']['info'],
      'format' => $form_state['values']['body']['format'],
    ))
    ->execute();

  // Store block delta to allow other modules to work with new block.
  $form_state['values']['delta'] = $delta;

  // Run the normal new block submission (borrowed from block_add_block_form_submit).
  $query = db_insert('block')->fields(array('visibility', 'pages', 'custom', 'title', 'module', 'theme', 'status', 'weight', 'delta', 'cache'));
  foreach (list_themes() as $key => $theme) {
    if ($theme->status) {
      $query->values(array(
        'visibility' => (int) $form_state['values']['visibility'],
        'pages' => trim($form_state['values']['pages']),
        'custom' => (int) $form_state['values']['custom'],
        'title' => $form_state['values']['title'],
        'module' => $form_state['values']['module'],
        'theme' => $theme->name,
        'status' => 0,
        'weight' => 0,
        'delta' => $delta,
        'cache' => DRUPAL_NO_CACHE,
      ));
    }
  }
  $query->execute();

  $query = db_insert('block_role')->fields(array('rid', 'module', 'delta'));
  foreach (array_filter($form_state['values']['roles']) as $rid) {
    $query->values(array(
      'rid' => $rid,
      'module' => $form_state['values']['module'],
      'delta' => $delta,
    ));
  }
  $query->execute();

  // Store regions per theme for this block.
  foreach ($form_state['values']['regions'] as $theme => $region) {
    db_merge('block')
      ->key(array('theme' => $theme, 'delta' => $delta, 'module' => $form_state['values']['module']))
      ->fields(array(
        'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
        'pages' => trim($form_state['values']['pages']),
        'status' => (int) ($region != BLOCK_REGION_NONE),
      ))
      ->execute();
  }

  drupal_set_message(t('Stellar block has been created.'));
  cache_clear_all();
  $form_state['redirect'] = 'admin/structure/block';
}


/**
 * Form constructor for the custom stellarjs_block block deletion form.
 *
 * @param $delta
 *   The unique ID of the block within the context of $module.
 *
 * @see stellarjs_block_delete_submit()
 */
function stellarjs_block_delete($form, &$form_state, $delta) {
  $block = block_load('stellarjs_block', $delta);
  $stellarjs_block = stellarjs_block_block_get($block->delta);
  $form['info'] = array('#type' => 'hidden', '#value' => $stellarjs_block['info'] ? $stellarjs_block['info'] : $stellarjs_block['title']);
  $form['bid'] = array('#type' => 'hidden', '#value' => $block->delta);

  return confirm_form($form, t('Are you sure you want to delete the block %name?', array('%name' => $stellarjs_block['info'])), 'admin/structure/block', '', t('Delete'), t('Cancel'));
}

/**
 * Form submission handler for stellarjs_block__delete().
 *
 * @see stellarjs_block_delete()
 */
function stellarjs_block_delete_submit($form, &$form_state) {
  // If there is a file, delete it.
  $file = stellarjs_block_get_file($form_state['values']['bid']);
  if (!empty($file->fid)) {
    file_usage_delete($file, 'stellarjs_block', 'stellarjs_block', $form_state['values']['bid']);
    file_delete($file);
  }

  db_delete('stellarjs_block')
    ->condition('bid', $form_state['values']['bid'])
    ->execute();
  db_delete('block')
    ->condition('module', 'stellarjs_block')
    ->condition('delta', $form_state['values']['bid'])
    ->execute();
  db_delete('block_role')
    ->condition('module', 'stellarjs_block')
    ->condition('delta', $form_state['values']['bid'])
    ->execute();
  drupal_set_message(t('The StellarJS block %name has been removed.', array('%name' => $form_state['values']['info'])));
  cache_clear_all();
  $form_state['redirect'] = 'admin/structure/block';
  return;
}
