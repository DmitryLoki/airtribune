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

});