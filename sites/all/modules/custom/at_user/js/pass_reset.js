(function ($) {
  Drupal.behaviors.pass_reset = {
    attach: function (context, settings) {
        $('#name_and_birthday').hide();
        $('#password-fieldset .fieldset-legend').hide();
        $(Drupal.toggleFieldset($('#password-fieldset fieldset')));
        $('html, body').animate({ scrollTop: $('#password-fieldset').offset().top }, 'slow');
    }
  };
})(jQuery);