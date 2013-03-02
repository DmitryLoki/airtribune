(function ($) {
  Drupal.behaviors.autoUpload = {
    attach: function (context, settings) {

      var widget = $('.image-widget').first();
      if (widget.find('.image-preview').size() == 0) {
        widget.addClass('photo-empty');
        widget.append("<div class='photo-empty-div'></div>").addClass();
      }

      $('form', context).delegate('input.form-file', 'change', function() {  
        $(this).next('input[type="submit"]').mousedown();
      }); 

      $('form', context).delegate('.image-preview', 'click', function() {  
        if (confirm(Drupal.t('Are you sure you want to delete the your photo?'))) {
          $(this).parent().find('.image-widget-data input[type="submit"]').mousedown();
        }
      });

    }
  };
})(jQuery);