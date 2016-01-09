<!-- Heading -->
<div class="cbp-l-project-title"><?php print $title;?></div>
<div class="cbp-l-project-subtitle"><?php print $name;?></div>

<!-- image Thumbnail -->
<div class="cbp-l-project-thumbnail"><?php print render($content['field_portfolio_thumbnail']);?></div>
<!-- Project detail -->
<div class="cbp-l-project-container">
  <div class="cbp-l-project-desc">
    <div class="cbp-l-project-desc-title"><span><?php print t('Project Description'); ?></span></div>
    <div class="cbp-l-project-desc-text"><?php print render($content['field_portfolio_description']); ?></div>
  </div>
  <div class="cbp-l-project-details">
    <div class="cbp-l-project-details-title"><span><?php print t('Project Details'); ?></span></div>

    <ul class="cbp-l-project-details-list">
      <li><strong>Client</strong> <?php print $node->field_portfolio_clients['und'][0]['value']; ?></li>
      <li><strong>Date</strong><?php print format_date($node->created, 'custom', 'd F Y');?></li>
      <li><strong>Categories</strong> <?php print render($content['field_portfolio_skills']); ?></li>
    </ul>
    <a href="#" target="_blank" class="cbp-l-project-details-visit"><?php print  t('visit the site');?></a>
  </div>
</div>
<?php print views_embed_view('portfolio_relate', 'block'); ?>

<br>
<br>
<br>
