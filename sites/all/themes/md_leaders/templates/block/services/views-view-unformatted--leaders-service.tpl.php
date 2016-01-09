<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="to_animate_child_blocks">
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
