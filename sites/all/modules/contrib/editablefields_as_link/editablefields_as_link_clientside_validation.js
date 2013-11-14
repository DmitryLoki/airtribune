(function ($) {
  $.fn.assign_clienside_validation = function (wrapper) {
    for (var ajax in Drupal.ajax) {
      Drupal.ajax[ajax] = false;
    }
    jQuery('#editablefields-as-link-form').validate({});
    var processed_element = jQuery('#' + wrapper).find('input,select').first();
    Drupal.ajax[jQuery('#' + wrapper).find('input[type="submit"]').attr('id')].validate_first = true;

    jQuery(wrapper).ajaxSend(function () {
      processed_element.blur()
    });
//      console.warn(wrapper);
//      console.warn(processed_element);
//      console.warn(Drupal.settings.clientsideValidation.forms['editablefields-as-link-form'].rules);
    Drupal.attachBehaviors();
  };
})(jQuery);