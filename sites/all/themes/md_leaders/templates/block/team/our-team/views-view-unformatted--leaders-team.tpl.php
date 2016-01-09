<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php $i=0; ?>  
<?php foreach ($rows as $id => $row): ?>
  <?php if ($i%2==0) echo'<div class="row team">'; ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
  <?php if ($i%2!=0) echo'</div>'; ?>
  <?php $i++; ?>  
<?php endforeach; ?>
<?php if ($i%2!=0) echo'</div>'; ?>