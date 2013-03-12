jQuery(function ($) {
    var passwordFieldset = $('#password-fieldset'),
        passwordFieldsetWrapper = passwordFieldset.find('.fieldset-wrapper'),
        passFields = $('#edit-current-pass,#edit-pass-pass1,#edit-pass-pass2'),
        formValidator = passwordFieldset.closest('form').validate();
    passwordFieldset.find('a.fieldset-title').bind('mousedown', function () {
        setTimeout(function () {
            if (passwordFieldsetWrapper.is(':visible')) {
                passFields.bind('keyup', function () {
                    Drupal.checkAllElementsValid(formValidator);
                    passFields.unbind('keyup', arguments.callee);
                })
            } else {
                passFields.val('');
                passFields.removeClass('error').siblings('.form_booble').css('display','none');
                passFields.parent().removeClass('field_error field_good field_excellent');
                Drupal.checkAllElementsValid(formValidator);
            }
        }, 500);

    })
});