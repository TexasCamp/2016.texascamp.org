<?php
/**
 * @file
 * Theme setting callbacks for the Media Star theme.
 */
global $base_url;
define('THEME_PATH',drupal_get_path('theme','md_leaders'));
// Add media browser js
static $included;

if ($included) {
    return;
}
$included = TRUE;
module_load_include('inc', 'media', 'includes/media.browser');
$javascript = media_browser_js();
foreach ($javascript as $key => $definitions) {
    foreach ($definitions as $definition) {
        $function = 'drupal_add_' . $key;
        call_user_func_array($function, $definition);
    }
}
// Add wysiwyg-specific settings.
$settings = array('wysiwyg_allowed_attributes' => variable_get('media__wysiwyg_allowed_attributes', array('height', 'width', 'hspace', 'vspace', 'border', 'align', 'style', 'class', 'id', 'usemap', 'data-picture-group', 'data-picture-align')));
drupal_add_js(array('media' => $settings), 'setting');

drupal_add_css('http://fonts.googleapis.com/css?family=Open+Sans:400,600','external');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/jquery.cookie.js');

drupal_add_library('system', 'ui.widget');
drupal_add_library('system', 'ui.mouse');
drupal_add_library('system', 'ui.slider');
drupal_add_library('system', 'ui.tabs');
drupal_add_library('system', 'ui.dialog');
drupal_add_library('system', 'ui.draggable');
drupal_add_library('system', 'ui.sortable');
drupal_add_library('system', 'ui.slider');
drupal_add_library('system', 'ui.accordion');

drupal_add_js(array('baseUrl' => $base_url),'setting');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/modernizr.custom.js');
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/style-frame.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/font-awesome.min.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/style-drupal.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/spectrum.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/bootstrap-dialog.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/jquery.mCustomScrollbar.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_leaders') . '/theme-setting/css/jquery-ui-1.10.4.css', array('group' => CSS_THEME));
if(module_exists('icon') && module_exists('fontello')) {
    $icon_bundles = icon_bundles();
    foreach($icon_bundles as $key => $value) {
        if($value['status'] == 1) {
            fontello_process_attached($key);
        }
    }
}
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/spectrum.js');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/bootstrap-dialog.js');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/jquery.choosefont.js');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/jquery.mCustomScrollbar.js');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/jquery.mousewheel.js');

drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/addmore.js');
drupal_add_js(drupal_get_path('theme', 'md_leaders') . '/theme-setting/js/script.js');

require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-general.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-design.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-text.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-display.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-pages.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-code.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/theme-settings-config.inc';

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */

