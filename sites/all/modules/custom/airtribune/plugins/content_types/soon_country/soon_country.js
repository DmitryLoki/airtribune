jQuery(function ($) {
  $('.countries_title_suffix_inner').each(function () {
    $(this).parent().show();
    $(this).jScrollPane({scrollbarWidth:4, showArrows:false});
    $(this).parent().hide(); 

  });
  $('.change_location_title').click(function(){
    $('.countries_title_suffix').show().height($('.countries_title_suffix_inner').outerHeight());
  })
});