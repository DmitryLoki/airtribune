(function($){
    $.fn.checkValidationResult = function(errorText) {
        var errorElement = this.data('error-element');

        if(!errorElement)  {
            errorElement = $('<span></span>');
            this.data('error-element', errorElement);
            this.before(errorElement);
        }
        if(errorText){
            errorElement.html(errorText).show();
        } else {
            errorElement.hide();
        }

    }
})(jQuery.noConflict());