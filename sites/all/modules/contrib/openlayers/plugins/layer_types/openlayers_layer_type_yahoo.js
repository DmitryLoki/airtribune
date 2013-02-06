
/**
 * Process Yahoo Layers
 *
 * @param layerOptions
 *   Object of options.
 * @param mapid
 *   Map ID.
 * @return
 *   Valid OpenLayers layer.
 */
Drupal.openlayers.layer.yahoo = function(title, map, options) {
  var layer = new OpenLayers.Layer.Yahoo("Yahoo");
  return layer;
};
