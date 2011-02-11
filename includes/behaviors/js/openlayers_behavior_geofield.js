/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */


(function($) {
  
/**
 * Geofield Behavior
 */
Drupal.behaviors.openlayers_behavior_geofield = {
  'attach': function(context, settings) {
    var data = $(context).data('openlayers');

    /*
     * Helper method called on addFeature
     */
    function setItem(feature) {
      geom = feature.clone().geometry.transform(
        feature.layer.map.projection,
        new OpenLayers.Projection('EPSG:4326'));
        
      centroid = geom.getCentroid();
      bounds = geom.getBounds();
      type = typeLookup(feature);
        
      feature.layer.map.data_form.wkt.val(geom.toString());
      feature.layer.map.data_form.type.val(type);
      feature.layer.map.data_form.lat.val(centroid.x);
      feature.layer.map.data_form.lon.val(centroid.y);
      feature.layer.map.data_form.left.val(bounds.left);
      feature.layer.map.data_form.top.val(bounds.top);
      feature.layer.map.data_form.bottom.val(bounds.bottom);
      feature.layer.map.data_form.right.val(bounds.right);
        
      for (var i = 0; i < selection_layer.features.length; i++) {
        if (selection_layer.features[i] != feature) {
          selection_layer.features[i].destroy();
        }
      }
    }
    
    function typeLookup(feature) {
      lookup = {
        'OpenLayers.Geometry.Point':'point',
        'OpenLayers.Geometry.LineString':'line',
        'OpenLayers.Geometry.Polygon':'polygon',
      };
      
      return lookup[feature.geometry.__proto__.CLASS_NAME];
    }
    
    if (data && data.map.behaviors['openlayers_behavior_geofield']) {
      
      data.openlayers.data_form = {
        'wkt':$(data.map.behaviors['openlayers_behavior_geofield']['wkt']),
        'type':$(data.map.behaviors['openlayers_behavior_geofield']['type']),
        'lat':$(data.map.behaviors['openlayers_behavior_geofield']['lat']),
        'lon':$(data.map.behaviors['openlayers_behavior_geofield']['lon']),
        'left':$(data.map.behaviors['openlayers_behavior_geofield']['left']),
        'top':$(data.map.behaviors['openlayers_behavior_geofield']['top']),
        'right':$(data.map.behaviors['openlayers_behavior_geofield']['right']),
        'bottom':$(data.map.behaviors['openlayers_behavior_geofield']['bottom'])
      };

      selection_layer = new OpenLayers.Layer.Vector('Selection Layer');      
      
      /*
       * Point Drawing
       */
      
      point_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Point,
        {
          featureAdded: setItem
        }
      );
      data.openlayers.addLayer(selection_layer);
      data.openlayers.addControl(point_control);
      point_control.activate();
      
      /*
       * Line Drawing
       */
      
      line_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Path,
        {
          featureAdded: setItem
        }
      );
      data.openlayers.addLayer(selection_layer);
      data.openlayers.addControl(line_control);
      
      /*
       * Polygon Drawing
       */
       
      polygon_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Polygon,
        {
          featureAdded: setItem
        }
      );
      data.openlayers.addLayer(selection_layer);
      data.openlayers.addControl(polygon_control);
      
      /*
       * Bounds drawing
       */

      bounds_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.RegularPolygon,
        {
          featureAdded: setItem
        }
      );

      bounds_control.handler.setOptions({
          'sides': 4,
          'irregular': true});

      data.openlayers.addControl(bounds_control);
      
      // Hold down control key for polygons
      // Hold down alt key for lines
      // Hold down shift for bounds
      // Eventually, we should make a really nice editing bar for this
      $(document).keydown(function(event) {
        // Shift  -> Boundary
        if (event.keyCode == 16) {
          point_control.deactivate();
          line_control.deactivate();
          polygon_control.deactivate();
          bounds_control.activate();
        }
        // Control  -> Lines
        if (event.keyCode == 17) {
          point_control.deactivate();
          polygon_control.deactivate();
          bounds_control.deactivate();
          line_control.activate();
        }
        // Alt  -> Polygons
        if (event.keyCode == 18) {
          point_control.deactivate();
          line_control.deactivate();
          bounds_control.deactivate();
          polygon_control.activate();
        }
      });

      $(document).keyup(function(event) {
        // On keyup, go back to points
        if (event.keyCode == 16 || event.keyCode == 17 || event.keyCode == 18) {
          bounds_control.deactivate();
          line_control.deactivate();
          polygon_control.deactivate();
          point_control.activate();
        }
      });
      
      /*
       * Draw features if the form has values
       */
      if (data.openlayers.data_form.wkt.val()) {
        geometry = new OpenLayers.Geometry.fromWKT(data.openlayers.data_form.wkt.val());
        geometry.transform(
            new OpenLayers.Projection('EPSG:4326'),
            data.openlayers.projection);
        
        feature = new OpenLayers.Feature.Vector(geometry);
        selection_layer.addFeatures([feature]);
      }
      
    }
  }
};
})(jQuery);
