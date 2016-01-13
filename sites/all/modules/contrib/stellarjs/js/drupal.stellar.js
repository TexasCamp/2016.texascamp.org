/**
* @file
* drupal.stellar.js
*
* Provides general enhancements.
*/

var Drupal = Drupal || {};

(function($, Drupal){
  "use strict";

	Drupal.behaviors.stellarjs = {
		attach: function(context, settings) {

			function disableOnMobile() {
				$(window).resize(function() {
					if ($(window).width() < 991 || navigator.userAgent.match(/(Android|iPod|iPhone|iPad|IEMobile|Opera Mini)/)) {
						$.stellar('destroy');
					} else {
						$.stellar();
					}
				}).trigger('resize');
			}

			if ($.fn.stellar) {
				// Initialize Stellar.
				$.stellar();

				if (settings.stellarjs.disable_on_mobile) {
					// Disable on mobile.
					switch (settings.stellarjs.disable_on_mobile) {
						case 1:
							$(window).resize(function() {
								if (navigator.userAgent.match(/(Android|iPod|iPhone|iPad|IEMobile|Opera Mini)/)) {
									$.stellar('destroy');
								} else {
									$.stellar();
								}
							}).trigger('resize');
							break;

						case 2:
							if (settings.stellarjs.mobile_screen_width.length > 0) {
								$(window).resize(function() {
									if ($(window).width() < settings.stellarjs.mobile_screen_width ) {
										$.stellar('destroy');
									} else {
										$.stellar();
									}
								}).trigger('resize');
							}
							break;

						default:
							disableOnMobile();
							break;
					}
					
				}

			}
		}
	};

})(jQuery, Drupal);