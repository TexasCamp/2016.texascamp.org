<?php

/**
 * @file
 * Theme settings general.
 */

function md_leaders_theme_settings_general(&$form, &$form_state) {
    global $base_url;
    $form['md_leaders_settings']['general'] = array(
        '#type'                     => 'fieldset',
        '#weight'               => -5,
        '#prefix'               => '<div id="md-general" class="md-tabcontent clearfix">',
        '#suffix'           => '</div><!-- / #md-general -->',
    );

    $form['md_leaders_settings']['general']['general_htmllist'] = array(
        '#markup'               => '<div id="md-content-sidebar" class="md-content-sidebar">
                                        <ul class="clearfix">
                                            <li><a href="#general-settings"><i class="fa fa-home"></i>Sites Settings</a></li>
                                            <li><a href="#logo-favicon-webclip"><i class="fa fa-picture-o"></i>Logo, Favicon &amp; Webclip</a></li>
                                            <li><a href="#custom-font"><i class="fa fa-font"></i>Custom Font</a></li>
                                        </ul>
                                    </div><!-- /.md-content-sidebar -->
                                    <div class="md-content-main">',
        '#weight'               => -15,
    );
    $form['md_leaders_settings']['general']['general_htmllistclose'] = array(
        '#markup'               => '</div><!-- /.md-content-main -->',
        '#weight'               => 15,
    );

/* 1.   General Settings
--------------------------------------------------------------------------*/
    $form['md_leaders_settings']['general']['general_settings'] = array(
        '#type'                     => 'fieldset',
        '#weight'               => -14,
        '#prefix'               => '<div id="general-settings" class="">',
        '#suffix'        => '</div><!-- / #general-settings -->',
    );
    /*$form['md_leaders_settings']['general']['general_settings']['general_setting_header'] = array(
        '#markup'  =>  '<div class="md-tabcontent-header">
                             <h3 class="md-tabcontent-title">General Settings</h3>
                             <p class="md-tabcontent-description">These settings that change your whole sites</p>
                        </div><!-- /.md-tabcontent-header -->'
    );*/
    $form['md_leaders_settings']['general']['general_settings']['general_setting_content'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div class="md-tabcontent-row">',
        '#suffix'   => '</div><!-- /.md-tabcontent-row -->'
    );
        $themes = list_themes();
        $features = $themes['md_leaders']->info['features'];
        // Toggle settings
        $toggles = array(
            'logo'                      => t('Logo'),
            'name'                      => t('Site name'),
            'slogan'                    => t('Site slogan'),
            'node_user_picture'         => t('User pictures in posts'),
            'comment_user_picture'      => t('User pictures in comments'),
            'comment_user_verification' => t('User verification status in comments'),

            'main_menu'                 => t('Main menu'),
            'secondary_menu'            => t('Secondary menu'),
        );

        // Some features are not always available
        $disabled = array();
        if (!variable_get('user_pictures', 0)) {
            $disabled['toggle_node_user_picture'] = TRUE;
            $disabled['toggle_comment_user_picture'] = TRUE;
        }
        if (!module_exists('comment')) {
            $disabled['toggle_comment_user_picture'] = TRUE;
            $disabled['toggle_comment_user_verification'] = TRUE;
        }

        $form['md_leaders_settings']['general']['general_settings']['general_setting_content']['theme_settings'] = array(
            '#type' => 'fieldset',
            '#prefix' => '<h3 class="md-tabcontent-title">Toggle Display</h3>',
            '#description' => t('Enable or disable the display of certain page elements.'),
        );
        foreach ($toggles as $name => $title) {
            if (in_array($name, $features)) {
                $form['md_leaders_settings']['general']['general_settings']['general_setting_content']['theme_settings']['toggle_' . $name] = array(
                    '#type' => 'checkbox',
                    '#default_value' => theme_get_setting('toggle_' . $name, 'md_leaders'),
                    '#field_suffix' => '<label class="label-checkbox" for="edit-toggle-'.str_replace('_','-',$name).'">'.$title.'</label>',
                    '#attributes'   => array(
                        'class' => array('input-checkbox')
                    ),
                    '#prefix'   =>  '<div class="form-elements">',
                    '#suffix'   => '</div>',
                );
                // Disable checkboxes for features not supported in the current configuration.
                if (isset($disabled['toggle_' . $name])) {
                    $form['md_leaders_settings']['general']['general_settings']['general_setting_content']['theme_settings']['toggle_' . $name]['#disabled'] = TRUE;
                }
            }

        }
        if(in_array('favicon', $features)) {
            $form['md_leaders_settings']['general']['general_settings']['general_setting_content']['theme_settings']['toggle_fvicon'] = array(
                '#type' => 'checkbox',
                '#default_value' => theme_get_setting('toggle_fvicon' , 'md_leaders'),
                '#field_suffix' => '<label class="label-checkbox" for="edit-toggle-fvicon">Shortcut Icon</label>',
                '#attributes'   => array(
                    'class' => array('input-checkbox')
                ),
                '#prefix'   =>  '<div class="form-elements">',
                '#suffix'   => '</div>',
            );
        }

        if (!element_children($form['md_leaders_settings']['general']['general_settings']['general_setting_content']['theme_settings'])) {
            // If there is no element in the theme settings fieldset then do not show
            // it -- but keep it in the form if another module wants to alter.
            $form['md_leaders_settings']['general']['general_settings']['general_setting_content']['theme_settings']['#access'] = FALSE;
        }

/* 2.   Logo, Favicon & Webclip
--------------------------------------------------------------------------*/
    $form['md_leaders_settings']['general']['logo_fav_webclip'] = array(
        '#type'                     => 'fieldset',
        '#weight'               => -13,
        '#prefix'               => '<div id="logo-favicon-webclip">',
        '#suffix'        => '</div><!-- / #general-settings -->',
    );
    /* $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_header'] = array(
        '#markup'  =>  '<div class="md-tabcontent-header">
                             <h3 class="md-tabcontent-title">Logo, Favicon, Webclip Settings</h3>
                             <p class="md-tabcontent-description">You can custom path for logo, favicon and webclip</p>
                        </div><!-- /.md-tabcontent-header -->'
    );*/
    $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div class="md-tabcontent-row">',
        '#suffix'   => '</div><!-- /.md-tabcontent-row -->'
    );


    // Logo settings

        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo'] = array(
            '#type' => 'fieldset',
            '#prefix' => '<h3 class="md-tabcontent-title">Logo image settings</h3>',
            '#description' => t('If toggled on, the following logo will be displayed.'),
            '#attributes' => array('class' => array('theme-settings-bottom')),
            '#weight'   => 1
        );
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['default_logo'] = array(
            '#type' => 'checkbox',
            '#field_suffix' => '<label class="label-checkbox" for="edit-default-logo--2'.'">Use the default logo</label>',
            '#attributes'   => array(
                'class' => array('input-checkbox')
            ),
            '#prefix'   =>  '<div class="form-elements">',
            '#suffix'   => '</div>',
            '#default_value' => theme_get_setting('default_logo', 'md_leaders'),
            '#tree' => FALSE,
            '#description' => t('Check here if you want the theme to use the logo supplied with it.')
        );
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings'] = array(
            '#type' => 'container',
            '#states' => array(
                // Hide the logo settings when using the default logo.
                'invisible' => array(
                    'input[name="default_logo"]' => array('checked' => TRUE),
                ),
            ),
        );

        if(module_exists('media')) {
            $logo = theme_get_setting('logo_normal_upload','md_leaders');
            $logo_retina = theme_get_setting('logo_retina_upload','md_leaders');

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_normal_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $logo_file = new stdClass();
            $logo_file->url = '';
            $logo_file->fid = '';

            $logo_file_hidden_value = theme_get_setting('logo_normal_upload','md_leaders');
            if(is_array($logo_file_hidden_value)) {
                if($logo_file_hidden_value['fid'] != 0) {
                    $file = file_load($logo_file_hidden_value['fid']);
                    if($file) {
                        $logo_file->url = $file->url;
                        $logo_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($logo_file_hidden_value)) {
                    $logo_file = json_decode($logo_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_normal_media_wrapper']['logo_normal_upload_media'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload logo image').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(isset($logo_file->url) ? $logo_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_normal_media_wrapper']['logo_normal_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('logo_normal_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );
            
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_retina_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $logo_retina_file = new stdClass();
            $logo_retina_file->url = '';
            $logo_retina_file->fid = '';

            $logo_retina_file_hidden_value = theme_get_setting('logo_retina_upload','md_leaders');
            if(is_array($logo_retina_file_hidden_value)) {
                if($logo_retina_file_hidden_value['fid'] != 0) {
                    $file = file_load($logo_retina_file_hidden_value['fid']);
                    if($file) {
                        $logo_retina_file->url = $file->url;
                        $logo_retina_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($logo_retina_file_hidden_value)) {
                    $logo_retina_file = json_decode($logo_retina_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_retina_media_wrapper']['logo_retina_upload_media'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload logo retina image').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(!empty($logo_retina_file->url) ? $logo_retina_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_retina_media_wrapper']['logo_retina_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('logo_retina_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );
        }

///////////// Logo footer ///////////////////////////////////////////////////////////////////////

        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo_footer'] = array(
            '#type' => 'fieldset',
            '#prefix' => '<h3 class="md-tabcontent-title">Logo image footer settings</h3>',
            '#description' => t('If toggled on, the following logo footer will be displayed.'),
            '#attributes' => array('class' => array('theme-settings-bottom')),
            '#weight'   => 1
        );
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo_footer']['default_logo_footer'] = array(
            '#type' => 'checkbox',
            '#field_suffix' => '<label class="label-checkbox" for="edit-default-logo-footer'.'">Use the default logo</label>',
            '#attributes'   => array(
                'class' => array('input-checkbox')
            ),
            '#prefix'   =>  '<div class="form-elements">',
            '#suffix'   => '</div>',
            '#default_value' => theme_get_setting('default_logo_footer', 'md_leaders'),
            '#tree' => FALSE,
            '#description' => t('Check here if you want the theme to use the logo supplied with it.')
        );
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo_footer']['settings'] = array(
            '#type' => 'container',
            '#states' => array(
                // Hide the logo settings when using the default logo.
                'invisible' => array(
                    'input[name="default_logo_footer"]' => array('checked' => TRUE),
                ),
            ),
        );

        if(module_exists('media')) {
            $logo_footer = theme_get_setting('logo_footer_upload','md_leaders');
            
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo_footer']['settings']['logo_footer_media_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('md-media-wrapper')
                )
            );
            $logo_footer_file = new stdClass();
            $logo_footer_file->url = '';
            $logo_footer_file->fid = '';

            $logo_footer_file_hidden_value = theme_get_setting('logo_footer_upload','md_leaders');
            if(is_array($logo_footer_file_hidden_value)) {
                if($logo_footer_file_hidden_value['fid'] != 0) {
                    $file = file_load($logo_footer_file_hidden_value['fid']);
                    if($file) {
                        $logo_footer_file->url = $file->url;
                        $logo_footer_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($logo_footer_file_hidden_value)) {
                    $logo_footer_file = json_decode($logo_footer_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo_footer']['settings']['logo_footer_media_wrapper']['logo_footer_upload_media'] = array(
                '#markup'       => '
                    <div class="form-wrapper  mb-20">
                        <h4 class="md-row-title">'.t('Upload Logo Footer').'</h4>
                            <div class="form-elements">
                                <div class="preview">
                                    <img class="img-preview" src="'.(!empty($logo_footer_file->url) ? $logo_footer_file->url : $base_url.'/'.THEME_PATH.'/theme-setting/img/theme-settings/no_image.png').'" alt="">
                                </div>
                            </div>
                            <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                    </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo_footer']['settings']['logo_footer_media_wrapper']['logo_footer_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('logo_footer_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );
        }

////////////////////////////////////////// FAVICON ///////////////////////////////////////////////////////////
    if (in_array('favicon', $features)) {
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon'] = array(
            '#type' => 'fieldset',
            '#prefix' => '<h3 class="md-tabcontent-title">Shortcut icon settings</h3>',
            '#description' => t("Your shortcut icon, or 'favicon', is displayed in the address bar and bookmarks of most browsers."),
            '#weight'   => 2
        );
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['default_favicon'] = array(
            '#type' => 'checkbox',
            '#field_suffix' => '<label class="label-checkbox" for="edit-default-favicon--2'.'">Use the default shortcut icon.</label>',
            '#attributes'   => array(
                'class' => array('input-checkbox')
            ),
            '#prefix'   =>  '<div class="form-elements">',
            '#suffix'   => '</div>',
            '#default_value' => theme_get_setting('default_favicon', 'md_leaders'),
            '#description' => t('Check here if you want the theme to use the default shortcut icon.')
        );
        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings'] = array(
            '#type' => 'container',
            '#states' => array(
                // Hide the favicon settings when using the default favicon.
                'invisible' => array(
                    'input[name="default_favicon"]' => array('checked' => TRUE),
                ),
            ),
        );
        if(module_exists('media')) {
            $fvicon = theme_get_setting('fvicon_upload','md_leaders');
            /*$form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings']['fvicon_upload'] = array(
                '#type' => 'media',
                '#tree' => TRUE,
                '#title' => t('Upload favicon image'),
                '#description' => t("If you don't have direct file access to the server, use this field to upload your shortcut icon."),
                '#default_value' => $fvicon, // e.g. $image = array('fid' => 1)
                '#media_options' => array(
                    'global' => array(
                        'types' => array(
                            'image' => 'image',
                        ),
                        'enabledPlugins' => array(
                            'upload' => 'upload',
                            'media_default--media_browser_1' => 'media_default--media_browser_1',
                        ),
                        'schemes' => array(
                            'public' => 'public',
                        ),
                        'file_directory' => 'media',
                        'file_extensions' => 'png gif jpg jpeg',
                        'uri_scheme' => 'public',
                    ),
                ),
            );*/
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings']['favicon_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $favicon_file = new stdClass();
            $favicon_file->url = '';
            $favicon_file->fid = '';

            $favicon_file_hidden_value = theme_get_setting('fvicon_upload','md_leaders');
            if(is_array($favicon_file_hidden_value)) {
                if($favicon_file_hidden_value['fid'] != 0) {
                    $file = file_load($favicon_file_hidden_value['fid']);
                    if($file) {
                        $favicon_file->url = $file->url;
                        $favicon_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($favicon_file_hidden_value)) {
                    $favicon_file = json_decode($favicon_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings']['favicon_media_wrapper']['favicon_upload_media'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload Favicon Image').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(!empty($favicon_file->url) ? $favicon_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings']['favicon_media_wrapper']['fvicon_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('fvicon_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );
        }

        // Inject human-friendly values for logo and favicon.
        foreach (array('logo' => 'logo.png', 'favicon' => 'favicon.ico') as $type => $default) {
            if (isset($form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content'][$type]['settings'][$type . '_path'])) {
                $element = &$form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content'][$type]['settings'][$type . '_path'];

                // If path is a public:// URI, display the path relative to the files
                // directory; stream wrappers are not end-user friendly.
                $original_path = $element['#default_value'];
                $friendly_path = NULL;
                if (file_uri_scheme($original_path) == 'public') {
                    $friendly_path = file_uri_target($original_path);
                    $element['#default_value'] = $friendly_path;
                }
            }
        }


        $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip'] = array(
            '#type'                     => 'fieldset',
            '#weight'                   => 3,
            '#prefix'                    => '<h3 class="md-tabcontent-title">Webclip settings</h3>',
            '#collapsible'              => TRUE
        );
        if(module_exists('media')) {
            $webclip_57 = theme_get_setting('webclip_57_upload','md_leaders');

            /*$form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_57_upload'] = array(
                '#type' => 'media',
                '#tree' => TRUE,
                '#title' => t('Upload custom iOS 57x57'),
                '#description' => t('Upload a 57px x 57px Png image that will be your website bookmark on retina iOS devices.'),
                '#default_value' => $webclip_57, // e.g. $image = array('fid' => 1)
                '#media_options' => array(
                    'global' => array(
                        'types' => array(
                            'image' => 'image',
                        ),
                        'enabledPlugins' => array(
                            'upload' => 'upload',
                            'media_default--media_browser_1' => 'media_default--media_browser_1',
                        ),
                        'schemes' => array(
                            'public' => 'public',
                        ),
                        'file_directory' => 'media',
                        'file_extensions' => 'png gif jpg jpeg',
                        'uri_scheme' => 'public',
                    ),
                ),
            );*/
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_57_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $webclip_57_file = new stdClass();
            $webclip_57_file->url = '';
            $webclip_57_file->fid = '';

            $webclip_57_file_hidden_value = theme_get_setting('webclip_57_upload','md_leaders');
            if(is_array($webclip_57_file_hidden_value)) {
                if($webclip_57_file_hidden_value['fid'] != 0) {
                    $file = file_load($webclip_57_file_hidden_value['fid']);
                    if($file) {
                        $webclip_57_file->url = $file->url;
                        $webclip_57_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($webclip_57_file_hidden_value)) {
                    $webclip_57_file = json_decode($webclip_57_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_57_media_wrapper']['webclip_57_upload_media'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload Custom iOS 57x57').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(!empty($webclip_57_file->url) ? $webclip_57_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_57_media_wrapper']['webclip_57_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('webclip_57_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );

            $webclip_72 = theme_get_setting('webclip_72_upload','md_leaders');
            /*$form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_72_upload'] = array(
                '#type' => 'media',
                '#tree' => TRUE,
                '#title' => t('Upload custom iOS 72x72'),
                '#description' => t('Upload a 72px x 72px Png image that will be your website bookmark on retina iOS devices.'),
                '#default_value' => $webclip_72, // e.g. $image = array('fid' => 1)
                '#media_options' => array(
                    'global' => array(
                        'types' => array(
                            'image' => 'image',
                        ),
                        'enabledPlugins' => array(
                            'upload' => 'upload',
                            'media_default--media_browser_1' => 'media_default--media_browser_1',
                        ),
                        'schemes' => array(
                            'public' => 'public',
                        ),
                        'file_directory' => 'media',
                        'file_extensions' => 'png gif jpg jpeg',
                        'uri_scheme' => 'public',
                    ),
                ),
            );*/

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_72_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $webclip_72_file = new stdClass();
            $webclip_72_file->url = '';
            $webclip_72_file->fid = '';

            $webclip_72_file_hidden_value = theme_get_setting('webclip_72_upload','md_leaders');
            if(is_array($webclip_72_file_hidden_value)) {
                if($webclip_72_file_hidden_value['fid'] != 0) {
                    $file = file_load($webclip_72_file_hidden_value['fid']);
                    if($file) {
                        $webclip_72_file->url = $file->url;
                        $webclip_72_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($webclip_72_file_hidden_value)) {
                    $webclip_72_file = json_decode($webclip_72_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_72_media_wrapper']['webclip_72_upload_media'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload Custom iOS 72x72').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(!empty($webclip_72_file->url) ? $webclip_72_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_72_media_wrapper']['webclip_72_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('webclip_72_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );

            $webclip_114 = theme_get_setting('webclip_114_upload','md_leaders');
            /*$form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_114_upload'] = array(
                '#type' => 'media',
                '#tree' => TRUE,
                '#title' => t('Upload custom iOS 114x114'),
                '#description' => t('Upload a 114px x 114px Png image that will be your website bookmark on retina iOS devices.'),
                '#default_value' => $webclip_114, // e.g. $image = array('fid' => 1)
                '#media_options' => array(
                    'global' => array(
                        'types' => array(
                            'image' => 'image',
                        ),
                        'enabledPlugins' => array(
                            'upload' => 'upload',
                            'media_default--media_browser_1' => 'media_default--media_browser_1',
                        ),
                        'schemes' => array(
                            'public' => 'public',
                        ),
                        'file_directory' => 'media',
                        'file_extensions' => 'png gif jpg jpeg',
                        'uri_scheme' => 'public',
                    ),
                ),
            );*/
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_114_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $webclip_114_file = new stdClass();
            $webclip_114_file->url = '';
            $webclip_114_file->fid = '';

            $webclip_114_file_hidden_value = theme_get_setting('webclip_114_upload','md_leaders');
            if(is_array($webclip_114_file_hidden_value)) {
                if($webclip_114_file_hidden_value['fid'] != 0) {
                    $file = file_load($webclip_114_file_hidden_value['fid']);
                    if($file) {
                        $webclip_114_file->url = $file->url;
                        $webclip_114_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($webclip_114_file_hidden_value)) {
                    $webclip_114_file = json_decode($webclip_114_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_114_media_wrapper']['webclip_114_upload_media'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload Custom iOS 114x114').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(!empty($webclip_114_file->url) ? $webclip_114_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_114_media_wrapper']['webclip_114_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('webclip_114_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );

            $webclip_144 = theme_get_setting('webclip_144_upload','md_leaders');
            /*$form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_144_upload'] = array(
                '#type' => 'media',
                '#tree' => TRUE,
                '#title' => t('Upload custom iOS 144x144'),
                '#description' => t('Upload a 57px x 57px Png image that will be your website bookmark on retina iOS devices.'),
                '#default_value' => $webclip_144, // e.g. $image = array('fid' => 1)
                '#media_options' => array(
                    'global' => array(
                        'types' => array(
                            'image' => 'image',
                        ),
                        'enabledPlugins' => array(
                            'upload' => 'upload',
                            'media_default--media_browser_1' => 'media_default--media_browser_1',
                        ),
                        'schemes' => array(
                            'public' => 'public',
                        ),
                        'file_directory' => 'media',
                        'file_extensions' => 'png gif jpg jpeg',
                        'uri_scheme' => 'public',
                    ),
                ),
            );*/
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_144_media_wrapper'] = array(
                '#type' => 'container',
                '#attributes'   => array(
                    'class'     => array('md-media-wrapper')
                )
            );
            $webclip_144_file = new stdClass();
            $webclip_144_file->url = '';
            $webclip_144_file->fid = '';

            $webclip_144_file_hidden_value = theme_get_setting('webclip_144_upload','md_leaders');
            if(is_array($webclip_144_file_hidden_value)) {
                if($webclip_144_file_hidden_value['fid'] != 0) {
                    $file = file_load($webclip_144_file_hidden_value['fid']);
                    if($file) {
                        $webclip_144_file->url = $file->url;
                        $webclip_144_file->fid = $file->fid;
                    }
                }
            } else {
                if(!empty($webclip_144_file_hidden_value)) {
                    $webclip_144_file = json_decode($webclip_144_file_hidden_value);
                }

            }

            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_144_media_wrapper']['webclip_144_upload'] = array(
                '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <h4 class="md-row-title">'.t('Upload Custom iOS 144x144').'</h4>
                        <div class="form-elements">
                            <div class="preview">
                                <img class="img-preview" src="'.(!empty($webclip_144_file->url) ? $webclip_144_file->url : $base_url.'/'.THEME_PATH.'/img/theme-settings/no_image.png').'" alt="">
                            </div>
                        </div>
                        <a href="#" class="media-select-button button element-hidden md-button">'.t('Select').'</a>
                </div>'
            );
            $form['md_leaders_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['webclip_144_media_wrapper']['webclip_144_upload'] = array(
                '#type'         => 'hidden',
                '#default_value' => theme_get_setting('webclip_144_upload','md_leaders'),
                '#attributes'       =>  array(
                    'class'         => array('media-hidden-value')
                )
            );
        }
    }


/* 3.   Custom font
--------------------------------------------------------------------------*/
    $form['md_leaders_settings']['general']['custom_font'] = array(
        '#type'                     => 'fieldset',
        '#weight'               => -12,
        '#prefix'               => '<div id="custom-font">',
        '#suffix'        => '</div><!-- / #general-settings -->',
    );
    /*$form['md_leaders_settings']['general']['custom_font']['custom_font_header'] = array(
        '#markup'  =>  '<div class="md-tabcontent-header">
                             <h3 class="md-tabcontent-title">Custom font for frontend pages</h3>
                             <p class="md-tabcontent-description">We define two 2 kinds of webfont: Google Fonts and Typekit</p>
                        </div><!-- /.md-tabcontent-header -->'
    );*/
    $form['md_leaders_settings']['general']['custom_font']['custom_font_content'] = array(
        '#type' => 'fieldset',
        '#prefix'   => '<div class="md-tabcontent-row">',
        '#suffix'   => '</div><!-- /.md-tabcontent-row -->'
    );
        $form['md_leaders_settings']['general']['custom_font']['custom_font_content']['googlewebfonts'] = array(
            '#type'                     => 'textarea',
            '#title'         => t('@import'),
            '#resizable' => FALSE,
            '#rows' => 1,
            '#description' => t("For example: http://fonts.googleapis.com/css?family=Kavoon|Hanalei+Fill"),
            '#default_value'    =>  theme_get_setting('googlewebfonts','md_leaders'),
            '#prefix'                   => '<h3 class="md-tabcontent-title">Google Web Fonts</h3>
        <ul class="steps">
            <li>Go to <a href="http://www.google.com/webfonts" target="_blank">www.google.com/webfonts</a>, choose your fonts and add to collection</li>
      <li>Click &quot;Use&quot; in the bottom bar after choose fonts</li>
      <li>Find &quot;Integrate the fonts into your CSS&quot;, copy all code from that field and paste it below to activate.</li>
        </ul>',
            '#attributes'       => array(
                'class'         => array('input-border')
            )
        );

        $form['md_leaders_settings']['general']['custom_font']['custom_font_content']['custom_font']['typekit_id'] = array(
            '#type'                     => 'textfield',
            '#title'         => t('Typekit'),
            '#description'      => t('<strong>* Note:</strong> Your kit must contain fonts and be published before entering your Typekit ID below. Check out <a href="http://help.typekit.com/customer/portal/articles/6780-adding-fonts-to-your-site" target="_blank">this article at Typekit\'s Help Center</a> for detailed information on how to add fonts to your kit. (Make sure you skip the part about adding CSS selectors, and remember to republish your kit after making any changes.)'),
            '#default_value'    =>  theme_get_setting('typekit_id','md_leaders'),
            '#prefix'                   => '<h3 class="md-tabcontent-title">Enter Your Typekit ID</h3>
        <ul class="steps">
            <li>Go to <a href="http://typekit.com/" target="_blank">www.typekit.com</a> and Log in to your account</li>
            <li>In the top bar of the Typekit website, click the green &quot;Launch Kit Editor&quot; button.</li>
            <li>In the top bar of the popup that appears, click the &quot;Kit Settings&quot; link and paste your domain. Once you\'ve done this, click &quot;Save Settings.&quot;</li>
            <li>In the same top bar of the popup, click the &quot;embed code&quot; link.</li>
            <li>In the overlay that appears, there is a line at the   bottom that says, &quot;If you are using a plugin or service that asks for a   Typekit ID, use this: ____.&quot; This is your Typekit ID. Paste it below to activate.</li>
        </ul><div class="form-group">',
            '#suffix'                   => '</div>',
            '#attributes'               => array(
                'class'                 => array('input-border big')
            )
        );

        
/* Hidden input
--------------------------------------------------------------------------*/
        $form['md_leaders_settings']['general']['general_settings']['general_setting_content']['savedcolor1'] = array(
            '#type'             => 'hidden',
            '#default_value'    => theme_get_setting('savedcolor1','md_leaders'),
            '#attributes' => array(
                    'id' => 'savedcolor1',
                ),
        );
}