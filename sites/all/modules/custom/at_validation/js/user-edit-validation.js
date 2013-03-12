jQuery(function ($) {
    var passwordFieldset = $('#password-fieldset'),
        passwordFieldsetWrapper = passwordFieldset.find('.fieldset-wrapper'),
        passFields = $('#edit-current-pass,#edit-pass-pass1,#edit-pass-pass2'),
        formValidator = passwordFieldset.closest('form').validate();
    passwordFieldset.find('a.fieldset-title').bind('mousedown', function () {
        setTimeout(function() {
            console.log(passFields.is(':hidden'));
            Drupal.checkAllElementsValid(formValidator);
        },500);

    })
});