jQuery(function ($) {

  $('.countries_title_suffix_inner').each(function () {

    var countriesInner = $(this);
    countriesInner.parent().show();
    countriesInner.jScrollPane({scrollbarWidth:4, showArrows:false});
    //fix jsp wrong height calculation
    countriesInner.css('padding-top','10px');
    var countriesTitleHeight = $(this).outerHeight(),
      countriesTitleSuffix = $('.countries_title_suffix');

    $('.change_location_title').click(function(e) {
      e.stopImmediatePropagation();
      //toggle height
      if(countriesTitleSuffix.height() > 0) {
        countriesTitleSuffix.height(0);
        $(document.body).unbind('click',bodyClickHandler);
      } else {
        countriesTitleSuffix.height(countriesTitleHeight);
        $(document.body).bind('click',bodyClickHandler);
      }
    });

    function bodyClickHandler(e) {
      if(countriesInner.find(e.target).length == 0) {
        countriesTitleSuffix.height(0);
      }
    }
  });
});