<?php
/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<div class="content-area" id="primary">
  <div role="main" class="site-content" id="content">
    <?php foreach ($rows as $id => $row): ?>
      <?php
      if ($classes_array[$id]) {
        print '<div class="' . $classes_array[$id] . '">';
      }
      ?>
      <?php print $row; ?>
      <?php
      if ($classes_array[$id]) {
        print '</div>';
      }
      ?>
    <?php endforeach; ?>
  </div>
</div>