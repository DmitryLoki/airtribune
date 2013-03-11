jQuery(document).ready(function () {
    var $ = jQuery,
        month = setBlurBind($('#edit-profile-main-field-birthdate-und-0-value-month')),
        day = setBlurBind($('#edit-profile-main-field-birthdate-und-0-value-day')),
        year = setBlurBind($('#edit-profile-main-field-birthdate-und-0-value-year')),
        form = month.closest('form'),
        formValidator = form.validate();

    function setBlurBind(element) {
        var changeHandlers = element.data('events').change;
        element.bind('change', function (event) {
            if (!month.val() || !day.val() || !year.val()) {
                event.stopImmediatePropagation();
            } else {
                formValidator.element(birthdateInput);
            }
        });
        changeHandlers.unshift(changeHandlers.pop());
        return element;
    }

    Drupal.disableTabKey(form);

    var birthdateInput = jQuery(
        '<input id="birthdate-fake-input" name="profile-main-fake-input" style="z-index:0;position:absolute;left:-10000px;border:none;margin-top:12px; visibility:hidden" disabled="disabled">');
    year.parent().parent().append(birthdateInput);
    birthdateInput.rules('add', {birthDateFilled:true});

    jQuery.validator.addMethod('birthDateFilled', function () {
        return month.val() && day.val() && year.val();
    }, 'Date of birth field is required.');

    var previousCustomErrorPlacement = Drupal.clientsideValidation.prototype.customErrorPlacement;
    Drupal.clientsideValidation.prototype.customErrorPlacement = function (error, element) {
        if (element.attr('id') == "edit-profile-main-field-birthdate-und-0-value") {
            previousCustomErrorPlacement.call(this, error, $('#birthdate-fake-input'));
        } else {
            previousCustomErrorPlacement.call(this, error, element);
        }
    };

    var updateValidationSettings = Drupal.settings.clientsideValidation.updateValidationSettings;
    Drupal.settings.clientsideValidation.updateValidationSettings = function (formValidator) {
        birthdateInput.rules('add', {birthDateFilled:true});
        updateValidationSettings.call(this, formValidator);
    };

    var ajaxValidationResult = $.fn.checkValidationResult;
    $.fn.checkValidationResult = function (errorText) {
        if ($(this).attr('id') == "edit-profile-main-field-birthdate-und-0-value") {
            ajaxValidationResult.call(birthdateInput, errorText);
        } else {
            ajaxValidationResult.call(this, errorText);
        }
    };

    //Throbber position fix for birthday fields
    var ajaxBeforeSend = Drupal.ajax.prototype.beforeSend;
    Drupal.ajax.prototype.beforeSend = function (xmlhttprequest, options) {
        if (options.extraData._triggering_element_name.indexOf('field_birthdate') > -1) {
            this.element = jQuery('.date-year')[0];
        }
        ajaxBeforeSend.apply(this, arguments);
    }
});