"use strict";
if(typeof Placeholdem === 'function') {
	if (document.querySelectorAll( '[placeholder]' ).length) {
		Placeholdem( document.querySelectorAll( '[placeholder]' ) );
	};
}

var $ = jQuery.noConflict();

function animateElements() {

	//animation to elements
	var windowHeight = jQuery(window).height();
	jQuery('.to_fade, .block-header, .block-header + p').each(function(){
	var imagePos = jQuery(this).offset().top;
	var topOfWindow = jQuery(window).scrollTop();
		if (imagePos < topOfWindow+windowHeight-100) {
			jQuery(this).addClass("animated fadeInUp");
		}
	});

	jQuery('.to_slide_left').each(function(){
	var imagePos = jQuery(this).offset().top;
	var topOfWindow = jQuery(window).scrollTop();
		if (imagePos < topOfWindow+windowHeight-100) {
			jQuery(this).addClass("animated fadeInLeft");
		}
	});

	jQuery('.to_slide_right').each(function(){
	var imagePos = jQuery(this).offset().top;
	var topOfWindow = jQuery(window).scrollTop();
		if (imagePos < topOfWindow+windowHeight-100) {
			jQuery(this).addClass("animated fadeInRight");
		}
	});

	jQuery('.to_animate_child_blocks').each(function(){
	var imagePos = jQuery(this).offset().top;
	var topOfWindow = jQuery(window).scrollTop();
		if (imagePos < topOfWindow+windowHeight-100) {
			jQuery(this).find('.block').each(function(index){
				var self = jQuery(this);
				setTimeout(function(){
					self.addClass("animated fadeInRight");
				}, index*200);
			});
		}
	});

}
(function($){
    $.fn.mdtextbold = function(){
        var $this = $(this),
            text_full = $this.text().split(' ');
                if($this.children("a").length > 0){        
                     $this.find("a").html(text_full.shift() + ' <strong>' + text_full.join(' ') + '</strong>');
                 }
                 else{
                     $this.html(text_full.shift() + ' <strong>' + text_full.join(' ') + '</strong>');
                 }
    }
    
    jQuery(document).ready(function() {
            //title strong
            if ( $.fn.mdtextbold ) {
		$( '.light_section h2' ).each(function(){
			$(this).mdtextbold();
		});
                $( '.light_section h3' ).each(function(){
			$(this).mdtextbold();
		});
                $( '.light_section .thumbnail h4' ).each(function(){
			$(this).mdtextbold();
		});
                $( '#info .block h3' ).each(function(){
			$(this).mdtextbold();
		});
                $( '.title_strong h3' ).each(function(){
			$(this).mdtextbold();
		});
                $( '.title_strong h2' ).each(function(){
			$(this).mdtextbold();
		});
	}
//        blog related
        $(window).resize(function() {
            var pic_width = $('.related-posts .entry-thumbnail').width();
                if (pic_width >270) {
                    pic_width = 270;
                    $('.related-posts .carousel img').width(270);
                }
            var pic_height = pic_width *264/ 270;
            $('.related-posts .carousel img').height(pic_height);
        }).resize();
    })
})(jQuery);

