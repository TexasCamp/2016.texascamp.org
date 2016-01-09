<?php

/**
 * @file
 * Theme settings .
 */

function md_leaders_theme_settings_code(&$form, &$form_state) {
	$form['md_leaders_settings']['code'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> 0,
		'#prefix'  				=> '<div id="md-code" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #md-custom-code -->',
	);
	
	$form['md_leaders_settings']['code']['code_htmllist'] = array(
		'#markup' 				=> '<div id="md-content-sidebar" class="md-content-sidebar">
                                        <ul class="clearfix">
                                            <li><a href="#code-header"><i class="fa fa-code"></i>Header Code</a></li>
                                            <li><a href="#code-footer"><i class="fa fa-code"></i>Footer Code</a></li>
                                            <li><a href="#code-css"><i class="fa fa-code"></i>Custom CSS Code</a></li>
                                        </ul>
                                    </div><!-- /.md-content-sidebar -->
			                        <div class="md-content-main">',
		'#weight' 				=> -15,
	);
	
	$form['md_leaders_settings']['code']['code_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);
	
	$form['md_leaders_settings']['code']['header_code'] = array(
		'#type' => 'textarea',
		'#resizable' => FALSE,
		'#rows' => 10,
		'#default_value' => theme_get_setting('header_code','md_leaders'),
		'#description' => t('The following code will be added in the &lt;head&gt; tag. Useful if you want to add additional script such as CSS or JS'),
		'#prefix'  				=> '<div id="code-header"><h3 class="md-tabcontent-title">'.t('Header Code').'</h3>',
		'#suffix'        => '</div><!-- / #code-header -->',
        '#attributes'           => array(
            'class'             => array('input-border big')
        )
	);
	
	$form['md_leaders_settings']['code']['footer_code'] = array(
		'#type' => 'textarea',
		'#resizable' => FALSE,
		'#rows' => 10,
		'#default_value' => theme_get_setting('footer_code','md_leaders'),
		'#description' => t('The following code will be added before the &lt;/body&gt; tag.'),
		'#prefix'  				=> '<div id="code-footer"><h3 class="md-tabcontent-title">'.t('Footer Code').'</h3>',
		'#suffix'        => '</div><!-- / #code-footer -->',
        '#attributes'           => array(
            'class'             => array('input-border big')
        )
	);
	
	$form['md_leaders_settings']['code']['custom_css'] = array(
		'#type' => 'textarea',
		'#resizable' => FALSE,
		'#rows' => 10,
		'#default_value' => theme_get_setting('custom_css','md_leaders'),
		'#description' => t('Insert custom CSS code in here (without &lt;/style&gt; tag). This overrides any other stylesheets. eg: a.button{color:green}'),
		'#prefix'  				=> '<div id="code-css"><h3 class="md-tabcontent-title">'.t('Custom CSS Code').'</h3>',
		'#suffix'        => '</div><!-- / #code-css -->',
        '#attributes'           => array(
            'class'             => array('input-border big')
        )
	);
}