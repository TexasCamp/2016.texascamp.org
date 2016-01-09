<?php

/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<?php
    $subtitle = variable_get($block->delta.'_block_sub_title');
    $quote = variable_get($block->delta.'_quote');
    $author = variable_get($block->delta.'_author');
?>

<?php if($block->delta == 'leaders_service-block'): ?>
    <section id="info" class="grey_section">
        <div class="container">
            <div class="row">
                <div class="col-sm-12 text-center">
                    <?php if (isset($subtitle) && $subtitle != null): ?>
                        <h2 class="block-header"><?php print $subtitle; ?></h2>
                    <?php endif; ?> 
                    <?php if (isset($quote) && $quote != null && isset($author) && $author != null): ?>      
                        <blockquote><?php print $quote; ?>
                            <h3> <?php print $author; ?> </h3>
                        </blockquote>
                    <?php endif; ?>       
                </div>
                <?php print $content; ?>
            </div>
        </div>
    </section>
<?php elseif($block->delta == 'portfolio-block_2'): ?>
	<section id="latest_works" class="grey_section">
        <div class="container">
            <div class="row">
                <div class="block col-sm-3">
                    <?php if (isset($subtitle) && $subtitle != null): ?>
                        <h3><?php print $subtitle; ?></h3>
                    <?php endif; ?>
                    <p>
                        <?php print $quote; ?>
                    </p>
                </div>
                <div class="col-sm-9 to_slide_left">
                    <?php print $content; ?>
                </div>
            </div>
        </div>
    </section>
<?php else:?>
        <div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

          <?php print render($title_prefix); ?>
                <?php if ($block->subject): ?>
                  <h2<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
                <?php endif;?>
          <?php print render($title_suffix); ?>

              <div class="content"<?php print $content_attributes; ?>>
                <?php print $content ?>
              </div>
        </div>
<?php endif;?>