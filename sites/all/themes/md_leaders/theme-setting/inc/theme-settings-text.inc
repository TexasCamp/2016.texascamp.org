<?php

/**
 * @file
 * Theme settings .
 */

function md_leaders_theme_settings_text(&$form, &$form_state) {
	$form['md_leaders_settings']['text'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -3,
		'#prefix'  				=> '<div id="md-text-typography" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #md-text-typography -->',
	);
	
	$form['md_leaders_settings']['text']['text_htmllist'] = array(
		'#markup' 				=> '<div id="md-content-sidebar" class="md-content-sidebar">
                                        <ul class="clearfix">
                                            <li><a href="#tt-text"><i class="fa fa-bold"></i>Text &amp; Links</a></li>
                                            <li><a href="#tt-typography"><i class="fa fa-italic"></i>Typography</a></li>
                                        </ul>
                                    </div><!-- /.md-content-sidebar -->
			                        <div class="md-content-main">',
		'#weight' 				=> -15,
	);
	
	$form['md_leaders_settings']['text']['text_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);
	
	/* 1.	Text & link style
	--------------------------------------------------------------------------*/
	$form['md_leaders_settings']['text']['text_normal'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="tt-text">',
		'#suffix'        	=> '</div><!-- / #tt-text -->',
	);
		
		// Text
		$form['md_leaders_settings']['text']['text_normal']['text_style'] = array(
	        '#type' 					=> 'fieldset',
			'#prefix'  				=> '<h3 class="md-tabcontent-title">'.t('Text style').'</h3>',
	    );
		
			$form['md_leaders_settings']['text']['text_normal']['text_style']['text_font'] = array(
				'#type'          	=> 'hidden',
				'#default_value' 	=> theme_get_setting('text_font','md_leaders'),
				'#prefix' => '<div id="text-font" class="choosefont clearfix">',
				'#suffix' => '</div>',
			);
			
			$form['md_leaders_settings']['text']['text_normal']['text_style']['ts_font_color'] = array(
				'#type'          	=> 'textfield',
				'#title'         	=> t('Color'),
				'#default_value' 	=> theme_get_setting('ts_font_color','md_leaders'),
				'#attributes' 		=> array(
                    'class' => array(
                        'form-colorpicker',
                    ),
	            ),
                '#field_prefix'           => '<div class="form-group label-inline">',
                '#field_suffix'           => '</div>'
			);

		// Text selection
		$form['md_leaders_settings']['text']['text_normal']['text_selection'] = array(
	    '#type' 					=> 'fieldset',
			'#prefix'  				=> '<h3 class="md-tabcontent-title">'.t('Text selection style').'</h3>',
	    );
			
			$form['md_leaders_settings']['text']['text_normal']['text_selection']['tss_bgcolor'] = array(
				'#type'          	=> 'textfield',
				'#title'         	=> t('Background color'),
				'#default_value' 	=> theme_get_setting('tss_bgcolor','md_leaders'),
                '#attributes' 		=> array(
                    'class' => array(
                        'form-colorpicker',
                    ),
                ),
                '#field_prefix'           => '<div class="form-group label-inline">',
                '#field_suffix'           => '</div>'
			);
			
			$form['md_leaders_settings']['text']['text_normal']['text_selection']['tss_tcolor'] = array(
				'#type'          	=> 'textfield',
				'#title'         	=> t('Text color'),
				'#default_value' 	=> theme_get_setting('tss_tcolor','md_leaders'),
                '#attributes' 		=> array(
                    'class' => array(
                        'form-colorpicker',
                    ),
                ),
                '#field_prefix'           => '<div class="form-group label-inline">',
                '#field_suffix'           => '</div>'
			);
			
		// Link
		$form['md_leaders_settings']['text']['text_normal']['link_style'] = array(
	    '#type' 					=> 'fieldset',
			'#prefix'  				=> '<h3 class="md-tabcontent-title">'.t('Link style').'</h3>',
			'#description'		=> '<p>This change will be applied to every link in your website</p>',
	  );
			
			$form['md_leaders_settings']['text']['text_normal']['link_style']['link_style_htmllist'] = array(
				'#markup' 				=> '<div id="md-text-subtabs" class="md-tabs md-subtabs">
								<div class="md-subtabs-head">
		              <ul class="clearfix">
		                <li> <a href="#link-regular">Regular</a> </li>
		                <li> <a href="#link-rollover">Rollover</a> </li>
		                <li> <a href="#link-visited">Visited</a> </li>
		                <li> <a href="#link-on">On</a> </li>
		              </ul>
		            </div>',
				'#weight' 				=> -15,
			);
			
			$form['md_leaders_settings']['text']['text_normal']['link_style']['link_style_htmllistclose'] = array(
				'#markup' 				=> '</div><!-- /#sub-tab -->',
				'#weight' 				=> 15,
			);
			
			// Link regular
			$form['md_leaders_settings']['text']['text_normal']['link_style']['link_regular'] = array(
				'#type' 					=> 'fieldset',
				'#weight' 				=> -5,
				'#prefix'  				=> '<div id="link-regular" class="md-subtabcontent clearfix">',
				'#suffix'        => '</div><!-- / #link-regular -->',
			);
			
				md_leaders_prepare_link_style($form,'regular');
			
			// Link rollover
			$form['md_leaders_settings']['text']['text_normal']['link_style']['link_rollover'] = array(
				'#type' 					=> 'fieldset',
				'#weight' 				=> -4,
				'#prefix'  				=> '<div id="link-rollover" class="md-subtabcontent clearfix">',
				'#suffix'        => '</div><!-- / #link-rollover -->',
			);
			
				md_leaders_prepare_link_style($form,'rollover');
			
			// Link visited
			$form['md_leaders_settings']['text']['text_normal']['link_style']['link_visited'] = array(
				'#type' 					=> 'fieldset',
				'#weight' 				=> -3,
				'#prefix'  				=> '<div id="link-visited" class="md-subtabcontent clearfix">',
				'#suffix'        => '</div><!-- / #link-visited -->',
			);
			
				md_leaders_prepare_link_style($form,'visited');
			
			// Link on
			$form['md_leaders_settings']['text']['text_normal']['link_style']['link_on'] = array(
				'#type' 					=> 'fieldset',
				'#weight' 				=> -2,
				'#prefix'  				=> '<div id="link-on" class="md-subtabcontent clearfix">',
				'#suffix'        => '</div><!-- / #link-on -->',
			);
			
				md_leaders_prepare_link_style($form,'on');
	
	/* 2.	Typography
	--------------------------------------------------------------------------*/
	$form['md_leaders_settings']['text']['text_typography'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="tt-typography"><h3 class="md-tabcontent-title">'.t('Heading').'</h3>',
		'#suffix'        => '</div><!-- / #tt-typography -->',
	);
    /*--------------------------------- Heading Style -------------------------------------------------*/
    $form['md_leaders_settings']['text']['text_typography']['typo_heading'] = array(
        '#type' 					=> 'fieldset',
        '#prefix'  				=> '',
    );

    $form['md_leaders_settings']['text']['text_typography']['typo_heading']['typo_heading_style_enable'] = array(
        '#type'          => 'checkbox',
        '#default_value' => theme_get_setting('typo_heading_style_enable','md_leaders') ? theme_get_setting('typo_heading_style_enable','md_leaders') : 0,
        '#suffix'				=> '<div id="typo-heading-style-custom-typo">',
        '#field_suffix' => '<label class="label-checkbox" for="edit-typo-heading-style-enable">Use custom settings for each Heading instead of the default above</label>',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
    );
    $form['md_leaders_settings']['text']['text_typography']['typo_heading']['typo_heading_settings'] = array(
        '#type'                 =>  'container',
        '#states'           => array(
            'visible'       => array(
                ':input[name="typo_heading_style_enable"]' => array(
                    'checked'     => TRUE
                )
            )
        ),

    );
    for($i=1;$i<=6;$i++){
        $form['md_leaders_settings']['text']['text_typography']['typo_heading']['typo_heading_settings']['typo_heading_h'.$i.''] = array(
            '#type' 					=> 'fieldset',
            '#prefix'  				=> '<h3>'.t('Heading !name', array('!name' => t($i))).'</h3>',
            '#description'		=> t('Change the Heading h'.$i.' font.'),
        );
        $form['md_leaders_settings']['text']['text_typography']['typo_heading']['typo_heading_settings']['typo_heading_h'.$i.'']['typo_heading_h'.$i.'_style'] = array(
            '#type'          	=> 'hidden',
            '#default_value' 	=> theme_get_setting('typo_heading_h'.$i.'_style','md_leaders'),
            '#prefix' => '<div id="typo_heading_h'.$i.'_style" class="choosefont clearfix">',
            '#suffix' => '</div>',
        );

        $form['md_leaders_settings']['text']['text_typography']['typo_heading']['typo_heading_settings']['typo_heading_h'.$i.'']['typo_heading_h'.$i.'_color'] = array(
            '#type'          	=> 'textfield',
            '#title'         	=> t('Color'),
            '#default_value' 	=> theme_get_setting('typo_heading_h'.$i.'_color'),
            '#prefix' => '<div class="form-font-color">',
            '#suffix' => '</div>',
            '#attributes' 		=> array(
                'class' => array(
                    'form-colorpicker',
                ),
            ),
        );
    }

}		
	

function md_leaders_prepare_link_style(&$form, $state) {
	$form['md_leaders_settings']['text']['text_normal']['link_style']['link_'.$state]['l_'.$state.'_color'] = array(
		'#type'          	=> 'textfield',
		'#title'         	=> t('Text color'),
		'#default_value' 	=> theme_get_setting('l_'.$state.'_color','md_leaders'),
		'#attributes' 		=> array(
            'class' => array(
                'form-colorpicker',
            ),
		),
        '#prefix'           => '<div class="form-group">',
        '#field_prefix'     => '<div class="form-group">',
        '#field_suffix'     => '</div>',
	);
	
	$form['md_leaders_settings']['text']['text_normal']['link_style']['link_'.$state]['l_'.$state.'_st'] = array(
		'#type' => 'checkbox',
		'#default_value' => theme_get_setting('l_'.$state.'_st','md_leaders'),
        '#field_suffix' => '<label class="label-checkbox" for="edit-l-'.$state.'-st">Strikethrough</label>',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
	);
	
	$form['md_leaders_settings']['text']['text_normal']['link_style']['link_'.$state]['l_'.$state.'_hl'] = array(
		'#type' => 'checkbox',
		'#default_value' => theme_get_setting('l_'.$state.'_hl','md_leaders'),
        '#field_suffix' => '<label class="label-checkbox" for="edit-l-'.$state.'-hl">Highlight</label>',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
        '#suffix'           => '</div>'
	);
	
	$form['md_leaders_settings']['text']['text_normal']['link_style']['link_'.$state]['l_'.$state.'_hlc'] = array(
		'#type'          	=> 'textfield',
        '#title'            => t('Highlight Color'),
		'#default_value' 	=> theme_get_setting('l_'.$state.'_hlc','md_leaders'),
		'#attributes' 		=> array(
            'class' => array(
                'form-colorpicker',
            ),
		),
        '#prefix'           => '<div class="form-group">',
        '#field_prefix'     => '<div class="form-group">',
        '#field_suffix'     => '</div>',
	);

	$form['md_leaders_settings']['text']['text_normal']['link_style']['link_'.$state]['l_'.$state.'_ts'] = array(
		'#type' => 'checkboxes',
		'#default_value'    => is_array(theme_get_setting('l_'.$state.'_ts','md_leaders')) ? theme_get_setting('l_'.$state.'_ts','md_leaders') : array(),
		'#options'          => drupal_map_assoc(array(t('bold'), t('italic'), t('underline'))),
        '#prefix'           => '<div class="form-group label-inline">',
        '#suffix'           => '</div></div>',
        '#attributes'       => array(
            //'class' => array('input-checkbox')
        ),
	);
}