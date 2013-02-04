if(location.hash.indexOf('h')>-1){
    hideTitle();
}else{
    zoomOutPoints();
}
function zoomOutPoints() {
    jQuery(function () {
        var $ = jQuery,
            map = $('.openlayers-map-events-map').data('openlayers').openlayers;
        map.zoomOut(true);
        insertFeatures(map);
        var title = $('.featured-header-title'),
            extent = map.getExtent(),
            features = [];

        for (var l in map.layers) {
            if (map.layers[l] instanceof OpenLayers.Layer.Vector) {
                features = features.concat(map.layers[l].features);
            }
        }

        var topMost = {top:-Infinity};
        features.forEach(function (feature) {
            var bound = feature.geometry.getBounds();
            if (bound.top > topMost.top) {
                topMost = bound;
            }
        });

        var pixel = map.getPixelFromLonLat(new OpenLayers.LonLat(topMost.left, topMost.top));

        var northMapPoint = map.getPixelFromLonLat(new OpenLayers.LonLat(extent.left, extent.top));

        map.pan(0, -northMapPoint.y - 110 + pixel.y);
    })
}

function hideTitle() {
    jQuery(window).load(function () {
        var $ = jQuery,
            map = $('.openlayers-map-events-map').data('openlayers').openlayers,
            mapContainer = $('#top'),
            containerOffset = mapContainer.offset();
        var title = $('.featured-header-title'),
            titleHeight = parseInt(title.css('height'), 10);

        mapContainer.bind('mousemove', function (event) {
            if (event.clientY - containerOffset.top > titleHeight + 30) {
                title.show();
            } else {
                title.hide();
            }
        });
        mapContainer.bind('mouseleave', function () {
            title.show();
        });
    })
}

function insertFeatures(map) {
    var extent = map.getExtent(),
        topmiddle = new OpenLayers.Geometry.Point((extent.right - extent.left) / 2, extent.top + 100000),
        topmiddleFeature = new OpenLayers.Feature.Vector(topmiddle),
        vectorLayer = new OpenLayers.Layer.Vector("points"),
        ring = new OpenLayers.Geometry.LinearRing([
            new OpenLayers.Geometry.Point(extent.left + 500000, extent.top + 200000),
            new OpenLayers.Geometry.Point(extent.left + 100000, extent.top + 200000),
            new OpenLayers.Geometry.Point(extent.left + 100000, extent.top + 500000)
        ]),
        polygon = new OpenLayers.Geometry.Polygon(ring),
        polygonFeature = new OpenLayers.Feature.Vector(polygon);
    vectorLayer.addFeatures(topmiddleFeature);
    vectorLayer.addFeatures(polygonFeature);

    map.addLayer(vectorLayer);
}