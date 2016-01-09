<?php

/**
 * @file
 * Theme settings .
 */

function md_leaders_theme_settings_config(&$form, &$form_state) {
    $form['md_leaders_settings']['config'] = array(
        '#type'                     => 'fieldset',
        '#weight'               => 0,
        '#prefix'               => '<div id="md-config" class="md-tabcontent clearfix">',
        '#suffix'        => '</div><!-- / #md-config -->',
    );

    $form['md_leaders_settings']['config']['config_htmllist'] = array(
        '#markup'               => '<div id="md-content-sidebar" class="md-content-sidebar">
                                        <ul class="clearfix">
                                            <li><a href="#config-backup"><i class="fa fa-rotate-left"></i>Backup</a></li>
                                            <li><a href="#config-restore"><i class="fa fa-cog"></i>Restore</a></li>
                                        </ul>
                                    </div><!-- /.md-content-sidebar -->
                                    <div class="md-content-main">',
        '#weight'               => -15,
    );

    $form['md_leaders_settings']['config']['config_htmllistclose'] = array(
        '#markup'               => '</div><!-- /.md-listleft -->',
        '#weight'               => 15,
    );

    $form['md_leaders_settings']['config']['backup'] = array(
        '#type' => 'fieldset',
        '#prefix'               => '<div id="config-backup"><h3 class="md-tabcontent-title">'.t('Backup Options').'</h3>',
        '#suffix'        => '</div><!-- / #backup -->',
    );
    $form['md_leaders_settings']['config']['backup']['backup_html'] = array(
        '#markup'     => '<div class="last-backup"></div>',
        '#prefix'     => '<p><strong>You can use button below to backup your current theme settings</strong></p>
                          <p>Remember save your current settings before backup</p>',
    );
    /*$form['md_leaders_settings']['config']['backup']['backup_code'] = array(
        '#type'         => 'textarea',
        '#description'        => 'Save your code'
    );*/
    $form['md_leaders_settings']['config']['backup']['backup_theme_settings'] = array(
        '#type' => 'submit',
        '#value'    => t('Backup All Settings'),
        '#submit'   => array('md_leaders_backup_theme_settings'),
    );

    $form['md_leaders_settings']['config']['restore'] = array(
        '#type' => 'fieldset',
        '#prefix'               => '<div id="config-restore"><h3 class="md-tabcontent-title">'.t('Restore Options').'</h3>',
        '#suffix'        => '</div><!-- / #restore -->',
    );

    $form['md_leaders_settings']['config']['restore']['restore_type'] = array(
        '#type'                     => 'select',
        '#title'                    => 'Choose type of restore theme settings',
        '#options'                  => array(
            'upload'                => t('Upload file'),
            'select'                => t('Select list files')
        ),
        '#attributes' => array(
            'class' => array('select'),
        ),
        '#prefix'                   => '<div class="form-group">',
        '#suffix'                   => '</div>',
        '#field_prefix'           => '<div class="md-selection big">',
        '#field_suffix'           => '</div>',
    );
    if(module_exists('media')) {
       /* $form['md_leaders_settings']['config']['restore']['restore_file_media_upload'] = array(
            '#type' => 'media',
            '#tree' => TRUE,
            '#title' => t('Upload Your Theme Settings Backup File'),
            '#description' => t(""),
            '#default_value' => array(), // e.g. $image = array('fid' => 1)
            '#media_options' => array(
                'global' => array(
                    'types' => array(
                        'document'  => 'document'
                    ),
                    'enabledPlugins' => array(
                        'upload'    => 'upload',
                    ),
                    'schemes' => array(
                        'public'    => 'public',
                        'http'      => 'http',
                        'https'     => 'https'
                    ),
                    'file_directory' => 'media',
                    'file_extensions' => 'txt',
                ),
            ),
            '#states'           => array(
                'visible'       => array(
                    ':input[name="restore_type"]' => array(
                        'value'     => 'upload'
                    )
                )
            ),
        );*/
    } else {
        $form['md_leaders_settings']['config']['restore']['restore_file_simple_upload'] = array(
            '#type'         => 'file',
            '#title'        => 'Upload your backup file to restore theme settings'
        );
    }
    $bu_folder = 'public://md_leaders_backup';
    if(file_prepare_directory($bu_folder) === false) {
        drupal_mkdir($bu_folder);
    }
    $backup_dir = getDirectoryList('public://md_leaders_backup');
    $list_files = array();
    if(!$backup_dir)
        $backup_dir = array();
    foreach($backup_dir as $key => $value) {
        if(strpos((string)($value),''.str_replace('_','-','md_leaders').'-backup') !== FALSE)
            $list_files[$value] = $value;
    }
    $form['md_leaders_settings']['config']['restore']['restore_from_file'] = array(
        '#type'             => 'select',
        '#options'          => $list_files,
        '#title'            => 'Choose your file you want to backup (Select list files are stored in "public://md_leaders_backup" folder)',
        '#attributes' => array(
            'class' => array('select'),
        ),
        '#prefix'                   => '<div class="form-group">',
        '#suffix'                   => '</div>',
        '#field_prefix'           => '<div class="md-selection big">',
        '#field_suffix'           => '</div>',
        '#states'           => array(
            'visible'       => array(
                ':input[name="restore_type"]' => array(
                    'value'     => 'select'
                )
            )
        ),
    );
    /*
    $form['md_leaders_settings']['config']['restore']['restore_code'] = array(
        '#type' => 'textarea',
        '#title'    => t('Transfer Theme Options Data'),
        '#default_value' => '',
        '#description' => t('You can transfer the saved options data between different installs by copying the text inside the text box. To import data from another install, replace the data in the text box with the one from another install and click "Restore Options".')
    );
    */
    $form['md_leaders_settings']['config']['restore']['restore_theme_settings'] = array(
        '#type' => 'submit',
        '#value'    => t('Restore Settings'),
        '#submit'   => array('md_leaders_restore_theme_settings'),
    );


}