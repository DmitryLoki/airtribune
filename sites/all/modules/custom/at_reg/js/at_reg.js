(function($){
  Drupal.behaviors.CDE = {
    ajaxSuccess: Drupal.ajax.prototype.success,
    attach: function(){
      Drupal.ajax.prototype.success = function (response) {
        Drupal.behaviors.CDE.ajaxSuccess.apply(this, arguments);
        //Update style on <select>
        if(this.selector.indexOf('#edit-profile-pilot-field-address-und-0-country')>-1) {
          updateForm(this.form);
        }
      }
    }
  }
})(jQuery);