<?php

/**

 *         1. preprocess_html

           2. process_html

           3. preprocess_page

           4. process_page



           5. preprocess_maintenance_page, font_to_css

 * 

 * 

 * Add body classes if certain regions have content.

 */

function md_leaders_preprocess_html(&$vars) {

    global $base_url;

    $css = "";

    $themepath = drupal_get_path('theme', 'md_leaders');

    drupal_add_js(array('themePath' => $themepath),'setting');

    if(module_exists('icon') && module_exists('fontello')) {

        $icon_bundles = icon_bundles();

        foreach($icon_bundles as $key => $value) {

            if($value['status'] == 1) {

                fontello_process_attached($key);

            }

        }

    }

    

    // Add css

  drupal_add_css(path_to_theme() . '/css/bootstrap.min.css');

  drupal_add_css(path_to_theme() . '/css/animations.css');

  drupal_add_css(path_to_theme() . '/css/main.css');



  // Add js

  

  drupal_add_js(path_to_theme() . '/js/vendor/modernizr-2.6.2.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/bootstrap.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/owl.carousel.min.js');

  

  

  drupal_add_js(path_to_theme() . '/js/vendor/hoverIntent.js');

  drupal_add_js(path_to_theme() . '/js/vendor/superfish.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.sticky.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/placeholdem.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.actual.min.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquerypp.custom.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.elastislide.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.flexslider-min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.ui.totop.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.isotope.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jflickrfeed.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.prettyPhoto.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.easypiechart.min.js');  

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.nicescroll.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.fractionslider.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/jquery.scrollTo-min.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.localscroll-min.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.parallax-1.1.3.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.bxslider.min.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.funnyText.min.js');

  drupal_add_js(path_to_theme() . '/js/vendor/grid.js');



  drupal_add_js(path_to_theme() . '/js/plugins.js');

  drupal_add_js(path_to_theme() . '/js/main.js');

//  drupal_add_js('https://maps.googleapis.com/maps/api/js?sensor=false');

  drupal_add_js('http://maps.google.com/maps/api/js?sensor=false');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery-migrate-1.2.1.min.js');

//  drupal_add_js(path_to_theme() . '/js/vendor/jquery.easing.1.3.js');

    

    

    

    

 //////////////////////////////////////////// SKIN SETTING ////////////////////////////////////////////

    if (theme_get_setting('skin_color')) {

        $skin_color = str_replace("#", "",theme_get_setting('skin_color','md_leaders'));



        $css .= '.md-slide-wrap .md-bullets {background-color: #'.$skin_color.';}'."\n";

        $css .= '.md-slide-wrap .md-bullets .md-bullet {border-color: #'.$skin_color.';}'."\n";

        $css .= '.md-slide-wrap .md-bullets .md-current {background-color: #'.$skin_color.';}'."\n";

        $css .= '#mainmenu li a.active {border-color: #'.$skin_color.';}'."\n";

        $css .= '#mainmenu li .dropdown-menu a.active {color: #'.$skin_color.';}'."\n";

        $css .= '@media (max-width: 767px) { #mainmenu li a.active {color: #'.$skin_color.';} }'."\n";

        $css .= '.nav-tabs > li.active > a {background-color: #'.$skin_color.';}'."\n";

        $css .= '.nav-tabs > li.active > a:hover, .nav-tabs > li.active > a:focus {background-color: #'.$skin_color.'

                ;}'."\n";

        $css .= '.nav-tabs > li > a:hover, .nav-tabs > li > a:focus {background-color: #'.$skin_color.';}'."\n";

        $css .= '.panel-title > a {background-color: #'.$skin_color.';}'."\n";

        $css .= '.panel-heading[class*="rt-icon-"]:before {color: #'.$skin_color.';}'."\n";

        $css .= '.pagination > li.active > a:hover {background-color: #'.$skin_color.'; border-color: #'.$skin_color.';}'."\n";

        $css .= '.pagination > li > a:hover {background-color: #'.$skin_color.'; border-color: #'.$skin_color.';}'."\n";

        $css .= '.carousel-indicators li {border-color: #'.$skin_color.';}'."\n";

        $css .= '.carousel-indicators .active {background-color: #'.$skin_color.';}'."\n";

        $css .= '.carousel-controls a:hover, .carousel-controls a:hover [class^="arrow-icon-"]:before {background-color: #'.$skin_color.';}'."\n";

        $css .= '.carousel-controls [class^="arrow-icon-"]:before, [class*=" arrow-icon-"]:before {border-color: #'.$skin_color.';}'."\n";

        $css .= '.progress-bar-danger {background-color: #'.$skin_color.';}'."\n";

        $css .= '.nav-tabs > li.active > a {background-color: #'.$skin_color.';}'."\n";

        $css .= '.nav-tabs > li.active > a:hover, .nav-tabs > li.active > a:focus {background-color: #'.$skin_color.';}'."\n";

        $css .= '.nav-tabs > li > a:hover, .nav-tabs > li > a:focus {background-color: #'.$skin_color.';}'."\n";

        $css .= '.nav-tabs.nav-justified > .active > a {background-color: #'.$skin_color.';}'."\n";

        $css .= '.alert.topalert {background-color: #'.$skin_color.';}'."\n";

        $css .= '.table > thead > tr > th {background-color: #'.$skin_color.';}'."\n";

        $css .= '::selection {background: #'.$skin_color.';}'."\n";

        $css .= '::-moz-selection {background: #'.$skin_color.'; }'."\n";

        $css .= 'blockquote:before {color: #'.$skin_color.'; }'."\n";

        $css .= 'blockquote:after {color: #'.$skin_color.'; }'."\n";

        $css .= 'a {color: #'.$skin_color.'; }'."\n";

        $css .= '.not_found {color: #'.$skin_color.'; }'."\n";

        $css .= '.highlight {color: #'.$skin_color.'; }'."\n";

        $css .= '#response {color: #'.$skin_color.'; }'."\n";

        $css .= '.theme_btn {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.theme_btn:active, .theme_btn:hover, .theme_btn:focus {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.theme_btn.inverse:hover {color: #'.$skin_color.'; }'."\n";

        $css .= 'ul.list1 li:before {color: #'.$skin_color.'; }'."\n";

        $css .= 'ul.list2 li:before {color: #'.$skin_color.'; }'."\n";

        $css .= 'ol.list3 li:after {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.light_section a, [class*="_section"] .light_section a {color: #'.$skin_color.'; }'."\n";

        $css .= '.grey_section a, [class*="_section"] .grey_section a {color: #'.$skin_color.'; }'."\n";

        $css .= '.color_section, [class*="_section"] .color_section {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.color_section .theme_btn {color: #'.$skin_color.'; }'."\n";

        $css .= '.color_section .theme_btn.inverse:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.dark_section a:hover, [class*="_section"] .dark_section a:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.dark_section .theme_btn {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.dark_section .theme_btn.inverse:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.darkgrey_section a, [class*="_section"] .darkgrey_section a {color: #'.$skin_color.'; }'."\n";

        $css .= '.darkgrey_section .theme_btn {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.darkgrey_section .theme_btn.inverse:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '#header-sticky-wrapper {background-color: #'.$skin_color.'; }'."\n";

        $css .= '#partners .owl-theme .owl-controls .owl-buttons div:hover:before {color: #'.$skin_color.'; }'."\n";

        $css .= '.sf-menu ul li a:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.sf-menu > li:hover > a, .sf-menu > li.sfHover > a, .sf-menu > li.active > a {border-color: #'.$skin_color.'; }'."\n";

        $css .= '.dropdown-menu > .active > a, .dropdown-menu > .active > a:hover, .dropdown-menu > .active > a:focus {color: #'.$skin_color.'; }'."\n";

        $css .= '@media (max-width: 767px) { .sf-menu > li > a:hover {color: #'.$skin_color.'; } .sf-menu > li:hover > a, .sf-menu > li.sfHover > a, .sf-menu > li.active > a {color: #'.$skin_color.'; } .sf-menu > li li.active > a, .sf-menu > li li > a:hover {color: #'.$skin_color.' !important; } }'."\n";

        $css .= '.menu-item-desc {color: #'.$skin_color.'; }'."\n";

        $css .= '.latest-works h3 {border-color: #'.$skin_color.'; }'."\n";

        $css .= '.latest-works h3 a:hover {color: #'.$skin_color.' !important; }'."\n";

        $css .= '.team .media {border-color: #'.$skin_color.'; }'."\n";

        $css .= '@media screen and (max-width: 991px) { .team .media {border-color: #'.$skin_color.'; } }'."\n";

        $css .= '.gallery-grid li > a + h3 {border-color: #'.$skin_color.'; }'."\n";

        $css .= '#portfolio_nav a:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.skills > a:hover, .client > a:hover, .location > a:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.format-small-image .entry-tags {border-color: #'.$skin_color.'; }'."\n";

        $css .= '.video-view {background-color: #'.$skin_color.'; border-color: #'.$skin_color.'; }'."\n";

        $css .= '.tags a, .tagcloud a {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.tags a:hover, .tagcloud a:hover {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.author-meta {border-color: #'.$skin_color.'; }'."\n";

        $css .= '@media screen and (max-width: 767px) { .author-meta {border-color: #'.$skin_color.'; } }'."\n";

        $css .= '.comment-author span.username {color: #'.$skin_color.'; }'."\n";

        $css .= '.single_teaser.icons.style1 [class^="rt-icon-"] {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.single_teaser.icons.style1 a.theme_btn:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.single_teaser h3 a:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.single_teaser_right h3 a {color: #'.$skin_color.'; }'."\n";

        $css .= '.single_teaser_right h3 a:hover {color: #'.$skin_color.';}'."\n";

        $css .= '.left_icons.style2 [class^="rt-icon-"] {color: #'.$skin_color.'; }'."\n";

        $css .= '.left_icons.style2:hover [class^="rt-icon-"] {background-color: #'.$skin_color.'; -webkit-box-shadow: 0 0 0 4px #'.$skin_color.'; box-shadow: 0 0 0 4px #'.$skin_color.'; }'."\n";

        $css .= '.widget_categories a:before, .widget_archive a:before, .widget_recent_entries a:before, .widget_nav_menu a:before {color: #'.$skin_color.'; }'."\n";

        $css .= '.widget_social_links a[class^="socialico-"] {color: #'.$skin_color.'; }'."\n";

        $css .= '.widget_social_links a[class^="socialico-"]:hover {color: #'.$skin_color.'; }'."\n";

        $css .= '.widget_schedule .dl-horizontal dt:before {color: #'.$skin_color.'; }'."\n";

        $css .= '.widget_text [class^="rt-icon-"], .widget_text [class*=" rt-icon-"] {color: #'.$skin_color.'; }'."\n";

        $css .= '.thumbnail:after {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.p-link {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.p-view:hover:before {color: #'.$skin_color.'; }'."\n";

        $css .= '.owl-theme .owl-controls .owl-buttons div {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.fs-pager-wrapper {background-color: #'.$skin_color.'; }'."\n";

        $css .= '.fs-pager-wrapper a {border-color: #'.$skin_color.'; }'."\n";

        $css .= '.fs-pager-wrapper .active {background-color: #'.$skin_color.'; }'."\n";

        $css .= '#toTop {background: #'.$skin_color.'; }'."\n";

        $css .= 'a[class^="socialico-"]:before {border-color: #'.$skin_color.'; }'."\n";

        $css .= 'a[class^="socialico-"]:hover:before {background-color: #'.$skin_color.'; }'."\n";

        $css .= '#mds-portfolio-content .mdp-filter-default .cbp-filter-counter:before {border-color: #'.$skin_color.'; }'."\n";

        $css .= '#mds-portfolio-content .mdp-filter-default .cbp-filter-counter {background-color: #'.$skin_color.'; }'."\n";

        $css .= '#mds-portfolio-content .mdp-filter-default .cbp-filter-item.cbp-filter-item-active {border-color: #'.$skin_color.'; background-color: #'.$skin_color.';}'."\n";

         $css .= '.cbp-item-wrapper {color: #'.$skin_color.'; }'."\n";

    }   







