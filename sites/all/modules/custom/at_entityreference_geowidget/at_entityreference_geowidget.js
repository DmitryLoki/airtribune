
(function ($) {
  Drupal.behaviors.atEntityreferenceGeowidget = {
    attach: function(context, settings) {
      var div, map;
      div = $('#' + settings.atEntityreferenceGeowidget.mapId + ':not(.at-entityreference-geowidget-processed)',context);
      map = div.data('openlayers');
      if (map !== undefined){
        /*var protocol = new OpenLayers.Protocol.HTTP({
           url: Drupal.settings.basePath + 'at_entityreference_geowidget',
           format: new OpenLayers.Format.WKT()
        });
        var strategies = [new OpenLayers.Strategy.BBOX()];
        var layer = new OpenLayers.Layer.Vector('test', {
          protocol: protocol,
          strategies: strategies,
          projection: 'EPSG:4326',
          preFeatureInsert: function(feature) {
           feature.geometry.transform('EPSG:4326', 'EPSG:900913');
          }
        });
        map.openlayers.addLayer(layer);*/
        var selectControl = map.openlayers.getControlsByClass('OpenLayers.Control.SelectFeature')[0];
        oldOnSelect = selectControl.onSelect;

        selectControl.onSelect = function(feature){
          oldOnSelect.call(this, feature);
          $("#popup").click(function(event){event.preventDefault();alert('a')})
        }
        map.openlayers.events.on({'moveend': Drupal.atEntityreferenceGeowidget.moveEndListener});
        div.addClass('at-entityreference-geowidget-processed');
        //$("#popup .openlayers-tooltip-name a").live('click', function(event) {alert('clicked');});
      }
    }
  }
  
  Drupal.atEntityreferenceGeowidget = {
    moveEndListener: function(event){
      //var point1 = new OpenLayers.Geometry.Point(event.object.getExtent().left, event.object.getExtent().top);
      //var point2 = new OpenLayers.Geometry.Point(event.object.getExtent().right, event.object.getExtent().bottom);
      //var sourceProj = event.object.getProjection();
      //var destProj = new OpenLayers.Projection('EPSG:4326');
      //OpenLayers.Projection.transform(point1, sourceProj, destProj);
      //var dataObj = {'lat1': point1.y, 'lat2': point2.y, 'lon1': point1.x, 'lon2': point2.x};
      //alert(point1.x + ' ' + point1.y + ' ' + point2.x + ' ' + point2.y);
      var layers = event.object.getLayersByName('test');
      var request = event.object.getExtent().transform(new OpenLayers.Projection('EPSG:900913'), new OpenLayers.Projection('EPSG:4326')).toString();
      $.get(Drupal.settings.basePath + 'at_entityreference_geowidget', {bbox: request}, $.proxy(Drupal.atEntityreferenceGeowidget.parseResponse, event.object));
      //layers[0].refresh({force: true});
    },
    
    parseResponse: function(response){
      //var layer = this.getLayersByName('test')[0];
      var layer = this.layers[4];
      layer.destroyFeatures();
      Drupal.openlayers.addFeatures(Drupal.settings.openlayers.maps[Drupal.settings.atEntityreferenceGeowidget.mapId], layer, response);
      layer.setVisibility(true);
    },
    
    addReference: function(event){
      alert('clicked');
    }
  }
})(jQuery);