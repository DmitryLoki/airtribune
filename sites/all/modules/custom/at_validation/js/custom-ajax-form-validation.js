(function ($) {

    var activeField;
    $.fn.checkValidationResult = function (errorText) {
        var that = this.length ? this : $(activeField),
            form = that.parents('form'),
            formValidator = form.validate();

        formValidator.errorsFor(that[0]).remove();
        Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
        if (errorText) {
            formValidator.showLabel(that[0], errorText);
        } else {
            formValidator.settings.success();
        }
        Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
    };

    jQuery(document).ready(function () {
        Drupal.settings.clientsideValidation.updateValidationSettings = function (formValidator) {
            formValidator.settings.success = $.proxy(function (error) {
                var successElements = $(this.successList);
                successElements.each(function (i, element) {
                    var currentElement = $(element),
                        errorElement = currentElement.data('error-element');
                    //Password fields validates separately
                    if(currentElement.attr('type') == 'password'){
                        return;
                    }
                    currentElement.parents('div.form-item').removeClass('field_error');
                    if (errorElement) {
                        errorElement.remove();
                    }
                });

            }, formValidator);
        };

        for (var f in Drupal.settings.clientsideValidation.forms) {
            var form = $('#' + f);
            Drupal.settings.clientsideValidation.updateValidationSettings(form.validate());

        }

        Drupal.clientsideValidation.prototype.customErrorPlacement = function (error, element) {
            if (!error.text()) {
                return;
            }
            var errorBubble =
                    jQuery('<span class="validate-error form_booble error"><span class="form_booble_inner">' + error.text() + '</span></span>')
                        .attr('for', element.attr('id'))
                        .attr('link', element.attr('id')),
                form = element.parents('div.form-item').addClass('field_error');
            form.find('span.form_booble.validate-error').remove();
            element.data('error-element', errorBubble);
            element.after(errorBubble);
        };

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

        var beforeSerialize = Drupal.ajax.prototype.beforeSerialize,
            ajaxSuccess = Drupal.ajax.prototype.success;

        Drupal.ajax.prototype.beforeSerialize = function (element, options) {
            if (options.url === '/at-validation/ajax') {
                var formValidator = element.validate();
                Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
                return formValidator.element(activeField);
            } else {
                beforeSerialize.call(this, element, options);
            }
        };

        Drupal.ajax.prototype.success = function () {
            ajaxSuccess.apply(this, arguments);
            var formValidator = $(activeField).parents('form').validate();
            Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
        }
    });

    $('#autocomplete li').live('click', function(){jQuery(this).parents('#autocomplete').hide()})
})(jQuery);