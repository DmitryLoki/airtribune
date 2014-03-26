(function ($) {
  Drupal.behaviors.pass_reset = {
    attach: function (context, settings) {
        $(Drupal.toggleFieldset($('#password-fieldset fieldset')));
        $('html, body').animate({ scrollTop: $('#password-fieldset').offset().top }, 'slow');
    }
  };
})(jQuery);