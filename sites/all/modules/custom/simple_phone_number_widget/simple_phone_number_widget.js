(function ($) {
  Drupal.behaviors.yourName = {
    attach : function(context, settings) {
      $('input.simple-phone-full-number').once(function(index, input){
          $(input).mask('+9999999999?99999', {placeholder: ""}).val('+');
      });
    }
  };
})(jQuery);
