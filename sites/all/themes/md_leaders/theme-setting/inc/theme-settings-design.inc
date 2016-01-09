<?php

/**
 * @file
 * Theme settings .
 */

function md_leaders_theme_settings_design(&$form, &$form_state) {
    global $base_url;
	$form['md_leaders_settings']['design'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -4,
		'#prefix'  				=> '<div id="md-design" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #md-design -->',
	);
	
	$form['md_leaders_settings']['design']['design_htmllist'] = array(
		'#markup' 				=> '<div id="md-content-sidebar" class="md-content-sidebar">
                                        <ul class="clearfix">
                                            <li><a href="#ds-sidebar"><i class="fa fa-th-list"></i>Sidebar</a></li>
                                            <li><a href="#ds-skin"><i class="fa fa-wrench"></i>Skins</a></li>
                                        </ul>
                                    </div><!-- /.md-content-sidebar -->
			                        <div class="md-content-main">',
		'#weight' 				=> -15,
	);
	$form['md_leaders_settings']['design']['design_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);
     
    
/* ==================================================================================
================================= Sidebar ===========================================
====================================================================================*/
    $form['md_leaders_settings']['design']['design_sidebar'] = array(
        '#type'             => 'fieldset',
        '#weight' 				=> -5,
        '#prefix'  				=> '<div id="ds-sidebar">',
        '#suffix'        => '</div><!-- / #ds-block -->',
    );
    $form['md_leaders_settings']['design']['design_sidebar']['sidebar_position'] = array(
        '#type'          => 'select',
        '#default_value' => theme_get_setting('sidebar_position','md_leaders') ? theme_get_setting('sidebar_position','md_leaders') : 'right',
        '#options'       => array(
            'no'        => t('No sidebar'),
            'left'      => t('Left'),
            'right' 	=> t('Right'),
        ),
        '#attributes'           => array(
            'class'             => array('select')
        ),
        '#prefix'                     => '<h3 class="md-tabcontent-title">Sidebar position</h3><div class="form-group">',
        '#suffix'                     => '</div>',
        '#field_prefix'               => '<div class="md-selection medium">',
        '#field_suffix'               => '</div>'
    );
    
/*--------------------------------- Skins -------------------------------------------*/
    $form['md_leaders_settings']['design']['design_skin'] = array(
        '#type'             => 'fieldset',
        '#weight'           => -11,
        '#prefix'           => '<div id="ds-skin" class="md-tabcontent clearfix">',
        '#suffix'           => '</div><!-- / #ds-skin -->',
    );
    $form['md_leaders_settings']['design']['design_skin']['skin_color'] = array(
        '#type'             => 'textfield',
        '#title'            => t('Skin Color'),
        '#default_value' => theme_get_setting('skin_color','md_leaders') ? theme_get_setting('skin_color','md_leaders') : '#e95d70',
        '#attributes'       => array(
            'class' => array(
                'form-colorpicker',
            ),
        ),
        '#field_prefix'     => '<div class="form-group label-inline">',
        '#field_suffix'     => '</div>'
    );
}

