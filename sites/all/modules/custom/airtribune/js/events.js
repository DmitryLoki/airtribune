jQuery(function ($) {

  var shortlink = $('link[rel="shortlink"]');
  //check we are on event page
  if (!shortlink.length) {
    return;
  }

  var href = shortlink.attr('href'),
    eventHref = href.match(/event\/(\d+)\//);

  if (!eventHref || eventHref.length < 2) {
    return;
  }

  var eventTitleLink = $('#event-title a'),
    eventID = eventHref[1];
  if (!eventTitleLink.length) {
    return;
  }

  var eventTitle = eventTitleLink.text(),
    eventHref = eventTitleLink.attr('href');

  //get previous recently viewed
  var lsKey = 'recentlyViewed',
    recentlyViewed = localStorage[lsKey] ? JSON.parse(localStorage[lsKey]) : [];

  //remove from recently viewed link on current event
  for (var i = 0, l = recentlyViewed.length; i < l; ++i) {
    if (recentlyViewed[i].eventID == eventID) {
      recentlyViewed.splice(i, 1);
      break;
    }
  }

  recentlyViewed.unshift({title: eventTitle, href: eventHref, eventID: eventID});

  localStorage[lsKey] = JSON.stringify(recentlyViewed);
});