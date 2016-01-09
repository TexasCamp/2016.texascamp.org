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

<div class="panel-display panel-blog clearfix" <?php if (!empty($css_id)) {print "id=\"$css_id\"";} ?>>
    <div class="panel-panel panel-top">
            <div class="inside"><?php print $content['top']; ?></div>
    </div>
    <div class="panel-panel panel-content">
        <div class="panel-panel panel-main">
            <div class="inside"><?php print $content['main']; ?></div>
        </div>
        <div class="panel-panel panel-sidebar">
            <div class="inside"><?php print $content['sidebar']; ?></div>
        </div>
    </div>
    <div class="panel-panel panel-bottom">
        <div class="inside"><?php print $content['bottom']; ?></div>
    </div>
</div>

