<?php
/**
 * @file
 * 'MD: Basic' style.
 */

// Plugin definition.
$plugin = array(
  'title' => t('MD: Styles'),
  'description' => t('Custom styles regions.'),
  'render region' => 'panels_md_basic_render_region',
  'render pane' => 'panels_md_basic_render_pane',
    'settings form' => 'panels_md_basic_element_region_settings_form',
  'pane settings form' => 'panels_md_basic_element_pane_settings_form',
);


/**
 * Wrapper settings form callback.
 */
function panels_md_basic_element_wrap_settings_form($style_settings) {

 /**
   * Wrapper
   */
  $form['wrap'] = array(
    '#type' => 'fieldset',
    '#title' => t('Wrapper'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Wrapper element
  $wrap_element = isset($style_settings['wrap']['element']) ? $style_settings['wrap']['element'] : 'div';
  $form['wrap']['element'] = array(
    '#title' => t('HTML Element'),
    '#type' => 'select',
    '#default_value' => $style_settings['wrap']['element'] ? $style_settings['wrap']['element'] : '- None -',
    '#options' => array(
      'none' => t('- None -'),
      'div' => t('DIV'),
      'section' => t('SECTION'),
    ),
  );

  // Wrapper attributes
  $wrap_attributes = isset($style_settings['wrap']['attributes']) ? $style_settings['wrap']['attributes'] : array();
  $form['wrap']['attributes'] = array(
      '#title' => t('Wrapper Attributes'),
    ) + _panels_md_basic_attribute_options($wrap_attributes);

  
  /* // Theming.
   * 
   $theme_default_value = !empty($style_settings['theme']) ? $style_settings['theme'] : FALSE;
   $form += _panels_md_basic_element_theme_options($theme_default_value);
   *
   */

  return $form;
}

/**
 * Title settings form callback.
 */
function panels_md_basic_element_title_settings_form($style_settings) {

 /**
   * Title
   */
  $form['title'] = array(
    '#type' => 'fieldset',
    '#title' => t('Title'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Title element
  $title_element = isset($style_settings['title']['element']) ? $style_settings['title']['element'] : 'h3';
  $form['title']['element'] = array(
      '#title' => t('HTML Element'),
      '#description' => t('HTML element to wrap around the title.'),
    ) + _panels_md_basic_element_options($title_element);

  // Title attributes
  $title_attributes = isset($style_settings['title']['attributes']) ? $style_settings['title']['attributes'] : array();
  $form['title']['attributes'] = array(
      '#title' => t('Title Attributes'),
    ) + _panels_md_basic_attribute_options($title_attributes);

  
  /*    // Theming.
   * 
   $theme_default_value = !empty($style_settings['theme']) ? $style_settings['theme'] : FALSE;
   $form += _panels_md_basic_element_theme_options($theme_default_value);
   *
   */

  return $form;
}

/**
 * Content settings form callback.
 */
function panels_md_basic_element_content_settings_form($style_settings) {

  // Content.
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Conetent element
  $content_element = isset($style_settings['content']['element']) ? $style_settings['content']['element'] : '';
  $form['content']['element'] = array(
      '#title' => t('HTML element'),
      '#description' => t('HTML element to wrap around the content.'),
    ) + _panels_md_basic_element_options($content_element);

  // Content attributes.
  $content_attributes = isset($style_settings['content']['attributes']) ? $style_settings['content']['attributes'] : array();
  $form['content']['attributes'] = array(
      '#title' => t('Content Attributes'),
    ) + _panels_md_basic_attribute_options($content_attributes);

  
  /*    // Theming.
   * 
   $theme_default_value = !empty($style_settings['theme']) ? $style_settings['theme'] : FALSE;
   $form += _panels_md_basic_element_theme_options($theme_default_value);
   *
   */

  return $form;
}

/**
 * Pane settings form callback.
 */
function panels_md_basic_element_pane_settings_form($style_settings) {
  
    // Wrapper form items, grabbed from the region settings.
  $form = panels_md_basic_element_wrap_settings_form($style_settings);

    // Title form items, grabbed from the region settings.
  $form += panels_md_basic_element_title_settings_form($style_settings);

  // Content form items, grabbed from the region settings.
  $form += panels_md_basic_element_content_settings_form($style_settings);

  
  
   $container_default_value = !empty($style_settings['container']) ? $style_settings['container'] : FALSE;
   $form += _panels_md_basic_element_container_options($container_default_value);
  
  /*    // Theming.
   *
   $theme_default_value = !empty($style_settings['theme']) ? $style_settings['theme'] : FALSE;
   $form += _panels_md_basic_element_theme_options($theme_default_value);
   *
   */

  return $form;
}

/**
 * Region settings form callback.
 */
function panels_md_basic_element_region_settings_form($style_settings) {
    
  $form = panels_md_basic_element_wrap_settings_form($style_settings);

  // Content form items, grabbed from the region settings.
  $form += panels_md_basic_element_content_settings_form($style_settings);

  
  
   $container_region_value = !empty($style_settings['container']) ? $style_settings['container'] : FALSE;
   $form += _panels_md_basic_element_container_options($container_region_value);

  return $form;
}

function _panels_md_basic_element_container_options($default_value = FALSE) {
  $options['container'] = array(
    '#type' => 'checkbox',
    '#title' => t('wrap the content with container theming layer.'),
    '#default_value' => $default_value,
  );

  return $options;
}



/**
 * Element options for settings forms.
 */
function _panels_md_basic_element_options($default_value = '') {
  $options = array(
    '#type' => 'select',
    '#default_value' => $default_value,
  );

  // Fallback element options, grabbed from View's defaults.
  $options['#options'] = variable_get('views_field_rewrite_elements', array(
    '0' => t('- None -'),
    'div' => 'DIV',
    'span' => 'SPAN',
    'h1' => 'H1',
    'h2' => 'H2',
    'h3' => 'H3',
    'h4' => 'H4',
    'h5' => 'H5',
    'h6' => 'H6',
    'p' => 'P',
    'strong' => 'STRONG',
    'em' => 'EM',
  ));

  return $options;
}

/**
 * Attribute options for settings forms.
 */
function _panels_md_basic_attribute_options($default_value = array()) {
  $options = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $options['id'] = array(
    '#type' => 'textfield',
    '#title' => t('id'),
    '#description' => t('CSS id to apply to the element, without the hash.'),
    '#default_value' => isset($default_value['id']) ? $default_value['id'] : '',
  );
  $options['class'] = array(
    '#type' => 'textfield',
    '#title' => t('class'),
    '#description' => t('CSS classes to apply to the element, separated by spaces.'),
    '#default_value' => isset($default_value['class']) ? $default_value['class'] : '',
  );

  return $options;
}



/**
 * Theme options for settings forms.
 */
/*
 * 
 function _panels_md_basic_element_theme_options($default_value = FALSE) {
  $options['theme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Additionally, wrap the content with Panels theming layer.'),
    '#default_value' => $default_value,
  );

  return $options;
}
* 
*/
