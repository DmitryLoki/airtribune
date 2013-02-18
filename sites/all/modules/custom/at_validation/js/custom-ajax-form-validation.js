(function ($) {
    $.fn.checkValidationResult = function (errorText) {
        var form = this.parents('form'),
            formValidator = form.validate();
        form.validate().settings.errorElement = 'span';
        formValidator.errorsFor(this[0]).remove();

        if (errorText) {
            formValidator.showLabel(this[0], errorText);
        }
    }
})(jQuery);

jQuery(document).ready(function () {
    Drupal.clientsideValidation.prototype.customErrorPlacement = function (error, element) {
        var errorBubble =
                jQuery('<span class="validate-error form_booble error"><span class="form_booble_inner">' + error.text() + '</span></span>')
                    .attr('for', element.attr('id'))
                    .attr('link', element.attr('id')),
            form = element.parents('div.form-item');

        form.find('span.form_booble.validate-error').remove();
        element.after(errorBubble);
    };

    var activeField;
    for (var field in Drupal.settings.ajax) {
        var f = jQuery(Drupal.settings.ajax[field].selector),
            event = Drupal.settings.ajax[field].event;
        //insert event handler before other handlers
        f.bind(event, function () {
            activeField = this;
        });
        var currentBindings = f.data('events')[event];
        currentBindings.unshift(currentBindings.pop());
    }

    var beforeSerialize = Drupal.ajax.prototype.beforeSerialize;

    Drupal.ajax.prototype.beforeSerialize = function (element, options) {
        if (options.url = '/at-validation/ajax') {
            var formValidator = element.validate();
            return formValidator.element(activeField);
        } else {
            beforeSerialize.call(this, element, options);
        }
    }

});