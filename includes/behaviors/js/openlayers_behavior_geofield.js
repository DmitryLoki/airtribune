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
      feature.layer.map.data_form.lat.val(centroid.y);
      feature.layer.map.data_form.lon.val(centroid.x);
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
      data.openlayers.addLayer(selection_layer);

      // Controls for Openlayers interaction for points, lines, polygons, and bounds
      
      point_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Point,
        {
          featureAdded: setItem
        }
      );
      data.openlayers.addControl(point_control);

      line_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Path,
        {
          featureAdded: setItem
        }
      );
      data.openlayers.addControl(line_control);

      polygon_control = new OpenLayers.Control.DrawFeature(
        selection_layer,
        OpenLayers.Handler.Polygon,
        {
          featureAdded: setItem
        }
      );
      data.openlayers.addControl(polygon_control);

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

      // Add buttons to control_panel for each control type
      geofield_button = new OpenLayers.Control.Button({
        displayClass: "openlayers_behavior_geofield_button status", 
        title: Drupal.t('Geofield Controls'),
        trigger: buttonTriggerGeofieldControl
      });

      // Create a panel to hold control buttons
      button_panel = new OpenLayers.Control.Panel({
        displayClass: 'openlayers_behavior_geofield_button_panel'
      });

      button_panel.addControls([geofield_button]);

      data.openlayers.addControl(button_panel);
      
      $('.openlayers_behavior_geofield_button_panel .openlayers_behavior_geofield_button', context).append('<ul><li class="point">Add a point</li><li class="line">Draw a line</li><li class="polygon">Draw a polygon</li><li class="bounds">Draw bounds</li></ul>');
      // @TODO: Maybe split logic up from presentation logic.
      $('.openlayers_behavior_geofield_button_panel .openlayers_behavior_geofield_button li', context).click(function() {
        $(this).parent().find('li').css('background-color', '#FFF');
        $(this).css('background-color', '#F00');
        
        if ($(this).hasClass('point')) {
          buttonToggle('point');
        } else if ($(this).hasClass('line')) {
          buttonToggle('line');
        } else if ($(this).hasClass('polygon')) {
          buttonToggle('polygon');
        } else if ($(this).hasClass('bounds')) {
          buttonToggle('bounds');
        }
      });
      
      function buttonTriggerGeofieldControl() {
        //buttonToggle('point');
      }
      
      //buttonToggle('none');

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

        // @TODO: NOT SURE IF THIS WORKS YET. OLD IN COMMENT
        //selection_layer.addFeatures([feature]);
        data.openlayers.addFeatures(data.openlayers, selection_layer, [feature]);
      }
      
    }
  }
};

// Function when buttons are clicked
function buttonToggle(which) {
  if (which == 'bounds') {
    point_control.deactivate();
    line_control.deactivate();
    polygon_control.deactivate();
    
    bounds_control.activate();
  }
  else if (which == 'line') {
    point_control.deactivate();
    polygon_control.deactivate();
    bounds_control.deactivate();
    
    line_control.activate();
  }
  else if (which == 'polygon') {
    point_control.deactivate();
    bounds_control.deactivate();
    line_control.deactivate();
    
    polygon_control.activate();
  }
  else if (which == 'point') {
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
})(jQuery);
