<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('MD Three row'),
  'category' => t('MD Layouts'),
  'icon' => 'md_threerow.png',
  'theme' => 'md_threerow',
  'css' => 'md_threerow.css',
  'regions' => array(
        'top' => t('Top'),
        'main' => t('Main'),
        'bottom' => t('Bottom'), 
      ),
);
