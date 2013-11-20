(function ($) {
  $.fn.assign_clienside_validation = function (wrapper) {
    for (var ajax in Drupal.ajax) {
      Drupal.ajax[ajax] = false;
    }
    jQuery('#editablefields-as-link-form').validate({});
    var container = $('#' + wrapper);
    var processed_element = container.find('input,select').first();
    Drupal.ajax[container.find('input[type="submit"]').attr('id')].validate_first = true;

    container.find('a.use-ajax').bind('mousedown', function(){
      var focused = container.find('input');
      focused.unbind('change.*');
    })
    jQuery(wrapper).ajaxSend(function () {
      processed_element.blur()
    });
//      console.warn(wrapper);
//      console.warn(processed_element);
//      console.warn(Drupal.settings.clientsideValidation.forms['editablefields-as-link-form'].rules);
    Drupal.attachBehaviors();
  };
})(jQuery);