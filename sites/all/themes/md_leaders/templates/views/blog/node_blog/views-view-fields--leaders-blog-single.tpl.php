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
<?php
//dsm($fields); 
?>
<article class="post type-post">
    <header class="entry-header">
        <?php print $fields['title']->content; ?>

        <?php if ($row->field_field_multimedia): ?>
            <div class="entry-thumbnail">
                <?php if ($row->field_field_multimedia[0]['rendered']['#bundle'] == 'video' || count($row->field_field_multimedia) == 1): ?>
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
        <?php endif; ?>


        <div class="entry-meta">
            <?php print $fields['name']->content; ?>
            <?php print $fields['field_category']->content; ?>
            <?php print $fields['created']->content; ?>
            <?php print $fields['comment_count']->content; ?>
        </div>
        <!-- .entry-meta --> 
    </header>
    <!-- .entry-header -->

    <div class="entry-content">
        <?php print $fields['body']->content; ?>
    </div>
    <!-- .entry-content -->

    <footer class="bottom-entry-meta">
        <div class="entry-tags row">
            <div class="col-sm-6">
                <span class="tags-links">
                    <?php print $fields['field_tags']->content; ?>
                </span>
            </div>
            <div class="col-sm-6">  
                <span class="st_facebook_hcount"></span>
                <span class="st_twitter_hcount"></span>
                <span class="st_googleplus_hcount"></span>
            </div>
        </div>
        <div class="author-meta row">
            <div class="col-sm-4 author-image">
                <?php print $fields['picture']->content; ?>
            </div>
            <div class="col-sm-8">
                <h3><?php print $fields['field_name_display']->content; ?>
                    <span class="author-social">
                        <?php print $fields['field_account_social']->content; ?>
                    </span>
                </h3>
                <p><?php print $fields['field_description']->content; ?></p>
            </div>
        </div>
    </footer>  
</article>	