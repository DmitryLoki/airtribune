jQuery(function ($) {

  var airvisWidget,
    accordion;

  var
    headerPictureContainer = $('.pane-header-slideshow-event-header'),
    raceDataTextBlock = $('.field-name-field-dates .field-item'),
    raceInfo = $('<div class="field field-name-field-race-info"></div>'),
    faiCategory = $('.field-name-field-fai-category');

  faiCategory.after(raceInfo.hide());
  raceDataTextBlock.data('contest-date-text', raceDataTextBlock.text());

  if (Drupal.settings.views_accordion) {
    //Need to get accordion instance
    $.each(Drupal.settings.views_accordion, function (id) {
      var viewname = this.viewname;
      var display = this.display;

      var displaySelector = '.view-id-' + viewname + '.view-display-id-' + display + ' .view-content',
        accordionElement = $(displaySelector);

      accordion = accordionElement.data('accordion');
    });
  }

  Drupal.behaviors.updateHeaderOnAjax = {
    attach: function (context) {
      if (accordion && accordion.active && $(accordion.active).parent().find(context).length > 0) {
        toggleHeader($(accordion.active));
      }
    }
  };

  //This callback calls when airvis widget initiated
  window.airvisPageLoadedCallback = function (airvis) {
    airvisWidget = airvis;
    var activeRaceBlock;

    if (accordion && accordion.active) {
      activeRaceBlock = $(accordion.active);
    } else if (!accordion) {
      activeRaceBlock = $('.event-day:eq(0)');
    }

    airvisWidget.on('domInit', function () {
      toggleHeader(activeRaceBlock);
    });

    //if loading successful - hide picture to display airvis widget
    airvisWidget.on('loaded', function (raceData) {
      headerPictureContainer.hide();
      faiCategory.hide();
      raceInfo.text(raceData.titles.taskTitle).css('display', 'inline').show();
      toggleRaceDateText(activeRaceBlock);
    });

    //if loading failed - show picture in header
    airvisWidget.on('loadingError', function () {
      headerPictureContainer.show();
      sedHeaderDefaultState();
    });
  };

  function sedHeaderDefaultState() {
    showContestHeaderPicture();
    toggleRaceDateText([]);
  }

  function showContestHeaderPicture() {
    headerPictureContainer.show();
    faiCategory.show();
    raceInfo.hide();
  }

  //toggle between race and contest dates
  function toggleRaceDateText(activeDayAccordionBlock) {
    var dateText;
    if (activeDayAccordionBlock.length !== 0) {
      //show task date
      dateText = activeDayAccordionBlock.find('.posted').text();
    } else {
      //show contest date
      dateText = raceDataTextBlock.text(raceDataTextBlock.data('contest-date-text'));
    }
    raceDataTextBlock.text(dateText);
  }

  //Rebuild airvis widget with new params. Events 'loaded' or 'loadingError' of airvisWidget will be fired after rebuild
  function rebuildRacePreview(contestId, raceId) {
    if (!airvisWidget) return;
    airvisWidget.setOption('contestId', contestId);
    airvisWidget.setOption('raceId', raceId);
    airvisWidget.rebuild();
  }


  //Toggle between header picture and airvis widget
  function toggleHeader(activeDayAccordionBlock) {
    //try to display widget, if any day opened
    if (activeDayAccordionBlock.length !== 0) {
      var raceInfo = activeDayAccordionBlock.parent().find('.race-links').data(),
        contestId = raceInfo ? raceInfo['contestCid'] : '',
        raceId = raceInfo ? raceInfo['raceCid'] : '';

      if (contestId !== '' && raceId !== '') {
        rebuildRacePreview(contestId, raceId);
      } else {
        sedHeaderDefaultState();
      }
    } else {
      sedHeaderDefaultState();
    }

  }
});
