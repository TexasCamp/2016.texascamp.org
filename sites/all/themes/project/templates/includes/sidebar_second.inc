<!-- sidebar-second -->
<?php if (!empty($page['sidebar_second'])): ?>
	<aside class="sidebar-second <?php print $sidebar_second_class; ?>" role="complementary">
		<div class="sidebar">
			<?php print render($page['sidebar_second']); ?>
		</div>
	</aside>
<?php endif; ?>