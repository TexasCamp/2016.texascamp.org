<?php
$Skills = $fields['field_portfolio_skills']->content;

$Skills = explode(",", $Skills);
$Count = 0;
?>

<li>
    <a href="#" data-largesrc="<?php print file_create_url($fields['field_portfolio_thumbnail']->content); ?>" data-title="<?php print $fields['title']->content; ?>" data-description="data-description">
        <img src="<?php print file_create_url($fields['field_portfolio_thumbnail']->content); ?>" alt="img01"/>
    </a>
    <h3><?php print $fields['title']->content; ?></h3>
    <div class="portfolio_description">
        <div class="block">
            <h3><?php print $fields['title']->content.' '.t('Details'); ?></h3>
            <p class="description">
                <?php print $fields['field_portfolio_description']->content; ?>
            </p>
            <p class="skills">
            	<span><?php print t('Skills'); ?>:</span> 
            	<?php
					foreach($Skills as $key=>$value) {
						$Count++;
						if($Count == count($Skills))
        					print $value;
						else
							print $value.', ';
					}
				?>
            </p>
            <p class="client">
            	<span><?php print t('Client'); ?>:</span> 
                <a href="<?php print $fields['field_portfolio_website']->content; ?>"><?php print $fields['field_portfolio_clients']->content; ?></a>
            </p>
            <p class="location">
            	<span><?php print t('Location'); ?>:</span> 
                <a href="<?php print $fields['field_portfolio_website']->content; ?>"><?php print $fields['field_portfolio_website']->content; ?></a>
            </p>
            <p class="view-project"><a href="<?php print $fields['path']->content; ?>" class="theme_btn"><?php print t('View Project'); ?></a></p>
        </div>
    </div>
</li>