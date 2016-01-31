"use strict";

(function($) {

  CKEDITOR.dialog.add( 'blocks', function( editor ) {
    var lang = editor.lang.blocks,
    commonLang = editor.lang.common;

    var options = [];
    $.ajax({ 
      type: "GET",
      url: Drupal.settings.basePath + 'ckeditor/blocks',
      success: function(result) {
        options = result;
      },
      async: false,
      cache: false
    });
    var items = [];
    $.each(options, function(key, value) {
      items.push([value, key]);
    });

    return {
      title: 'Edit Block',
      minWidth: 400,
      minHeight: 300,
      contents: [
        {
          id: 'info',
          label: lang.infoTab,
          accessKey: 'I',
          elements: [
            {
              id: 'block',
              type: 'select',
              label: lang.blockTitle,
              items: items,
              setup: function( widget ) {
                this.setValue( widget.data.block );
              },
              commit: function( widget ) {
                widget.setData( 'block', this.getValue() );
              }
            },
          ]
        }
      ]
    };
  } );
})(jQuery);