function md_leaders_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL, $no_js_use = FALSE) {
    if(isset($form_id)){
      return;
    }
    // Need to hide default theme settings in system, we create it after
    unset($form['theme_settings']);
    hide($form['logo']);
    hide($form['favicon']);
    // Make default dialog markup for icon
    icon_default_dialog();

    $form['md_leaders_settings']['html_header'] = array(
        '#markup' => '<div id="md-framewp" class="md-framewp">
		<div id="md-framewp-header">
			<!-- /////////////////// ALERT BOX ///////////////// -->
				<div class="md-alert-boxs">

				</div>
		</div><!-- /#md-framewp-header -->
		<div id="md-framewp-body">
			<div id="md-tabs-framewp" class="md-tabs-framewp">
				<ul class="clearfix">
					<li><a href="#md-general">General</a></li>
					<li><a href="#md-design">Design</a></li>
					<li><a href="#md-display">Display</a></li>
					<li><a href="#md-text-typography">Text & Typography</a></li>
					<li><a href="#md-code">Custom Code</a></li>
					<li><a href="#md-config">Backup & Restore</a></li>
				</ul>
			</div><!-- /.md-tabs-framewp -->
			<div class="md-content-framewp">',
        '#weight' => -99,
    );
    md_leaders_theme_settings_general($form, $form_state);
    md_leaders_theme_settings_design($form, $form_state);
    md_leaders_theme_settings_display($form, $form_state);
    md_leaders_theme_settings_text($form, $form_state);
    md_leaders_theme_settings_code($form, $form_state);
    md_leaders_theme_settings_config($form, $form_state);


    $form['actions']['reset']      = array(
        '#type'         => 'submit',
        '#value'        => t('Reset Settings'),
        '#submit'       => array('md_leaders_reset_settings_submit'),
        '#weight'       => 98,
        '#attributes'   => array(
            'class' => array('btn btn-reset'),
            'onClick'   => 'return confirm("Are you sure want to reset all settings to default ?")'
        )
    );
    $form['actions']['submit']['#weight'] = 97;
    $form['actions']['submit']['#attributes'] = array(
        'class' => array('btn btn-save'),
    );
    $form['actions']['#prefix'] = '</div><!-- /.md-content-framewp -->
		</div><!-- /#md-framewp-body -->
		<div id="md-framewp-footer" class="md-framewp-footer">
		    <div class="footer-left">
				<div class="md-button-group">';
    $form['actions']['#suffix'] = '</div>
              </div>
              <div class="footer-right">
              </div>
        </div>
    </div><!-- /.md-framewp -->';

    // Load font styles
    $fonts = load_font_configure();
    drupal_add_js(array('font_array' => $fonts[0]), 'setting');
    drupal_add_js(array('font_vars' => $fonts[1]), 'setting');
    // add for fonts END
    $form['#validate'][] = 'md_leaders_validate_theme_settings';
    $form['#submit'][] = 'md_leaders_save_settings_submit';
}

/**
 * Custom validation for md_leaders theme setting
 */
function md_leaders_validate_theme_settings($form, &$form_state) {

}


/**
 * Final submit handler.
 *
 * Reports what values were finally set.
 */

