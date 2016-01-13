<?php
/**
 * @file
 * Default theme implementation to wrap block rows.
 *
 * Available variables:
 * - $content: The renderable array containing the menu.
 * - $classes: A string containing the CSS classes for the DIV tag. 
 *
 */
?>
<div class="<?php print $classes; ?>">
  <?php print render($content); ?>
</div>
