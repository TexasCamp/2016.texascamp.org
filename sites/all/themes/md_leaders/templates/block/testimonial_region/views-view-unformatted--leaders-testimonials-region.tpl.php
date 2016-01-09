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
  
  <div class="col-sm-12 text-center">
      <div id="carousel-testimonials" class="carousel dxcarousel slide widget_testimonials block">
          <a class="carousel-control left" href="#carousel-testimonials" data-slide="prev"></a>
          <a class="carousel-control right" href="#carousel-testimonials" data-slide="next"></a>
          <div class="carousel-inner">  
              <?php foreach ($rows as $id => $row): ?>
                  <div class="item <?php if ($id=="0") { print 'active';  }?>" >
                    <?php print $row; ?>
                  </div>
             <?php endforeach; ?>
          </div>
      </div>
  </div>