function md_leaders_save_settings_submit($form, &$form_state) {
    // Exclude unnecessary elements before saving.
    form_state_values_clean($form_state);
    $values = $form_state['values'];
    // Extract the name of the theme from the submitted form values, then remove
    // it from the array so that it is not saved as part of the variable.
    $theme_key = $values['var'];
    unset($values['var']);

    $form_input = $form_state['input'];
//    $form_state['values']['hd_image_slide'] = array();
//    $form_state['values']['hd_ct'] = array();
    $form_state['values']['highlights_info'] = array();
    $form_state['values']['hd_ico'] = array();
    $form_state['values']['ft_social'] = array();
    $form_state['values']['contact_info'] = array();

   foreach($form_state['input'] as $key => $value) {

       
        //Header Social
        $hdsocial_info_match = "/hdsocial_info_order/i";
        if(preg_match($hdsocial_info_match,$key)) {
            $explode = explode("|",$value);
            foreach($explode as $key2 => $value2) {
                $new_key = str_replace("-","_",$value2);
                $new_explode = explode("_",$new_key);
                end($new_explode);
                $number = current($new_explode);
                if($new_key != null) {
                    
                    $icon_input = $form_input['hdsocial_info_icon_'.$number]['icon'];
                    if($icon_input != null){
                        $ft_sc_icon_explode = explode("|",$icon_input);
                        $form_state['values']['hdsocial_info'][$new_key]['icon']['bundle'] = $ft_sc_icon_explode[0];
                        $form_state['values']['hdsocial_info'][$new_key]['icon']['icon'] = $ft_sc_icon_explode[1];
                    }
                    
                    $form_state['values']['hdsocial_info'][$new_key]['detail'] = $form_input['hdsocial_info_detail_'.$number] ? $form_input['hdsocial_info_detail_'.$number] : '';

                }
            }
        }
       
       
       //highlights Detail
        $highlights_info_match = "/highlights_info_order/i";
        if(preg_match($highlights_info_match,$key)) {
            $explode = explode("|",$value);
            foreach($explode as $key2 => $value2) {
                $new_key = str_replace("-","_",$value2);
                $new_explode = explode("_",$new_key);
                end($new_explode);
                $number = current($new_explode);
                if($new_key != null) {
                    $form_state['values']['highlights_info'][$new_key]['detail'] = $form_input['highlights_info_detail_'.$number] ? $form_input['highlights_info_detail_'.$number] : '';

                }
            }
        }

       
       //Header panel ico
        $hd_ico_match = "/hd_ico_order/i";
        if(preg_match($hd_ico_match,$key)) {
            $explode = explode("|",$value);
            foreach($explode as $key2 => $value2) {
                $new_key = str_replace("-","_",$value2);
                $new_explode = explode("_",$new_key);
                end($new_explode);
                $number = current($new_explode);
                if($new_key != null) {
                    $icon_input = $form_input['hd_ico_icon_'.$number]['icon'];
                    if($icon_input != null){
                        $ft_sc_icon_explode = explode("|",$icon_input);
                        $form_state['values']['hd_ico'][$new_key]['icon']['bundle'] = $ft_sc_icon_explode[0];
                        $form_state['values']['hd_ico'][$new_key]['icon']['icon'] = $ft_sc_icon_explode[1];
                    }
                    $form_state['values']['hd_ico'][$new_key]['panel_href'] = $form_input['hd_ico_panel_href_'.$number] ? $form_input['hd_ico_panel_href_'.$number] : '';
                    $form_state['values']['hd_ico'][$new_key]['panel_detail'] = $form_input['hd_ico_panel_detail_'.$number] ? $form_input['hd_ico_panel_detail_'.$number] : '';
                }
            }
        }
       
       
        
       
        //Footer Social
        $ft_social_match = "/ft_social_order/i";
        if(preg_match($ft_social_match,$key)) {
            $explode = explode("|",$value);
            foreach($explode as $key2 => $value2) {
                $new_key = str_replace("-","_",$value2);
                $new_explode = explode("_",$new_key);
                end($new_explode);
                $number = current($new_explode);
                if($new_key != null) {
                    $icon_input = $form_input['ft_social_icon_'.$number]['icon'];
                    if($icon_input != null){
                        $ft_sc_icon_explode = explode("|",$icon_input);
                        $form_state['values']['ft_social'][$new_key]['icon']['bundle'] = $ft_sc_icon_explode[0];
                        $form_state['values']['ft_social'][$new_key]['icon']['icon'] = $ft_sc_icon_explode[1];
                    }
                    $form_state['values']['ft_social'][$new_key]['link'] = $form_input['ft_social_link_'.$number] ? $form_input['ft_social_link_'.$number] : '';

                }
            }
        }
        //Contact Detail
        $contact_info_match = "/contact_info_order/i";
        if(preg_match($contact_info_match,$key)) {
            $explode = explode("|",$value);
            foreach($explode as $key2 => $value2) {
                $new_key = str_replace("-","_",$value2);
                $new_explode = explode("_",$new_key);
                end($new_explode);
                $number = current($new_explode);
                if($new_key != null) {
                    $icon_input = $form_input['contact_info_icon_'.$number]['icon'];
                    if($icon_input != null){
                        $contact_info_icon_explode = explode("|",$icon_input);
                        $form_state['values']['contact_info'][$new_key]['icon']['bundle'] = $contact_info_icon_explode[0];
                        $form_state['values']['contact_info'][$new_key]['icon']['icon'] = $contact_info_icon_explode[1];
                    }
                    $form_state['values']['contact_info'][$new_key]['detail'] = $form_input['contact_info_detail_'.$number] ? $form_input['contact_info_detail_'.$number] : '';

                }
            }
        }
    }


    $form_state['#rebuild'] = true;
    cache_clear_all();
}
function saveImage($path, $upload, $form_state_value) {
    if ($image_file = file_save_upload($upload)) {
        $parts = pathinfo($image_file->filename);
        $destination = 'public://' . $parts['basename'];
        $image_file->status = FILE_STATUS_PERMANENT;
        if (file_copy($image_file, $destination, FILE_EXISTS_REPLACE)) {
            $_POST[$path] = $form_state_value[$path] = $parts['basename'];
        }
    }
    if (isset($form_state_value[$path])) {
        $file_path = $form_state_value[$path];

        $file_scheme = file_uri_scheme($path);
        if($file_scheme == 'http' || $file_scheme == 'https'){
            $newimagename = basename(rawurldecode($file_path));
            $external_file = file_get_contents(rawurldecode($file_path));
            file_save_data($external_file, 'public://'.$newimagename.'',$replace = FILE_EXISTS_REPLACE);
            $form_state_value[$path] = $newimagename;
        }
    }
    return $form_state_value;
}
/**
 * @param $form
 * @param $form_state
 * Reset all theme settings
 */
