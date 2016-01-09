<?php

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_md_portfolio_mdp_plugin_style(&$vars) {

  $options = $vars['options'];
  $view = $vars['view'];
  //check value default of options in plugin style
  $md_data = array('filter' => null, 'options' => null);

  if(!isset($options['md_style_flag']) || ($options['md_style_flag'] == null)){
    $mdsp = new MDP_PORTFOLIO;
    $mdsp->view_input_style($view);
    $md_options_default = $mdsp->var_plugin_style();

    foreach($md_options_default as $md_key => $md_value) {
      $options[$md_key] = $md_value;
    }
    $options['md_style_flag'] = 1;
  }

  if($options['md_style_view']['filter_tax_id_field_name'] != '0') {
    $md_arg_temp = explode('/',$options['md_style_view']['filter_tax_id_field_name']);
    $options['md_style_view']['filter_default_tax_id'] = $md_arg_temp[0];
    $options['md_style_view']['filter_default_field'] = $md_arg_temp[1];
  }

  $term_filter = null;
  $mdsp_term = new MDP_LOADTERM;
  $term_filter_machine_name = taxonomy_vocabulary_machine_name_load($options['md_style_view']['filter_default_tax_id']);
  if($term_filter_machine_name != null){
    $term_filter = $mdsp_term->load_term($term_filter_machine_name->vid);
  }
  $filter_content = '';
  if($term_filter != null) {
    if($options['md_style_filter_type'] == 'cbp-l-filters-dropdown'){
      $filter_count = '';
      if($options['md_style_filter_count']['flag_check'] != '0') {
        $filter_count .= '<span class="cbp-filter-counter"></span>';
      }
      $filter_content .= '  <div class="cbp-l-filters-dropdownHeader">'.$options['md_style_filter_dropdown_header'].'</div>';
      $filter_content .= '  <ul class="cbp-l-filters-dropdownList">';
      $filter_content .= '    <li>';
      $filter_content .= '      <div data-filter="*" class="cbp-filter-item-active cbp-filter-item">All '.$filter_count.'</div>';
      $filter_content .= '    </li>';
      if(count($term_filter) != 0) {
        foreach($term_filter as $term_filter_key => $term_filter_value) {
          $filter_content .= '<li>';
          $filter_content .= '    <div data-filter=".mds-filter-'.$term_filter_key.'" class="cbp-filter-item">'.$term_filter_value.$filter_count.'</div>';
          $filter_content .= '</li>';
        }
      }
      $filter_content .= '  </ul>';
    } else {
      $filter_count = '';
      if($options['md_style_filter_count']['flag_check'] != '0') {
        $filter_count .= '<div class="cbp-filter-counter '.$options['md_style_filter_count']['options']['count_type'].'"></div>';
      }

      $filter_content .= '<div data-filter="*" class="cbp-filter-item-active cbp-filter-item cbp-l-filters-list-first">All '.$filter_count.'</div>';
      $md_count = count($term_filter);
      $md_count_start = 1;
      if(count($term_filter) != 0) {
        foreach($term_filter as $term_filter_key => $term_filter_value) {
          if($md_count_start == $md_count) {
            $filter_content .= '<div data-filter=".mds-filter-'.$term_filter_key.'" class="cbp-filter-item cbp-l-filters-list-last">'.$term_filter_value.$filter_count.'</div>';
          } else {
            $filter_content .= '<div data-filter=".mds-filter-'.$term_filter_key.'" class="cbp-filter-item">'.$term_filter_value.$filter_count.'</div>';
          }
          $md_count_start++ ;
        }
      }
    }
  }
  //$options['md_style_view']['display_id'] = $view->current_display;
  $md_data['options'] = $options;

  $md_data['filter'] = $filter_content;
  $vars['md_data'] = $md_data;

  $wdt_json = drupal_json_encode($md_data['options']);
  drupal_add_js(array(
    'md_style' => $wdt_json,
  ), array('type' => 'setting'));

  $md_path = current_path();
  if(strpos($md_path, 'admin/structure/views') !== true) {
    $md_css_inline = '.' . $options['md_style_container_type'] . ' .cbp-item {';
    $md_css_inline .= 'width : '. $options['md_style_item_width'] .$options['md_style_item_width_unit']. ';';
    $md_css_inline .= 'height : '. $options['md_style_item_height'] . 'px;';
    $md_css_inline .= '}';
    if(($md_data['options']['md_style_container_type'] == 'cbp-l-grid-masonry') && (count($md_data['options']['md_style_item_level_height']) != 0)){
      foreach($md_data['options']['md_style_item_level_height'] as $key => $value){
        $md_css_inline .= '.cbp-item.mdp-level-height-'. $key .' {';
        $md_css_inline .= 'height: '. $value . 'px;';
        $md_css_inline .= '}';
      }
    }
    drupal_add_css($md_css_inline, array('type' => 'inline', 'group' => CSS_THEME , 'weight' => 52));
    drupal_add_library('md_portfolio','md_portfolio_lib');
  }
//  dsm($md_data);
}

