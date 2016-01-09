<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
**/


include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme/form.theme.inc';
include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme/pager.theme.inc';
include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme/textfield.theme.inc';
include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme/textarea.theme.inc';
//include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme/superfish.theme.inc';
include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme/webform_element.theme.inc';

//custom menu main
//function md_leaders_links__system_main_menu($variables) {
//   $pid = variable_get('menu_main_links_source', 'main-menu');
//    $tree = menu_tree($pid);
//	return drupal_render($tree);
//}
function md_leaders_links__system_main_menu($vars) {
    $class = implode($vars['attributes']['class'], ' ');
    $html = '<ul class="' . $class . '">';
    foreach ($vars['links'] as $key => $link) {
        if (is_numeric($key)) {
            $sub_menu = '';
            $link_class = '';
            $link_title = $link['#title'];
            if (!empty($link['#below'])) {
                $link_class = ' class="dropdown"';
                $sub_menu = theme('links__system_main_menu', array('links' => $link['#below'], 'attributes' => array('class' => array('dropdown-menu'))));
            }
            $html .= '<li' . $link_class . '>' . l($link_title, $link['#href'], $link) . $sub_menu . '</li>';
        }
    }
    $html .= '</ul>';

    return $html;
}

function md_leaders_breadcrumb($variables) {
  if (count($variables['breadcrumb']) > 0) {  
    return '<ul class="breadcrumb"><li>' . implode('</li><li>', $variables['breadcrumb']) . '</li></ul>';
  }
}

/**
 * preprocess for module panel
 */
//function md_leaders_preprocess_panels_pane(&$vars) {
//}

/**
 * Removes the ugly .panels-separator.
 */
function md_leaders_panels_default_style_render_region($variables) {
  $output = '';
  $output .= implode('', $variables['panes']);
  return $output;
}

function md_leaders_field__field_portfolio_skills__portfolio($vars) {
  $values = array();
  foreach ($vars['items'] as $item) {
    $values[] = l($item['#title']);
  }
  return implode(", ", $values);
}


/*---------------------------------------------------------------------------------------
                    THEME SETTING
-----------------------------------------------------------------------------------------*/
include_once './' . drupal_get_path('theme', 'md_leaders') . '/theme-setting/inc/template.process.inc';

function base_url() {
    global $base_url;
    return $base_url;
}