(function($){
    jQuery(document).ready(function() {

            //menu
            if (jQuery().superfish) {
                    jQuery('ul.sf-menu').superfish({
                            delay:       700,
                            animation:   {opacity:'show',height:'show'},
                            animationOut: {opacity: 'hide'},
                            speed:       'fast',
                            disableHI:   false,
                            cssArrows:   false,
                            autoArrows:  false
                    });
            }

            //toTop
            if (jQuery().UItoTop) {
                jQuery().UItoTop({ easingType: 'easeOutQuart' });
            }



        //prettyPhoto
        if (jQuery().prettyPhoto) {
                    jQuery("a[data-gal^='prettyPhoto']").prettyPhoto({
                            hook: 'data-gal',
                            theme: 'facebook' /* light_rounded / dark_rounded / light_square / dark_square / facebook / pp_default*/
                    });
            }

            //carousel
            if (jQuery().carousel) {
                    jQuery('.carousel').carousel();
            }

            //owl carousel
            if (jQuery().owlCarousel) {
                    //upcomming events carousel
                jQuery(".owl-carousel.owl-items-3").owlCarousel({
                    navigation : true,
                    navigationText : false,
                    pagination : false,
                    items: 3
                });
                //team carousel
                jQuery(".owl-carousel.team").owlCarousel({
                    navigation : true,
                    navigationText : false,
                    pagination : false,
                    items: 4,
                });
                //partners
                jQuery(".partners").owlCarousel({
                    navigation : true,
                    navigationText : false,
                    pagination : false,
                    items: 5,
                    autoPlay: 5000
                });
            }

            //single page localscroll and scrollspy
            var navHeight = jQuery('#header').outerHeight(true) + 40;
            jQuery('body').scrollspy({
                    target: '.mainmenu_wrap',
                    offset: navHeight
            });
            if (jQuery().localScroll) {
                    jQuery('#mainmenu, #land').localScroll({
                            duration:1900,
                            easing:'easeOutQuart',
                            offset: 0
                    });

            }

            //portfolio and horizontal slider animation
            jQuery('.portfolio_links').find('a').css({opacity: 0});
            jQuery('.isotope-item, .horizontal_slider_introimg, .portfolio_item_image').hover(
                    function() {
                            jQuery( this ).find('.portfolio_links a').stop().animate({ opacity: 1}, 50, 'easeOutExpo').parent().find('.p-view').toggleClass('moveFromLeft').end().find('.p-link').toggleClass('moveFromRight');
                    }, function() {
                            jQuery( this ).find('.portfolio_links a').stop().animate({ opacity: 0}, 50, 'easeOutExpo').parent().find('.p-view').toggleClass('moveFromLeft').end().find('.p-link').toggleClass('moveFromRight');
                    }
            );

            //twitter
            //slide tweets
            jQuery('#tweets .twitter').bind('loaded', function(){
                    jQuery(this).addClass('flexslider').find('ul').addClass('slides');
            });
            if (jQuery().tweet) {
                    jQuery('.twitter').tweet({
                            modpath: "./twitter/",
                        count: 1,
                        avatar_size: 48,
                        loading_text: 'loading twitter feed...',
                        join_text: 'auto',
                        username: 'ThemeForest', 
                        template: "{avatar}{time}{join}<span class=\"tweet_text\">{tweet_text}</span>"
                    });
            }
            //webform
            $('.webform-client-form').addClass('contact-form');

    });
})(jQuery);

jQuery(window).load(function(){

	
	//init gallery
	Grid.init(); 
        
        
        
	setTimeout(function(){
		jQuery('.progress-bar').addClass('stretchRight');
		//init animation
		animateElements();
	}, 600);

	//stick header to top
	if (jQuery().sticky) {
	    jQuery("#header").sticky({ 
	    		topSpacing: 0,
	    		scrollBeforeStick: 220
	    	},
	    	function(){ 
	    		jQuery("#header").stop().animate({opacity:0}, 0).delay(500).stop().animate({opacity:1}, 800);
	    	},
	       	function(){ 
	    		jQuery("#header").stop().animate({opacity:0}, 0).delay(800).stop().animate({opacity:1}, 1000);
	    	}
	    );
	}
	
	jQuery('body').delay(1000).scrollspy('refresh');

	//preloader
	jQuery(".preloaderimg").fadeOut();
	jQuery(".preloader").delay(200).fadeOut("slow").delay(200, function(){
		jQuery(this).remove();
	});

	//fractionslider
	if (jQuery().fractionSlider) {
		var $mainSlider = jQuery('#mainslider');
		jQuery('.slider').fractionSlider({
			'fullWidth': 			true,
			'controls': 			false, 
			'pager': 				true,
			'responsive': 			true,
			'dimensions': 			"1920,700",
		    'increase': 			true,
			'pauseOnHover': 		false,
			'slideEndAnimation': 	true,
			'timeout' : 			3000,
			'speedOut' : 			1000
			
		});
	}



	//flickr
	// use http://idgettr.com/ to find your ID
	if (jQuery().jflickrfeed) {
		jQuery("#flickr").jflickrfeed({
			flickrbase: "http://api.flickr.com/services/feeds/",
			limit: 6,
			qstrings: {
				id: "63512867@N07"
			},
			itemTemplate: '<a href="{{image_b}}" data-gal="prettyPhoto[pp_gal]"><li><img alt="{{title}}" src="{{image_s}}" /></li></a>'
		}, function(data) {
			jQuery("#flickr a").prettyPhoto({
				hook: 'data-gal',
				theme: 'facebook'
	   		});
	   		jQuery("#flickr li").hover(function () {						 
			   jQuery(this).find("img").stop().animate({ opacity: 0.5 }, 200);
		    }, function() {
			   jQuery(this).find("img").stop().animate({ opacity: 1.0 }, 400);
		    });
		});
	}

});

jQuery(window).resize(function(){
	if (jQuery().sticky) {
		jQuery("#header").sticky('update');
	}
	jQuery('body').scrollspy('refresh');

});

jQuery(window).scroll(function() {

	animateElements();

});
