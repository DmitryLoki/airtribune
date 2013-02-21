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
    $('.event-map-enable-accommodations').data('layer', getLayerByDrupalID(map.layers, "event_map_overlay_accommodations"));
    $('.event-map-enable-activities').data('layer', getLayerByDrupalID(map.layers, "event_map_overlay_activities"));

    eyes.bind('click', function () {
        $(this).toggleClass('event-map-enable-active');
        var layer = $(this).data('layer');
        if(!layer){
            console.error('No layer found for',this);
            return
        }
        layer.setVisibility(!layer.visibility);
    });

    function getLayerByDrupalID(layers, drupalID) {
        for (var i = 0, l = layers.length; i < l; ++i) {
            if (layers[i].layers !== undefined) {
                return getLayerByDrupalID(layers[i].layers, drupalID);
            }
            if (layers[i].drupalID === drupalID) {
                return layers[i];
            }
        }
    }
});