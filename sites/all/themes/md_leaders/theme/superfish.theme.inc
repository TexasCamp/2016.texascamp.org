<?php

/**
 * @file
 * Contains the theme function override for 'superfish'.
 */

/**
 * Theme function to allow any menu tree to be themed as a Superfish menu.
 */
function md_leaders_superfish($variables) {  //dsm($variables);
  global $user, $language;

  $id = $variables['id'];
  $menu_name = $variables['menu_name'];
  $mlid = $variables['mlid'];
  $sfsettings = $variables['sfsettings'];

  $menu = menu_tree_all_data($menu_name);

  if (function_exists('i18n_menu_localize_tree')) {
    $menu = i18n_menu_localize_tree($menu);
  }

  // For custom $menus and menus built all the way from the top-level we
  // don't need to "create" the specific sub-menu and we need to get the title
  // from the $menu_name since there is no "parent item" array.
  // Create the specific menu if we have a mlid.
  if (!empty($mlid)) {
    // Load the parent menu item.
    $item = menu_link_load($mlid);
    $title = check_plain($item['title']);
    $parent_depth = $item['depth'];
    // Narrow down the full menu to the specific sub-tree we need.
    for ($p = 1; $p < 10; $p++) {
      if ($sub_mlid = $item["p$p"]) {
        $subitem = menu_link_load($sub_mlid);
        $key = (50000 + $subitem['weight']) . ' ' . $subitem['title'] . ' ' . $subitem['mlid'];
        $menu = (isset($menu[$key]['below'])) ? $menu[$key]['below'] : $menu;
      }
    }
  }
  else {
    $result = db_query("SELECT title FROM {menu_custom} WHERE menu_name = :a", array(':a' => $menu_name))->fetchField();
    $title = check_plain($result);
  }

  $output['content'] = '';
  $output['subject'] = $title;
  if ($menu) {
    // Set the total menu depth counting from this parent if we need it.
    $depth = $sfsettings['depth'];
    $depth = ($sfsettings['depth'] > 0 && isset($parent_depth)) ? $parent_depth + $depth : $depth;

    $var = array(
      'id' => $id,
      'menu' => $menu,
      'depth' => $depth,
      'trail' => superfish_build_page_trail(menu_tree_page_data($menu_name)),
      'sfsettings' => $sfsettings
    );
    if ($menu_tree = theme('superfish_build', $var)) {
      if ($menu_tree['content']) {
        // Add custom HTML codes around the main menu.
        if ($sfsettings['wrapmul'] && strpos($sfsettings['wrapmul'], ',') !== FALSE) {
          $wmul = explode(',', $sfsettings['wrapmul']);
          // In case you just wanted to add something after the element.
          if (drupal_substr($sfsettings['wrapmul'], 0) == ',') {
            array_unshift($wmul, '');
          }
        }
        else {
          $wmul = array();
        }
        $output['content'] = isset($wmul[0]) ? $wmul[0] : '';
        $output['content'] .= '<ul id="mainmenu"';
        $output['content'] .= ' class="nav menu sf-menu responsive-menu superfish sf-' . $menu_name . ' sf-' . $sfsettings['type'] . ' sf-style-' . $sfsettings['style'];
        $output['content'] .= ($sfsettings['itemcounter']) ? ' sf-total-items-' . $menu_tree['total_children'] : '';
        $output['content'] .= ($sfsettings['itemcounter']) ? ' sf-parent-items-' . $menu_tree['parent_children'] : '';
        $output['content'] .= ($sfsettings['itemcounter']) ? ' sf-single-items-' . $menu_tree['single_children'] : '';
        $output['content'] .= ($sfsettings['ulclass']) ? ' ' . $sfsettings['ulclass'] : '';
        $output['content'] .= ($language->direction == 1) ? ' rtl' : '';
        $output['content'] .= '">' . $menu_tree['content'] . '</ul>';
        $output['content'] .= isset($wmul[1]) ? $wmul[1] : '';
      }
    }
  }
  return $output;
}

/**
 * Helper function that builds the nested lists of a Superfish menu.
 */
