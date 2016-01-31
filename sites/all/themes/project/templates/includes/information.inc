<?php
$help = (!empty($page['help'])) ? element_children($page['help']) : NULL;
$tab_check = (!empty($tabs)) ? element_children($tabs) : NULL;
$block_check = (!empty($tabs['#primary']) || !empty($tabs['#secondary'])) ? TRUE : FALSE;
?>
<?php if ($is_front): ?>
	<?php if (!empty($messages) ||  !empty($tab_check) || !empty($help) || !empty($action_links) || $block_check): ?>
		<!-- Information -->
		<div class="information">
			<div class="container">
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
		</div>
	<?php endif; ?>
<?php else: ?>
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
<?php endif; ?>