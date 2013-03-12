(function ($) {
  Drupal.behaviors.autoUpload = {
    attach: function (context, settings) {

      
      var widget = $('.image-widget').first();
      widget.prev('label').hide();
      if (!widget.find('.image-preview').size() && !widget.find('.photo-empty-div').size()) {
        widget.addClass('photo-empty');
        widget.append("<div class='photo-empty-div'></div>").addClass();
      }
      else if(!widget.find('.delete-photo').size()){
        widget.find('.image-preview').append('<div class="delete-photo"><div class="delete-photo-plus"></div></div>');
        widget.find('.image-widget-data span').hide();
      }

      $('form', context).delegate('input.form-file', 'change', function() {  
        $(this).parents('.image-widget-data').find('input[type="submit"]').mousedown();
      }); 

      $('form', context).delegate('.image-preview', 'click', function() {  
        if (confirm(Drupal.t('Are you sure you want to delete photo?'))) {
          $(this).parent().find('.image-widget-data input[type="submit"]').mousedown();
        }
      });

      $('#user-profile-form').ajaxComplete(function(event, xhr, settings) {
        if ((event.target.id) == 'user-profile-form') {
          var messages = $('#user-profile-form .messages');
          messages.show().delay(7000).fadeOut(1000);
          $('input.form-file').forms({file_bt: ''});
        }
      });

    }
  };
})(jQuery);