<section class="main-container">
	<div class="container">
		<?php include 'information.inc'; ?>
		<div class="row">

			<!-- main start -->
			<div class="main <?php print $main_class; ?>" >
				<!-- title -->
				<?php include 'title.inc'; ?>
				<a id="main-content"></a>
				
				<?php print render($page['content']); ?>
			</div>
			<!-- main end -->

			<?php include 'sidebar_first.inc'; ?>
			<?php include 'sidebar_second.inc'; ?>
	
		</div>
	</div>
</section>