//////////////////////////////////////////// FAVICON SETTING ////////////////////////////////////////////

   // Add favicon.
    if (theme_get_setting('toggle_fvicon','md_leaders')) {
        $favicon_path = '';
        if(theme_get_setting('default_favicon','md_leaders') == 0) {
            $favicon = theme_get_setting('fvicon_upload','md_leaders');
            if(!empty($favicon)) {
                if(is_array($favicon)) {
                    if($favicon['fid'] != 0) {
                        $file = file_load((string)($favicon['fid']));
                        if($file) {
                            $favicon_path = file_create_url($file->uri);
                        }
                    }
                } else {
                    $file = json_decode($favicon);
                    $favicon_path = $file->url;
                }
            } else {
                $favicon_path = base_url().'/'.$themepath.'/favicon.ico';
            }
        } else {
            $favicon_path = base_url().'/'.$themepath.'/favicon.ico';
        }
        $type = theme_get_setting('favicon_mimetype','md_leaders');
        drupal_add_html_head_link(array('rel' => 'shortcut icon', 'href' => drupal_strip_dangerous_protocols($favicon_path), 'type' => $type));
    }
    // iOs webclip
    if(theme_get_setting('webclip_57_upload','md_leaders')) {
        $file_upload = theme_get_setting('webclip_57_upload','md_leaders');
        if(is_array($file_upload)) {
            if($file_upload['fid'] != 0) {
                $file = file_load($file_upload['fid']);
                if($file) {
                    $path = file_create_url($file->uri);
                    $vars['ios_57'] = $path;
                }
            } else {
                $vars['ios_57'] = '';
            }
        } else {
            $file = json_decode($file_upload);
            $vars['ios_57'] = $file->url;
        }
    } else {
        $vars['ios_57'] = '';
    }
    if(theme_get_setting('webclip_72_upload','md_leaders')) {
        $file_upload = theme_get_setting('webclip_72_upload','md_leaders');
        if(is_array($file_upload)) {
            if($file_upload['fid'] != 0) {
                $file = file_load($file_upload['fid']);
                if($file) {
                    $path = file_create_url($file->uri);
                    $vars['ios_72'] = $path;
                }
            } else {
                $vars['ios_72'] = '';
            }
        } else {
            $file = json_decode($file_upload);
            $vars['ios_72'] = $file->url;
        }
    }
    if(theme_get_setting('webclip_114_upload','md_leaders')) {
        $file_upload = theme_get_setting('webclip_114_upload','md_leaders');
        if(is_array($file_upload)) {
            if($file_upload['fid'] != 0) {
                $file = file_load($file_upload['fid']);
                if($file) {
                    $path = file_create_url($file->uri);
                    $vars['ios_114'] = $path;
                }
            } else {
                $vars['ios_114'] = '';
            }
        } else {
            $file = json_decode($file_upload);
            $vars['ios_114'] = $file->url;
        }
    }
    if(theme_get_setting('webclip_144_upload','md_leaders')) {
        $file_upload = theme_get_setting('webclip_144_upload','md_leaders');
        if(is_array($file_upload)) {
            if($file_upload['fid'] != 0) {
                $file = file_load($file_upload['fid']);
                if($file) {
                    $path = file_create_url($file->uri);
                    $vars['ios_144'] = $path;
                }
            } else {
                $vars['ios_144'] = '';
            }
        } else {
            $file = json_decode($file_upload);
            $vars['ios_144'] = $file->url;
        }
    }



    

    

    /* ------------------------- Blog Page ------------------------*/



