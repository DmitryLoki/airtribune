(function ($) {
  Drupal.behaviors.mail_change = {
    attach: function (context, settings) {
      $('#mail-edit-pencil').click(function() {
        //$('#mail-dummy').hide();
        $('#name_and_birthday').hide();
        $('#password-fieldset').hide();
        $('#mail-change').show();
        $('html, body').animate({ scrollTop: $('#edit-account').offset().top }, 'slow');
      });
    }
  };
})(jQuery);