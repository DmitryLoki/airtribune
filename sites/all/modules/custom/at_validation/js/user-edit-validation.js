jQuery(function ($) {
    var passwordFieldset = $('#password-fieldset'),
        passwordFieldsetWrapper = passwordFieldset.find('.fieldset-wrapper'),
        passFields = $('#edit-current-pass,#edit-pass-pass1,#edit-pass-pass2'),
        passField = passFields.filter('#edit-pass-pass2'),
        passConfirm = passFields.filter('#edit-pass-pass2'),
        form =  passwordFieldset.closest('form'),
        formValidator =form.validate();
    passwordFieldset.find('a.fieldset-title').bind('mousedown', function () {
        setTimeout(function () {
            if (passwordFieldsetWrapper.is(':visible')) {
                passConfirm[0].visited = false;
                passFields.bind('keyup', function () {
                    if(passConfirm.val() == "" || passField.val() == "") {
                        form.find('input.form-submit').addClass('disabled');
                    }
                    passFields.unbind('keyup', arguments.callee);
                })
            } else {
                passFields.val('');
                passFields.removeClass('error').siblings('.form_booble').css('display','none');
                passFields.parent().removeClass('field_error field_weak field_good field_excellent');
                Drupal.checkAllElementsValid(formValidator);
            }
        }, 500);

    })
});