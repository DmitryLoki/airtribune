(function ($) {

Drupal.behaviors.ulogin_async = {};
Drupal.behaviors.ulogin_async.attach = function(context, settings) {
  
  function uloginInitWidgets() {
    $.each(Drupal.settings.ulogin, function(index, value) {
      $('#' + value + ':not(.ulogin-processed)', context).addClass('ulogin-processed').each(function() {
        uLogin.initWidget(value);
      });
    });
  }
  
  if (typeof uLogin != 'undefined') {
    uloginInitWidgets();
  }
  else {
    /*$.getScript('//ulogin.ru/js/ulogin.js', function(data, textStatus, jqXHR) {
      uloginInitWidgets();
    });*/
    $.ajax({
      url: '//ulogin.ru/js/ulogin.js',
      dataType: 'script',
      cache: true, //otherwise will get fresh copy every page load, this is why not $.getScript().
      success: function(data, textStatus, jqXHR) {
        uloginInitWidgets();
      }
    });
  }
};

})(jQuery);
