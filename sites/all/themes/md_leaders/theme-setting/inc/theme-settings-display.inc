<?php

/**
 * @file
 * Theme settings .
 */

function md_leaders_theme_settings_display(&$form, &$form_state) {
    global $base_url;
	$form['md_leaders_settings']['display'] = array(
		'#type' 			    => 'fieldset',
		'#weight' 				=> -1,
		'#prefix'  				=> '<div id="md-display" class="md-tabcontent clearfix">',
		'#suffix'               => '</div><!-- / #md-display -->',
	);

	$form['md_leaders_settings']['display']['display_htmllist'] = array(
		'#markup' 				=> '<div id="md-content-sidebar" class="md-content-sidebar">
                                        <ul class="clearfix">
                                            <li><a href="#s-hdsocial"><i class="fa fa-info-circle"></i>Header Social</a></li>
                                            <li><a href="#s-highlights"><i class="fa fa-archive"></i>Highlights Block</a></li>
                                            <li><a href="#copyright"><i class="fa fa-save"></i>Copyright</a></li>
                                            <li><a href="#s-map"><i class="fa fa-map-marker"></i>Map</a></li>
                                        </ul>
                                    </div><!-- /.md-content-sidebar -->
			                        <div class="md-content-main">',
		'#weight' 				=> -15,
	);

	$form['md_leaders_settings']['display']['display_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);
  

/* ==================================================================================
================================= Header Socila =====================================
====================================================================================*/
    $form['md_leaders_settings']['display']['display_hdsocial'] = array(
        '#type'                 => 'fieldset',
        '#weight' 				=> 1,
        '#prefix'  				=> '<div id="s-hdsocial">',
        '#suffix'               => '</div><!-- / #footer -->',
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div id="hdsocial-info"><h3 class="md-tabcontent-title">Header Infomation</h3>',
        '#suffix'   => '</div>',
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['_wrapper'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div id="hdsocial-info-wrapper">',
        '#suffix'   => '</div>',
        '#attributes'   => array(
            'class' => array('hdsocial-info-wrapper'),
        )
    );
    $max_num = theme_get_setting('hdsocial_info_max_num','md_leaders') ? theme_get_setting('hdsocial_info_max_num','md_leaders') : 1;
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_popup_add_wrapper'] = array(
        '#markup'   => '<a class="add-more md-button" data-preview="hdsocial_info_preview" data-max-num="'.$max_num.'" href="#hdsocial-info-sortable-no'.$max_num.'">Add More</a>',
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_popup_close_wrapper'] = array(
        '#markup' => '</div>'
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div id="hdsocial_info_preview" class="data-container"><div class="popup-wrapper"></div>',
        '#sufix'    => '</div>'
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview']['hdsocial_info_order'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'class'    => 'hidden-order'
        ),
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview']['hdsocial_info_max_num'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'class'    => 'hidden-num'
        ),
        '#default_value' => theme_get_setting('hdsocial_info_max_num','md_leaders') ? theme_get_setting('hdsocial_info_max_num','md_leaders') : 1,
    );
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview']["hdsocial_info_preview_openhtml"] = array(
        '#markup'   => '<ul id="hdsocial_info_sortable" class="sortable">'
    );
    if(theme_get_setting('hdsocial_info','md_leaders') == null) {
        $hdsocial_info = array(
            'hdsocial_info_sortable_no1' => array(
                'icon' => array(
                    'icon' => '',
                    'bundle' => ''
                ),
                'detail'  => ''
            )
        );
    } else {
        $hdsocial_info = theme_get_setting('hdsocial_info','md_leaders');
    }

    foreach($hdsocial_info as $key => $value){
        $explode = explode("_",$key);
        end($explode);
        $num = current($explode);
        //$info_icon = $hdsocial_info[$key]['icon'];
        $info_icon = isset($hdsocial_info[$key]['icon']) ? $hdsocial_info[$key]['icon'] : array("icon" => "", "bundle" => "");
        $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview'][$key.'_openhtml'] = array(
            '#markup' => '<li id="hdsocial-info-sortable-'.$num.'" class="draggable-item sortable-item toggle-item" data-num="'.substr($num,2).'" data-id="hdsocial-info-sortable-no'.substr($num,2).'"><a href="#" class="md-remove">X</a>'
        );
        $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview'][$key]['hdsocial_info_icon_'.$num] = array(
            '#type' => 'icon_selector',
            '#title'    => 'Header Icon',
            '#default_bundle' => isset($info_icon['bundle']) ? $info_icon['bundle'] : '',
            '#default_icon' => isset($info_icon['icon']) ? $info_icon['icon'] : '',
            '#prefix'               => '<div class="form-group icon-picker">',
            '#suffix'               => '</div>',
        );

        $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview'][$key]['hdsocial_info_detail_'.$num] = array(
            '#type' => 'textfield',
            '#title'    => 'Detail',
            '#attributes' => array(
                'class' => array('input-border'),
            ),
            '#default_value' => $hdsocial_info[$key]['detail'],
            '#maxlength' => 1000,
            '#prefix'               => '<div class="form-group">',
            '#suffix'               => '</div>'
        );
        $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview'][$key.'_closehtml'] = array(
            '#markup' => '</li>'
        );
    }
    $form['md_leaders_settings']['display']['display_hdsocial']['hdsocial_info']['hdsocial_info_wrapper']['hdsocial_info_preview']["hdsocial_info_preview_closehtml"] = array(
        '#markup'   => '</ul>'
    );        
        
        
  /* 4.	Copyright
--------------------------------------------------------------------------*/
  $form['md_leaders_settings']['display']['copyright'] = array(
    '#type' => 'fieldset',
    '#weight' => -5,
    '#prefix' => '<div id="copyright"><h3 class="md-tabcontent-title">Copyright setting</h3>',
    '#suffix' => '</div>',
  );
  $form['md_leaders_settings']['display']['copyright']['copyright_text'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('Text'),
    '#default_value' => theme_get_setting('copyright_text', 'md_leaders'),
  );
  
  
  
