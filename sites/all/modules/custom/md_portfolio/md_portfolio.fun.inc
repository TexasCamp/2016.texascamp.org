<?php

class MDP_PORTFOLIO {

  public $md_style_flag = '0';
  public $vid = '0';
  public $vname = '0';
  public $display_id = '0';
  public $filter_tax_id = '0';
  public $filter_tax_id_field_name = '0';
  public $filter_tax_mname = '0';
  public $filter_field = '0';
  public $display_handler = '0';
  public $load_content_type = array();
  public $load_taxonomy = array();
  public $item_width = 25;
  public $item_height = 200;
  public $load_view_mode = array();

  public function get_taxonomy($content_type = '') {
    $taxs = array();

    if(count($content_type) != 0) {
      foreach($content_type as $type) {
        $tax_load = $this->filter_taxonomy_to_content_type($type);
        if($tax_load != null) {
          foreach($tax_load as $key => $value) {
            $taxs[$key] = $value;
          }
        }
      }
    }

    return $taxs;
  }

  public function filter_taxonomy_to_content_type($content_type = '') {
    $tax = null;
    $fields = field_info_instances('node', $content_type);
    if(count($fields) != 0) {
      foreach($fields as $key => $field) {
        if($field['display']['default']['type']) {
          if($field['display']['default']['type'] == 'taxonomy_term_reference_link') {
            $field_info = field_info_field($key);
            if($field_info['type'] == 'taxonomy_term_reference') {
              $field_name = $field['field_name'];
              $tax_vol = $field_info['settings']['allowed_values'][0]['vocabulary'];
              $tax_info = taxonomy_vocabulary_machine_name_load($tax_vol);
              $tax[$tax_info->vid.'/'.$field_name] = $field_info['field_name'];
              $this->filter_tax_id_field_name = $tax_info->vid.'/'.$field_name;
              $this->filter_tax_id = $tax_info->vid;
              $this->filter_tax_mname = $tax_vol;
              $this->filter_field = $field_name;
            }
          }
        }
      }
    }

    return $tax;
  }

  public function get_content_type($display_handler = '') {
    //dsm($display_handler);
    //load all content type select in filter criteria
    if($display_handler->plugin_name == 'default') {//display handler : master
      $content_type_load  = isset($display_handler->display->display_options['filters']) ? ($display_handler->display->display_options['filters']) : null;
    } else {
      $content_type_load  = isset($display_handler->default_display->display->display_options['filters']) ? ($display_handler->default_display->display->display_options['filters']) : null;
    }

    $content_type_arg = array();
    if(isset($content_type_load['type']) && $content_type_load['type']['table'] == 'node') {
      $type = $content_type_load['type'];
      if(count($type['value']) != 0) {
        $content_type_arg = $type['value'];
        unset($content_type_arg['all']);
      }
    }

    return $content_type_arg;
  }

  public function view_input_style($view = '') {
    //dsm($view);
    $this->vid = $view->vid;
    $this->vname = $view->name;
    $this->display_id = $view->current_display;
    $this->display_handler = $view->display_handler;
    $this->load_content_type = $this->get_content_type($view->display_handler);//get all content type
    $this->load_taxonomy = $this->get_taxonomy($this->load_content_type);//get all taxonomy in content types
    $this->load_view_mode = $this->get_view_mode_for_node();
    
    return true;
  }

  public function get_view_mode_for_node() {
    $entity_info = entity_get_info('node');
    $options = array();
    if (!empty($entity_info['view modes'])) {
      foreach ($entity_info['view modes'] as $mode => $settings) {
        $options[$mode] = $settings['label'];
      }
    }
    if (empty($options)) {
      $options = array(
        'teaser' => t('Teaser'),
        'full' => t('Full content')
      );
    }

    return $options;
  }

  function buildmodes_list_modes($all = FALSE) {
    $buildmodes = array();
    if ($all) {
      $buildmodes += content_build_modes();
      foreach (array(NODE_BUILD_NORMAL, 'full', 'teaser', NODE_BUILD_PREVIEW, NODE_BUILD_SEARCH_INDEX, NODE_BUILD_SEARCH_RESULT, NODE_BUILD_RSS, NODE_BUILD_PRINT) as $mode) {
        unset($buildmodes[$mode]);
      }
    }
    $buildmodes += variable_get('buildmodes_modes', array());
    // For convinience prupose we sort by alpha keys
    ksort($buildmodes);

    return $buildmodes;
  }

