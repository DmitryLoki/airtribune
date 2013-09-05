jQuery(function ($) {


  var mapContainer = $('[id^="openlayers-map"]');
  if (!mapContainer) return;

  var map = mapContainer.data('openlayers').openlayers,
    eventsFeaturesLayer = map.getLayersBy('drupalID', "events_map_overlay")[0];

  //get accordion object
  $.each(Drupal.settings.views_accordion, function (title, accordionSettings) {
    var accordionContainer = $(accordionSettings.header).parent(),
      accordion = accordionContainer.data('accordion');
    if (!accordion) return;

    $(accordionSettings.header)
      .unbind('click.accordion')
      .bind('click', function (event) {
        var accordionPaneHeader = $(this),
          accordionPane = $(this).next();
        accordionPaneHeader.toggleClass('ui-state-active ui-state-default');
        accordionPane.toggleClass('ui-accordion-content-active');

        var options = {
          toHide: $(),
          toShow: $(),
          complete: function(){
            accordion.active = this;
            accordion._trigger('change');
          }
        };
        options[accordionPaneHeader.hasClass('ui-state-active') ? 'toShow' : 'toHide'] = accordionPane;

        $.ui.accordion.animations.slide(options);

        event.preventDefault();
      });

    accordion.option('change', onChange);

    function onChange() {
      filterEventsFeaturesOnMap();
      scrollToActiveTab();
    }

    function filterEventsFeaturesOnMap() {
      var activePanesHeaders = accordionContainer.find('.ui-state-active'),
        years = [];

      if (activePanesHeaders.length) {
        years = activePanesHeaders.find('a').text().trim().split(/\s+/gi);
      }

      $.each(eventsFeaturesLayer.features, function (i, feature) {
        var featureDescription = $(feature.attributes.description),
          eventDate = featureDescription.find('span.dates').text();

        //show feature if year string in feature description
        if (years.some(function (year) {
          return eventDate.indexOf(year) > -1
        })) {
          feature.style = null;
        } else {
          feature.style = {display: 'none'}
        }

      });
      eventsFeaturesLayer.redraw();
    }
    filterEventsFeaturesOnMap();

    function scrollToActiveTab() {
      var $active = $(accordion.active);
      if ($active.length !== 0) {
        $('body,html').animate({scrollTop: $active.offset().top}, 400);
      }
    }

  });

});