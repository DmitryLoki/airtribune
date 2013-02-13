(function ($) {
    Drupal.behaviors.atEntityreferenceGeowidget = {
        attach:function (context, settings) {
            var div, map;
            div = $('#' + settings.atEntityreferenceGeowidget.mapId + ':not(.at-entityreference-geowidget-processed)', context);
            map = div.data('openlayers');
            if (map !== undefined) {

                var selectControl = map.openlayers.getControlsByClass('OpenLayers.Control.SelectFeature')[0],
                    oldOnSelect = selectControl.onSelect;

                selectControl.onSelect = function (feature) {
                    if (this.selectedFeature && this.selectedFeature.popup) {
                        this.selectedFeature.popup.destroy();
                        this.selectedFeature.popup = null;
                    }
                    this.selectedFeature = feature;
                    oldOnSelect.call(this, feature);
                    $("#popup a").click(function (event) {
                        event.preventDefault();
                        alert('a')
                    });

                    $("#popup_close").bind('mousedown', function () {
                        event.stopPropagation();
                        try {
                            selectControl.unselect();
                        } catch (e) {
                        }
                    })
                };

                selectControl.onUnselect = function (feature) {
                    if (this.selectedFeature && this.selectedFeature.popup) {
                        this.selectedFeature.popup.destroy();
                        this.selectedFeature.popup = null;
                    }
                };

                map.openlayers.events.on({'moveend':Drupal.atEntityreferenceGeowidget.moveEndListener});
                div.addClass('at-entityreference-geowidget-processed');
            }
        }
    }

    Drupal.atEntityreferenceGeowidget = {
        moveEndListener:function (event) {
            var request = event.object.getExtent().transform(new OpenLayers.Projection('EPSG:900913'), new OpenLayers.Projection('EPSG:4326')).toString();
            $.get(Drupal.settings.basePath + 'at_entityreference_geowidget', {bbox:request}, $.proxy(Drupal.atEntityreferenceGeowidget.parseResponse, event.object));
        },

        parseResponse:function (response) {
            var layer = this.layers[4],
                features = [];
            var wktFormat = new OpenLayers.Format.WKT();
            //add just those features, that not on a map already
            for (var i = 0; i < response.length; ++i) {
                var f = wktFormat.read(response[i].wkt);
                if (response[i].attribute) {
                    f.attribute = response[i].attribute;
                }
                for (var j = 0; j < layer.features.length; ++j) {
                    if (!layer.features[j].centroid) {
                        layer.features[j].centroid = layer.features[j].geometry.getCentroid();
                    }
                    var geomCentroid = f.geometry.getCentroid();
                    if (layer.features[j].centroid.x == geomCentroid.x && layer.features[j].centroid.y == geomCentroid.y) {
                        return;
                    }
                }
                features.push(f);
            }
            //Drupal.openlayers.addFeatures(Drupal.settings.openlayers.maps[Drupal.settings.atEntityreferenceGeowidget.mapId], layer, response);
            layer.addFeatures(features);
            layer.setVisibility(true);
        },

        addReference:function (event) {
            alert('clicked');
        }
    }
})(jQuery);