function md_leaders_superfish_build($variables) { //dsm($variables);
  $output = array('content' => '');
  $id = $variables['id'];
  $menu = $variables['menu'];
  $depth = $variables['depth'];
  $trail = $variables['trail'];
  // Keep $sfsettings untouched as we need to pass it to the child menus.
  $settings = $sfsettings = $variables['sfsettings'];
  $megamenu = $megamenu_below = $settings['megamenu'];
  $total_children = $parent_children = $single_children = 0;
  $i = 1;

  // Reckon the total number of available menu items.
  foreach ($menu as $menu_item) {
    if (!isset($menu_item['link']['hidden']) || $menu_item['link']['hidden'] == 0) {
      $total_children++;
    }
  }

  foreach ($menu as $menu_item) {

    $show_children = $megamenu_wrapper = $megamenu_column = $megamenu_content = FALSE;
    $item_class = $link_options = $link_class = $item_number = array();
    $mlid = $menu_item['link']['mlid'];

    if (!isset($menu_item['link']['hidden']) || $menu_item['link']['hidden'] == 0) {
      $item_class[] = ($trail && in_array($mlid, $trail)) ? 'active' : '';
      // Add helper classes to the menu items and hyperlinks.
      $settings['firstlast'] = ($settings['dfirstlast'] == 1 && $total_children == 1) ? 0 : $settings['firstlast'];
      $item_class[] = ($settings['firstlast'] == 1) ? (($i == 1 && $i == $total_children) ? 'firstandlast' : (($i == 1) ? 'first' : (($i == $total_children) ? 'last' : 'middle'))) : '';
      $settings['zebra'] = ($settings['dzebra'] == 1 && $total_children == 1) ? 0 : $settings['zebra'];
      $item_class[] = ($settings['zebra'] == 1) ? (($i % 2) ? 'odd' : 'even') : '';
      $item_class[] = ($settings['itemcount'] == 1) ? 'sf-item-' . $i : '';
      $item_number = ($menu_item['link']['depth'] == 1) ? str_pad($i, 2, '0', STR_PAD_LEFT) : '';
      //$item_class[] = ($settings['itemdepth'] == 1) ? 'sf-depth-' . $menu_item['link']['depth'] : '';
      //$link_class[] = ($settings['itemdepth'] == 1) ? 'sf-depth-' . $menu_item['link']['depth'] : '';
      $menu_item['link']['localized_options']['attributes']['item_number'] = $item_number;
      $item_class[] = ($settings['liclass']) ? $settings['liclass'] : '';
      if (strpos($settings['hlclass'], ' ')) {
        $l = explode(' ', $settings['hlclass']);
        foreach ($l as $c) {
          $link_class[] = $c;
        }
      }
      else {
        $link_class[] = $settings['hlclass'];
      }
      $i++;

      // Hide hyperlink descriptions ("title" attribute).
      if ($settings['hidelinkdescription'] == 1) {
        unset($menu_item['link']['localized_options']['attributes']['title']);
      }

      // Insert hyperlink description ("title" attribute) into the text.
      $show_linkdescription = ($settings['linkdescription'] == 1 && !empty($menu_item['link']['localized_options']['attributes']['title'])) ? TRUE : FALSE;
      if ($show_linkdescription) {
        if (!empty($settings['hldmenus'])) {
          $show_linkdescription = (is_array($settings['hldmenus'])) ? ((in_array($mlid, $settings['hldmenus'])) ? TRUE : FALSE) : (($mlid == $settings['hldmenus']) ? TRUE : FALSE);
        }
        if (!empty($settings['hldexclude'])) {
          $show_linkdescription = (is_array($settings['hldexclude'])) ? ((in_array($mlid, $settings['hldexclude'])) ? FALSE : $show_linkdescription) : (($settings['hldexclude'] == $mlid) ? FALSE : $show_linkdescription);
        }
        if ($show_linkdescription) {
          $menu_item['link']['title'] .= ' <span class="sf-description">';
          $menu_item['link']['title'] .= (!empty($menu_item['link']['localized_options']['attributes']['title'])) ? $menu_item['link']['localized_options']['attributes']['title'] : array();
          $menu_item['link']['title'] .= '</span>';
          $link_options['html'] = TRUE;
        }
      }

      // Add custom HTML codes around the menu items.
      if ($sfsettings['wrapul'] && strpos($sfsettings['wrapul'], ',') !== FALSE) {
        $wul = explode(',', $sfsettings['wrapul']);
        // In case you just wanted to add something after the element.
        if (drupal_substr($sfsettings['wrapul'], 0) == ',') {
          array_unshift($wul, '');
        }
      }
      else {
        $wul = array();
      }

      // Add custom HTML codes around the hyperlinks.
      if ($settings['wraphl'] && strpos($settings['wraphl'], ',') !== FALSE) {
        $whl = explode(',', $settings['wraphl']);
        // The same as above
        if (drupal_substr($settings['wraphl'], 0) == ',') {
          array_unshift($whl, '');
        }
      }
      else {
        $whl = array();
      }

      // Add custom HTML codes around the hyperlinks text.
      if ($settings['wraphlt'] && strpos($settings['wraphlt'], ',') !== FALSE) {
        $whlt = explode(',', $settings['wraphlt']);
        // The same as above
        if (drupal_substr($settings['wraphlt'], 0) == ',') {
          array_unshift($whlt, '');
        }
        $menu_item['link']['title'] = $whlt[0] . check_plain($menu_item['link']['title']) . $whlt[1];
        $link_options['html'] = TRUE;
      }

      $expanded = ($sfsettings['expanded'] == 1) ? (($menu_item['link']['expanded'] == 1) ? TRUE : FALSE) : TRUE;

      if (!empty($menu_item['link']['has_children']) && !empty($menu_item['below']) && $depth != 0 && $expanded === TRUE) {

        // Megamenu is still beta, there is a good chance much of this will be changed.
        if (!empty($settings['megamenu_exclude'])) {
          if (is_array($settings['megamenu_exclude'])) {
            $megamenu_below = (in_array($mlid, $settings['megamenu_exclude'])) ? 0 : $megamenu;
          }
          else {
            $megamenu_below = ($settings['megamenu_exclude'] == $mlid) ? 0 : $megamenu;
          }
          // Send the result to the sub-menu.
          $sfsettings['megamenu'] = $megamenu_below;
        }
        if ($megamenu_below == 1) {
          $megamenu_wrapper = ($menu_item['link']['depth'] == $settings['megamenu_depth']) ? TRUE : FALSE;
          $megamenu_column = ($menu_item['link']['depth'] == $settings['megamenu_depth'] + 1) ? TRUE : FALSE;
          $megamenu_content = ($menu_item['link']['depth'] >= $settings['megamenu_depth'] && $menu_item['link']['depth'] <= $settings['megamenu_levels']) ? TRUE : FALSE;
        }
        // Render the sub-menu.
        $var = array(
          'id' => $id,
          'menu' => $menu_item['below'],
          'depth' => $depth,
          'trail' => $trail,
          'sfsettings' => $sfsettings
        );
        $children = theme('superfish_build', $var);
        // Check to see whether it should be displayed.
        $show_children = (($menu_item['link']['depth'] <= $depth || $depth == -1) && $children['content']) ? TRUE : FALSE;
        if ($show_children) {
          // Add item counter classes.
          if ($settings['itemcounter']) {
            $item_class[] = 'sf-total-children-' . $children['total_children'];
            $item_class[] = 'sf-parent-children-' . $children['parent_children'];
            $item_class[] = 'sf-single-children-' . $children['single_children'];
          }
          // More helper classes.
          $item_class[] = ($megamenu_column) ? 'sf-megamenu-column' : '';
          $item_class[] = $link_class[] = 'current';
        }
        $parent_children++;
      }
      else {
        $item_class[] = 'deeper';
        $item_class[] = 'parent';
        $single_children++;
      }

      $item_class = implode(' ', array_remove_empty($item_class));

      if (isset($menu_item['link']['localized_options']['attributes']['class'])) {
        $link_class_current = $menu_item['link']['localized_options']['attributes']['class'];
        $link_class = array_merge($link_class_current, array_remove_empty($link_class));
      }
      $menu_item['link']['localized_options']['attributes']['class'] = array_remove_empty($link_class);

      // The Context module uses theme_menu_link, Superfish does not, this is why we have to do this.
      if (function_exists('context_active_contexts')) {
        if ($contexts = context_active_contexts()) {
          foreach ($contexts as $context) {
            if ((isset($context->reactions['menu']))) {
              if ($menu_item['link']['href'] == $context->reactions['menu']) {
                $menu_item['link']['localized_options']['attributes']['class'][] = 'active';
              }
            }
          }
        }
      }

      $link_options += $menu_item['link']['localized_options'];

      // Render the menu item.
      // Should a theme be used for menu items?
      if ($settings['use_item_theme']) {
        $item_variables = array(
          'element' => array(
            'attributes' => array(
              'id' => 'menu-' . $mlid . '-' . $id,
              'class' => trim($item_class),
            ),
            'below' => ($show_children) ? $children['content'] : NULL,
            'item' => $menu_item,
            'localized_options' => $link_options,
          ),
          'properties' => array(
            'megamenu' => array(
              'megamenu_column' => $megamenu_column,
              'megamenu_wrapper' => $megamenu_wrapper,
              'megamenu_content' => $megamenu_content,
            ),
            'use_link_theme' => $settings['use_link_theme'],
            'wrapper' => $whl,
          ),
        );
        $output['content'] .= theme('superfish_menu_item', $item_variables);
      }
      else {
        $output['content'] .= '<li id="menu-' . $mlid . '-' . $id . '"';
        $output['content'] .= ($item_class) ? ' class="' . trim($item_class) . '">' : '>';
        $output['content'] .= ($megamenu_column) ? '<div class="sf-megamenu-column">' : '';
        $output['content'] .= isset($whl[0]) ? $whl[0] : '';
        if ($settings['use_link_theme']) {
          $link_variables = array(
            'menu_item' => $menu_item,
            'link_options' => $link_options,
          );
          $output['content'] .= theme('superfish_menu_item_link', $link_variables);
        }
        else {
          $output['content'] .= l($menu_item['link']['title'], $menu_item['link']['href'], $link_options);
        }
        $output['content'] .= isset($whl[1]) ? $whl[1] : '';
        $output['content'] .= ($megamenu_wrapper) ? '<ul class="sf-megamenu"><li class="sf-megamenu-wrapper ' . $item_class . '">' : '';
        $output['content'] .= ($show_children) ? (isset($wul[0]) ? $wul[0] : '') : '';
        $output['content'] .= ($show_children) ? (($megamenu_content) ? '<ol>' : '<ul>') : '';
        $output['content'] .= ($show_children) ? $children['content'] : '';
        $output['content'] .= ($show_children) ? (($megamenu_content) ? '</ol>' : '</ul>') : '';
        $output['content'] .= ($show_children) ? (isset($wul[1]) ? $wul[1] : '') : '';
        $output['content'] .= ($megamenu_wrapper) ? '</li></ul>' : '';
        $output['content'] .= ($megamenu_column) ? '</div>' : '';
        $output['content'] .= '</li>';
      }
    }
  }
  $output['total_children'] = $total_children;
  $output['parent_children'] = $parent_children;
  $output['single_children'] = $single_children;
  return $output;
}

