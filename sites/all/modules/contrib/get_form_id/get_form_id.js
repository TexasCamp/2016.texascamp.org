(function ($) {
    Drupal.behaviors.get_form_id = {
        attach: function() {
            // Select all content in input field.
            $('#get-form-id-form input[type=text]').focus(function(){
                $(this).select();
            });
            // Prevent webkit browsers from interference.
            $('#get-form-id-form input[type=text]').mouseup(function(e){
                e.preventDefault();
            });
        }
    };
}(jQuery));