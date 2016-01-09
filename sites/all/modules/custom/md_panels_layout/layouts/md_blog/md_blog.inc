<?php

// Plugin definition
$plugin = array(
  'title' => t('MDB Blog Layout'),
  'category' => t('MD Layouts'),
  'icon' => 'md_blog.png',
  'theme' => 'md_blog',
  'admin css' => 'md_blog.admin.css',
  'regions' => array(
    'top' => t('Top'),
    'main' => t('Main'),
    'bottom' => t('Bottom'),  
    'sidebar' => t('Sidebar'),
  ),
);
