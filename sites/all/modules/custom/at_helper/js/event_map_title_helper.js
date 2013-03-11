Drupal.behaviors.events_map_title_helper = {
    attach:function (context) {
        var $ = jQuery,
            mapContainer = $(context),
            mapData = mapContainer.data('openlayers');

        if (!mapData || mapData.shifted) return;

        var map = mapData.openlayers,
            features = [];

        for (var l in map.layers) {
            if (map.layers[l] instanceof OpenLayers.Layer.Vector) {
                features = features.concat(map.layers[l].features);
            }
        }

        setTimeout(function () {
            if (features.length < 2) {
                return;
            }

            var topMost = {top:-Infinity},
                topMostFeature = {},
                title = $('.featured-header-title'),
                extent;

            //Search for feature with max top (min y) property
            features.forEach(function (feature) {
                var bound = feature.geometry.getBounds();
                if (bound.top > topMost.top) {
                    topMost = bound;
                    topMostFeature = feature;
                }
            });

            var titleHeight = parseInt(title.css('height'), 10),
                pixel = map.getViewPortPxFromLonLat(new OpenLayers.LonLat(topMost.left, topMost.top));

            //if topmost feature already below title
            if (titleHeight > pixel.y && pixel.y > 0) {
                return;
            }

            //for rear cases, when feature out of map
            if(pixel.y < 0) {
                titleHeight = -titleHeight;
                pixel.y = -pixel.y;
            }

            map.pan(0, titleHeight - (pixel.y) - 140, {animate: false});

            extent = map.getExtent();

            //set mark, that map paned
            mapContainer.data('shifted', true);

            for (var i = 0, zoomOutNeeded = false, l = features.length; i < l; i++) {
                var feature = features[i];
                if (!extent.containsBounds(feature.geometry.getBounds())) {
                    zoomOutNeeded = true;
                    break;
                }
            }
            if (zoomOutNeeded) {
                map.zoomOut();
            }
        }, 100)
    }
};
