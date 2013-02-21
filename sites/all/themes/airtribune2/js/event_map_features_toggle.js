jQuery(document).ready(function () {
    if (!Drupal.settings.openlayers) {
        return;
    }
    var $ = jQuery,
        maps = Drupal.settings.openlayers.maps,
        mapContainer,
        map;

    for (var m in maps) {
        mapContainer = $('#' + maps[m].id);
        if (mapContainer.data('openlayers')) {
            map = mapContainer.data('openlayers').openlayers;
        }
    }
    if (!map) {
        return;
    }

    var eyes = $('.event-map-enable');
    $('.event-map-enable-accommodations').data('layer', map.layers[4]);
    $('.event-map-enable-activities').data('layer', map.layers[5]);

    eyes.bind('click', function () {
        $(this).toggleClass('event-map-enable-active');
        var layer = $(this).data('layer');
        layer.setVisibility(!layer.visibility);
    })
});