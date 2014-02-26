(function ($) {

  Drupal.behaviors.at_tracker = {
    attach: function (context, settings) {
      $.fn.changeBindTrackerField = function(data, wrapperId) {
        var field = $(wrapperId + ' select[name="' + data + '[und][0][value]"]'),
        fieldAjax = Drupal.ajax[field.attr('id')];
        field.unbind('mousedown');
        field.on('click', function(){
          field.attr('size',1);
          field.on('mousedown', function(event){
            fieldAjax.eventResponse(field, event);
          });
        });
      }
    }
  }

})(jQuery);