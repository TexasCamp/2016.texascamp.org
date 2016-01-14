<?php

function project_form_system_theme_settings_alter(&$form, &$form_state) {

	$default_settings = array();

	$filename = DRUPAL_ROOT . '/' . drupal_get_path('theme', 'project') . '/project.info';
	$info = drupal_parse_info_file($filename);
	if (isset($info['settings'])) {
		$default_settings = $info['settings'];
	}

	// Add checkbox for Search if enabled.
	if (module_exists('search')) {
		$form['theme_settings']['toggle_search'] = array(
			'#type' => 'checkbox',
			'#title' => t('Search'),
			'#default_value' => theme_get_setting('toggle_search'),
		);
	}

	$form['project'] = array(
		'#type' => 'vertical_tabs',
		'#prefix' => '<h2><small>Project</small></h2>',
		'#weight' => -8,
	);

	$form['project_config'] = array(
		'#type' => 'fieldset',
		'#group' => 'project',
		'#title' => t('Display'),
		'#description' => t('Full width, block striping, etc.'),
		'#attributes' => array(
	    'class' => array('columns'),
	  ),
	);
	$form['project_config']['column_left'] = array(
	  '#type' => 'container',
	  '#attributes' => array(
	    'class' => array('column-left'),
	  ),
	);
	$form['project_config']['column_right'] = array(
	  '#type' => 'container',
	  '#attributes' => array(
	    'class' => array('column-right'),
	  ),
	);
	$form['project_config']['column_left']['project_front_container'] = array(
		'#type' => 'select',
		'#title' => t('Full Width Front Page'),
		'#default_value' => theme_get_setting('project_front_container'),
		'#description' => t('Choose to either turn the blocks on the front page into full-width containers or leave them boxed.'),
		'#options' => array(
			0 => t('Boxed'),
			1 => t('Wide'),
		),
	);
	$form['project_config']['column_left']['project_sidebars_front'] = array(
		'#type' => 'select',
		'#title' => t('Sidebars on Front'),
		'#default_value' => theme_get_setting('project_sidebars_front'),
		'#description' => t('If no, the sidebars will never be loaded on the front page. Alternatively, if sidebars are allowed and exist, the front page will never be rendered as wide.'),
		'#options' => array(
			0 => t('No'),
			1 => t('Yes'),
		),
		'#states' => array(
      'visible' => array(
        ':input[name=project_front_container]' => array('value' => 0),
      ),
    ),
	);
	$form['project_config']['column_left']['project_sidebar_column'] = array(
		'#type' => 'select',
		'#title' => t('Sidebar Column Width'),
		'#default_value' => theme_get_setting('project_sidebar_column'),
		'#description' => t('Default column width is col-sm-3, wide is col-sm-4'),
		'#options' => array(
			0 => t('Default'),
			1 => t('Wide'),
		),
	);
	
  $form['project_config']['column_right']['colorize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Colorize Theme'),
    '#default_value' => theme_get_setting('colorize'),
    '#description' => t('Use colors defined to skin the theme.'),
  );

	$form['project_config']['column_right']['project_block_striping'] = array(
		'#type' => 'select',
		'#title' => t('Block Striping'),
		'#default_value' => theme_get_setting('project_block_striping'),
		'#description' => t('Adds odd/even classes to blocks on the home page.'),
		'#options' => array(
			0 => t('No'),
			1 => t('Yes'),
		),
	);

	/********************* Project Regions ***********************/
	$form['project_regions'] = array(
		'#type' => 'fieldset',
		'#group' => 'project',
		'#title' => t('Regions'),
		'#description' => t('Settings for different regions.'),
	);

	$form['project_regions']['header_top'] = array(
		'#type' => 'fieldset',
		'#title' => t('Header Top'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['project_regions']['header_top']['header_top_color'] = array(
		'#type' => 'select',
		'#title' => t('Header Top Color'),
		'#description' => t('Change the color of the header top section.'),
		'#default_value' => (theme_get_setting('header_top_color')) ? theme_get_setting('header_top_color') : 'no-color',
		'#options' => array(
			'no-color' => t('Default (no-color)'),
			'dark' => t('Dark'),
			'colored' => t('Colored'),
		),
	);

	$form['project_regions']['header'] = array(
		'#type' => 'fieldset', 
		'#title' => t('Header'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['project_regions']['header']['header_sticky'] = array(
		'#type' => 'select',
		'#title' => t('Header Sticky'),
		'#description' => t('Change stickiness of header region.'),
		'#default_value' => (theme_get_setting('header_sticky')) ? theme_get_setting('header_sticky') : 'fixed',
		'#options' => array(
			'fixed' => t('Fixed (default)'),
			'static' => t('Static'),
		),
	);
	$form['project_regions']['header']['navbar_actions'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Navbar Actions'),
		'#description' => t('Change actions of navigation bar.'),
		'#default_value' => (theme_get_setting('navbar_actions')) ? theme_get_setting('navbar_actions') : '',
		'#options' => array(
			'onclick' => t('OnClick'),
			'animated' => t('Animated'),
		),
	);

	$form['project_regions']['main_content'] = array(
		'#type' => 'fieldset', 
		'#title' => t('Main Content'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['project_regions']['main_content']['page_title_separator'] = array(
		'#type' => 'select',
		'#title' => t('Page Title Separator'),
		'#description' => t('Adds a separator below the page title.'),
		'#default_value' => (theme_get_setting('page_title_separator')) ? theme_get_setting('page_title_separator') : 0,
		'#options' => array(
			1 => t('None'),
			2 => t('Left to Right'),
			3 => t('Right to Left'),
		),
	);

	$form['project_regions']['footer'] = array(
		'#type' => 'fieldset', 
		'#title' => t('Footer'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['project_regions']['footer']['footer_dark'] = array(
		'#type' => 'select',
		'#title' => t('Footer Dark'),
		'#description' => t('Add dark class to footer.'),
		'#default_value' => (theme_get_setting('footer_dark')) ? theme_get_setting('footer_dark') : 0,
		'#options' => array(
			'light' => t('Light (default)'),
			'dark' => t('Dark'),
		),
	);

	/********************* Project Plugins ***********************/
	$form['project_plugins'] = array(
		'#type' => 'fieldset',
		'#group' => 'project',
		'#title' => t('Plugins'),
		'#description' => t('Additional libraries to enhance the theme.'),
	);
	$form['project_plugins']['animate'] = array(
		'#type' => 'select',
		'#title' => t('Animate.css'),
		'#description' => t('Plug and play, app-like animations for your websites and web apps. Read the docs on !github', array('!github' => l('Github.', 'https://daneden.github.io/animate.css/'))),
		'#default_value' => (theme_get_setting('animate')) ? theme_get_setting('animate') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (animate.min.css)'),
			2 => t('Development (animate.css)'),
			3 => t('CDN'),
		),
	);
	$form['project_plugins']['morphext'] = array(
		'#type' => 'select',
		'#title' => t('Morphext'),
		'#description' => t('The simplest text rotator powered by jQuery and Animate.css. Read the docs on their !site', array('!site' => l('site.', 'http://morphext.fyianlai.com/'))),
		'#default_value' => (theme_get_setting('morphext')) ? theme_get_setting('morphext') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (morphext.min.js)'),
			2 => t('Development (morphext.min.js)'),
		),
		'#states' => array(
      'invisible' => array(
        ':input[name="animate"]' => array('value' => 0),
      ),
    ),
	);

	$form['project_plugins']['bootstrap_notify'] = array(
		'#type' => 'select',
		'#title' => t('Bootstrap Notify'),
		'#description' => t('A jQuery plugin helps to turn standard bootstrap alerts into "growl" like notifications. Read the docs on their !site', array('!site' => l('site.', 'http://bootstrap-notify.remabledesigns.com/'))),
		'#default_value' => (theme_get_setting('bootstrap_notify')) ? theme_get_setting('bootstrap_notify') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (bootstrap-notify.min.js)'),
			2 => t('Development (bootstrap-notify.js)'),
		),
	);
	$form['project_plugins']['chartjs'] = array(
		'#type' => 'select',
		'#title' => t('Chart.js'),
		'#description' => t('Simple, clean and engaging charts for designers and developers. Read the docs on their !site', array('!site' => l('site.', 'http://www.chartjs.org/docs/'))),
		'#default_value' => (theme_get_setting('chartjs')) ? theme_get_setting('chartjs') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (Chart.min.js)'),
			2 => t('Development (Chart.js)'),
			3 => t('CDN'),
		),
	);
	$form['project_plugins']['hover_css'] = array(
		'#type' => 'select',
		'#title' => t('Hover.css'),
		'#description' => t('A collection of CSS3 powered hover effects to be applied to links, buttons, logos, SVG, featured images and so on. Read the docs on !github', array('!github' => l('Github.', 'https://github.com/IanLunn/Hover'))),
		'#default_value' => (theme_get_setting('hover_css')) ? theme_get_setting('hover_css') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (hover.min.css)'),
			2 => t('Development (hover.css)'),
			3 => t('CDN'),
		),
	);
	$form['project_plugins']['hover_css'] = array(
		'#type' => 'select',
		'#title' => t('Hover.css'),
		'#description' => t('A collection of CSS3 powered hover effects to be applied to links, buttons, logos, SVG, featured images and so on. Read the docs on !github', array('!github' => l('Github.', 'https://github.com/IanLunn/Hover'))),
		'#default_value' => (theme_get_setting('hover_css')) ? theme_get_setting('hover_css') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (hover.min.css)'),
			2 => t('Development (hover.css)'),
			3 => t('CDN'),
		),
	);
	$form['project_plugins']['vide'] = array(
		'#type' => 'select',
		'#title' => t('Vide'),
		'#description' => t('Easy as hell jQuery plugin for video backgrounds. Read the docs on !github', array('!github' => l('Github.', 'http://vodkabears.github.io/vide/'))),
		'#default_value' => (theme_get_setting('vide')) ? theme_get_setting('vide') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (jquery.vide.min.js)'),
			2 => t('Development (jquery.vide.js)'),
		),
	);
	$form['project_plugins']['waypoints'] = array(
		'#type' => 'select',
		'#title' => t('Waypoints'),
		'#description' => t('Waypoints is a library that makes it easy to execute a function whenever you scroll to an element. Read the docs on !github', array('!github' => l('Github.', 'https://github.com/imakewebthings/waypoints'))),
		'#default_value' => (theme_get_setting('waypoints')) ? theme_get_setting('waypoints') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (jquery.waypoints.min.js)'),
			2 => t('Development (jquery.waypoints.js)'),
			3 => t('CDN'),
		),
	);
	$form['project_plugins']['jasny'] = array(
		'#type' => 'fieldset', 
		'#title' => t('Jasny Bootstrap'),
		'#description' => t('Jasny Bootstrap is an extension to vanilla Bootstrap, adding a number of features and components. Read the docs on !site', array('!site' => l('Jasny.net.', 'http://www.jasny.net/bootstrap/getting-started/'))),
		'#collapsible' => FALSE,
	);
	$form['project_plugins']['jasny']['jasny_css'] = array(
		'#type' => 'select',
		'#title' => t('Jasny CSS'),
		'#default_value' => (theme_get_setting('jasny_css')) ? theme_get_setting('jasny_css') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (jasny-bootstrap.min.css)'),
			2 => t('Development (jasny-bootstrap.css)'),
			3 => t('CDN'),
		),
	);
	$form['project_plugins']['jasny']['jasny_js'] = array(
		'#type' => 'select',
		'#title' => t('Jasny JS'),
		'#default_value' => (theme_get_setting('jasny_js')) ? theme_get_setting('jasny_js') : 0,
		'#options' => array(
			0 => t('Disabled'),
			1 => t('Production (jasny-bootstrap.min.js)'),
			2 => t('Development (jasny-bootstrap.js)'),
			3 => t('CDN'),
		),
	);

}
