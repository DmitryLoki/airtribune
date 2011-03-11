/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */


(function($) {
  
// Set some constants to use with control buttons.
BUTTON_BOUNDS_TOGGLE = 1;
BUTTON_LINE_TOGGLE = 2;
BUTTON_POLYGON_TOGGLE = 3;
BUTTON_POINT_TOGGLE = 4;

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
        
      // Sets the values of text fields on form based on what user clicked
      feature.layer.map.data_form.wkt.val(geom.toString());
      feature.layer.map.data_form.type.val(type);
      feature.layer.map.data_form.lat.val(centroid.x);
      feature.layer.map.data_form.lon.val(centroid.y);
      feature.layer.map.data_form.left.val(bounds.left);
      feature.layer.map.data_form.top.val(bounds.top);
      feature.layer.map.data_form.bottom.val(bounds.bottom);
      feature.layer.map.data_form.right.val(bounds.right);
        
      // Removes any previous points added to the map
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
      
      // Creates jQuery objects of the geo text fields
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

      // Create a layer on the map for selections
      selection_layer = new OpenLayers.Layer.Vector('Selection Layer');      
      
      // Create a panel to hold control buttons
      button_panel = new OpenLayers.Control.Panel({
        displayClass: 'openlayers_behavior_geofield_button_panel'
      });

      // Define controls for buttons' functionality
      bounds_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.RegularPolygon,
        {
          featureAdded: setItem
        });

      bounds_control.handler.setOptions({
          'sides': 4,
            'irregular': true});

      data.openlayers.addControl(bounds_control);

      line_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Path,
        {
          featureAdded: setItem
        });
      data.openlayers.addControl(line_control);

      polygon_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Polygon,
        {
          featureAdded: setItem
        });
      data.openlayers.addControl(polygon_control);

      point_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Point,
        {
          featureAdded: setItem
        });
      data.openlayers.addControl(point_control);
      

      // Function when buttons are clicked
      buttonToggle = function(which) {
        alert('which: ' + which + ';');

        if (which == BUTTON_BOUNDS_TOGGLE) {
          point_control.deactivate();
          line_control.deactivate();
          polygon_control.deactivate();
          
          bounds_control.activate();
        }
        else if (which == BUTTON_LINE_TOGGLE) {
          point_control.deactivate();
          polygon_control.deactivate();
          bounds_control.deactivate();
          
          line_control.activate();
        }
        else if (which == BUTTON_POLYGON_TOGGLE) {
          point_control.deactivate();
          bounds_control.deactivate();
          line_control.deactivate();
          
          polygon_control.activate();
        }
        else if (which == BUTTON_POINT_TOGGLE) {
          bounds_control.deactivate();
          line_control.deactivate();
          polygon_control.deactivate();
          
          point_control.activate();
        }
        else {
          point_control.deactivate();
          bounds_control.deactivate();
          line_control.deactivate();
          polygon_control.deactivate();
        }
      }

      // Add buttons to control_panel for each control type
      point_button = new OpenLayers.Control.Button({
        displayClass: "openlayers_behavior_geofield_button", 
        title: Drupal.t('Set a point'),
        trigger: buttonToggle(BUTTON_POINT_TOGGLE)
      });

      line_button = new OpenLayers.Control.Button({
        displayClass: "openlayers_behavior_geofield_button", 
        title: Drupal.t('Add a line'),
        trigger: buttonToggle(BUTTON_LINE_TOGGLE)
      });

      polygon_button = new OpenLayers.Control.Button({
        displayClass: "openlayers_behavior_geofield_button", 
        title: Drupal.t('Add a polygon'),
        trigger: buttonToggle(BUTTON_POLYGON_TOGGLE)
      });

      bounds_button = new OpenLayers.Control.Button({
        displayClass: "openlayers_behavior_geofield_button", 
        title: Drupal.t('Set bounds'),
        trigger: buttonToggle(BUTTON_BOUNDS_TOGGLE)
      });
      button_panel.addControls([point_button, line_button, polygon_button, bounds_button]);

      data.openlayers.addControl(button_panel);

      buttonToggle(99);

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