//    if(in_array('node-type-blog',$vars['classes_array'])) {

//        $vars['classes_array'][] = 'blog-page';

//    }

//

//    /* ---------------------------------------------- Header -----------------------------------------------------*/

//    $header_bg_type = theme_get_setting('header_background_type','bs');

//    drupal_add_js(array('hdBgType' => $header_bg_type),'setting');

//    if($header_bg_type == 'image') {

//        if(theme_get_setting('header_slide_delay_time','bs')) {

//            drupal_add_js(array('hdSlideDelayTime' => theme_get_setting('header_slide_delay_time','bs')),'setting');

//        }

//        if(theme_get_setting('header_slide_effect','bs')) {

//            drupal_add_js(array('hdSlideEffect' => theme_get_setting('header_slide_effect','bs')),'setting');

//        }

//        if(theme_get_setting('header_slide_animation','bs')) {

//            drupal_add_js(array('hdSlideAnimation' => theme_get_setting('header_slide_animation','bs')),'setting');

//        }

//    }

//    if($header_bg_type == 'video') {

//        if(theme_get_setting('header_video_resolution','bs')){

//            $hd_video_res = theme_get_setting('header_video_resolution','bs');

//            drupal_add_js(array('headerVideoRes' => $hd_video_res),'setting');

//        }

//    }

//    if($header_bg_type == 'static') {

//        if(theme_get_setting('header_static_image_upload','bs')) {

//            $file_upload =  theme_get_setting('header_static_image_upload','bs');

//            if($file_upload['fid'] != 0) {

//                $file = file_load($file_upload['fid']);

//                if($file) {

//                    $css .= '.text-ticker-holder {background-image : url("'.file_create_url($file->uri).'");}';

//                }

//

//            }

//

//        }

//    }

//    /* ---------------------------------------------- 404 Page -----------------------------------------------------*/

//    if(theme_get_setting('choose_nf_pattern','bs')) {

//        $css .= ".nf-pattern { background: #000000 url(" . $base_url .'/'. $themepath ."/images/background/patterns/". theme_get_setting('choose_nf_pattern','bs') . ".png) repeat scroll center center;}\n";