function template_preprocess_md_portfolio_mdp_plugin_rows(&$vars) {
  $view = $vars['view'];
  // Loop through the fields for this view.
  $previous_inline = FALSE;
  $md_fields = array(); // ensure it's at least an empty array.
  foreach ($view->field as $id => $field) {
    // render this even if set to exclude so it can be used elsewhere.
    $field_output = $view->style_plugin->get_field($view->row_index, $id);
    $empty = $field->is_value_empty($field_output, $field->options['empty_zero']);
    if (empty($field->options['exclude']) && (!$empty || (empty($field->options['hide_empty']) && empty($vars['options']['hide_empty'])))) {
      $object = new stdClass();
      $object->handler = &$view->field[$id];
      $object->inline = !empty($vars['options']['inline'][$id]);

      $object->element_type = $object->handler->element_type(TRUE, isset($vars['options']['default_field_elements']), $object->inline);
      if ($object->element_type) {
        $class = '';
        if ($object->handler->options['element_default_classes']) {
          $class = 'field-content';
        }

        if ($classes = $object->handler->element_classes($view->row_index)) {
          if ($class) {
            $class .= ' ';
          }
          $class .=  $classes;
        }

        $pre = '<' . $object->element_type;
        if ($class) {
          $pre .= ' class="' . $class . '"';
        }
        if($object->element_type != 'span'){
          $field_output = $pre . '>' . $field_output . '</' . $object->element_type . '>';
        }

      }

      // Protect ourself somewhat for backward compatibility. This will prevent
      // old templates from producing invalid HTML when no element type is selected.
      if (empty($object->element_type)) {
        $object->element_type = 'span';
      }

      $object->content = $field_output;
      if (isset($view->field[$id]->field_alias) && isset($vars['row']->{$view->field[$id]->field_alias})) {
        $object->raw = $vars['row']->{$view->field[$id]->field_alias};
      }
      else {
        $object->raw = NULL; // make sure it exists to reduce NOTICE
      }

      if (!empty($vars['options']['separator']) && $previous_inline && $object->inline && $object->content) {
        $object->separator = filter_xss_admin($vars['options']['separator']);
      }

      $object->class = drupal_clean_css_identifier($id);

      $previous_inline = $object->inline;
      $object->inline_html = $object->handler->element_wrapper_type(TRUE, TRUE);
      if ($object->inline_html === '' && (isset($vars['options']['default_field_elements']))) {
        $object->inline_html = $object->inline ? 'span' : 'div';
      }

      // Set up the wrapper HTML.
      $object->wrapper_prefix = '';
      $object->wrapper_suffix = '';

      if ($object->inline_html) {
        $class = '';
        if ($object->handler->options['element_default_classes']) {
          $class = "views-field views-field-" . $object->class;
        }

        if ($classes = $object->handler->element_wrapper_classes($view->row_index)) {
          if ($class) {
            $class .= ' ';
          }
          $class .= $classes;
        }
        $object->wrapper_prefix = '<' . $object->inline_html;
        if ($class) {
          $object->wrapper_prefix .= ' class="' . $class . '"';
        }
        $object->wrapper_prefix .= '>';
        $object->wrapper_suffix = '</' . $object->inline_html . '>';
      }

      // Set up the label for the value and the HTML to make it easier
      // on the template.
      $object->label = check_plain($view->field[$id]->label());
      $object->label_html = '';
      if ($object->label) {
        $object->label_html .= $object->label;
        if ($object->handler->options['element_label_colon']) {
          $object->label_html .= ': ';
        }

        $object->element_label_type = $object->handler->element_label_type(TRUE, isset($vars['options']['default_field_elements']));
        if ($object->element_label_type) {
          $class = '';
          if ($object->handler->options['element_default_classes']) {
            $class = 'views-label views-label-' . $object->class;
          }

          $element_label_class = $object->handler->element_label_classes($view->row_index);
          if ($element_label_class) {
            if ($class) {
              $class .= ' ';
            }

            $class .= $element_label_class;
          }

          $pre = '<' . $object->element_label_type;
          if ($class) {
            $pre .= ' class="' . $class . '"';
          }
          $pre .= '>';

          $object->label_html = $pre . $object->label_html . '</' . $object->element_label_type . '>';
        }
      }

      $md_field_render = '';
      if (!empty($object->separator)){
        $md_field_render .= $object->separator;
      }

      $md_field_render .= $object->wrapper_prefix;
      $md_field_render .= $object->label_html;
      $md_field_render .= $object->content;
      $md_field_render .= $object->wrapper_suffix;

      $md_fields[$id] = $md_field_render;
    }
  }

//  dsm($md_fields);
//  dsm($vars['options']);
  $md_data = array(
    'fields' => array(),
    'images' => array(),
    'data_filter' => '',
    'class_link' => '',
    'href' => '',
    'options' => array(),
    'row_style' => '',
    'md_level_height' => ''
  );

  if((!isset($vars['options']['md_rows'])) || (count($vars['options']['md_rows']) != count($md_fields))){
    // if field in row option != field list or do not exits md_rows
    foreach($md_fields as $key => $value){
      $md_data['fields'][$key]['display'] = 1;
      $md_data['fields'][$key]['content'] = $value;
    }
  } else {
    $md_options = $vars['options']['md_rows'];
    $md_style = $view->style_plugin->options;
    $md_node_view_mode = isset($md_style['md_style_view_node']) ? $md_style['md_style_view_node'] : 'full_page';

    if(count($md_options) != 0){
      foreach($md_options as $field_name => $field_options){
        if(isset($md_fields[$field_name]) && ($field_options['flag'] == 1)){
          //if exist field_name in options vs flag display = 1
          $md_data['fields'][$field_name]['display'] = 1;
          $md_data['fields'][$field_name]['content'] = $md_fields[$field_name];
        }
        if(count($field_options) > 2){
          //when field is image
          $md_field_flag = $field_options['flag'];
          $md_imgs = $view->style_plugin->get_field($view->row_index, $field_name);
          $md_img_url = md_portfolio_get_link_img($md_imgs);
          $md_data['images'][$field_name]['url'] = $md_img_url;

          if(count($field_options[$md_field_flag]['field_display']) != 0){
            foreach($field_options[$md_field_flag]['field_display'] as $field_img_display_name => $field_img_display_value){
              if(($field_img_display_value == 1) && (isset($md_fields[$field_img_display_name]))){
                $md_data['images'][$field_name]['fields_display'][$field_img_display_name] = $md_fields[$field_img_display_name];
              }
            }
          }

          if($md_field_flag == 'caption'){
            $md_data['class_link'] = $field_options['caption']['class_link'];
            if($field_options['caption']['text'] != ''){
              $md_data['images'][$field_name]['fields_display']['0'] =  $field_options['caption']['text'];
            }

            if($md_data['class_link'] == 'cbp-lightbox'){
              $md_data['href'] = ' href="'.$md_img_url.'" ';
              $md_data['class_link'] .= ' mpd-cursor';
            } elseif($md_data['class_link'] == 'none'){
              $md_data['href'] = '';
            } else {
              $md_data['class_link'] .= ' mpd-cursor';
              $md_load_content_url = url('md-portfolio/loadcontent/'.$md_node_view_mode.'/'.$vars['row']->nid);
              $md_data['href'] = ' href="'.$md_load_content_url.'" ';
            }
          } elseif($md_field_flag == 'more'){
            $md_load_content_url = url('md-portfolio/loadcontent/'.$md_node_view_mode.'/'.$vars['row']->nid);
            if($field_options['more']['full_page_flag'] == 1){
              $md_data['images'][$field_name]['fields_display'][1] = '<a class="cbp-singlePage cbp-l-caption-buttonLeft" href="'.$md_load_content_url.'">'.$field_options['more']['full_page_text'] .'</a>';
            }
            if($field_options['more']['inline_page_flag'] == 1){
              $md_data['images'][$field_name]['fields_display'][2] = '<a class="cbp-singlePageInline cbp-l-caption-buttonLeft" href="'.$md_load_content_url.'">'.$field_options['more']['inline_page_text'] .'</a>';
            }
            if($field_options['more']['caption_flag'] == 1){
              $md_data['images'][$field_name]['fields_display'][0] = '<a class="cbp-lightbox cbp-l-caption-buttonRight" href="'.$md_img_url.'">'.$field_options['more']['caption_text'] .'</a>';
            }
          }

        }
      }
    }
  }

  //get term in result
  $md_index = $view->row_index;
  $results = $view->result;
  $options = isset($vars['options']['md_row'])? $vars['options']['md_row'] : '';
  $md_result_row = $view->result[$md_index];
  $check_node_field_data = property_exists($md_result_row, '_field_data');
  if($check_node_field_data) {
    $filter_field = isset($md_style['md_style_view']['filter_default_field']) ? $md_style['md_style_view']['filter_default_field'] : null;
    if($filter_field != null) {
      $entity = $results[$md_index]->_field_data['nid']['entity'];
      $filter_field_data = $entity->$filter_field;
      if(isset($filter_field_data[LANGUAGE_NONE]) && (count($filter_field_data[LANGUAGE_NONE]) != 0)) {
        foreach($filter_field_data[LANGUAGE_NONE] as $filter_field_data_key => $filter_field_data_value) {
          //dsm($filter_field_data_value);
          $md_data['data_filter'] .= ' mds-filter-'.$filter_field_data_value['tid'];
        }
      }
    }
  }
//  dsm($results);
  if(count($results) != 0){
    $md_node_load = node_load($results[$md_index]->nid);
    $md_level_height_value = field_get_items('node', $md_node_load, 'field_mdp_height');
    if(($md_level_height_value != null) && (count($md_level_height_value) != 0)){
      $md_data['md_level_height'] = 'mdp-level-height-'.$md_level_height_value[0]['value'];
    }
  }

  $md_data['options'] = $options;

  if(!isset($md_data['options']['md_row_height_flag'])) {
    $md_data['options']['md_row_height_flag'] = '1';
  }

  if(!isset($md_data['options']['md_row_height'])) {
    $md_data['options']['md_row_height'] = 300;
  }

  $wdt_json = drupal_json_encode($md_data['options']);
  drupal_add_js(array(
    'md_row' => $wdt_json,
  ), array('type' => 'setting'));

  if($md_data['options']['md_row_height_flag'] == '0') {
    $row_style = 'style="height: '.$md_data['options']['md_row_height'].'px;"';
  } else {
    $row_style = '';
  }

  $md_data['row_style'] = $row_style;
  $vars['md_data'] = $md_data;

}