function md_leaders_reset_settings_submit($form, &$form_state){
    $theme_settings = variable_get('theme_md_leaders_settings');
    $default_settings = _md_leaders_theme_default_settings($theme_settings);
    variable_set('theme_md_leaders_settings',null);
    variable_set('theme_md_leaders_settings',$default_settings);
    drupal_set_message('All settings reset to default');
    cache_clear_all();
}
/**
 * Backup Theme Settings
 */
function md_leaders_backup_theme_settings() {
    global $theme_key;
    $theme_settings = variable_get('theme_md_leaders_settings');
    $current_time = time();
    $cv_datetime = date("Y-m-d",$current_time);
    $backup_file = serialize(base64_encode(drupal_json_encode($theme_settings)));
    $bu_folder = 'public://md_leaders_backup';
    if(file_prepare_directory($bu_folder) === false) {
        drupal_mkdir($bu_folder);
    }
    if (file_unmanaged_save_data($backup_file, $bu_folder . '/'.str_replace('_','-','md_leaders').'-backup-'.$cv_datetime.'-'.$current_time.'.txt', FILE_EXISTS_REPLACE) === FALSE) {
        drupal_set_message(t("Could not create backup file."));
        return;
    } else {
        drupal_set_message(t("Backup Theme Settings Successful!"));
        drupal_set_message(t("Your backup settings is stored in ".file_create_url(''.$bu_folder.'/'.str_replace('_','-','md_leaders').'-backup-'.$cv_datetime.'-'.$current_time.'.txt').""));
    }
}
/**
 * Restore Theme settings
 */
function md_leaders_restore_theme_settings($form, &$form_state) {
    $values = $form_state['values'];
    if($values['restore_type'] !=  null) {

        if($values['restore_type'] == 'upload') {
            if($form_state['values']['restore_file_media_upload']['fid'] != 0) {
                $file = file_load($form_state['values']['restore_file_media_upload']['fid']);
                if($file == false) {
                    drupal_set_message(t("Your file upload isn't found, please upload again"),'warning');
                    return;
                }

                $file_content = file_get_contents($file->uri);
                $restore_settings = drupal_json_decode(base64_decode(unserialize($file_content)));
                if(is_array($restore_settings)) {
                    variable_set('theme_md_leaders_settings',array());
                    variable_set('theme_md_leaders_settings',$restore_settings);
                    file_delete($file,$force = true);
                    cache_clear_all();
                    drupal_set_message(t('All your theme settings have been restored'));
                } else {
                    drupal_set_message(t("Your file upload isn't correct, please upload again"),'warning');
                    return;
                }


            } else {
                drupal_set_message(t('Please choose your file upload'),'error');
                return;
            }
        } else {
            if($values['restore_from_file'] == null) {
                drupal_set_message('Choose your backup file in list or move back up to backup folder','warning');
                return;
            } else {
                $file_content = file_get_contents("public://md_leaders_backup/{$values['restore_from_file']}");
                $restore_settings = drupal_json_decode(base64_decode(unserialize($file_content)));
                if(is_array($restore_settings)) {
                    variable_set('theme_md_leaders_settings',array());
                    variable_set('theme_md_leaders_settings',$restore_settings);
                    cache_clear_all();
                    drupal_set_message(t('All your theme settings have been restored'));
                } else {
                    drupal_set_message(t("Your choosen backup file isn't correct, please choose again"),'warning');
                    return;
                }
            }
        }
    }


    if ($restore_file = file_save_upload('restore_file_simple_upload')) {
        $file_content = file_get_contents($restore_file->uri);
        $restore_settings = drupal_json_decode(base64_decode(unserialize($file_content)));
        variable_set('theme_md_leaders_settings',$restore_settings);
        cache_clear_all();
        drupal_set_message(t('All your theme settings have been restored'));
    }
    if(isset($form_state['values']['restore_file_media_upload'])) {

    }

}


