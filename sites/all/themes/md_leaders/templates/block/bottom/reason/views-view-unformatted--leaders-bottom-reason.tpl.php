<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
  
<?php $i=1; ?>  
<?php foreach ($rows as $id => $row): ?>
    <div class="panel panel-default">
            <div class="panel-heading">
                <h4 class="panel-title">
                    <a href="#collapse<?php echo $i; ?>" data-parent="#accordion" data-toggle="collapse" class="collapsed">
                        <?php print ($view->result[$id]->node_title); ?>
                    </a>
                </h4>
            </div>
            <div class="panel-collapse collapse" id="collapse<?php echo $i ;?>" style="height: 0px;">
                <div class="panel-body">
                    <p><?php print ($view->result[$id]->field_body[0]['raw']['value']); ?></p>
                </div>
            </div>
        </div>
    <?php $i++; ?>
<?php endforeach; ?>