jQuery(document).ready(function($) {
  $('#edit-extra-use-existing-email-field').change(function(){
    var sel = $("#edit-extra-use-existing-email-field option:selected");
    if (sel[0]["value"] != 'mailchimp_field') {
      $('#field_settings').show();
    }
    else {
      $('#field_settings').hide();
    }
  });

  if ($("#edit-extra-use-existing-email-field option:selected")[0]['value'] != 'mailchimp_field') {
    $('#field_settings').show();
  }
  else {
    $('#field_settings').hide();
  }
});