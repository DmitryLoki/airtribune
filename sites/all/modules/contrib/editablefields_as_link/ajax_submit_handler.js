(function ($) {
  function appendThrobberBehavior(container) {
    var ajaxSubmit = Drupal.ajax[container.find('input[type="submit"]').attr('id')],
      tempValue = $('<span class="temp-value"></span>');

    if (container.hasClass('at-editablefield-number_integer at-editablefield-phone_number')) {
      ajaxSubmit.options.beforeSubmit = function () {
        container.addClass('ajaxing');
        container.prepend(tempValue.html(container.find('input[type="text"]').val()));
      };
    } else if (container.has('at-editablefield-list_integer')) {
      ajaxSubmit.options.beforeSubmit = function () {
        container.addClass('ajaxing');
      };
    }
    container.find('input[type="text"]').unbind('change');
  }

  $(function ($) {
    $(document).find('.at-editablefield-list_integer').each(function (i, e) {
      appendThrobberBehavior($(e));
    });

    var oldClientsideValidationAssign = $.fn.assign_clienside_validation;
    $.fn.assign_clienside_validation = function (wrapper) {
      var container = $('#' + wrapper);
      appendThrobberBehavior(container);
      oldClientsideValidationAssign.call(this, wrapper);
    }
  })
})(jQuery);