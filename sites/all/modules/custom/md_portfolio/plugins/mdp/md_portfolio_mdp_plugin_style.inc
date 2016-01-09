<?php

class MdPortfolioPluginStyle extends views_plugin_style{

  public function option_definition() {
    $options = parent::option_definition();
    $MDP = new MDP_PORTFOLIO();
    $mds_options_default = $MDP->var_plugin_style();
    //load options for mdsp when setting first
    if(!isset($options['md_style_flag'])) {
      foreach($mds_options_default as $mds_key => $mds_value) {
        $options[$mds_key] = array('default' => $mds_value);
      }
    }
    //$options = null;
    return $options;
  }

  function options_form(&$form, &$form_state) {
    //dsm($this->options);
    $view = $this->view;
    $MDP = new MDP_PORTFOLIO();
    $MDP->view_input_style($view);
    $mds_options_load = $MDP->var_plugin_style();

    //load options value with view
    if($this->options['md_style_flag'] == '0') {//check flag == 0
      foreach($mds_options_load as $mds_key => $mds_value) {
        $this->options[$mds_key] = $mds_value;
      }
      $this->options['md_style_flag'] = '1';
    }
    //dsm($this->options);
    foreach($mds_options_load['md_style_view'] as $temp_key => $temp_value) {
      if($temp_key != 'filter_tax_id_field_name') {//do not create form with filter_tax_id_field_name
        $form['md_style_view'][$temp_key] = array(
          '#type' => 'hidden',
          '#default_value' => $temp_value
        );
      }
    }

    $form['md_style_flag'] = array(
      '#type' => 'hidden',
      '#default_value' => $this->options['md_style_flag']
    );

    $form['md_style_container_type'] = array(
      '#type' => 'select',
      '#title' => t('Template'),
      '#options' => array(
        'cbp-l-grid-blog' => t('Blog posts'),
        'cbp-l-grid-fullScreen' => t('Full screen'),
        'cbp-l-grid-gallery' => t('Lightbox gallery'),
        'cbp-l-grid-projects' => t('Juicy projects'),
        'cbp-l-grid-gallery' => t('Lightbox gallary'),
        'cbp-l-grid-masonry' => t('Masonry'),
      ),
      '#default_value' => $this->options['md_style_container_type'],
      '#weight' => -1,
      '#suffix' => '<div style="margin: 10px 0px 10px 0px;"><hr></div>',
      '#attributes' => array(
        'id' => 'md-style-container-type'
      )
    );

    if($MDP->check_filter() == true) {
      $form['md_style_view']['filter_tax_id_field_name'] = array(
        '#type' => 'select',
        '#title' => 'Taxonomy filter',
        '#description' => 'filter load to taxonomy in content type',
        '#options' => $MDP->load_taxonomy,
        '#default_value' => array($this->options['md_style_view']['filter_tax_id_field_name'])
      );
    } else {
      $form['md_style_view']['filter_tax_id_field_name'] = array(
        '#type' => 'hidden',
        '#prefix' => '<h4 style="color: #de903e;">Do not find Taxonomy filter</h4>',
        '#default_value' => '0',
      );
    }

    $form['md_style_filter_type'] = array(
      '#type' => 'select',
      '#title' => t('Filter style'),
      '#options' => array(
        'cbp-l-filters-list' => t('List'),
        'cbp-l-filters-button' => t('Button'),
        'cbp-l-filters-dropdown' => t('Dropdown'),
        'cbp-l-filters-alignRight' => t('Align right'),
        'cbp-l-filters-alignCenter' => t('Align center'),
        'cbp-l-filters-alignLeft' => t('Align left'),
      ),
      '#default_value' => $this->options['md_style_filter_type'],
      '#attributes' => array(
        'id' => 'md-style-filter-type'
      )
    );

    $form['md_style_filter_dropdown_header'] = array(
      '#type' => 'textfield',
      '#title' => t('Header for Dropdown'),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('md-style-filter-type' => array('cbp-l-filters-dropdown')),
      '#default_value' => $this->options['md_style_filter_dropdown_header'],
    );

    $form['md_style_animationType'] = array(
      '#type' => 'select',
      '#title' => t('Animations for filters'),
      '#options' => array(
        'fadeOut' => t('Fade Out'),
        'quicksand' => t('Quicksand'),
        'boxShadow' => t('Box Shadow'),
        'bounceLeft' => t('Bounce Left'),
        'bounceTop' => t('Bounce Top'),
        'bounceBottom' => t('Bounce Bottom'),
        'moveLeft' => t('Move Left'),
        'slideLeft' => t('Slide Left'),
        'fadeOutTop' => t('Fade Out Top'),
        'sequentially' => t('Sequentially'),
        'skew' => t('Skew'),
        'slideDelay' => t('SlideDelay'),
        '3dflip' => t('3D Flip'),
        'rotateSides' => t('RotateSides'),
        'flipOutDelay' => t('FlipOutDelay'),
        'flipOut' => t('FlipOut'),
        'unfold' => t('Unfold'),
        'foldLeft' => t('FoldLeft'),
        'scaleDown' => t('ScaleDown'),
        'scaleSides' => t('ScaleSides'),
        'frontRow' => t('FrontRow'),
        'flipBottom' => t('FlipBottom'),
        'rotateRoom' => t('RotateRoom')
      ),
      '#default_value' => $this->options['md_style_animationType'],
    );

    $form['md_style_filter_count']['flag_check'] = array(
      '#type' => 'checkbox',
      '#title' => t('Filter with items count'),
      '#default_value' => $this->options['md_style_filter_count']['flag_check'],
      '#attributes' => array(
        'id' => 'mds-style-filter-count-flag-check'
      )
    );

    $form['md_style_filter_count']['options'] = array(
      '#type' => 'fieldset',
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('mds-style-filter-count-flag-check' => array('1')),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['md_style_filter_count']['options']['count_type'] = array(
      '#type' => 'select',
      '#title' => 'Count type',
      '#options' => array('cbp-count-default' => t('Inline'), 'cbp-count-tooltip' => t('Tooltip')),
      '#default_value' => $this->options['md_style_filter_count']['options']['count_type']
    );

    $form['md_style_filter_count']['options']['field_prefix'] = array(
      '#type' => 'textfield',
      '#title' => 'Field Prefix',
      '#default_value' => $this->options['md_style_filter_count']['options']['field_prefix']
    );

    $form['md_style_filter_count']['options']['field_suffix'] = array(
      '#type' => 'textfield',
      '#title' => 'Field Suffix',
      '#default_value' => $this->options['md_style_filter_count']['options']['field_suffix'],
    );

    $form['md_style_width'] = array(
      '#type' => 'textfield',
      '#title' => t('Wrapper width'),
      '#required' => true,
      '#default_value' => $this->options['md_style_width'],
      '#size' => 13,
      '#prefix' => '<hr><div style="margin: 10px 10px 10px 0px;display: inline-block;">',
      '#suffix' => '</div>',
    );

    $form['md_style_width_unit'] = array(
      '#type' => 'select',
      '#options' => array('px' => t('px'), '%' => t('%')),
      '#default_value' => $this->options['md_style_width_unit'],
      '#prefix' => '<div style="display: inline-block;">',
      '#suffix' => '</div>',
    );

    $form['md_style_item_width'] = array(
      '#type' => 'textfield',
      '#title' => t('Items width'),
      '#required' => true,
      '#default_value' => $this->options['md_style_item_width'],
      '#size' => 13,
      '#prefix' => '<hr><div style="margin: 10px 10px 10px 0px;display: inline-block;">',
      '#suffix' => '</div>',
    );

    $form['md_style_item_width_unit'] = array(
      '#type' => 'select',
      '#options' => array('px' => t('px'), '%' => t('%')),
      '#default_value' => $this->options['md_style_item_width_unit'],
      '#prefix' => '<div style="display: inline-block;">',
      '#suffix' => '</div>',
    );

    $form['md_style_item_height'] = array(
      '#type' => 'textfield',
      '#title' => t('Items height'),
      '#field_suffix' => t('px'),
      '#required' => true,
      '#default_value' => $this->options['md_style_item_height'],
      '#size' => 13,
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('md-style-container-type' => array('cbp-l-grid-blog', 'cbp-l-grid-fullScreen', 'cbp-l-grid-gallery', 'cbp-l-grid-projects', 'cbp-l-grid-gallery')),
    );

    $md_level_height = md_portfolio_get_value_field('field_mdp_height');
    $form['md_style_item_level_height'] = array(
      '#type' => 'fieldset',
      '#title' => t('Mansory items height'),
      '#size' => 13,
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('md-style-container-type' => array('cbp-l-grid-masonry')),
      '#attributes' => array(
        'class' => array('md-style-container-type-level-height-fieldset')
      )
    );

    if(count($md_level_height) != 0){
      foreach($md_level_height as $key => $value){
        $form['md_style_item_level_height'][$key] = array(
          '#type' => 'textfield',
          '#title' => t($value),
          '#default_value' => isset($this->options['md_style_item_level_height'][$key])? $this->options['md_style_item_level_height'][$key] : '300',
          '#field_suffix' => 'px',
          '#size' => 13,
        );
      }
    } else {
      $form['md_style_item_level_height']['message_height'] = array(
        '#markup' => t('You need to create field with machine name field_mdp_height (type <strong>List(text)</strong>, widget <strong>Select list</strong>) to config mansory item height<br><br><strong>Allowed values list</strong>:<br>height1|Height 1<br>height2|Height 2<br>...')
      );
    }

    $form['md_style_gridAdjustment'] = array(
      '#type' => 'select',
      '#title' => t('Grid Adjustment'),
      '#options' => array(
        'default' => t('Default'),
        'alignCenter' => t('Align Center'),
        'responsive' => t('Responsive'),
      ),
      '#default_value' => $this->options['md_style_gridAdjustment'],
    );

    $form['md_style_gapHorizontal'] = array(
      '#type' => 'textfield',
      '#field_suffix' => 'px',
      '#required' => true,
      '#title' => t('Gap Horizontal'),
      '#default_value' => $this->options['md_style_gapHorizontal'],
      '#size' => 13,
    );

    $form['md_style_gapVertical'] = array(
      '#type' => 'textfield',
      '#field_suffix' => 'px',
      '#required' => true,
      '#title' => t('Gap Vertical'),
      '#default_value' => $this->options['md_style_gapVertical'],
      '#size' => 13,
    );

    $form['md_style_displayType'] = array(
      '#type' => 'select',
      '#description' => t('The plugin will display his content based on the following values. '),
      '#title' => t('Item appear style'),
      '#options' => array(
        'default' => t('default'),
        'fadeIn' => t('fadeIn'),
        'lazyLoading' => t('Lazy Loading'),
        'fadeInToTop' => t('Fade In To Top'),
        'sequentially' => t('Sequentially'),
        'bottomToTop' => t('Bottom To Top')
      ),
      '#default_value' => $this->options['md_style_displayType'],
    );

    $form['md_style_displayTypeSpeed'] = array(
      '#type' => 'textfield',
      '#description' => t('only integers, values in ms ex: 200, 300, 500'),
      '#title' => t('Appear speed'),
      '#default_value' => $this->options['md_style_displayTypeSpeed'],
      '#size' => 13,
    );

    $form['md_style_caption'] = array(
      '#type' => 'select',
      '#title' => t('Caption'),
      '#description' => t('Caption - the overlay that is shown when you put the mouse over an item.'),
      '#options' => array(
        'pushTop' => ('Push Top'),
        'pushDown' => ('Push Down'),
        'revealBottom' => ('Reveal Bottom'),
        'revealTop' => ('Reveal Top'),
        'revealLeft' => ('Reveal Left'),
        'moveRight' => ('Move Right'),
        'overlayBottomPush' => ('Overlay Bottom Push'),
        'overlayBottom' => ('Overlay Bottom'),
        'overlayBottomReveal' => ('Overlay Bottom Reveal'),
        'overlayBottomAlong' => ('Overlay Bottom Along'),
        'overlayRightAlong' => ('Overlay Right Along'),
        'minimal' => ('Minimal'),
        'fadeIn' => ('Fade In'),
        'zoom' => ('Zoom'),
      ),
      '#default_value' => $this->options['md_style_caption'],
    );

    $form['md_style_view_node'] = array(
      '#type' => 'select',
      '#title' => 'View node for content',
      '#description' => 'view node',
      '#options' => $MDP->load_view_mode,
      '#default_value' => array($this->options['md_style_view_node']),
    );


   $form['md_style_class_add_filter'] = array(
     '#type' => 'textfield',
     '#title' => t('Filter class'),
     '#default_value' => $this->options['md_style_class_add_filter'],
     //'#suffix' => '<h4></h4>',
   );

  $form['md_style_class_add_style'] = array(
     '#type' => 'textfield',
     '#title' => t('Wrapper class'),
     '#default_value' => $this->options['md_style_class_add_style'],
     //'#suffix' => '<h4></h4>',
   );

  }
}

