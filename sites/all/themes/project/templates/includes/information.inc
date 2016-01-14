<?php
	$help = element_children($page['help']);
	$tab_check = element_children($tabs);
	$block_check = (!empty($tabs['#primary']) || !empty($tabs['#secondary'])) ? TRUE : FALSE;
?>
<?php if (!empty($messages) ||  !empty($tab_check) || !empty($help) || !empty($action_links) || $block_check): ?>
	<!-- Information -->
	<div class="information">
	  <?php print $messages; ?>
	  <?php if (!empty($tabs)): ?>
		  <?php print render($tabs); ?>
		<?php endif; ?>
		<?php if (!empty($page['help'])): ?>
		  <?php print render($page['help']); ?>
		<?php endif; ?>
		<?php if (!empty($action_links)): ?>
		  <ul class="action-links"><?php print render($action_links); ?></ul>
		<?php endif; ?>
	</div>
<?php endif; ?>