/**
 * Returns HTML for a menu item.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu item.
 *   - properties: Various properties of a menu item.
 *
 * @ingroup themeable
 */
function md_leaders_superfish_menu_item($variables) {
  $element = $variables['element'];
  $properties = $variables['properties'];
  if (isset($element['item']['link']['localized_options']['attributes']['item_number'])) {
    $item_number = $element['item']['link']['localized_options']['attributes']['item_number'];
  }
  else {
    $item_number = '';
  };
  if (isset($element['item']['link']['localized_options']['attributes']['title'])) {
    $description = $element['item']['link']['localized_options']['attributes']['title'];
  }
  else {
    $description = '';
  };
  $sub_menu = '';

  if ($element['below']) {
    $sub_menu .= isset($variables['wrapper']['wul'][0]) ? $variables['wrapper']['wul'][0] : '';
    $sub_menu .= ($properties['megamenu']['megamenu_content']) ? '<ol>' : '<ul class="nav-child list-unstyled small">';
    $sub_menu .= $element['below'];
    $sub_menu .= ($properties['megamenu']['megamenu_content']) ? '</ol>' : '</ul>';
    $sub_menu .= isset($variables['wrapper']['wul'][1]) ? $variables['wrapper']['wul'][1] : '';
  }

  $output = '<li' . drupal_attributes($element['attributes']) . '>';
  $output .= ($item_number != '') ? '<span class="menu-item-number">' . $item_number . '</span>' : '';
  $output .= ($properties['megamenu']['megamenu_column']) ? '<div class="sf-megamenu-column">' : '';
  $output .= isset($properties['wrapper']['whl'][0]) ? $properties['wrapper']['whl'][0] : '';
  if ($properties['use_link_theme']) {
    $link_variables = array(
      'menu_item' => $element['item'],
      'link_options' => $element['localized_options']
    );
    $output .= theme('superfish_menu_item_link', $link_variables);
  }
  else {
    $output .= l($element['item']['link']['title'], $element['item']['link']['href'], $element['localized_options']);
  }
  $output .= isset($properties['wrapper']['whl'][1]) ? $properties['wrapper']['whl'][1] : '';
  $output .= ($properties['megamenu']['megamenu_wrapper']) ? '<ul class="sf-megamenu"><li class="sf-megamenu-wrapper ' . $element['attributes']['class'] . '">' : '';
  $output .= ($description != '') ? '<span class="menu-item-desc">' . $description . '</span>' : '';
  $output .= $sub_menu;
  $output .= ($properties['megamenu']['megamenu_wrapper']) ? '</li></ul>' : '';
  $output .= ($properties['megamenu']['megamenu_column']) ? '</div>' : '';
  $output .= '</li>';

  return $output;
}