//    }

    

    

    /* ---------------------------------------------- Google Map -----------------------------------------------------*/

    if(theme_get_setting('default_marker_pic','md_leaders') == 1) {

                 $pic_path = $base_url.'/'.$themepath.'/theme-setting/img/marker.png';

    }

    else {             

        $marker_upload = theme_get_setting('marker_pic_upload','md_leaders');

        if($marker_upload['fid'] != 0  && $marker_upload != null) {

              $file = file_load($marker_upload['fid']);

              if($file) {

                  $pic_path = file_create_url($file->uri);

              }

          }

          else {

              $pic_path = $base_url.'/'.$themepath.'/theme-setting/img/marker.png';

          }

    

    }      

    

    

    if(theme_get_setting('map_marker_title','md_leaders') != null){

        drupal_add_js(array('mapMarkerTitle' => theme_get_setting('map_marker_title','md_leaders')),'setting');

    } else {

        drupal_add_js(array('mapMarkerTitle' => 'Megadrupal'),'setting');

    }

    if(theme_get_setting('map_marker_description','md_leaders')!= null){

        drupal_add_js(array('mapMarkerDes' => theme_get_setting('map_marker_description','md_leaders')),'setting');

    } else {

        drupal_add_js(array('mapMarkerDes' => 'Ha Noi , Viet Nam'),'setting');

    }

    if(theme_get_setting('map_latlng','md_leaders')!= null){

        drupal_add_js(array('mapLatlng' => theme_get_setting('map_latlng','md_leaders')),'setting');

    } else {

        drupal_add_js(array('mapLatlng' => '40.748395,-73.985542'),'setting');

    }

    if(theme_get_setting('map_types','md_leaders')!= null){

        drupal_add_js(array('mapTypes' => theme_get_setting('map_types','md_leaders')),'setting');

    } else {

        drupal_add_js(array('mapTypes' => 'ROADMAP'),'setting');

    }

    if(theme_get_setting('map_zoom_level','md_leaders')!= null){

        drupal_add_js(array('mapZoom' => theme_get_setting('map_zoom_level','md_leaders')),'setting');

    } else {

        drupal_add_js(array('mapZoom' => 16),'setting');

    }

    if(theme_get_setting('map_latlng','md_leaders')){

            $map_title = theme_get_setting('map_marker_title','md_leaders');

            $map_des = theme_get_setting('map_marker_description','md_leaders');

            $map_latlng = theme_get_setting('map_latlng','md_leaders');

            $map_types = theme_get_setting('map_types','md_leaders');

            $map_zoom_level = theme_get_setting('map_zoom_level','md_leaders');

            $map_js = ' jQuery(document).ready(function() {

        if(jQuery("#map_canvas").size() > 0) {

            var onMobile = false;

            //if (/Android|webOS|iPhone|iPad|iPod|BlackBerry/i.test(navigator.userAgent)) {

            //    onMobile = true;

            //}



            //if (onMobile == false){

                jQuery(window).load(function(){

                    //Google Map

                    var settings = {

                            zoom: '.$map_zoom_level.',

                            center: new google.maps.LatLng('.$map_latlng.'),

                            mapTypeId: google.maps.MapTypeId.'.$map_types.',

                            mapTypeControl: false,

                            scrollwheel: false,

                            draggable: true,

                            mapTypeControlOptions: {style: google.maps.MapTypeControlStyle.DROPDOWN_MENU},

                            navigationControl: false,

                            navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL}

                        };

                    var map = new google.maps.Map(document.getElementById("map_canvas"), settings);

                    google.maps.event.addDomListener(window, "resize", function() {

                        var center = map.getCenter();

                        google.maps.event.trigger(map, "resize");

                        map.setCenter(center);

                    });

                    var contentString =

                        \'<div id="content"><h3>'.$map_title.'</h3><div id="bodyContent"><p>'.$map_des.'</p></div></div>\';

                    var infowindow = new google.maps.InfoWindow({

                        content: contentString

                    });

                    var companyImage = new google.maps.MarkerImage("'.$pic_path.'",

                        new google.maps.Size(63,68), //Width and height of the marker

                        new google.maps.Point(0,0),

                        new google.maps.Point(35,20) //Position of the marker

                    );

                    var companyPos = new google.maps.LatLng('.$map_latlng.');

                    var companyMarker = new google.maps.Marker({

                        position: companyPos,

                        map: map,

                        icon: companyImage,

                        title:"Creative News",

                        zIndex: 3});

                    google.maps.event.addListener(companyMarker, "click", function() {

                        infowindow.open(map,companyMarker);

                    });

                });

            //}

        }

    });';

            drupal_add_js($map_js,array('type' => 'inline','scope' => 'footer'));

    }



    $vars['theme_setting_css'] = $css;





	// Enable Responsive

	if (theme_get_setting('responsive','md_leaders')) {

		$menuid = 'main-menu';

		if (!empty($vars['page']['superfish'])) {

			$tmp_array_keys = array_keys($vars['page']['superfish']);

			$menuid = str_replace("_","-",$tmp_array_keys[0]);

		}

		$selecnav = '(function ($) {

			$(function(){

				selectnav(\''.$menuid.'\', {

					label: \''.t('--- Table of content ---').'\',//first select field

					nested: true,

					indent: \'-\'

			 });

		});

		})(jQuery);';

		drupal_add_js($selecnav, 'inline');

		$vp = array(

          '#type' => 'html_tag',

          '#tag' => 'meta',

          '#attributes' => array(

            'name' =>  'viewport',

            'content' =>  'width=100%, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no'

          )

        );

        drupal_add_html_head($vp, 'viewport');

	}



    

    

    /*    Background page

     *------------------------------------------------------------------*/

        

//        if(theme_get_setting('background_pic_about','md_leaders')) {

//            $file_upload = theme_get_setting('background_pic_about','md_leaders');

//            if($file_upload['fid'] != 0 && $file_upload != null) {

//                $file = file_load($file_upload['fid']);

//                if($file) {

//                    $css .= '.page-about-us #main{background-image: url("'.file_create_url($file->uri).'");}'."\n";

//                }

//            }

//        }

//        

//         if(theme_get_setting('background_pic_service','md_leaders')) {

//            $file_upload = theme_get_setting('background_pic_service','md_leaders');

//            if($file_upload['fid'] != 0 && $file_upload != null) {

//                $file = file_load($file_upload['fid']);

//                if($file) {

//                    $css .= '.page-services #main{background-image: url("'.file_create_url($file->uri).'");}'."\n";

//                }

//            }

//        }

//        

//        if(theme_get_setting('background_pic_product','md_leaders')) {

//            $file_upload = theme_get_setting('background_pic_product','md_leaders');

//            if($file_upload['fid'] != 0 && $file_upload != null) {

//                $file = file_load($file_upload['fid']);

//                if($file) {

