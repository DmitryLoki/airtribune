/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * OpenLayers Zoom to Layer Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_layerzoom', function (data, options) {
  var map = data.openlayers;
  for (var layerName in options) {
    if (options[layerName].enable) {
      var layers = map.getLayersBy('drupalID', layerName);
      // Go through selected layers to get full extent.
      for (var i in layers) {
        layer = layers[i];
        // Restrict zoom levels.
        var keys = Object.keys(options[layerName].resolutions);
        layer.alwaysInRange = false;
        layer.minResolution = options[layerName].resolutions[keys[keys.length-1]];
        layer.maxResolution = options[layerName].resolutions[keys[0]];
      }
    }
  }
});
