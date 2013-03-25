jQuery(document).ready(function(){
    var $ = jQuery,
        ajaxSuccess = Drupal.ajax.prototype.success;
    Drupal.ajax.prototype.success = function (response) {
        if(response && response[0] && response[0].command == "settings" && response[0].merge) {
            response[0].merge = false;
        }
        ajaxSuccess.apply(this, arguments);
        if(response && response[1] && response[1].command == "insert") {
            var element = jQuery('#'+jQuery(response[1].data).attr('id'));
            Drupal.settings.clientsideValidation.updateValidationSettings(element.parents('form').validate());
            if(window.updateForm) {
                updateForm(element);
            }
        }

    };
});