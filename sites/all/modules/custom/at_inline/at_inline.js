(function ($) {
  window.onceFn = jQuery.fn.once;
  window.ajaxSubmitFn = jQuery.fn.ajaxSubmit;
  
  Drupal.behaviors.at_inline = {
    attach: function (context) {
      
      $('.set-a-task-link').once(function(){
      $(this).mousedown(function(){
      window.jQuery.fn.once = window.onceFn;
      window.jQuery.fn.ajaxSubmit = window.ajaxSubmitFn ;
      })});
      
      $('.at-inline-close').click(function(){
        $(this).closest('.at-inline-set-a-task-wrapper').html("");
      });
    }
  }
})(jQuery);
