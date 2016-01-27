<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<!--[if IE 9]> <html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>" class="ie9"> <![endif]-->
<!--[if !IE]><!-->
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<!--
_______                          __________      _____                           _____             
__  __ \___________________      ___  ____/________  /______________________________(_)___________ 
_  / / /__  __ \  _ \_  __ \     __  __/  __  __ \  __/  _ \_  ___/__  __ \_  ___/_  /__  ___/  _ \
/ /_/ /__  /_/ /  __/  / / /     _  /___  _  / / / /_ /  __/  /   __  /_/ /  /   _  / _(__  )/  __/
\____/ _  .___/\___//_/ /_/      /_____/  /_/ /_/\__/ \___//_/    _  .___//_/    /_/  /____/ \___/ 
       /_/                                                        /_/                              

Open Enterprise CMS brought to you by Levelten Interactive.
http://getcm2.com

-->
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <!-- HTML5 element support for IE6-8 -->
  <!--[if lt IE 9]>
    <script src="//html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
    <div class="page-wrapper">

      <div class="header-container">
        <?php include 'includes/header_top.inc'; ?>


        <!-- Header -->
<header <?php if(!empty($header_attr)) {print drupal_attributes($header_attr);} ?> >
  <div class="container">
    <div class="row">

        <div class="col-md-1">
          <!-- header-left start -->
          <div class="header-left clearfix">
            <!-- logo -->
            <?php if ($logo): ?>
              <div id="logo" class="logo">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
                  <img class="img-responsive" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                </a>
              </div>
            <?php endif; ?>
            <!-- name-and-slogan -->
            <?php if (!empty($site_name)): ?>
              <div class="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
              </div>
            <?php endif; ?>
            <?php if (!empty($site_slogan)): ?>
              <div class="site-slogan">
                <?php print $site_slogan; ?>
              </div>
            <?php endif; ?>
          </div> <!-- header-left start -->
        </div>

        <div class="col-md-11">
          <!-- header-right start -->
          <div class="header-right clearfix">
            <!-- main-navigation start -->
            <div <?php if ($navbar_attr){ print drupal_attributes($navbar_attr); } ?>>
              <nav class="navbar navbar-default" role="navigation">
                <div class="container-fluid">
                  <!-- Toggle get grouped for better mobile display -->
                  <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar-collapse-1">
                      <span class="sr-only">Toggle navigation</span>
                      <span class="icon-bar"></span>
                      <span class="icon-bar"></span>
                      <span class="icon-bar"></span>
                    </button>
                  </div>
                  <!-- Collect the nav links, forms, and other content for toggling -->
                  <div class="collapse navbar-collapse" id="navbar-collapse-1">
                    <?php if (!empty($main_menu)): ?>
                      <?php print drupal_render($main_menu); ?>
                    <?php endif; ?>
                    <!-- header buttons -->
                    <div class="header-dropdown-buttons hidden-xs">
                      <?php if($toggle_search): ?>
                        <div class="btn-group dropdown">
                          <button type="button" class="btn dropdown-toggle" data-toggle="dropdown" aria-expanded="false">
                            <?php print $search_icon; ?>
                          </button>
                          <ul class="dropdown-menu dropdown-menu-right dropdown-animation">
                            <li><?php print $search_box; ?></li>
                          </ul>
                        </div>
                      <?php endif; ?>
                    </div> <!-- header buttons end-->
                  </div> <!-- end-navbar -->
                </div>
              </nav>
            </div>
          </div>
        </div>
    </div> <!-- /.row -->
  </div> <!-- /.container -->
</header>

          

        <?php include 'includes/header_bottom.inc'; ?>
      </div>

      <!-- breadcrumbs -->
      <?php if (!empty($breadcrumb)):?> 
        <div class="breadcrumb-container">
          <div class="container">
            <?php print $breadcrumb; ?>
          </div>
        </div>
      <?php endif;?>

      <!-- banner -->
      <?php include 'includes/banner.inc'; ?>

      <!-- top-bar -->
      <?php include 'includes/top_bar.inc'; ?>

      <!-- main-content -->
      <section class="main-container">
        <div class="container">
          <?php include 'includes/information.inc'; ?>
          <div class="row">

            <!-- main start -->
            <div class="main <?php print $main_class; ?>" >
              <!-- title -->
              <?php include 'includes/title.inc'; ?>
              <a id="main-content"></a>
              
              <?php print render($content); ?>
            </div>
            <!-- main end -->

            <?php include 'includes/sidebar_first.inc'; ?>
            <?php include 'includes/sidebar_second.inc'; ?>
        
          </div>
        </div>
      </section>

      <!-- footer -->
      <footer id="footer" <?php print drupal_attributes($footer_attr); ?>>
        <div class="footer">
          <div class="container">
            <div class="footer-inner">
              <div class="row">
                <?php if (!empty($page['footer'])): ?>
                  <?php print render($page['footer']); ?>
                <?php endif; ?>
              </div>
            </div>
          </div>
        </div>
        <div class="subfooter">
          <div class="container">
            <div class="subfooter-inner">
              <div class="row">
                <?php if (!empty($page['footer_bottom'])): ?>
                  <?php print render($page['footer_bottom']); ?>
                <?php endif; ?>
              </div>
            </div>
          </div>
        </div>
      </footer>
    </div>
  </body>
</html>