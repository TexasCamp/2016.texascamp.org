<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('MD One column'),
  'category' => t('MD Layouts'),
  'icon' => 'md_onecol.png',
  'theme' => 'md_onecol',
  'css' => 'md_onecol.css',
  'regions' => array('main' => t('Main column')),
);
