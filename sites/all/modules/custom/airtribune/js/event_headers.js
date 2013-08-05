jQuery(function ($) {

  //get features from map
  var mapContainer = $('[id^="openlayers-map"]');
  if (!mapContainer) return;

  var map = mapContainer.data('openlayers').openlayers,
    eventsFeaturesLayer = map.getLayersBy('drupalID', "events_map_overlay")[0];

  //get accordion object
  $.each(Drupal.settings.views_accordion, function (title, accordionSettings) {
    var accordion = $(accordionSettings.header).parent().data('accordion');
    if (!accordion) return;

    accordion.option('change', filterEventFeaturesOnMap);

    function filterEventFeaturesOnMap() {
      var activeAccordionBlock = accordion.active,
        year = '';

      if (activeAccordionBlock.length) {
        year = activeAccordionBlock.find('a').text().trim();
      }

      $.each(eventsFeaturesLayer.features, function (i, feature) {
        var featureDescription = $(feature.attributes.description);

        //show feature if year string in feature description
        if (year == '' || featureDescription.find('span.dates').text().indexOf(year) > -1) {
          feature.style = null;
        } else {
          feature.style = {display: 'none'}
        }

      });
      eventsFeaturesLayer.redraw();
    }

    filterEventFeaturesOnMap();
  });


});