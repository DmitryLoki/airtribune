(function ($) {
  Drupal.behaviors.mail_change = {
    attach: function (context, settings) {
      $('#mail-edit-pencil').click(function() {
        $('#name-gender-dob, #personalisation, #password-fieldset').hide();
        $('#mail-change,#mail-edit-cancel-link').show();
      });
      $('#mail-edit-cancel-link').click(function() {
        $('#name-gender-dob, #personalisation, #password-fieldset').show();
        $('#mail-change,#mail-edit-cancel-link').hide();
      });
    }
  };
})(jQuery);