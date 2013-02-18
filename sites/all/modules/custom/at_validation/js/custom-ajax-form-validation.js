(function ($) {
    $.fn.checkValidationResult = function (errorText) {
        var form = this.parents('form'),
            formValidator = form.validate();

        formValidator.errorsFor(this[0]).remove();

        if(errorText){
            formValidator.showLabel(this[0], errorText);
        }
    }
})(jQuery);

Drupal.behaviors.customFormValidation = {
    attach:function () {
        Drupal.clientsideValidation.prototype.customErrorPlacement = function (error, element) {
            element.after(error);
        };
    }
};