//                    $css .= '.page-shop-list #main,.page-type-products #main{background-image: url("'.file_create_url($file->uri).'");}'."\n";

//                }

//            }

//        }

        

        

        

        

        

        

        

        

        

    $vars['theme_setting_css'] = $css;

    //Google Fonts

    if(theme_get_setting('googlewebfonts','md_leaders')) {

        drupal_add_css(theme_get_setting('googlewebfonts'),'external');

    }

    // Typekit

    if (theme_get_setting('typekit_id','md_leaders')) {

            drupal_add_js('http://use.typekit.net/'.theme_get_setting('typekit_id','md_leaders').'.js', 'external');

            drupal_add_js('try{Typekit.load();}catch(e){}', 'inline');

    }



        

        

        

    

        

        

	/*----------------------------------------------------------------------------------------

         *  Text/typography

	---------------------------------------------------------------------------------------- */

      

        

        $typography = '';

      

        

    // common text

    if (theme_get_setting('text_font', 'md_leaders') || theme_get_setting('ts_font_color', 'md_leaders')) {

        $typography = "body {";

        $typography .= md_leaders_font_to_css(theme_get_setting('text_font', 'md_leaders'));

        if (theme_get_setting('ts_font_color', 'md_leaders')) {

            $typography .= 'color: ' . theme_get_setting('ts_font_color') . ';';

        }

        $typography .= "}\n";

    }

    

    

    /////

    $text_font_arr = explode("|", theme_get_setting('text_font', 'md_leaders'));

    if (count($text_font_arr) == 5 && $text_font_arr[0] != '0') {

        $typography .= '#forum, ul.quicktabs-tabs, #nav ul.sf-menu li li,.ui-widget {font-family: ' . $text_font_arr[4] . ';}';

    }

    /////

	// Text selection

	if (theme_get_setting('tss_bgcolor','md_leaders') || theme_get_setting('tss_tcolor','md_leaders')) {

    $tss_bgcolor = '';

    $tss_tcolor = '';

		if (theme_get_setting('tss_bgcolor','md_leaders')) {

		  $tss_bgcolor   = 'background: '.theme_get_setting('tss_bgcolor','md_leaders').';';

		}

		if (theme_get_setting('tss_tcolor','md_leaders')) {

		  $tss_tcolor   = 'color: '.theme_get_setting('tss_tcolor','md_leaders').';';

		}

    $typography   .= "::-moz-selection {". $tss_bgcolor . $tss_tcolor . "text-shadow: none;}\n";

    $typography   .= "::selection {" . $tss_bgcolor . $tss_tcolor. "text-shadow: none;}\n";

	}

	// link regular

	if (theme_get_setting('l_regular_color','md_leaders') || theme_get_setting('l_regular_st','md_leaders') || theme_get_setting('l_regular__hl','md_leaders') || theme_get_setting('l_regular_ts','md_leaders')) {

    $typography   .= "a:link, #node-title a {";

		if (theme_get_setting('l_regular_color','md_leaders')) {

      $typography   .= 'color: '.theme_get_setting('l_regular_color','md_leaders').';';

		}

		if (theme_get_setting('l_regular__hl','md_leaders')) {

		  $typography   .= 'background-color: '.theme_get_setting('l_regular__hlc','md_leaders').';';

		}

        if(theme_get_setting('l_regular_st','md_leaders') == 1) {

            $typography .= 'text-decoration: line-through';

        }

		$l_text_style = theme_get_setting('l_regular_ts','md_leaders');

		if ($l_text_style['bold']) {

		  $typography   .= 'font-weight: '.$l_text_style['bold'].';';

		}

		if ($l_text_style['italic']) {

		  $typography   .= 'font-style: '.$l_text_style['italic'].';';

		}

		if ($l_text_style['underline']) {

		  $typography   .= 'text-decoration: '.$l_text_style['underline'].';';

		}

		$typography   .= "}\n";

	}

	// link rollover

	if (theme_get_setting('l_rollover_color','md_leaders') || theme_get_setting('l_rollover_st','md_leaders') || theme_get_setting('l_rollover__hl','md_leaders') || theme_get_setting('l_rollover_ts','md_leaders')) {

		$typography   .= "a:hover, #node-title a:hover {";

		if (theme_get_setting('l_rollover_color')) {

		  $typography   .= 'color: '.theme_get_setting('l_rollover_color','md_leaders').';';

		}

		if (theme_get_setting('l_rollover__hl')) {

		  $typography   .= 'background-color: '.theme_get_setting('l_rollover__hlc','md_leaders').';';

		}

        if(theme_get_setting('l_rollover_st','md_leaders') == 1) {

            $typography .= 'text-decoration: line-through';

        }

		$l_text_style = theme_get_setting('l_rollover_ts','md_leaders');

		if ($l_text_style['bold']) {

		  $typography   .= 'font-weight: '.$l_text_style['bold'].';';

		}

		if ($l_text_style['italic']) {

		  $typography   .= 'font-style: '.$l_text_style['italic'].';';

		}

		if ($l_text_style['underline']) {

		  $typography   .= 'text-decoration: '.$l_text_style['underline'].';';

		}

		$typography   .= "}\n";

	}



	// link visited

	if (theme_get_setting('l_visited_color','md_leaders') || theme_get_setting('l_visited_st','md_leaders') || theme_get_setting('l_visited__hl','md_leaders') || theme_get_setting('l_visited_ts','md_leaders')) {

		$typography   .= "a:visited, #node-title a:visited {";

		if (theme_get_setting('l_visited_color')) {

		  $typography   .= 'color: '.theme_get_setting('l_visited_color','md_leaders').';';

		}

		if (theme_get_setting('l_visited__hl')) {

		  $typography   .= 'background-color: '.theme_get_setting('l_visited__hlc','md_leaders').';';

		}

        if(theme_get_setting('l_visited_st','md_leaders') == 1) {

            $typography .= 'text-decoration: line-through';

        }

		$l_text_style = theme_get_setting('l_visited_ts','md_leaders');

		if ($l_text_style['bold']) {

		  $typography   .= 'font-weight: '.$l_text_style['bold'].';';

		}

		if ($l_text_style['italic']) {

		  $typography   .= 'font-style: '.$l_text_style['italic'].';';

		}

		if ($l_text_style['underline']) {

		  $typography   .= 'text-decoration: '.$l_text_style['underline'].';';

		}

		$typography   .= "}\n";

	}



	// link on

	if (theme_get_setting('l_on_color','md_leaders') || theme_get_setting('l_on_st','md_leaders') || theme_get_setting('l_on_hl','md_leaders') || theme_get_setting('l_on_ts','md_leaders')) {

		$typography   .= "a:focus, a:active, #node-title a:focus, #node-title a:active {";

		if (theme_get_setting('l_on_color')) {

		  $typography   .= 'color: '.theme_get_setting('l_on_color','md_leaders').';';

		}

		if (theme_get_setting('l_on_hl')) {

		  $typography   .= 'background-color: '.theme_get_setting('l_on_hlc','md_leaders').';';

		}

        if(theme_get_setting('l_on_st','md_leaders') == 1) {

            $typography .= 'text-decoration: line-through';

        }

		$l_text_style = theme_get_setting('l_on_ts','md_leaders');

		if ($l_text_style['bold']) {

		  $typography   .= 'font-weight: '.$l_text_style['bold'].';';

		}

		if ($l_text_style['italic']) {

		  $typography   .= 'font-style: '.$l_text_style['italic'].';';

		}

		if ($l_text_style['underline']) {

		  $typography   .= 'text-decoration: '.$l_text_style['underline'].';';

		}

		$typography   .= "}\n";

	}

	// Main menu

	if (theme_get_setting('typo_menu_style','md_leaders') || theme_get_setting('typo_menu_color','md_leaders')) {

		$typography   .= "#menu li{";

		if (theme_get_setting('text_font','md_leaders')) {

		  $typography   .= md_leaders_font_to_css(theme_get_setting('typo_menu_style','md_leaders'));

		}



		if (theme_get_setting('typo_menu_color','md_leaders')) {

		  $typography   .= 'color: '.theme_get_setting('typo_menu_color','md_leaders').';';

		}

		$typography   .= "}\n";



		if (theme_get_setting('typo_menu_color','md_leaders')) {

		  $typography   .= '#menu li a, #nav ul.sf-menu li a {color: '.theme_get_setting('typo_menu_color','md_leaders').';}';

		}

		if (theme_get_setting('typo_menu_hover_color','md_leaders')) {

		  $typography   .= '#menu li > a:hover,#menu li.sfHover > a, #main li:hover a {color: '.theme_get_setting('typo_menu_hover_color','md_leaders').';}'."\n";

		}

		if (theme_get_setting('typo_menu_active_color','md_leaders')) {

		  $typography   .= '#menu li > a:hover, #menu li.sfHover > a, #menu li a.active, #menu li.active a {color: '.theme_get_setting('typo_menu_active_color','md_leaders').';}'."\n";

		}

	}

    /*-------------------------------------- Heading --------------------------------*/

    if(theme_get_setting('typo_heading_style_enable','md_leaders') == 1){

        for($i=1;$i<=6;$i++){

            $typography .= 'h'.$i.' {';

            if(theme_get_setting('typo_heading_h'.$i.'_style') || theme_get_setting('typo_heading_h'.$i.'_color','md_leaders')){

                if(theme_get_setting('typo_heading_h'.$i.'_style')){

                    $typography .= md_leaders_font_to_css(theme_get_setting('typo_heading_h'.$i.'_style'));

                }

                if(theme_get_setting('typo_heading_h'.$i.'_color','md_leaders')){

                    $typography .= ' color: '.theme_get_setting('typo_heading_h'.$i.'_color').';';

                }

            }

            $typography .= "}\n";

        }

    }

	/*------------------------------------ Node title ---------------------------------*/