/* ==================================================================================
================================= Our Highlights Bottom ==============================
====================================================================================*/
$form['md_leaders_settings']['display']['display_highlights'] = array(
        '#type'                 => 'fieldset',
        '#weight' 				=> 1,
        '#prefix'  				=> '<div id="s-highlights">',
        '#suffix'               => '</div><!-- / #footer -->',
    );

    $form['md_leaders_settings']['display']['display_highlights']['highlights_info'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div id="highlights-info"><h3 class="md-tabcontent-title">Our Highlights</h3>',
        '#suffix'   => '</div>',
    );
    
    
    
//highlights text
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_text'] = array(
        '#type' => 'textarea',
        '#resizable'    => false,
        '#default_value'    => theme_get_setting('highlights_text','md_leaders') ? theme_get_setting('highlights_text','md_leaders') : '',
        '#attributes'       => array(
            'class'         => array('textarea-border')
        )
    );	
    
//highlights list    
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['_wrapper'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div id="highlights-info-wrapper">',
        '#suffix'   => '</div>',
        '#attributes'   => array(
            'class' => array('highlights-info-wrapper'),
        )
    );
    $max_num = theme_get_setting('highlights_info_max_num','md_leaders') ? theme_get_setting('highlights_info_max_num','md_leaders') : 1;
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_popup_add_wrapper'] = array(
        '#markup'   => '<a class="add-more md-button" data-preview="highlights_info_preview" data-max-num="'.$max_num.'" href="#highlights-info-sortable-no'.$max_num.'">Add More</a>',
    );
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_popup_close_wrapper'] = array(
        '#markup' => '</div>'
    );
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div id="highlights_info_preview" class="data-container"><div class="popup-wrapper"></div>',
        '#sufix'    => '</div>'
    );
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview']['highlights_info_order'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'class'    => 'hidden-order'
        ),
    );
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview']['highlights_info_max_num'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'class'    => 'hidden-num'
        ),
        '#default_value' => theme_get_setting('highlights_info_max_num','md_leaders') ? theme_get_setting('highlights_info_max_num','md_leaders') : 1,
    );
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview']["highlights_info_preview_openhtml"] = array(
        '#markup'   => '<ul id="highlights_info_sortable" class="sortable">'
    );
    if(theme_get_setting('highlights_info','md_leaders') == null) {
        $highlights_info = array(
            'highlights_info_sortable_no1' => array(
                'detail'  => ''
            )
        );
    } else {
        $highlights_info = theme_get_setting('highlights_info','md_leaders');
    }

    foreach($highlights_info as $key => $value){
        $explode = explode("_",$key);
        end($explode);
        $num = current($explode);
        $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview'][$key.'_openhtml'] = array(
            '#markup' => '<li id="highlights-info-sortable-'.$num.'" class="draggable-item sortable-item toggle-item" data-num="'.substr($num,2).'" data-id="highlights-info-sortable-no'.substr($num,2).'"><a href="#" class="md-remove">X</a>'
        );

        $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview'][$key]['highlights_info_detail_'.$num] = array(
            '#type' => 'textfield',
            '#title'    => 'Detail',
            '#attributes' => array(
                'class' => array('input-border'),
            ),
            '#default_value' => $highlights_info[$key]['detail'],
            '#maxlength' => 1000,
            '#prefix'               => '<div class="form-group">',
            '#suffix'               => '</div>'
        );
        $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview'][$key.'_closehtml'] = array(
            '#markup' => '</li>'
        );
    }
    $form['md_leaders_settings']['display']['display_highlights']['highlights_info']['highlights_info_wrapper']['highlights_info_preview']["highlights_info_preview_closehtml"] = array(
        '#markup'   => '</ul>'
    );            
        
        
        
     
    ////////////////////////////////////////////////////// Google map //////////////////////////////////////////////////////
    $form['md_leaders_settings']['display']['map'] = array(
        '#type'                 => 'fieldset',
        '#weight' 				=> 1,
        '#prefix'  				=> '<div id="s-map">',
        '#suffix'               => '</div><!-- / #footer -->',
    );
    $form['md_leaders_settings']['display']['map']['map_marker_title'] = array(
        '#type' 				=> 'textfield',
        '#default_value' 	    =>  theme_get_setting('map_marker_title','md_leaders') ? theme_get_setting('map_marker_title','md_leaders') : t('Megadrupal'),
        '#prefix'               => '<div class="md-tabcontent-header">
                                            <h3 class="md-tabcontent-title">Marker Title</h3>
                                        </div><!-- /.md-row-description -->
                                        <div class="form-group">',
        '#suffix'               => '</div>',
        '#attributes'           => array(
            'class'             => array('input-border big')
        )
    );
    $form['md_leaders_settings']['display']['map']['map_marker_description'] = array(
        '#type' 			    => 'textarea',
        '#resizable'            => FALSE,
        '#default_value' 	    =>  theme_get_setting('map_marker_description','md_leaders') ? theme_get_setting('map_marker_description','md_leaders') : t('Ha Noi , Viet Nam, Asia'),
        '#prefix'               => '<div class="md-tabcontent-header">
                                            <h3 class="md-tabcontent-title">Marker Description</h3>
                                        </div><!-- /.md-row-description -->
                                        <div class="form-group">',
        '#suffix'               => '</div>',
        '#attributes'           => array(
            'class'             => array('input-border normal')
        )
    );
    $form['md_leaders_settings']['display']['map']['map_latlng'] = array(
        '#type' 				=> 'textfield',
        '#default_value' 	    =>  theme_get_setting('map_latlng','md_leaders') ? theme_get_setting('map_latlng','md_leaders') : t('40.761467,-73.956379'),
        '#description'          =>  t('Find your map point by reading our documentation'),
        '#prefix'               => '<div class="md-tabcontent-header">
                                            <h3 class="md-tabcontent-title">Google Map location</h3>
                                        </div><!-- /.md-row-description -->
                                        <div class="form-group">',
        '#suffix'               => '</div>',
        '#attributes'           => array(
            'class'             => array('input-border big')
        )
    );
    $form['md_leaders_settings']['display']['map']['map_types']   = array(
        '#type'                 => 'select',
        '#options'              => array(
            'ROADMAP'           => t('Road Map'),
            'SATELINE'          => t('Sate Line'),
            'HYBRID'            => t('Hybrid'),
            'TERRAIN'           => t('Terrain'),
        ),
        '#default_value'        => theme_get_setting('map_types','md_leaders') ? theme_get_setting('map_types','md_leaders') : t('ROADMAP'),
        '#prefix'               => '<div class="md-tabcontent-header">
                                            <h3 class="md-tabcontent-title">Map types</h3>
                                        </div><!-- /.md-row-description -->
                                        <div class="form-group">',
        '#suffix'               => '</div>',
        '#attributes'           => array(
            'class'             => array('select')
        ),
        '#field_prefix'         => '<div class="md-selection medium">',
        '#field_suffix'         => '</div>'
    );
    
    ///////////// marker pic ///////////////////////////////////////////////////////////////////////

        $form['md_leaders_settings']['display']['map']['marker_pic'] = array(
            '#type' => 'fieldset',
            '#prefix' => '<h3 class="md-tabcontent-title">marker image pic settings</h3>',
            '#description' => t('If toggled on, the following marker pic will be displayed.'),
            '#attributes' => array('class' => array('theme-settings-bottom')),
            '#weight'   => 1
        );
        $form['md_leaders_settings']['display']['map']['marker_pic']['default_marker_pic'] = array(
            '#type' => 'checkbox',
            '#field_suffix' => '<label class="label-checkbox" for="edit-default-marker-pic'.'">Use the default marker</label>',
            '#attributes'   => array(
                'class' => array('input-checkbox')
            ),
            '#prefix'   =>  '<div class="form-elements">',
            '#suffix'   => '</div>',
            '#default_value' => theme_get_setting('default_marker_pic', 'md_leaders'),
            '#tree' => FALSE,
            '#description' => t('Check here if you want the theme to use the marker supplied with it.')
        );
        $form['md_leaders_settings']['display']['map']['marker_pic']['settings'] = array(
            '#type' => 'container',
            '#states' => array(
                // Hide the marker settings when using the default marker.
                'invisible' => array(
                    'input[name="default_marker_pic"]' => array('checked' => TRUE),
                ),
            ),
        );

        if(module_exists('media')) {
        $marker = theme_get_setting('marker_file','md_leaders');
        
        $form['md_leaders_settings']['display']['map']['marker_pic']['settings']['marker_media_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('md-media-wrapper')
                )
            );
            $marker_file = new stdClass();
            $marker_file->url = '';
            $marker_file->fid = '';

            $marker_file_hidden_value = theme_get_setting('marker_file','md_leaders');
            if(is_array($marker_file_hidden_value)) {
                if($marker_file_hidden_value['fid'] != 0) {
                    $file = file_load($marker_file_hidden_value['fid']);
                    if($file) {
                        $marker_file->url = $file->url;
                        $marker_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($marker_file_hidden_value)) {
                    $marker_file = json_decode($marker_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['display']['map']['marker_pic']['settings']['marker_media_wrapper']['marker_upload_media'] = array(
                '#markup'       => '
                    <div class="form-wrapper  mb-20">
                        <h4 class="md-row-title">'.t('Upload Map Marker').'</h4>
                            <div class="form-elements">
                                <div class="preview">
                                    <img class="img-preview" src="'.(!empty($marker_file->url) ? $marker_file->url : $base_url.'/'.THEME_PATH.'/theme-setting/img/theme-settings/no_image.png').'" alt="">
                                </div>
                            </div>
                            <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                    </div>'
            );
            $form['md_leaders_settings']['display']['map']['marker_pic']['settings']['marker_media_wrapper']['marker_file'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('marker_file','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );
        }
    
    // Zoom map
    $form['md_leaders_settings']['display']['map']['map_zoom_level'] = array(
        '#type'                 => 'select',
        '#options'              => array(
            '14'                => '14',
            '15'                => '15',
            '16'                => '16',
            '17'                => '17',
            '18'                => '18'
        ),
        '#default_value'        => theme_get_setting('map_zoom_level','md_leaders') ? theme_get_setting('map_zoom_level','md_leaders') : '17',
        '#prefix'               => '<div class="md-tabcontent-header">
                                            <h3 class="md-tabcontent-title">Map Zoom Level</h3>
                                        </div><!-- /.md-row-description -->
                                        <div class="form-group">',
        '#suffix'               => '</div>',
        '#attributes'           => array(
            'class'             => array('select')
        ),
        '#field_prefix'         => '<div class="md-selection small">',
        '#field_suffix'         => '</div>',
    );
    

}