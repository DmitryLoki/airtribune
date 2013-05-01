jQuery(function ($) {

  var airvisWidget,
    accordion;

  //Need to get accordion instance
  $.each(Drupal.settings.views_accordion, function (id) {
    var viewname = this.viewname;
    var display = this.display;

    var displaySelector = '.view-id-' + viewname + '.view-display-id-' + display + ' .view-content',
      accordionElement = $(displaySelector);

    accordion = accordionElement.data('accordion');

    accordionElement.bind('accordionchange', function () {
      toggleHeader($(accordion.active));
    });
  });

  //This callback calls when airvis widget initiated
  window.airvisPageLoadedCallback = function (airvis) {
    airvisWidget = airvis;

    airvisWidget.on('domInit', function () {
      toggleHeader($(accordion.active));
    });

    //if loading successful - hide picture to display airvis widget
    airvisWidget.on('loaded', function () {
      headerPictureContainer.hide();
    });

    //if loading failed - show picture in header
    airvisWidget.on('loadingError', function () {
      headerPictureContainer.show();
    });
  };

  var headerPictureContainer = $('.pane-header-slideshow-event-header');

  //Rebuild airvis widget with new params. Events 'loaded' or 'loadingError' of airvisWidget will be fired after rebuild
  function rebuildRacePreview(contestId, raceId) {
    airvisWidget.setOption('contestId', contestId);
    airvisWidget.setOption('raceId', raceId);
    airvisWidget.rebuild();
  }

  //Toggle between header picture and airvis widget
  function toggleHeader(activeDayBlock) {
    //try to display widget, if any day opened
    if (activeDayBlock.length !== 0) {

      var raceInfo = activeDayBlock.parent().find('.data-race').data(),
        contestId = raceInfo['contest-id'],
        raceId = raceInfo['race-id'];

      if(contestId !== '' && raceId !== '') {
        rebuildRacePreview(contestId, raceId);
      } else {
        headerPictureContainer.show();
      }
    } else {
      headerPictureContainer.show();
    }

  }
});