function icon_default_markup() {
    $icon_bundles = icon_bundles();
}
/**
 * Analys goole link to get font information
 */
function _md_leaders_process_google_web_font($fonts) {
    if (strpos($fonts, '@import url(') !== FALSE) {
        preg_match("/http:\/\/\s?[\'|\"]?(.+)[\'|\"]?\s?(\)|\')/Uix", $fonts, $ggwflink);
    }

    preg_match('/([^\?]+)(\?family=)?([^&\']+)/i', $fonts, $matches);
    $gfonts = explode("|", $matches[3]);

    for ($i = 0; $i < count($gfonts); $i++) {
        $gfontsdetail = explode(":", $gfonts[$i]);
        $gfontname = str_replace("+", " ", $gfontsdetail['0']);
        $fontarray[] = $gfontname;
        if (array_key_exists('1', $gfontsdetail)) {
            $tmpft = explode(",", $gfontsdetail['1']);
            $gfontweigth[$i] = "";
            for ($j = 0; $j < count($tmpft); $j++) {
                if (preg_match("/italic/i", $tmpft[$j])) {
                    $gfontstyle = "i";
                } else {
                    $gfontstyle = "n";
                }
                $tmpw = str_replace("italic", "", $tmpft[$j]);
                $seperator = ",";

                if ($j == (count($tmpft) - 1)) {
                    $seperator = "";
                }

                if ($tmpw) {
                    $gfontweigth[$i] .= $gfontstyle . str_replace("00", "", $tmpw) . $seperator;
                } else {
                    $gfontweigth[$i] .= "n4" . $seperator;
                }
            }
        } else {
            $gfontweigth[$i] = "n4";
        }
        $fontvars[] = array(
            'CSS' => '"' . $gfontname . '"',
            'Weight' => $gfontweigth[$i],
        );
    }

    return array($fontarray, $fontvars);
}
/**
 * Get fonts information from type-kit id
 */
function _md_leaders_process_typekit_font($typekit_id) {
    $tk_url = 'http://typekit.com/api/v1/json/kits/' . $typekit_id . '/published';
    $typekit = json_decode(file_get_contents($tk_url), true);
    for ($i = 0; $i < count($typekit['kit']['families']); $i++) {
        $fontarray[] = $typekit['kit']['families'][$i]['name'];
        $fontweight = "";
        for ($j = 0; $j < count($typekit['kit']['families'][$i]['variations']); $j++) {
            if (($j + 1) == count($typekit['kit']['families'][$i]['variations'])) {
                $fontweight .= $typekit['kit']['families'][$i]['variations'][$j];
            } else {
                $fontweight .= $typekit['kit']['families'][$i]['variations'][$j] . ',';
            }
        }
        $fontvars[] = array(
            'CSS' => $typekit['kit']['families'][$i]['css_stack'],
            'Weight' => $fontweight,
        );
    }

    return array($fontarray, $fontvars);
}
/**
 * Load font configure
 */