/**
 * Theme a menu item link.
 *
 * @param $variables
 *   An array of variables containing:
 *    - menu_item: The menu item array.
 *    - link_options: An array of link options.
 *
 * @ingroup themeable
 */
function md_leaders_superfish_menu_item_link($variables) {
  $menu_item = $variables['menu_item'];
  if ($menu_item['link']['menu_name'] == 'menu-home-menu') {
    if (isset($menu_item['link']['localized_options']['fragment'])) {
      return '<a href="#' . $menu_item ['link']['localized_options']['fragment'] . '">' . $menu_item['link']['title'] . '</a>';
    }
  }
  if ($menu_item['link']['link_path'] == '<front>' && $menu_item['link']['menu_name'] == 'main-menu') {
    if (isset($menu_item['link']['localized_options']['fragment'])) {
      return '<a href="' . $GLOBALS['base_url'] . '#' . $menu_item ['link']['localized_options']['fragment'] . '">' . $menu_item['link']['title'] . '</a>';
    }
  }
  $link_options = $variables['link_options'];

  return l($menu_item['link']['title'], $menu_item['link']['href'], $link_options);
}

function md_image_save($path, $upload, $form_state_value) {
  if ($image_file = file_save_upload($upload)) {
    $parts = pathinfo($image_file->filename);
    $destination = 'public://' . $parts['basename'];
    $image_file->status = FILE_STATUS_PERMANENT;
    if (file_copy($image_file, $destination, FILE_EXISTS_REPLACE)) {
      $_POST[$path] = $form_state_value[$path] = $parts['basename'];
    }
  }
  if ($file_path = $form_state_value [$path]) {
    $file_scheme = file_uri_scheme($path);
    if ($file_scheme == 'http' || $file_scheme == 'https') {
      $newimagename = basename(rawurldecode($file_path));
      $external_file = file_get_contents(rawurldecode($file_path));
      file_save_data($external_file, 'public://' . $newimagename . '', $replace = FILE_EXISTS_REPLACE);


      $form_state_value[$path] = $newimagename;
    }
  }
  return $form_state_value;
}
