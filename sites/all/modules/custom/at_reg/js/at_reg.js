(function($){
  Drupal.behaviors.CDE = {
    attach: function(){
      var ajaxSuccess = Drupal.ajax.prototype.success;
      Drupal.ajax.prototype.success = function (response) {
        ajaxSuccess.apply(this, arguments);
        //Update style on <select>
        if(this.selector.indexOf('#edit-profile-pilot-field-address-und-0-country')>-1) {
          updateForm(this.form);
        }
      }
    }
  }
})(jQuery);