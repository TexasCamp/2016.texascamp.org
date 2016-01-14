<?php if (!empty($title_prefix) || !empty($title) || !empty($title_suffix)): ?>
	<div class="page-title-wrapper">
		<?php print render($title_prefix); ?>
		<?php if (!empty($title)): ?>
			<h1 class="page-title"><?php print $title; ?></h1>
		<?php endif; ?>
		<?php print render($title_suffix); ?>
		<div class="separator-<?php print $page_title_separator; ?>"></div>
	</div>
<?php endif; ?>
