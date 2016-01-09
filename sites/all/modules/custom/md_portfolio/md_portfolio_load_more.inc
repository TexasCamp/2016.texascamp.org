<?php

/**
 * @file
 *
 * The plugin to handle Load More pager.
 *
 * @ingroup views_pager_plugins
 */

class md_portfolio_load_more extends views_plugin_pager_full {

  /**
   * Summary title overwrite.
   */
  function summary_title() {
    if (!empty($this->options['offset'])) {
      return format_plural($this->options['items_per_page'], 'Load more pager, @count item, skip @skip', 'Load more pager, @count items, skip @skip', array('@count' => $this->options['items_per_page'], '@skip' => $this->options['offset']));
    }
    return format_plural($this->options['items_per_page'], 'Load more pager, @count item', 'Load more pager, @count items', array('@count' => $this->options['items_per_page']));
  }

  /**
   * Options definition overwrite.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['waypoint'] = array(
      'contains' => array(
        'infinite' => array('default' => FALSE),
      ),
    );
    $options['more_button_text'] = array(
      'default' => t('Load more'),
      'translateable' => TRUE,
    );
    $options['advance'] = array(
      'contains' => array(
        'row_class' => array('default' => ''),
        'content_class' => array('default' => ''),
      ),
    );
    $options['wle_page_check'] = array('default' => 1);
    $options['wle_page_button_link'] = array('default' => 'Load More');
    $options['items_per_page'] = array('default' => 6);

    return $options;
  }

  /**
   * Options form overwrite.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Keep items per page as the first form element on the page followed by
    // the option to change the 'load more' button text
    $form['tags']['#type'] = 'hidden';
    $form['quantity']['#type'] = 'hidden';
    $form['expose']['#type'] = 'hidden';
    $form['total_pages']['#type'] = 'hidden';
    $form['offset']['#type'] = 'hidden';
    $form['id']['#type'] = 'hidden';

    $form['items_per_page']['#weight'] = -2;

    $form['wle_page_check'] = array(
      '#type' => 'select',
      '#title' => t('Use load more'),
      '#options' => array(0 => 'None', 1 => 'Button Link', 2 => 'Infinite Scroll'),
      '#default_value' => isset($this->options['wle_page_check']) ? $this->options['wle_page_check'] : '1',
      '#weight' => -1,
      '#attributes' => array(
        'id' => 'wle_page_check'
      ),
    );

    $form['wle_page_button_link'] = array(
      '#type' => 'textfield',
      '#title' => t('Text for button link load more'),
      '#dependency' => array(
        'wle_page_check' => array(1),
      ),
      '#default_value' => isset($this->options['wle_page_button_link']) ? $this->options['wle_page_button_link'] : 'load more',
      '#weight' => -1,
    );

  }

  /**
   * render overwrite.
   */
  function render($input) {
    //dsm($this->view->query->pager->display->display_plugin);
    if($this->view->query->pager->plugin_name == 'md_load_more') {
      $this->view->query->pager->options['wle_page_check'] = isset($this->options['wle_page_check']) ? $this->options['wle_page_check'] : '0';
      $this->view->query->pager->options['wle_page_button_link'] = isset($this->options['wle_page_button_link']) ? $this->options['wle_page_button_link'] : 'load more';
    }
    $options = $this->view->query->pager->options;
    $md_total_pager = $this->get_pager_total();
    $wle_page = '';
    if($md_total_pager > 1){
      if($options['wle_page_check'] == '1') {
        $wle_page =  '<div class="cbp-l-loadMore-button">';
        $wle_page .=  '    <a href="#" class="cbp-l-loadMore-button-link" name="1">'.$options['wle_page_button_link'].'</a>';
        $wle_page .=  '</div>';
      } elseif($options['wle_page_check'] == '2') {
        $wle_page =  '<div class="cbp-l-loadMore-button">';
        $wle_page .=  '    <a href="#" class="cbp-l-loadMore-text-link" name="1">'.$options['wle_page_button_link'].'</a>';
        $wle_page .=  '</div>';
      }
    }

    if($this->view->style_plugin->plugin_name != 'md_portfolio_mdp_plugin_style') {
      $wle_page = 'MD load more only support for MD Portfolio...';
    }
    if($this->view->style_plugin->row_plugin->plugin_name != 'md_portfolio_mdp_plugin_rows') {
      $wle_page = 'MD load more only support for MD Portfolio...';
    }
    $options['max_pager'] = $md_total_pager;
//    dsm($options);
    $wdt_json = drupal_json_encode($options);
    drupal_add_js(array(
      'md_portfolio_loadmore' => $wdt_json,
    ), array('type' => 'setting'));

    return $wle_page;
  }

}
