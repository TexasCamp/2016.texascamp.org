<?php

class MdPortfolioPluginRows extends views_plugin_row {

  public function option_definition() {
    $options = parent::option_definition();
    $options['md_rows'] = '';
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $MDP = new MDP_PORTFOLIO();
    $fields = array();
    $handler = $this->display->handler;
    $mds_check_style = $MDP->check_style($handler);
    if($mds_check_style) {
      $form['md_row_flag'] = array(
        '#type' => 'hidden',
        '#default_value' => '1'
      );

      $get_field = $handler->get_handlers('field');
      $mds_fields = $MDP->field_plugin_row($get_field);
      $mds_fields_other = $MDP->field_plugin_row_other($mds_fields);
      if($mds_fields != false) {
        foreach($mds_fields as $field_name => $fields_value) {
          $form['md_rows'][$field_name] = array(
            '#type' => 'fieldset',
            '#title' => $fields_value['name'],
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
          );

          if($fields_value['flag_image']) {

            $form['md_rows'][$field_name]['field'] = array(
              '#type' => 'hidden',
              '#default_value' => $fields_value['md_rows']['field'],
            );

            $form['md_rows'][$field_name]['flag'] = array(
              '#type' => 'select',
              '#title' => t('Display'),
              '#options' => array('0' => 'Disable', '1' => 'Enable', 'caption' => 'Caption', 'more' => 'More'),
              '#default_value' => isset($this->options['md_rows'][$field_name]['flag']) ? $this->options['md_rows'][$field_name]['flag'] : '0',
              '#attributes' => array(
                'id' => $field_name.'_flag_check'
              )
            );

            $form['md_rows'][$field_name]['caption'] = array(
              '#type' => 'fieldset',
              '#process' => array('ctools_dependent_process'),
              '#dependency' => array(
                $field_name.'_flag_check' => array('caption'),
              ),
              '#collapsible' => TRUE,
              '#collapsed' => FALSE,
            );

            $form['md_rows'][$field_name]['caption']['class_link'] = array(
              '#type' => 'select',
              '#title' => t('More info link Load node content '),
              '#options' => array('cbp-lightbox' => t('Lightbox'),'cbp-singlePage' => t('Full page'), 'cbp-singlePageInline' => t('Inline page'), 'none' => t('None')),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['caption']['class_link']) ? $this->options['md_rows'][$field_name]['caption']['class_link'] : 'cbp-singlePage')
            );

            $form['md_rows'][$field_name]['caption']['text'] = array(
              '#type' => 'textfield',
              '#title' => t('Text'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['caption']['text'])) ? $this->options['md_rows'][$field_name]['caption']['text'] : 'Mega Drupal',
            );

            $form['md_rows'][$field_name]['caption']['field_display'] = array(
              '#type' => 'fieldset',
              '#title' => t('Add field display in Caption')
            );

            if($mds_fields_other != false) {
              foreach($mds_fields_other as $mds_fields_other_key => $mds_fields_other_value) {
                $form['md_rows'][$field_name]['caption']['field_display'][$mds_fields_other_key] = array(
                  '#type' => 'checkbox',
                  '#title' => t($mds_fields_other_value['name']),
                  '#default_value' => (isset($this->options['md_rows'][$field_name]['caption']['field_display'][$mds_fields_other_key]) ? $this->options['md_rows'][$field_name]['caption']['field_display'][$mds_fields_other_key] : '0')
                );
              }
            }

            $form['md_rows'][$field_name]['more'] = array(
              '#type' => 'fieldset',
              '#process' => array('ctools_dependent_process'),
              '#dependency' => array(
                $field_name.'_flag_check' => array('more'),
              ),
              '#collapsible' => TRUE,
              '#collapsed' => FALSE,
            );

            $form['md_rows'][$field_name]['more']['caption_flag'] = array(
              '#type' => 'checkbox',
              '#title' => t('Button View Image'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['caption_flag'])) ? $this->options['md_rows'][$field_name]['more']['caption_flag'] : '0',
              '#attributes' => array(
                'id' => $field_name.'-caption-flag'
              )
            );

            $form['md_rows'][$field_name]['more']['caption_text'] = array(
              '#type' => 'textfield',
              '#title' => t('Text'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['caption_text'])) ? $this->options['md_rows'][$field_name]['more']['caption_text'] : 'View Image',
              '#dependency' => array(
                $field_name.'-caption-flag' => array('1'),
              )
            );

            $form['md_rows'][$field_name]['more']['full_page_flag'] = array(
              '#type' => 'checkbox',
              '#title' => t('Button Load Content : Full page'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['full_page_flag'])) ? $this->options['md_rows'][$field_name]['more']['full_page_flag'] : '0',
              '#attributes' => array(
                'id' => $field_name.'-full-page'
              )
            );

            $form['md_rows'][$field_name]['more']['full_page_text'] = array(
              '#type' => 'textfield',
              '#title' => t('Text'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['full_page_text'])) ? $this->options['md_rows'][$field_name]['more']['full_page_text'] : 'View Content',
              '#dependency' => array(
                $field_name.'-full-page' => array('1'),
              )
            );

            $form['md_rows'][$field_name]['more']['inline_page_flag'] = array(
              '#type' => 'checkbox',
              '#title' => t('Button Load Content : Inline page'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['inline_page_flag'])) ? $this->options['md_rows'][$field_name]['more']['inline_page_flag'] : '0',
              '#attributes' => array(
                'id' => $field_name.'-inline-page'
              )
            );

            $form['md_rows'][$field_name]['more']['inline_page_text'] = array(
              '#type' => 'textfield',
              '#title' => t('Text'),
              '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['inline_page_text'])) ? $this->options['md_rows'][$field_name]['more']['inline_page_text'] : 'View Content',
              '#dependency' => array(
                $field_name.'-inline-page' => array('1'),
              )
            );

            $form['md_rows'][$field_name]['more']['field_display'] = array(
              '#type' => 'fieldset',
              '#title' => t('Add field display in more')
            );

            if($mds_fields_other != false) {
              foreach($mds_fields_other as $mds_fields_other_key => $mds_fields_other_value) {
                $form['md_rows'][$field_name]['more']['field_display'][$mds_fields_other_key] = array(
                  '#type' => 'checkbox',
                  '#title' => t($mds_fields_other_value['name']),
                  '#default_value' => (isset($this->options['md_rows'][$field_name]['more']['field_display'][$mds_fields_other_key]) ? $this->options['md_rows'][$field_name]['more']['field_display'][$mds_fields_other_key] : '0')
                );
              }
            }

          } else {
            $form['md_rows'][$field_name]['field'] = array(
              '#type' => 'hidden',
              '#default_value' => $fields_value['field'],
            );

            $form['md_rows'][$field_name]['flag'] = array(
              '#type' => 'select',
              '#title' => t('Display'),
              '#options' => array('0' => 'Disable', '1' => 'Enable'),
              '#default_value' => isset($this->options['md_rows'][$field_name]['flag']) ? $this->options['md_rows'][$field_name]['flag'] : '0',
            );
          }

        }
      }
    } else {
      $form['md_row_flag'] = array(
        '#type' => 'hidden',
        '#prefix' => '<h4 style="color: #FF6600;">Plugin row support only for MD - Style Portfolio</h4>',
        '#default_value' => '0'
      );
    }
    //dsm($fields);
  }

}
