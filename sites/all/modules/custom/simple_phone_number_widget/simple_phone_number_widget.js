(function ($) {
  Drupal.behaviors.yourName = {
    attach : function(context, settings) {
      function plusize(el){
        if($(el).val().length == 0) {
          $(el).val("+");
        }
        else if($(el).val()[0]!="+") {
          $(el).val("+" + $(el).val());
        }
      }

      $('input.simple-phone-full-number').each(function(){
          $(this).keyup(function(){
              plusize(this);
          });
          $(this).focusin(function(){
              plusize(this);
          });
      });
    }
  };
})(jQuery);

