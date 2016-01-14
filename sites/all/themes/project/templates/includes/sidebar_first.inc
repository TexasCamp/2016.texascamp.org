<!-- sidebar-first -->
<?php if (!empty($page['sidebar_first'])): ?>
	<aside class="sidebar-first <?php print $sidebar_first_class; ?>" role="complementary">
		<div class="sidebar">
			<?php print render($page['sidebar_first']); ?>
		</div>
	</aside>
<?php endif; ?>