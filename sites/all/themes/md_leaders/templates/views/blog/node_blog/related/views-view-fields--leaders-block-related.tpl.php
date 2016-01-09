<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>

<?php if (!empty($row->field_field_multimedia)): ?>
    <?php if ($row->field_field_multimedia[0]['rendered']['#bundle'] == 'image' && count($row->field_field_multimedia) == 1): ?>
    <article class="post format-standard">
    <?php elseif ($row->field_field_multimedia[0]['rendered']['#bundle'] == 'video'): ?>
    <article class="post format-video">
    <?php  else: ?>
       <article class="post format-gallery">
    <?php endif; ?>

	<div class="entry-thumbnail">
	  <?php if ($row->field_field_multimedia[0]['rendered']['#bundle'] == 'video'):?>
		<?php print $fields['field_image']->content; ?>
		<?php print $fields['field_link_video']->content; ?>
	  <?php  elseif (count($row->field_field_multimedia) == 1): ?>
                <?php print $fields['field_multimedia']->content; ?>
            <?php else: ?>
              <div id="carousel-generic" class="carousel slide">

                <div class="carousel-inner">
                  <div class="item active">
                    <?php print $fields['field_multimedia']->content; ?>
                  </div>
                </div>

                <!-- Controls -->
                <a class="left carousel-control" href="#carousel-generic" data-slide="prev">
                  <span class="icon-prev"></span>
                </a>
                <a class="right carousel-control" href="#carousel-generic" data-slide="next">
                  <span class="icon-next"></span>
                </a>
              </div>
            <?php endif; ?>
	</div>
<?php  else: ?>  
        <article class="post format-small-image">
            <div class="entry-thumbnail">
                <?php print $fields['field_image']->content; ?>
            </div>
<?php endif; ?>	
	
	<?php print $fields['title']->content; ?>
	<?php print $fields['created']->content; ?>
	
	<p class="introtext"><?php print $fields['body']->content; ?></p>
	<p class="entry-share">

<!--		<a title="Facebook" href="#" class="socialico-facebook social_sharebt"><span class="st_facebook_hcount"></span></a>
		<a title="Twitter" href="#" class="socialico-twitter social_sharebt"><span class="st_twitter_hcount"></span></a>
		<a title="Google" href="#" class="socialico-google social_sharebt"><span class="st_googleplus_hcount"></span></a>-->

	</p>
</article>
