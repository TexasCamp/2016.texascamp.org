<?php
/**
 * @file
 * Adativetheme implementation to present a Panels layout.
 *
 * Available variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 * - $css_id: unique id if present.
 * - $panel_prefix: prints a wrapper when this template is used in certain context,
 *   such as when rendered by Display Suite or other module - the wrapper is
 *   added by Adaptivetheme in the appropriate process function.
 * - $panel_suffix: closing element for the $prefix.
 *
 * @see adaptivetheme_preprocess_two_33_66()
 * @see adaptivetheme_preprocess_node()
 * @see adaptivetheme_process_node()
 */
?>

<?php
$wrapper_classes = array();
//$item = menu_get_item();
//if ($item['path'] == 'blog' ||$item['path'] == 'taxonomy/term/%' || $item['path'] == 'post-date/%') {
//$wrapper_classes[] = 'blog';
//}
//if (isset($vars['node']) && $vars['node']->type == 'article') {
//$wrapper_classes[] = 'blog-single';
//}
$path_alias  = drupal_get_path_alias();
$path       = drupal_get_normal_path($_GET['q']);
$path_tearm  = "taxonomy/term/*";
$path_view   = "blog" . PHP_EOL . "post-date/*";
$path_node   = "blog/*";

if (drupal_match_path($path_alias, $path_view) || drupal_match_path($path, $path_tearm)){
        $wrapper_classes[] = 'blog';
}
if (drupal_match_path($path_alias, $path_node)){
        $wrapper_classes[] = 'blog-single';
}

?>



<?php if (trim(implode(' ', $wrapper_classes)) == 'blog-single'): ?>
    <script type="text/javascript" src="http://w.sharethis.com/button/buttons.js"></script>
    <script type="text/javascript">stLight.options({publisher: "ur-6a7e320d-37d8-511-633d-4264e3ae8c", doNotHash: false, doNotCopy: false, hashAddressBar: false});</script>
<?php endif; ?>

<?php print $content['top']; ?>

<section class="grey_section" id="middle">
	<div class="container">
            <div class="row <?php print implode(' ', $wrapper_classes); ?>">
                
                
                    <?php if (theme_get_setting('sidebar_position', 'md_leaders') == 'left'): ?>
                        <aside class="col-sm-3">
                            <?php print render($content['sidebar']); ?>
                        </aside>
                    <?php endif; ?>

                    <?php if (trim(implode(' ', $wrapper_classes)) == 'blog'): ?>
                            <?php if (theme_get_setting('sidebar_position', 'md_leaders') == 'no'): ?>
                              <div class="col-sm-12"><?php print $content['main']; ?></div>
                            <?php else: ?>
                              <div class="col-sm-9"><?php print $content['main']; ?></div>
                            <?php endif; ?>
                              
                    <?php elseif (trim(implode(' ', $wrapper_classes)) == 'blog-single'): ?>
                            <?php if (theme_get_setting('sidebar_position', 'md_leaders') == 'no'): ?>
                                    <div class="col-sm-12"><div class="content-area" id="primary">
                                        <div role="main" class="site-content" id="content">
                                          <?php print $content['main']; ?>
                                        </div>
                                      </div></div>
                            <?php else: ?>
                                    <div class="col-sm-9"><div class="content-area" id="primary">
                                        <div role="main" class="site-content" id="content">
                                          <?php print $content['main']; ?>
                                        </div>
                                      </div></div>
                            <?php endif; ?>
                     <?php else: ?>
                            <?php if (theme_get_setting('sidebar_position', 'md_leaders') == 'no'): ?>
                                <div class="col-sm-12"><?php print $content['main']; ?></div>
                            <?php else: ?>
                                <div class="col-sm-9"><?php print $content['main']; ?></div>
                            <?php endif; ?>
                    <?php endif; ?>

                    <?php if (theme_get_setting('sidebar_position', 'md_leaders') == 'right'): ?>
                        <aside class="col-sm-3">
                            <?php print render($content['sidebar']); ?>
                        </aside>
                    <?php endif; ?>
         </div>
      </div>
</section>
<?php print $content['bottom']; ?>

