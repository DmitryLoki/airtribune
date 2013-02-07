(function ($) {

if (typeof(Drupal.ulogin) == 'undefined') {
Drupal.ulogin = function() {
  return {
    token: function(token) {
      //console.log(token);
    }
  };
}();
}

Drupalulogintoken = function(token) {
  console.log(token);
};

})(jQuery);