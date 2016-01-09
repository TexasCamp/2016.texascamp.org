/**
 * Megadrupal.com
 */

(function($) {
	$.fn.choosefont = function() {
		return this.each(function() {
			var self = $(this),
			id = self.attr('id'),
			inputhidden = 'input[name=' + id.replace(/-/g,"_") +']',
			fontfamilyval = "",
			fwchange = 1;
			
			self.find('.form-font').remove();
			// Restore from input
			data_arr = $(inputhidden).val().split('|');
			data_arr[0] = typeof data_arr[0] !== 'undefined' ? data_arr[0] : "0";
			if (!data_arr[0]) data_arr[0] = "0";
			data_arr[1] = typeof data_arr[1] !== 'undefined' ? data_arr[1] : "n4";
			data_arr[2] = typeof data_arr[2] !== 'undefined' ? data_arr[2] : "";
			data_arr[3] = typeof data_arr[3] !== 'undefined' ? data_arr[3] : "px";
			data_arr[4] = typeof data_arr[4] !== 'undefined' ? data_arr[4] : "0";
			if (!Drupal.settings.font_vars[data_arr[0]]) {
				data_arr[0] = "1";
			}
            var text_transform_arr = new Array('-','none','capitalize','lowercase','uppercase')

			//Build HTML
			html = '<div class="form-choosefont"><div class="form-inline">';
				html += '<div class="form-group"><label for="'+id +'-fontfamily">Font Family</label>';
				html += '<div class="md-selection medium"><select id="'+id +'-fontfamily" class="select">';
				$.each(Drupal.settings.font_array, function(key, value) {
					if (key == data_arr[0]) { _select = ' selected="selected"'} else { _select = '';}
					html += '<option'+_select+' value="'+key+'">'+value+'</option>';
				});
				html += '</select></div></div>';
				html += '<div class="form-group"><label for="fontweight-'+id +'">Weight</label><div class="md-selection small"><div id="fontweight-'+id+'" class="form-font-weight"></div></div></div>';
				html += '<div class="form-group"><label for="'+id +'-fontsize">Size</label>';
				html += '<input type="text" maxlength="128" value="'+data_arr[2]+'" id="'+id+'-fontsize" class="input-bgcolor gray small form-text" /></div>';
				html += '<div class="form-group"><label for="'+id +'-sizetype">Sizetype</label><div class="md-selection small"><select id="'+id +'-sizetype" class="select">';
				if (data_arr[3] == "em") {
					html += '<option value="px">px</option><option selected="selected" value="em">em</option>';
				} else {
					html += '<option value="px">px</option><option value="em">em</option>';
				}
				html += '</select></div></div>';
                html += '<div class="form-group"><label for="'+id +'-uppercase">Text transform</label>';
                html += '<div class="md-selection medium"><select id="'+id +'-uppercase" class="select">';
                $.each(text_transform_arr, function(key, value) {
                    if (value == data_arr[4]) { _select = ' selected="selected" '} else { _select = '';}
                    html += '<option ' + _select + ' value="'+value+'">'+value+'</option>';
                });
                html += '</select></div>';
			html += '</div></div></div>';

			self.prepend(html);

			fontfamilyval = data_arr[0];
			fontweight_html = '<select id="'+id +'-fontweight" class="select">';
			fontweight_arr = Drupal.settings.font_vars[fontfamilyval].Weight.split(',');
			$.each(fontweight_arr, function(index, value) {
				optval = $.trim(value);
				if (optval == data_arr[1]) { _select = ' selected="selected"'} else { _select = '';}
				fontweight_html += '<option'+_select+' value="'+optval+'">'+_expandFontWeight(optval)+'</option>';
			});
			fontweight_html += '</select>';
			$('#fontweight-'+id).html(fontweight_html);

			// Build preview
			if(!$('#previewbtn-'+id).length) {
				self.append('<div id="preview-'+id+'" class="textpreview form-elements"><p class="tp-textdemo">Grumpy wizards make toxic brew for the evil Queen and Jack.</p></div>');
			}

			$('#' + id +'-fontfamily').change(function(){
					fontfamilyval = $(this).val();
					fontweight_html = '<select id="'+id +'-fontweight" class="select">';
					fontweight_arr = Drupal.settings.font_vars[fontfamilyval].Weight.split(',');
					$.each(fontweight_arr, function(index, value) {
						optval = $.trim(value);
						fontweight_html += '<option value="'+optval+'">'+_expandFontWeight(optval)+'</option>';
					});
					fontweight_html += '</select>';
					$('#fontweight-'+id).html(fontweight_html);
					fwchange = 1;
					_updateTextStyle();
                    _updatePreview(id);

			});

			$('#fontweight-'+id +'').on('change',function(){
					_updateTextStyle();
                    _updatePreview(id);
	        });
			
			$('#'+id +'-fontsize').focusout(function(){
					_updateTextStyle()
                    _updatePreview(id);
	        }).trigger('focusout');

			$('#'+id +'-sizetype,'+ '#'+ id +'-uppercase').on('change',function(){
					_updateTextStyle()
                    _updatePreview(id);
	        });
            $('#'+id +'-fontweight','#'+id +'-fontsize','#'+id +'-sizetype,'+ '#'+ id +'-uppercase').trigger('change');


  		// Functions
			function _updateTextStyle() {
				_fontfamily = $('#'+ id +'-fontfamily').val();
				_fontweight = $('#'+ id +'-fontweight').val();
				_fontsize = $('#'+id+'-fontsize').val();
				_sizetype = $('#'+ id +'-sizetype').val();
				_uppercase = $('#'+ id +'-uppercase').val();

				_fontfamilydetail = Drupal.settings.font_vars[_fontfamily].CSS;

				_style = '';
				if (_fontfamily != 0) {
					_style += 'font-family: ' + _fontfamilydetail + ';';
					if (_fontweight) {
						_style += 'font-weight: ' + _expandFontWeight(_fontweight).toLowerCase() + ';';
					}
				}
				
				if (_fontsize) {
					_style += 'font-size: ' + _fontsize + _sizetype + ';';
				}
				if (_uppercase != "-") {
					_style += 'text-transform: ' + _uppercase + ';';
				}
				
				$(inputhidden).val(_fontfamily + "|" + _fontweight + "|" + _fontsize + "|" + _sizetype + "|" + _uppercase + "|" + _style)
			}

			function _updatePreview(id) {
				_fontfamily = $('#'+ id +'-fontfamily').val();
				_fontweight = $('#'+ id +'-fontweight').val();
				_fontsize = $('#'+id+'-fontsize').val();
				_sizetype = $('#'+ id +'-sizetype').val();
				_texttransform = 'none';
                _texttransform = $('#'+ id +'-uppercase').val();
				_color = '#' + $('#'+id).next().find('input.form-colorpicker').val();
				_fontweightarr = _fontweight.split('');
				if (_fontweightarr[0] == "i") {_fontweightarr[0] = "italic"}
				else {_fontweightarr[0] = "normal"}

				_fontfamilydetail = Drupal.settings.font_vars[_fontfamily].CSS;
				$('#preview-'+id+' .tp-textdemo').css({
					'font-family': _fontfamilydetail,
					'font-weight': _fontweightarr[1] + "00",
					'font-style': _fontweightarr[0],
					'font-size': _fontsize + _sizetype,
					'text-transform': _texttransform,
					'color': _color
				})
			}

			function _expandFontWeight(fw, ept) {
				switch(fw) {
					case 'n1':
						fontExpand = "Thin";
						break;
					case 'i1':
						fontExpand = "Thin Italic";
						break;
					case 'n2':
						fontExpand = "Extra Light";
						break;
					case 'i2':
						fontExpand = "Extra Light Italic";
						break;
					case 'n3':
						fontExpand = "Light";
						break;
					case 'i3':
						fontExpand = "Light Italic";
						break;
					case 'n4':
						fontExpand = "Normal";
						break;
					case 'i4':
						fontExpand = "Italic";
						break;
					case 'n5':
						fontExpand = "Medium";
						break;
					case 'i5':
						fontExpand = "Medium Italic";
						break;
					case 'n6':
						fontExpand = "Semi Bold";
						break;
					case 'i6':
						fontExpand = "Semi Bold Italic";
						break;
					case 'n7':
						fontExpand = "Bold";
						break;
					case 'i7':
						fontExpand = "Bold Italic";
						break;
					case 'n8':
						fontExpand = "Extra Bold";
						break;
					case 'i8':
						fontExpand = "Extra Bold Italic";
						break;
					case 'n9':
						fontExpand = "Heavy";
						break;
					case 'i9':
						fontExpand = "Heavy Italic";
						break;
					default:
						fontExpand = "undefined";
				}

				return fontExpand;
			}

		});
	}
})(jQuery);