/**
 * @file
 *
 * Favicon generator color picker function.
 */

(function($) {
  Drupal.behaviors.favicon_generator = {
    attach: function(context, settings) {
      // Attach color wheel behaviour.
      $('.favicon_generator_colorpicker').farbtastic('#edit-favicon-generator-color');

      // Attach onClick event for swatches.
      $('.form-item-favicon-generator-color .color-preset:not(.favicon-generator-color-preset-processed)')
      .addClass('favicon-generator-color-preset-processed')
      .click(function() {
        var color = $(this).css('background-color');

        color = Drupal.favicon_generator.rgb2hex(color);
        $.farbtastic('.favicon_generator_colorpicker').setColor(color);
      });
    }
  };

  Drupal.favicon_generator = Drupal.favicon_generator || {};
  Drupal.favicon_generator.rgb2hex = function(rgb) {
    if (rgb.search("rgb") == -1) {
      return rgb;
    }
    else {
      rgb = rgb.match(/^rgb\((\d+),\s*(\d+),\s*(\d+)\)$/);
      return ("#" +
        Drupal.favicon_generator.hex(rgb[1]) +
        Drupal.favicon_generator.hex(rgb[2]) +
        Drupal.favicon_generator.hex(rgb[3]));
    }
  };
  Drupal.favicon_generator.hex = function(x) {
    return ("0" + parseInt(x).toString(16)).slice(-2);
  };
})(jQuery);
