(function ($) {
    var activeField,
        allElementsValid = false;

    $.fn.checkValidationResult = function (errorText) {
        var that = this.length ? this : $(activeField),
            form = that.parents('form'),
            formValidator = form.validate();

        formValidator.errorsFor(that[0]).remove();
        Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
        var validationMethod = 'failed-ajax-validation-' + that.attr('name');
        if (errorText) {
            jQuery.validator.addMethod(validationMethod, function () {
                return false
            }, errorText);
            that.rules('add', validationMethod);

            var elementRules = Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[that.attr('name')];
            if (!elementRules) {
                Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[that.attr('name')] = {};
            }
            Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[that.attr('name')][validationMethod] = true;

        } else {
            if (Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[that.attr('name')]) {
                delete Drupal.settings.clientsideValidation.forms[form.attr('id')].rules[that.attr('name')][validationMethod];
            }
            that.rules('remove', validationMethod);
        }
        formValidator.element(that);
        Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
        checkAllElementsValid(formValidator);
    };

    var checkAllElementsValid = Drupal.checkAllElementsValid = function (formValidator) {
        if (allElementsValid) {
            return;
        }
        var allElements = formValidator.elements(),
            submitButton = allElements.closest('form').find('input.form-submit'),
            successList = formValidator.successList.slice(0);
        allElementsValid = true;
        for (var i = 0, l = allElements.length; i < l; ++i) {
            var element = allElements.get(i);
            if (!formValidator.check(element) && ($(element).rules().required || $(element).attr('type') === 'password')) {
                allElementsValid = false;
                break;
            }
        }
        formValidator.successList = successList;
        submitButton[allElementsValid ? 'removeClass' : 'addClass']('disabled');
    };

    Drupal.disableTabKey = function (form) {
        form.validate().elements().each(function (i, element) {
            var keyUpBindings = $(element).bind('keyup',function (event) {
                if (event.keyCode === 9) {//TAB key
                    event.stopImmediatePropagation();
                }
            }).data('events').keyup;
            keyUpBindings.unshift(keyUpBindings.pop());
        });
    };

    jQuery(document).ready(function () {

        Drupal.settings.clientsideValidation.updateValidationSettings = function (formValidator) {

            formValidator.settings.success = $.proxy(function (error) {
                var successElements = $(this.successList);
                successElements.each(function (i, element) {
                    var currentElement = $(element),
                        errorElement = currentElement.data('error-element');
                    currentElement.closest('div.form-item').removeClass('field_error');

                    if (currentElement.attr('id') == 'edit-pass-pass2') {
                        var successBubble = createBubble(Drupal.settings.password.confirmSuccess);
                        currentElement.closest('div.form-item').addClass('field_excellent').find('.form-text').
                            after(successBubble);
                        currentElement.data('error-element', successBubble);
                    }

                    if (errorElement) {
                        errorElement.remove();
                    }
                });

                checkAllElementsValid(formValidator);
            }, formValidator);

            if ($('#edit-pass-pass1').length > 0) {
                var passField = $('#edit-pass-pass1'),
                    passMatchField = $('#edit-pass-pass2'),
                    passCheckFunction = Drupal.behaviors.password.passCheck;

                jQuery.validator.addMethod('passFieldValid', function () {
                    if (passField.val()) {
                        $.validator.messages.passFieldValid = "";
                        return !passCheckFunction();
                    }
                    else {
                        $.validator.messages.passFieldValid = "Password is required.";
                        return false;
                    }

                }, '');
                jQuery.validator.addMethod('passMatchValid', function () {
                    return passField.val() == passMatchField.val();
                }, Drupal.settings.password.confirmFailure);

                passField.rules('add', {passFieldValid:true, required:true});
                passField.rules('remove', 'required');
                passMatchField.rules('add', {passMatchValid:true, required:true});
            }
        };

        for (var f in Drupal.settings.clientsideValidation.forms) {
            var form = $('#' + f),
                validator = form.validate();
            Drupal.settings.clientsideValidation.updateValidationSettings(validator);
            checkAllElementsValid(validator);
            form.find('select').bind('change', function () {
                var $this = $(this);
                if ($this.rules()) {
                    validator.element(this);
                }
            })
        }

        Drupal.clientsideValidation.prototype.customErrorPlacement = function (error, element) {
            if (!error.text()) {
                return;
            }
            allElementsValid = false;
            var errorBubble = createBubble(error.html())
                .attr('for', element.attr('id'))
                .attr('link', element.attr('id'));
            var previousErrorElement = element.data('error-element');
            if (previousErrorElement) {
                previousErrorElement.remove();
            }
            element.data('error-element', errorBubble);
            if (element.attr('id') == 'birthdate-fake-input') {
                var form = element.parents('div.form-item')
                element.parent().after(errorBubble);
            }
            else {
                var form = element.closest('div.form-item')
                element.after(errorBubble);
            }
            form.addClass('field_error').removeClass('field_excellent');
            element.closest('form').find('input.form-submit').addClass('disabled');
        };

        var createBubble = Drupal.createErrorBubble = function (html) {
            return jQuery('<span class="form_booble"><span class="form_booble_inner">' + html + '</span></span>');
        };

        for (var field in Drupal.settings.ajax) {
            var f = jQuery(Drupal.settings.ajax[field].selector),
                event = Drupal.settings.ajax[field].event;
            //insert event handler before other handlers
            f.bind(event, function () {
                activeField = this;
                $(this).rules('remove', 'failed-ajax-validation-' + this.name);
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
                var validationResult = formValidator.element(activeField);
                element.find('input.form-submit').addClass('disabled');
                return validationResult;
            } else {
                beforeSerialize.call(this, element, options);
            }
        };

        Drupal.ajax.prototype.success = function () {
            ajaxSuccess.apply(this, arguments);
            var formValidator = $(activeField).parents('form').validate();
            if (formValidator) {
                Drupal.settings.clientsideValidation.updateValidationSettings(formValidator);
            }
        };

        setTimeout(function () {
            var passField = $('.password-field');
            if (passField.length && passField.val() != '') {
                passField.parents('form').validate().element(passField[0]);
            }
        }, 500);

        $('#autocomplete li')
            .live('click', function () {
                jQuery(this).parents('#autocomplete').remove()
            });

        $('.form-autocomplete')
            .bind('focusout', function () {
                $('#autocomplete').remove();
            })
            .bind('keydown', function (event) {

                var selectedLi = $('#autocomplete li.selected');
                if (event.keyCode == 13 /* enter key*/ && selectedLi.length) {
                    this.value = selectedLi.text();
                    event.stopPropagation();
                    event.preventDefault();
                }
            });
    });

    $.validator.prototype.focusInvalid = function () {
        if (this.settings.focusInvalid) {
            try {
                var topElement = $(this.errorList.length && this.errorList[0].element || [])
                    .filter(":visible")
                    .focus()
                    // manually trigger focusin event; without it, focusin handler isn't called, findLastActive won't have anything to find
                    .trigger("focusin");
                $(document.body).scrollTo(topElement);
            } catch (e) {
                // ignore IE throwing errors when focusing hidden elements
            }
        }
    }

    //Throbber position fix for birthday fields
    var ajaxBeforeSend = Drupal.ajax.prototype.beforeSend;
    Drupal.ajax.prototype.beforeSend = function (xmlhttprequest, options) {
        if (options.extraData._triggering_element_name.indexOf('field_birthdate') > -1) {
            this.element = jQuery('.date-year')[0];
        }
        ajaxBeforeSend.apply(this, arguments);
    }


})(jQuery);
