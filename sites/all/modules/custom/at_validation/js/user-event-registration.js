jQuery(document).ready(function(){
    var ajaxSuccess = Drupal.ajax.prototype.success;
    Drupal.ajax.prototype.success = function (response) {
        if(response && response[0] && response[0].command == "settings" && response[0].merge) {
            response[0].merge = false;
            response[1] = {};
        }
        ajaxSuccess.apply(this, arguments);

    };
});