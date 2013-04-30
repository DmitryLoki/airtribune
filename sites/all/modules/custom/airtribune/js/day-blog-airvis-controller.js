jQuery(function ($) {

  $.each(Drupal.settings.views_accordion, function (id) {
    var viewname = this.viewname;
    var display = this.display;

    /* the selectors we have to play with */
    var displaySelector = '.view-id-' + viewname + '.view-display-id-' + display + ' .view-content',
      accordionElement = $(displaySelector),
      accordion = accordionElement.data('accordion');

    accordionElement.bind('accordionchange', function () {
      toggleHeader($(accordion.active));
    });

    setTimeout(function () {
      toggleHeader($(accordion.active));
    }, 5000);

  });

  var headerPictureContainer = $('.pane-header-slideshow-event-header');

  function toggleHeader(activeDayBlock) {

    if (activeDayBlock.length !== 0) {

      var raceInfo = activeDayBlock.parent().find('.data-race').data(),
        contestId = raceInfo['contest-id'],
        raceId = raceInfo['race-id'];

      if (contestId !== "" && raceId !== "") {
        airvisPage.setOption('contestId', contestId);
        airvisPage.setOption('raceId', raceId);
        airvisPage.rebuild();
        headerPictureContainer.hide();
        return;
      }
    }
    headerPictureContainer.show();
  }


});