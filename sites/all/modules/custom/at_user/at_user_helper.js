(function($){

Drupal.behaviors.at_user = {
    attach: function (context, settings) {
        // $("#edit-mail").bind('keyup', $.proxy(this.checkIsEmailExists, this));
        $("#edit-mail").live('keyup', function() {
            checkIsEmailExists($(this).val()); // need to call this!!!
        });
    },
    /**
     * Checks that email is exists in site users via ajax
     * @param callback
     */
    checkIsEmailExists: function(callback){
        var that = this;
        
        // Caching to prevent re-requesting
        if(this.IsMailExists !== undefined) {
            callback(this.IsMailExists);
            return;
        }
        callback = callback || function(){};
        $.ajax({
            url: "user/is_email_exists/" + data.mail,
            dataType: 'json',
            success:function successCallback(data){
                if (data.exists == 'TRUE') {
                    that.IsMailExists = true;
                }
            },
            error:function errorCallback(error){
                that.IsMailExists = false;
            },
            complete: function(){
                callback(that.IsMailExists);
            }
        });
    }
};

})(jQuery);