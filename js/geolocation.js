(function ($) {
  // @TODO: Make this a proper drupal behavior.
  $(document).ready(function(){
    if (geo_position_js.init()) {
    geo_position_js.getCurrentPosition(success_callback, error_callback);
    }
    else {
    
    }
    
    function success_callback(p) {
      $('#geofield_lat').val(p.coords.latitude);
      $('#geofield_lon').val(p.coords.longitude);
    }
    
    function error_callback(p) {
    
    }
  });
})(jQuery);
