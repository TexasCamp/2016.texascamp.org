<?php

/**
 * @file
 * Default theme implementation for field collection items.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) field collection item label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-field-collection-item
 *   - field-collection-item-{field_name}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="progress">
    <div class="progress-bar <?php print render($content['field_about_skill_color']['#items'][0]['value']); ?>" role="progressbar" aria-valuenow="<?php print render($content['field_about_skill_value'][0]); ?>" aria-valuemin="0" aria-valuemax="100" style="width: <?php print $content['field_about_skill_value'][0]['#markup']; ?>%">
        <span><?php print render($content['field_about_skill_name'][0]); ?></span>
    </div>
</div>