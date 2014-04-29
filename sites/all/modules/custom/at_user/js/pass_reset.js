(function ($) {
  Drupal.behaviors.pass_reset = {
    attach: function (context, settings) {
        $('#name-gender-dob, #personalisation').hide();
        $('#tasks').hide();
        $('#edit-field-account-tiny-path').hide();
        $(Drupal.toggleFieldset($('#password-fieldset fieldset')));
    }
  };
})(jQuery);