  public function var_plugin_style() {
    $mdp = array(
      'md_style_flag' => $this->md_style_flag,
      'md_style_view' => array(
        'vid' => $this->vid,
        'vname' => $this->vname,
        'display_id' => $this->display_id,
        'filter_tax_id_field_name' => $this->filter_tax_id_field_name,
        'filter_default_tax_id' => $this->filter_tax_id,
        'filter_default_tax_mname' => $this->filter_tax_mname,
        'filter_default_field' => $this->filter_field,
        'filter_div_id' => 'mdp-filter-'.$this->vid,
        'grid_div_id' => 'mdp-grid-'.$this->vid,
      ),
      'md_style_filter_count' => array(
        'flag_check' => '1',
        'options' => array(
          'count_type' => 'cbp-count-tooltip',
          'field_prefix' => '(',
          'field_suffix' => ')'
        )
      ),
      'md_style_filter_type' => 'cbp-l-filters-alignCenter',
      'md_style_item_width' => $this->item_width,
      'md_style_item_width_unit' => '%',
      'md_style_item_height' => $this->item_height,
      'md_style_container_type' => 'cbp-l-grid-blog',
      'md_style_animationType' => '3dflip',
      'md_style_caption' => 'pushTop',
      'md_style_displayType' => 'default',
      'md_style_displayTypeSpeed' => '400',
      'md_style_gridAdjustment' => 'alignCenter',
      'md_style_gapHorizontal' => '5',
      'md_style_gapVertical' => '5',
      'md_style_class_add_style' => '',
      'md_style_class_add_filter' => '',
      'md_style_width' => '100',
      'md_style_width_unit' => '%',
      'md_style_view_node' => 'full_page',
    );

    return $mdp;
  }

  public function var_plugin_row() {
    $mdp = array(
    );
    return $mdp;
  }

  public function field_plugin_row($handlers = '') {
    $mds = null;
    foreach ($handlers as $field => $handler) {
      if ($label = $handler->label()) {
        $fields[$field]['name'] = $label;
      }
      else {
        $fields[$field]['name'] = $handler->ui_name();
      }

      $options = $handler->options;

      $fields[$field]['field'] = $options['field'];
      if(isset($options['type'])) {
        $fields[$field]['type'] = $options['type'];
        if($options['type'] == 'image') {
          $fields[$field]['flag_image'] = '1';
          $fields[$field]['field'] = $options['field'];
        } else {
          $fields[$field]['flag_image'] = '0';
        }

      } else {
        $fields[$field]['type'] = '0';
        $fields[$field]['flag_image'] = '0';
      }
    }

    $mds = $fields;
    //dsm($mds);
    return $mds;
  }

  public function field_plugin_row_other($fields = '') {
    $mds = false;
    if($fields != false) {
      foreach($fields as $key => $value) {
        if(!$value['flag_image']) {
          $mds[$key] = $value;
        }
      }
    }
    //dsm($mds);
    return $mds;
  }

  public function var_plugin_page() {
    $mds = array(

    );
    return $mds;
  }

  public function check_filter() {
    if($this->filter_tax_id_field_name == '0') {
      return false;
    }

    return true;
  }

  public function check_style($handler = '') {
    $mds_check = false;
    $style_name = (($handler->display->handler->view->display['default']->display_options['style_plugin'])? ($handler->display->handler->view->display['default']->display_options['style_plugin']) : false);

    if($style_name == 'md_portfolio_mdp_plugin_style') {
      $mds_check = true;
    }
    return $mds_check;
  }

}

class MDP_LOADTERM {
  public $taxonomy = null;

  function load_term($tax ='') {
    $terms = array();
    $result = false;
    if(strlen($tax) != 0) {
      $term_list = taxonomy_get_tree($tax);
      if(count($term_list) != 0) {//get filter control for portfolio
        foreach($term_list as $key => $value) {
          $result[$value->tid] = $value->name;
        }
      }
    }

    return $result;
  }
}