function load_font_configure() {
    $theme_default = variable_get('theme_default', 'Bartik');
    $fontarray = array(
        t('Default'),
        t('Arial'),
        t('Verdana'),
        t('Trebuchet MS'),
        t('Georgia'),
        t('Times New Roman'),
        t('Tahoma'),
    );

    $fontvars = array(
        array('CSS' => '', 'Weight' => 'n4'),
        array('CSS' => 'Arial, sans-serif', 'Weight' => 'n4, n7, i4, i7'),
        array('CSS' => 'Verdana, Geneva, sans-serif', 'Weight' => 'n4, n7, i4, i7'),
        array('CSS' => 'Trebuchet MS, Tahoma, sans-serif', 'Weight' => 'n4, n7, i4, i7'),
        array('CSS' => 'Georgia, serif', 'Weight' => 'n4, n7, i4, i7'),
        array('CSS' => 'Times New Roman, serif', 'Weight' => 'n4, n7, i4, i7'),
        array('CSS' => 'Tahoma, Geneva, Verdana, sans-serif', 'Weight' => 'n4, n7, i4, i7'),
    );
    $google_font = theme_get_setting('googlewebfonts','md_leaders');
    if ($google_font != '') {
        $result = _md_leaders_process_google_web_font($google_font);
        add_font_style($result, $fontarray, $fontvars);
    }
    $typekit = theme_get_setting('typekit_id','md_leaders');;

    if ($typekit != '') {
        $result = _md_leaders_process_typekit_font($typekit);
        add_font_style($result, $fontarray, $fontvars);
    }

    return array($fontarray, $fontvars);
}

function add_font_style($results, &$font_array, &$font_vars) {
    if (is_array($results)) {
        foreach ($results[0] as $id => $font_name) {
            $key = array_search($font_name, $font_array);
            if ($key === FALSE) {
                $font_array[] = $font_name;
                $font_vars[] = $results[1][$id];
            } else {
                $font_vars[$key] = $results[1][$id];
            }
        }
    }
}

/**
 * @param $directory
 * @return array
 * Get Directory List
 */
function getDirectoryList ($directory){
    // create an array to hold directory list
    $results = array();
    // create a handler for the directory
    $handler = opendir($directory);
    // open directory and walk through the filenames
    while ($file = readdir($handler)) {
        // if file isn't this directory or its parent, add it to the results
        if ($file != "." && $file != "..") {
            $results[] = $file;
        }
    }
    // tidy up: close the handler
    closedir($handler);
    // done!
    return $results;
}
/**
 * @param $haystack
 * @param $needle
 * @param int $offset
 * @return bool
 * Check string in string
 */
function strposa($haystack, $needle, $offset=0) {
    if(!is_array($needle)) $needle = array($needle);
    foreach($needle as $query) {
        if(strpos($haystack, $query, $offset) !== false) return true; // stop on first true result
    }
    return false;
}
function icon_default_dialog() {

    $options = array();
    $icon_default_value = array();
    if(module_exists('icon')) {
        foreach (icon_bundles() as $bundle_name => $bundle) {
            if (!$bundle['status']) {
                continue;
            }
            foreach ($bundle['icons'] as $icon_key => $icon_value) {
                $icon_name = is_string($icon_key) ? $icon_key : $icon_value;
                if (is_array($icon_value) && isset($icon_value['name'])) {
                    $icon_name = $icon_value['name'];
                }
                $icon_title = is_string($icon_value) ? $icon_value : $icon_name;
                if (is_array($icon_value) && isset($icon_value['title'])) {
                    $icon_title = $icon_value['title'];
                }
                $options[$bundle['title']][$bundle['name'] . '|' . $icon_name] = $icon_title;
            }
            $icon_default_value = $options;
        }
        $icon_mark_up = '';
        $icon_fake_markup = '<ul class="list-icon">';
        foreach($icon_default_value as $key => $value) {
            $icon_mark_up .= '<option selected="selected" value="">- No Icon -</option><optgroup label="'.$key.'">';
            foreach ($icon_default_value[$key] as $key2 => $value2) {
                $fake_icon_explode = explode("|",$key2);
                $icon_fake_markup .= '<li><a href="#'.$fake_icon_explode[1].'" class="fake-icon" alt="'.$fake_icon_explode[1].'" icon-name="'.$fake_icon_explode[1].'" data-bundle="'.$fake_icon_explode[0].'" data-icon="'.$key2.'"><i class="'.$fake_icon_explode[0].' '.$fake_icon_explode[1].'"></i></a></li>';
                $icon_mark_up .= '<option value="'.$key2.'">'.$value2.'</option>';
            }
            $icon_mark_up .= '</optgroup>';
        }
        $icon_fake_markup .= '</ul>';
        drupal_add_js(array('icMarkUp' => $icon_mark_up),'setting');
        drupal_add_js(array('icFake' => $icon_fake_markup),'setting');
    }

}

