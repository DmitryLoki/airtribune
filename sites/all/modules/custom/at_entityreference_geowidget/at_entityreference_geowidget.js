(function ($) {
    Drupal.behaviors.atEntityreferenceGeowidget = {
        attach:function (context, settings) {
            var div, map, that = Drupal.behaviors.atEntityreferenceGeowidget;
            div = $('#' + settings.atEntityreferenceGeowidget.mapId + ':not(.at-entityreference-geowidget-processed)', context);
            map = div.data('openlayers');
            if (map !== undefined) {
                //map.openlayers.addLayer(new OpenLayers.Layer.Vector('references'));
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
                
                if (Drupal.settings.atEntityreferenceGeowidget.value) {
                  var layer = map.openlayers.getLayersBy('drupalID', Drupal.settings.atEntityreferenceGeowidget.drupalID)[0];
                  var val = Drupal.settings.atEntityreferenceGeowidget.value;
                  var features = layer.getFeaturesByAttribute('nid', val);
                  //map.setCenter(features[0].geometry.getCentroid());
                  that.selectControl.select(features[0]);
                  $("#popup .entityreference-select").click();
                }
            }
        }
    };

    var entityReferenceWidget = {
        moveEndListener:function (event) {
            var request = event.object.getExtent().transform(new OpenLayers.Projection('EPSG:900913'), new OpenLayers.Projection('EPSG:4326')).toString();
            $.get(Drupal.settings.basePath + 'at_entityreference_geowidget/' + request + '/' + Drupal.settings.atEntityreferenceGeowidget.cid, {}, $.proxy(this.parseResponse, event.object));
        },

        parseResponse:function (response) {
            var layer = this.getLayersBy('drupalID', Drupal.settings.atEntityreferenceGeowidget.drupalID)[0],
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
        },
        
        processClick:function(event){
          //var nid = $(event.target).find('.nid');
          var nid = $(event.target).siblings('.views-field-nid');
          $('.field-type-entityreference .selected input').val($.trim(nid.text()));
          $('.entityreference-selected').html(nid.parents('.openlayers-tooltip-description').find('.views-field-title').html());
        }
    }
})(jQuery);