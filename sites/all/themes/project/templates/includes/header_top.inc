<!-- Header Top -->
<?php if (!empty($page['header_top']) || !empty($secondary_nav)): ?>
	<?php if (!empty($secondary_nav)): ?>
		<div <?php if (!empty($header_top_attr)) { print drupal_attributes($header_top_attr);} ?>>
			<div class="container">
				<div class="row">
					<div class="col-xs-3 col-sm-6 col-md-9">
						<div class="header-top-first clearfix">
							<?php print render($page['header_top']); ?>
						</div>
					</div>
					<div class="col-xs-9 col-sm-6 col-md-3">
						<div id="header-top-second"  class="clearfix">
							<?php if (!empty($secondary_nav)): ?>
							<div id="secondary-navbar-menu">
								<nav class="navbar-menu" role="navigation">
									<?php print render($secondary_nav); ?>
								</nav>
							</div>
							<?php endif; ?>
						</div>
					</div>
				</div>
			</div>
		</div>
	<?php else: ?>
		<div <?php if (!empty($header_top_attr)) { print drupal_attributes($header_top_attr);} ?>>
			<div class="container">
				<div class="row">
					<div class="col-md-12">
						<div class="header-top-first clearfix">
							<?php print render($page['header_top']); ?>
						</div>
					</div>
				</div>
			</div>
		</div>
	<?php endif; ?>
<?php endif; ?>