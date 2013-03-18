(function ($) {
  Drupal.behaviors.autoUpload = {
    attach: function (context, settings) {

      var widget = $('.image-widget').first();
      widget.once(function(){
          widget.prev('.inline-label').css({'visibility':'hidden'});
          if (!widget.find('.image-preview').size() && !widget.find('.photo-empty-div').size()) {
              widget.addClass('photo-empty');
              widget.append("<div class='photo-empty-div'></div>").addClass();
          }
          else if(!widget.find('.delete-photo').size()){
              widget.find('.image-preview').append('<div class="delete-photo"><div class="delete-photo-plus"></div></div>');
              widget.find('.image-widget-data span').hide();
          }
      });


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

(function($){
    //Override default drupal file validation to show custom error message
  var oldDrupalValidateExtension = Drupal.file.validateExtension,
      oldAttach = Drupal.behaviors.fileValidateAutoAttach.attach,
      validateFunction = function(event) {
        var fileInput = $(this);

        fileInput.closest('.image-widget-data').siblings('.form_booble').remove();
        fileInput.closest('.form-managed-file').removeClass('field_error');
        var result = oldDrupalValidateExtension.call(this, event);

        //exactly 'false', not undefined
        if(result === false) {
          var errorMessage = $('.file-upload-js-error'),
              errorBubble = Drupal.createErrorBubble(errorMessage.html());
          errorMessage.after(errorBubble);
          errorMessage.remove();
          fileInput.closest('.form-managed-file').addClass('field_error');
          event.stopImmediatePropagation();
        }

        return result;
      };

    Drupal.file.validateExtension = validateFunction;
    Drupal.behaviors.fileValidateAutoAttach.attach = function(context, settings) {
      Drupal.file.validateExtension = validateFunction;
      oldAttach.call(this, context, settings);
    };
})(jQuery);