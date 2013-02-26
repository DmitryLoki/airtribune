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

    var passCheckFunction = Drupal.behaviors.password.passCheck,
        passCheckFunctionMatch = Drupal.behaviors.password.passCheckMatch;

    $('#edit-pass-pass1').rules('add', {depends: function(){if(!passCheckFunction()){
        $('#edit-pass-pass1')
    }}});
    $('#edit-pass-pass2').rules('add', {depends: function(){passCheckFunctionMatch();}});

    $('#autocomplete li').live('click', function(){jQuery(this).parents('#autocomplete').hide()})
});