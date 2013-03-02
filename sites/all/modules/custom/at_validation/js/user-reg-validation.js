jQuery(document).ready(function () {
    var $ = jQuery,
        month = setBlurBind($('#edit-profile-main-field-birthdate-und-0-value-month')),
        day = setBlurBind($('#edit-profile-main-field-birthdate-und-0-value-day')),
        year = setBlurBind($('#edit-profile-main-field-birthdate-und-0-value-year'));

    function setBlurBind(element) {
        var changeHandlers = element.data('events').change;
        element.bind('change', function (event) {
            if (!month.val() || !day.val() || !year.val()) {
                event.stopImmediatePropagation();
            }
        });
        changeHandlers.unshift(changeHandlers.pop());
        return element;
    }

    var birthdateInput = jQuery(
        '<input id="birthdate-fake-input" name="profile-main-fake-input" style="position:absolute;left:-1000px;margin-top:12px">');
    year.parents('.form-item:last').append(birthdateInput);
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
        if($(this).attr('id') == "edit-profile-main-field-birthdate-und-0-value"){
            ajaxValidationResult.call(birthdateInput, errorText);
        } else {
            ajaxValidationResult.call(this, errorText);
        }
    }
});