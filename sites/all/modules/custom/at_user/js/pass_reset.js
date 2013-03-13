(function ($) {
  Drupal.behaviors.pass_reset = {
    attach: function (context, settings) {

    $('#name_and_birthday').hide();
    $('html, body').animate({ scrollTop: $('#edit-pass-pass1').offset().top }, 'slow');
    $(Drupal.toggleFieldset($('#password-fieldset fieldset')));

    }
  };
})(jQuery);