//	if (theme_get_setting('typo_nodetitle_style','bs') || theme_get_setting('nodetitle_color','bs')) {

//		$typography   .= "#node-title {";

//		if (theme_get_setting('typo_nodetitle_style')) {

//		  $typography   .= bs_font_to_css(theme_get_setting('typo_nodetitle_style'));

//		}

//

//		if (theme_get_setting('nodetitle_color','bs')) {

//		  $typography   .= 'color: '.theme_get_setting('nodetitle_color','bs').';';

//		}

//		$typography   .= "}\n";

//

//		if (theme_get_setting('nodetitle_color')) {

//		  $typography   .= '#node-title a {color: '.theme_get_setting('nodetitle_color','bs').';}'."\n";

//		}

//

//		if (theme_get_setting('nodetitle_hover_color')) {

//		  $typography   .= '#node-title a:hover {color: '.theme_get_setting('nodetitle_hover_color','bs').';}'."\n";

//		}

//	}

//

//	if (theme_get_setting('nodetitle_enable','bs') == 1) {

//		foreach (node_type_get_types() as $type => $name) {

//			if (theme_get_setting('typo_n'.$type.'title_style') || theme_get_setting('n'.$type.'title_color','bs')) {

//				$typography   .= "#node-title span.node-$type-title {";

//				if (theme_get_setting('typo_n'.$type.'title_style')) {

//				  $typography   .= bs_font_to_css(theme_get_setting('typo_n'.$type.'title_style','bs'));

//				}

//

//				if (theme_get_setting('n'.$type.'title_color','bs')) {

//				  $typography   .= 'color: '.theme_get_setting('n'.$type.'title_color','bs').';';

//				}

//				$typography   .= "}\n";

//

//				if (theme_get_setting('n'.$type.'title_color','bs')) {

//				  $typography   .= '#node-title span.node-'.$type.'-title a {color: '.theme_get_setting('n'.$type.'title_color','bs').';}'."\n";

//				}

//

//				if (theme_get_setting('n'.$type.'title_hover_color','bs')) {

//				  $typography   .= '#node-title span.node-'.$type.'-title a:hover {color: '.theme_get_setting('n'.$type.'title_hover_color','bs').';}'."\n";

//				}

//			}

//		}

//	}

//

//    // View block title

//    if (theme_get_setting('typo_view_title_style','bs') || theme_get_setting('typo_view_title_color','bs')) {

//        $typography   .= ".flx-intro-2 h2 {";

