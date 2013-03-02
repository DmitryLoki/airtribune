jQuery(document).ready(function(){
    var ajaxSuccess = Drupal.ajax.prototype.success;
    Drupal.ajax.prototype.success = function (response) {
        if(response && response[0] && response[0].command == "settings" && response[0].merge) {
            response[0].merge = false;
        }
        ajaxSuccess.apply(this, arguments);
        if(response[1] && response[1].command == "insert") {
            updateForm(jQuery('#'+jQuery(response[1].data).attr('id')));
        }

    };
});