/**
 * Default theme settings
 */
function _md_leaders_theme_default_settings ($theme_settings) {
    $default_settings = array();
    foreach ($theme_settings as $key => $setting) {
        $default_settings[$key] = null;
    }
    $default_settings['toggle_logo'] = 1;
    $default_settings['toggle_name'] = 0;
    $default_settings['toggle_slogan'] = 0;
    $default_settings['toggle_node_user_picture'] = 1;
    $default_settings['toggle_comment_user_picture'] = 1;
    $default_settings['toggle_comment_user_verification'] = 0;
    $default_settings['toggle_favicon'] = 1;
    $default_settings['toggle_main_menu'] = 0;
    $default_settings['toggle_secondary_menu'] = 0;
    $default_settings['default_logo'] = 1;
    $default_settings['default_favicon'] = 1;
    
    $default_settings['default_logo_footer'] = 1;
    $default_settings['default_marker_pic'] = 1;
    $default_settings['copyright_text'] = '&copy; Copyright - Leaders Theme by <a href="http://megadrupal.com">MegaDrupal</a>';
    
    $default_settings['skins'] = 'default';
    $default_settings['nodetitle_enable'] = 0;
    $default_settings['typo_view_title_enable'] = 0;
//    $default_settings['social_link_1'] = 'http://facebook.com';
    
    
//    $default_settings['place_text'] = 'BEAUTYSPOT';
//    $default_settings['place_dec'] = '9015 Sunset Boulevard';
//    $default_settings['place_info'] = 'Ca 90069';
//    $default_settings['time-work_first'] = '10:00 - 16:00';
//    $default_settings['time-work_second'] = '10:00 - 14:00';
//    $default_settings['time-work_end'] = 'Closed';
//    
//    $default_settings['place_section_enabled'] = 1;
//    $default_settings['time-work_section_enabled'] = 1;
//    $default_settings['place_headerpanel_enabled'] = 1;
//    $default_settings['time-work_headerpanel_enabled'] = 1;
//    
//    
//    
//    $default_settings['default_background_about'] = 1;
//    $default_settings['default_background_service'] = 1;
//    $default_settings['default_background_product'] = 1;
    
//    $default_settings['nf_background'] = 'custom';
//    $default_settings['preloader_delay_time'] = '350';
//    $default_settings['preloader_bg_type'] = 'skin';
//    $default_settings['preloader_type'] = '1';
//    $default_settings['preloader_enable_logo'] = 1;
//    $default_settings['menu_sticky'] = 1;
//    $default_settings['menu_bg_color'] = '1A1A1A';
//    $default_settings['menu_link_color'] = '7A7A7A';
//    $default_settings['menu_link_hover_color'] = 'FFFFFF';
//    $default_settings['nf_text'] = 'Oops! I couldnt find that one.<br>Click the button below to go back home.';
//    $default_settings['css3_textarea'] = 0;
//    $default_settings['webclip_precomp'] = 1;
//    $default_settings['maintenance_message'] = '<p><span>Our awesome website is</span> <br> Under construction </p>';
    $default_settings['contact_text'] = 'Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim.Aliquam lorem ante, dapibus in.';
//    $default_settings['contact_map'] = 'https://maps.google.com/maps?f=q&amp;source=s_q&amp;hl=en&amp;geocode=&amp;q=Sunset+Boulevard,+Los+Angeles,+CA,+United+States&amp;aq=0&amp;oq=sunset+boul&amp;sll=37.0625,-95.677068&amp;sspn=61.323728,135.263672&amp;ie=UTF8&amp;hq=&amp;hnear=Sunset+Blvd,+Los+Angeles&amp;ll=34.080988,-118.412647&amp;spn=0.003985,0.008256&amp;t=m&amp;z=14&amp;output=embed';

    return $default_settings;
}