//        if (theme_get_setting('typo_view_title_style','bs')) {

//            $typography   .= bs_font_to_css(theme_get_setting('typo_view_title_style','bs'));

//        }

//

//        if (theme_get_setting('typo_view_title_color')) {

//            $typography   .= 'color: '.theme_get_setting('typo_view_title_color','bs').' !important;';

//        }

//        $typography   .= "}\n";

//

//    }

//

//    if (theme_get_setting('typo_view_title_enable','bs') == 1) {

//        $views = views_get_all_views($reset = FALSE);

//        foreach ($views as $view_name => $view) {

//            if(($view->disabled) !== true){

//                $view_title = $view->name;

//

//                if (theme_get_setting('typo_view_'.$view_title.'_title_style') || theme_get_setting('typo_view_'.$view_title.'_title_color','bs')) {

//                    $typography   .= ".flx-intro-2 h2.view-".$view_title."-title {";

//                    if (theme_get_setting('typo_view_'.$view_title.'_title_style')) {

//                        $typography   .= bs_font_to_css(theme_get_setting('typo_view_'.$view_title.'_title_style','bs'));

//                    }

//

//                    if (theme_get_setting('typo_view_'.$view_title.'_title_color','bs')) {

//                        $typography   .= 'color: '.theme_get_setting('typo_view_'.$view_title.'_title_color','bs').' !important;';

//                    }

//                    $typography   .= "}\n";

//                }

//            }

//

//        }

//    }

//    //View block description

//    if (theme_get_setting('typo_view_description_style','bs') || theme_get_setting('typo_view_description_color','bs')) {

//        $typography   .= ".flx-intro-2 h5.flx-intro-excerpt {";

//        if (theme_get_setting('typo_view_description_style','bs')) {

//            $typography   .= bs_font_to_css(theme_get_setting('typo_view_description_style','bs'));

//        }

//

//        if (theme_get_setting('typo_view_description_color','bs')) {

//            $typography   .= 'color: '.theme_get_setting('typo_view_description_color','bs').' !important;';

//        }

//        $typography   .= "}\n";

//

//    }

//

//    if (theme_get_setting('typo_view_description_enable','bs') == 1) {

//        $views = views_get_all_views($reset = FALSE);

//        foreach ($views as $view_name => $view) {

//            if(($view->disabled) !== true){

//                $view_title = $view->name;

//

//                if (theme_get_setting('typo_view_'.$view_title.'_description_style','bs') || theme_get_setting('typo_view_'.$view_title.'_description_color','bs')) {

//                    $typography   .= ".flx-intro-2 span.view-".$view_title."-description {";

//                    if (theme_get_setting('typo_view_'.$view_title.'_description_style','bs')) {

//                        $typography   .= bs_font_to_css(theme_get_setting('typo_view_'.$view_title.'_description_style','bs'));

//                    }

//

//                    if (theme_get_setting('typo_view_'.$view_title.'_description_color','bs')) {

//                        $typography   .= 'color: '.theme_get_setting('typo_view_'.$view_title.'_description_color','bs').' !important;';

//                    }

//                    $typography   .= "}\n";

//                }

//            }

//

//        }

//    }

//    if (theme_get_setting('typo_webformtitle_style','bs') || theme_get_setting('typo_webformtitle_color','bs')) {

//        $typography   .= ".flx-map-form span.webform-title{";

//        if (theme_get_setting('typo_webformtitle_style','bs')) {

//            $typography   .= bs_font_to_css(theme_get_setting('typo_webformtitle_style','bs'));

//        }

//

//        if (theme_get_setting('typo_webformtitle_color','bs')) {

//            $typography   .= 'color: '.theme_get_setting('typo_webformtitle_color','bs').' !important;';

//        }

//        $typography   .= "}\n";

//

//    }

//    if (theme_get_setting('typo_webformdescription_style','bs') || theme_get_setting('typo_webformdescription_color','bs')) {

//        $typography   .= ".flx-map-form span.webform-description{";

//        if (theme_get_setting('typo_webformdescription_style','bs')) {

//            $typography   .= bs_font_to_css(theme_get_setting('typo_webformdescription_style','bs'));

//        }

//

//        if (theme_get_setting('typo_webformdescription_color','bs')) {

//            $typography   .= 'color: '.theme_get_setting('typo_webformdescription_color','bs').' !important;';

//        }

//        $typography   .= "}\n";

//    }



    

    

    

    

	$vars['typography'] = $typography;



	/* Get theme settings

	---------------------------------------------------------------------------------------- */

//	$vars['footer_text']   = theme_get_setting('footer_text','md_leaders');

	$vars['header_code']   = theme_get_setting('header_code','md_leaders');

	$vars['footer_code']   = theme_get_setting('footer_code','md_leaders');

	if (theme_get_setting('custom_css','md_leaders')) {

		$vars['custom_css']  = theme_get_setting('custom_css','md_leaders');

	}

	drupal_add_css(path_to_theme() . '/css/ie7.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));

}





/**

 * Override or insert vars into the page template for HTML output.

 */

function md_leaders_process_html(&$vars) {

    // Hook into color.module.

    if (module_exists('color')) {

      _color_html_alter($vars);

    }

    $classes = explode(' ', $vars['classes']);

    if ($node = menu_get_object()) {

      $node_type_class = drupal_html_class('node-type-' . $node->type);

      if (in_array($node_type_class, $classes)) {

        theme_get_setting('extra_page_classes','md_leaders') == 0 ? '' : $classes = str_replace($node_type_class, '', $classes);

        $classes = str_replace('node-type-', 'page-type-', $classes);

      }

    }

    $vars['classes'] = trim(implode(' ', $classes));

}





/**

 * Override or insert vars into the page template.

 */

