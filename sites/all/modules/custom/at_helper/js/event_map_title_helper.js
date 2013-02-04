Drupal.behaviors.events_map_title_helper = {
    attach: function(context){
        var $ = jQuery,
            mapContainer = $(context),
            mapData = mapContainer.data('openlayers');

        if(!mapData || mapData.shifted) return;

        var map = mapData.openlayers,
            features = [];

        for (var l in map.layers) {
            if (map.layers[l] instanceof OpenLayers.Layer.Vector) {
                features = features.concat(map.layers[l].features);
            }
        }

        if(features.length < 2) return;

        map.zoomOut();

        var topMost = {top:-Infinity},
            title = $('.featured-header-title'),
            extent = map.getExtent();

        features.forEach(function (feature) {
            var bound = feature.geometry.getBounds();
            if (bound.top > topMost.top) {
                topMost = bound;
            }
        });

        var pixel = map.getPixelFromLonLat(new OpenLayers.LonLat(topMost.left, topMost.top));
        var northMapPoint = map.getPixelFromLonLat(new OpenLayers.LonLat(extent.left, extent.top));

        map.pan(0, -northMapPoint.y - parseInt(title.css('height')) + pixel.y);

        //set mark, that map zoomed and paned
        mapContainer.data('shifted', true);
    }
};
