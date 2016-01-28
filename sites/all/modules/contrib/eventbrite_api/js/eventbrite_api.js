(function ($, Drupal, window, document, undefined) {
    $(document).ready(function(){
        $('#edit-add-account').click(function() {
            var firstid = $('#eventbrite_api_accounts table.sticky-enabled tbody tr:last-child :radio').val();
            var numaccts = $('#eventbrite_api_accounts table.sticky-enabled tbody tr').length;
            console.log(numaccts);
            $( "#eventbrite_api_accounts table.sticky-enabled tbody tr:last-child" ).clone().each(function() {
                $(this).children('td').each(function() {
                    $(this).find('input').each(function() {
                        if ($(this).attr('name') == 'forms[auth]') {
                            $(this).attr('name', $(this).attr('name').replace(firstid, '-' + numaccts));
                        }
                        else {
                            $(this).attr('id', $(this).attr('name').replace(firstid, '-' + numaccts));
                        }
                        if ($(this).attr('id').indexOf('delete') > 0) {
                            $(this).hide();
                        }
                        $(this).val('');
                    });
                });
            }).appendTo($('#eventbrite_api_accounts table.sticky-enabled tbody'));
        });
    });
})(jQuery, Drupal, this, this.document);