function md_leaders_preprocess_page(&$vars, $hook) {

  //------------------------footer-----------------------

  if (theme_get_setting('copyright_text', 'md_leaders')) {

    $vars['copyright'] = theme_get_setting('copyright_text', 'md_leaders');

  } 

  $vars['logo_path']="";
  if(theme_get_setting('default_logo', 'md_leaders')) {
        $vars['logo_path'] = '';
  }else{
        if(theme_get_setting('logo_normal_upload','md_leaders')) {
            $file_upload = json_decode(theme_get_setting('logo_normal_upload','md_leaders'));
            if($file_upload->fid != 0) {
                $vars['logo_path'] = $file_upload->url;
            } else {
                $vars['logo_path'] = '';
            }
        }
  }
  

  /**

   * 404 template

   */

  $status = drupal_get_http_header("status");

  if ($status == "404 Not Found") {

    $vars['theme_hook_suggestions'][] = 'page__404';

    if (theme_get_setting('notfound_title', 'md_leaders')) {

      $vars['notfound_title'] = theme_get_setting('notfound_title', 'md_leaders');

    }

    if (theme_get_setting('notfound_description', 'md_leaders')) {

      $vars['notfound_description'] = theme_get_setting('notfound_description', 'md_leaders');

    }

  }

 

  

  

   /**

   * Preloader

   */

  $css = '';

  

  if (theme_get_setting('toggle_preload', 'md_leaders') == 0) {

    $vars['preload'] = 1;



    //loading

    if (theme_get_setting('preload_loading', 'md_leaders')) {

      $fid_preload_loading = theme_get_setting('preload_loading', 'md_leaders');

      $file = file_load((string) ($fid_preload_loading['fid']));



      if ($file) {

        $loading_url = file_create_url($file->uri);

        $css .= '.preloaderimg {background: url(' . $loading_url . ') no-repeat 50% 50% transparent;}';

      }

    }



  }

  drupal_add_css($css, array('group' => CSS_THEME, 'type' => 'inline'));

  

}



function md_leaders_process_page(&$vars) {

    // Hook into color.module.

    if (module_exists('color')) {

      _color_page_alter($vars);

    }

    $status = drupal_get_http_header("status");

    if($status == "404 Not Found") {

      $vars['theme_hook_suggestions'][] = 'page__404';

    }

    $vars['social_links'] = 0;

    // Since the title and the shortcut link are both block level elements,

    // positioning them next to each other is much simpler with a wrapper div.

    if (!empty($vars['title_suffix']['add_or_remove_shortcut']) && $vars['title']) {

      // Add a wrapper div using the title_prefix and title_suffix render elements.

      $vars['title_prefix']['shortcut_wrapper'] = array(

        '#markup' => '<div class="shortcut-wrapper clearfix">',

        '#weight' => 100,

      );

      $vars['title_suffix']['shortcut_wrapper'] = array(

        '#markup' => '</div>',

        '#weight' => -99,

      );

      // Make sure the shortcut link is the first item in title_suffix.

      $vars['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;

    }



}

/**

 * Implements hook_preprocess_maintenance_page().

 */

function md_leaders_preprocess_maintenance_page(&$vars) {

    $theme_path = drupal_get_path('theme','md_leaders');

    if(module_exists('fontello')) {

        drupal_add_css(drupal_get_path('module','fontello').'/css/fontello.fix.css');

        drupal_add_css('public://icon/fontello/fontello/css/fontello.css');

        drupal_add_css('public://icon/fontello/fontello/css/animation.css');

    }

   

    /********************************** Skin ********************************/

//    if (theme_get_setting('skins') != '0') {

//        drupal_add_css($theme_path . '/css/import/skin/'.theme_get_setting('skins').'.css', array('group' => CSS_THEME));

//    }

    if (!$vars['db_is_active']) {

        unset($vars['site_name']);

    }

    // Always print the site name and slogan, but if they are toggled off, we'll

    // just hide them visually.

    $vars['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;

    $vars['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;

    if ($vars['hide_site_name']) {

        // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.

        $vars['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));

    }

    if ($vars['hide_site_slogan']) {

        // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.

        $vars['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));

    }

}







//-------------------------font select on theme-setting------------------------------------

function md_leaders_font_to_css($font) {

    $font_arr = explode("|", $font);

    $css = "";

    if(count($font_arr) == 6) {

        if ($font_arr[0] != '0') {

            $css = ''.$font_arr[5].';';

        }

    }

    return $css;

}



function md_leaders_expand_font_weight($fw) {

    switch($fw) {

            case 'n1':

                    $fontExpand = "font-style: normal; font-weight: 100;";

            break;

            case 'i1':

                    $fontExpand = "font-style: italic; font-weight: 100;";

                    break;

            case 'n2':

                    $fontExpand = "font-style: normal; font-weight: 200;";

            break;

            case 'i2':

                    $fontExpand = "font-style: italic; font-weight: 200;";

                    break;

            case 'n3':

                    $fontExpand = "font-style: normal; font-weight: 300;";

            break;

            case 'i3':

                    $fontExpand = "font-style: italic; font-weight: 300;";

                    break;

            case 'n4':

                    $fontExpand = "font-style: normal; font-weight: normal;";

            break;

            case 'i4':

                    $fontExpand = "font-style: italic; font-weight: normal";

                    break;

            case 'n5':

                    $fontExpand = "font-style: normal; font-weight: 500;";

            break;

            case 'i5':

                    $fontExpand = "font-style: italic; font-weight: 500;";

                    break;

            case 'n6':

                    $fontExpand = "font-style: normal; font-weight: 600;";

            break;

            case 'i6':

                    $fontExpand = "font-style: italic; font-weight: 600;";

                    break;

            case 'n7':

                    $fontExpand = "font-style: normal; font-weight: bold;";

            break;

            case 'i7':

                    $fontExpand = "font-style: italic; font-weight: bold;";

                    break;

            case 'n8':

                    $fontExpand = "font-style: normal; font-weight: 800;";

            break;

            case 'i8':

                    $fontExpand = "font-style: italic; font-weight: 800;";

                    break;

            case 'n9':

                    $fontExpand = "font-style: normal; font-weight: 800;";

            break;

            case 'i9':

                    $fontExpand = "font-style: italic; font-weight: 800;";

                    break;

            default:

                    $fontExpand = "";

    }



    return $fontExpand;

}



function md_leaders_check_und($param) {

	if (isset($param['und'])) {

		return $param['und'][0];

	} else {

		return $param[0];

	}

}

function theme_path() {

    $theme_path = drupal_get_path('theme','md_leaders');



    return $theme_path;

}