jQuery(function ($) {
  var recentlyViewedBlock = $('#recently-viewed');
  if(!recentlyViewedBlock.length) {
    return;
  }

  //get previous recently viewed
  var currentLanguagePrefix = '/'+$('html').attr('lang');
  currentLanguagePrefix = currentLanguagePrefix == '/en' ? '' : currentLanguagePrefix;

  var lsKey = 'recentlyViewed',
    recentlyViewed = localStorage[lsKey] ? JSON.parse(localStorage[lsKey]) : [];

  if(!recentlyViewed.length) {
    return;
  }

  var content = '<ul>';
  for (var i = 0; i < recentlyViewed.length; i++) {
    var eventPageInfo = recentlyViewed[i];
    content += '<li><a href="'+currentLanguagePrefix+eventPageInfo.href+'">'+eventPageInfo.title+'</a></li>';
  }
  content += '</ul>';

  recentlyViewedBlock.append(content);
  recentlyViewedBlock.parents('.pane-recently-viewed').show();
});