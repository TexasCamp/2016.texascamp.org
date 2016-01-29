<?php

/**
 * @file
 * Contains admin UI.
 */

/**
 * Form builder; This function allows configuration in administration sections.
 *
 * @see system_settings_form()
 */
function favicon_generator_settings() {
  $form = array();

  $form['#attached']['js'] = array(
    'misc/farbtastic/farbtastic.js',
    drupal_get_path('module', 'favicon_generator') . '/favicon_generator.js',
  );
  $form['#attached']['css'] = array(
    'misc/farbtastic/farbtastic.css',
    drupal_get_path('module', 'favicon_generator') . '/favicon_generator.css',
  );

  // Background Color.
  $form['favicon_generator_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Background Color'),
    '#default_value' => variable_get('favicon_generator_color', '#00aba9'),
    '#description' => '<div class="favicon_generator_colorpicker"></div>',
    '#size' => 7,
    '#maxlength' => 7,
  );
  // Add presets.
  $colors = array(
    '00aba9' => t('Teal'),
    '2d89ef' => t('Blue'),
    'da532c' => t('Dark Orange'),
    '00a300' => t('Green'),
    '2b5797' => t('Dark Blue'),
    'b91d47' => t('Dark Red'),
    'ffc40d' => t('Yellow'),
    '603cba' => t('Dark Purple'),
    '9f00a7' => t('Light Purple'),
  );
  $form['favicon_generator_color']['#description'] .= '<div class="color-presets">';
  foreach ($colors as $hex => $name) {
    $form['favicon_generator_color']['#description'] .=
      '<div class="color-preset" style="background-color: #' . $hex . ';" >' . $name . '<br/>#' . $hex . '</div>';
  }
  $form['favicon_generator_color']['#description'] .= '</div>';

  // Margin.
  $form['favicon_generator_margin'] = array(
    '#type' => 'select',
    '#title' => t('Margin size (for a 57x57 icon)'),
    '#options' => array(
      0 => t('0px'),
      1 => t('1px'),
      2 => t('2px'),
      3 => t('3px'),
      4 => t('4px'),
      5 => t('5px'),
      6 => t('6px'),
      7 => t('7px'),
      8 => t('8px'),
      9 => t('9px'),
      10 => t('10px'),
      11 => t('11px'),
      12 => t('12px'),
      13 => t('13px'),
      14 => t('14px'),
      15 => t('15px'),
    ),
    '#default_value' => variable_get('favicon_generator_margin', 4),
  );

  $form = array_merge($form, module_invoke_all('favicon_generator_admin'));

  $form['favicon_generator_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to icon files'),
    '#field_prefix' => t('public://'),
    '#default_value' => variable_get('favicon_generator_path', ''),
  );

  $form['#submit'][] = 'favicon_generator_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Additional submit handler for the settings form.
 *
 * Displays a message to reupload the favicon.
 */
function favicon_generator_settings_form_submit($form, &$form_state) {
  drupal_set_message(
    t('(Re-)save your theme settings at !link to rebuild the favicon set.',
      array(
        '!link' => l(
          url(
            'admin/appearance/settings',
            array('absolute' => TRUE)
          ),
          'admin/appearance/settings'
        ),
      )
    )
  );
}
