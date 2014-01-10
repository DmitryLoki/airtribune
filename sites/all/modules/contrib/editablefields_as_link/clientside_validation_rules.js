(function($) {
  $.fn.assign_clienside_validation = function(wrapper) {
    jQuery('#editablefields-as-link-form').validate({});
    var processed_element = $('#'+wrapper).find('input,select').first();
    $(wrapper).ajaxSend(function(){processed_element.blur()});
  };
})(jQuery);