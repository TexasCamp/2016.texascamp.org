"use strict";

(function($) {
  
  CKEDITOR.plugins.add('blocks', {
    lang: 'en',
    requires: 'widget,dialog',
    icons: 'blocks',
    init: function(editor) {

      CKEDITOR.dialog.add('blocks', this.path + 'dialogs/blocks.js');

      function getBlockHtmlFromId(id) {
        var ret;
        var parts = id.replace('[block:', '').replace(']', '').split('=');
        $.ajax({ 
          type: "GET",
          url: Drupal.settings.basePath + 'ckeditor/block/' + parts[0] + '/' + parts[1],
          success: function(result) {
            ret = result.html;
          },
          async: false,
          cache: false
        });
        return ret;
      }

      function getIdFromBlock(block) {

      }

      // Register the featurette widget.
      editor.widgets.add('blocks', {
        allowedContent: '*',
        editables: {},
        parts: {
          div: 'div.blocks'
        },
        // Define the template of a new Simple Box widget.
        // The template will be used when creating new instances of the Simple Box widget.
        template: '<div class="blocks">Test</div>',
        button: 'Insert a block',
        dialog: 'blocks',
        upcast: function(element) {
          if(element.name == 'div' && element.hasClass('blocks')) {
            var blockId = '';
            if ((element.children.length > 0) && (blockId = element.children[0].value)) {
              element.attributes['data-block'] = blockId;
            }
            return true;
          }
          return false;
        },
        downcast: function(element) {
          element.setHtml(element.attributes['data-block']);
          delete element.attributes['data-block'];
          return element;
        },
        init: function() {
          this.setData('block', this.parts.div.getHtml());
        },
        data: function() {
          this.parts.div.setAttribute('data-block', this.data.block);
          if (this.data.block) {
            this.parts.div.setHtml(getBlockHtmlFromId(this.data.block));
          }
        }
      });
    }
  });

})(jQuery);