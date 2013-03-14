(function ($) {
    Drupal.behaviors.atEntityreferenceGeowidget = {
        attach:function (context, settings) {
            var div, map, that = Drupal.behaviors.atEntityreferenceGeowidget;
            div = $('#' + settings.atEntityreferenceGeowidget.mapId + ':not(.at-entityreference-geowidget-processed)', context);
            map = div.data('openlayers');
            if (map !== undefined) {

                var selectControl = this.selectControl = map.openlayers.getControlsByClass('OpenLayers.Control.SelectFeature')[0],
                    oldOnSelect = selectControl.onSelect;

                selectControl.onSelect = function (feature) {
                    if (that.selectedFeature && that.selectedFeature.popup) {
                        that.selectedFeature.popup.destroy();
                        that.selectedFeature.popup = null;
                    }
                    that.selectedFeature = feature;
                    oldOnSelect.call(that, feature);
                    $("#popup .entityreference-select").click(function (event) {
                        //event.preventDefault();
                        entityReferenceWidget.processClick(event);
                        return false;
                    });

                    $("#popup_close").bind('mousedown', function () {
                        event.stopPropagation();
                        try {
                            that.selectedFeature = undefined;
                            selectControl.onUnselect();
                            selectControl.unselect();
                        } catch (e) {
                        }
                    })
                };
                var oldOnUnselect = selectControl.onUnselect;
                selectControl.onUnselect = function(){
                    that.selectedFeature = undefined;
                    oldOnUnselect.call(this, arguments[0]);
                };

                map.openlayers.events.on({'moveend':$.proxy(entityReferenceWidget.moveEndListener, entityReferenceWidget)});
                map.openlayers.events.triggerEvent('moveend');
                div.addClass('at-entityreference-geowidget-processed');
            }
        }
    };

    var entityReferenceWidget = {
        moveEndListener:function (event) {
            var request = event.object.getExtent().transform(new OpenLayers.Projection('EPSG:900913'), new OpenLayers.Projection('EPSG:4326')).toString();
            $.get(Drupal.settings.basePath + 'at_entityreference_geowidget', {bbox:request}, $.proxy(this.parseResponse, event.object));
        },

        parseResponse:function (response) {
            var layer = this.layers[4],
                map = layer.map,
                that = Drupal.behaviors.atEntityreferenceGeowidget;

            if (map.popups.length) {
                map.removePopup(map.popups[0]);
            }

            layer.removeAllFeatures();
            Drupal.openlayers.addFeatures(Drupal.settings.openlayers.maps[Drupal.settings.atEntityreferenceGeowidget.mapId], layer, response);

            if (that.selectedFeature) {
                //Select feature that replaces already selected feature
                var centroid = that.selectedFeature.geometry.getCentroid();
                for (var i = 0, features = layer.features; i < features.length; ++i) {
                    var featureCentroid = features[i].geometry.getCentroid();
                    if (centroid.x == featureCentroid.x && centroid.y == featureCentroid.y) {
                        if (map.popups.length) {
                            features[i].popup = window.popup;
                        }
                        that.selectControl.select(features[i]);
                        return;
                    }
                }
            }
            if (Drupal.settings.atEntityreferenceGeowidget.value) {
              var val = Drupal.settings.atEntityreferenceGeowidget.value;
              var features = map.layers[4].getFeaturesByAttribute('nid', val);
              that.selectControl.select(features[0]);
              $("#popup .entityreference-select").click();
            }
        },
        
        processClick:function(event){
          var nid = $(event.target).find('.nid');
          $('.field-type-entityreference .selected input').val(nid.text());
          $('.entityreference-selected').html(nid.parents('.openlayers-tooltip-description').find('.views-field-title').html());
        }
    }
})(jQuery);