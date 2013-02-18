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

    var passField = $('[id^="edit-pass"]'),
        form = passField.parents('form');

    passField.bind({
        'keyup':passValidate,
        'blur':passValidate
    });
    function passValidate() {
        var validator = form.validate(),
            passStrengthBubble =  $(this).siblings('.password-strength.form_booble');
        if (this.value.length == 0) {
            passStrengthBubble.hide();
        } else {
            passStrengthBubble.css('display','inline-block')
        }
        if (validator.element(this)) {
            $(this).parents('.form-item').find('span.form_booble.validate-error[link="' + $(this).attr('id') + '"]').remove();
        }
    }

    form.validate().settings.errorElement = 'span';
});