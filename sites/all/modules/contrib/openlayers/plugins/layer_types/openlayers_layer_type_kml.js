/**
 * @file
 * Layer handler for KML layers
 */

/**
 * Openlayer layer handler for KML layer
 */
Drupal.openlayers.layer.kml = function(title, map, options) {

  var layer = new OpenLayers.Layer.Vector(title, {
    name: options.name,
    drupalID: options.drupalID,
    layer_handler: options.layer_handler,
    styleMap: Drupal.openlayers.getStyleMap(map, options.drupalID)
  });

  // KML Projection handling and formating options
  var kml_options = options.formatOptions;
  kml_options.internalProjection = new OpenLayers.Projection('EPSG:' + map.projection);
  kml_options.externalProjection = new OpenLayers.Projection('EPSG:' + options.projection);

  if (options.method == 'file' || options.method == 'url') {
    var uri = options.url;
    // Use an AJAX like call to get data from URL
    OpenLayers.Request.GET({
      url: uri,
      callback: function (response) {
        addFeatures(response.responseText, kml_options);
      }
    });
  }

  if (options.method == 'raw') {
    addFeatures(options.raw, kml_options);
  }

  function addFeatures(kml, options) {
    var format = new OpenLayers.Format.KML(options);
    var features = format.read(kml);
    // Add features, if needed
    if (features) {
      layer.addFeatures(features);
      layer.events.triggerEvent('loadend');
    }
  }

  return layer;
};
