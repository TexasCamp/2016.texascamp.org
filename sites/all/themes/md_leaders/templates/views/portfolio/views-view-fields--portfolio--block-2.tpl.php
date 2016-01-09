<div class="owl-carousel-item portfolio_item_image">
    <div class="portfolio_links">  
        <img src="<?php print file_create_url($fields['field_portfolio_thumbnail']->content); ?>" alt="">
        <a class="p-view prettyPhoto" title="" data-gal="prettyPhoto[gal]" href="<?php print file_create_url($fields['field_portfolio_thumbnail']->content); ?>"></a>
        <a class="p-link" title="" href="<?php print base_path().'/default-folio'; ?>"></a>
    </div>

    <h3><a href="<?php print base_path().'/default-folio'; ?>"><?php print $fields['title']->content; ?></a></h3>

</div>