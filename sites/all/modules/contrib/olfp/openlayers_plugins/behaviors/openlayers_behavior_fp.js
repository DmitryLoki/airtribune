/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/*jslint bitwise: true, sloppy: true, vars: true, white: true */
/*properties
 Control, FeaturePopups, addBehavior, addControl, addLayer, content, drupalID,
 fp, getLayersBy, hover, hoverItem, hoverList, hoveritem, hoverlist, item,
 layer, layers, length, olfphover, olfphoveritem, olfphoverlist, olfpitem,
 olfpsingle, openlayers, popup, prototype, push, single, templates, theme,
 title, tooltip
 */
/**
 * Javascript Drupal Theming function for inside of Popups
 *
 * @return
 *  Template HTML.
 */
Drupal.theme.prototype.olfpsingle = function (title, content) {

  var title = title || '<div class="openlayers-fp openlayers-tooltip-name">${.name}</div>';
  var content = content || '<div class="openlayers-fp openlayers-tooltip-description">${.description}</div>';

  return title + content;
};

Drupal.theme.prototype.olfpitem = function (item) {
  return item || '<li><a href="#" ${showPopup()}>${.name}</a></li>';
};

Drupal.theme.prototype.olfplist = function (content) {
  return content || '<h2>${layer.name} - ${count}</h2><ul>${html}</ul>';
};

Drupal.theme.prototype.olfphover = function (item) {
  return item || '<li>${.name}</li>';
};

Drupal.theme.prototype.olfphoveritem = function (item) {
  return item || '<li>${.name}</li>';
};

Drupal.theme.prototype.olfphoverlist = function (content) {
  return content || '<b>${count} ${i18n("features")}:</b><br>${html}';
};

// Make sure the namespace exists
Drupal.openlayers.fp = Drupal.openlayers.fp || {};

/**
 * OpenLayers Feature Popups Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_fp', function (context, options) {
  var map = context.openlayers;
  var layers = [];
  var i;
  var layeroptions;

  for (i in options.layers) {
    layeroptions = options.layers[i];
    if (layeroptions.layer === 1) {
      var selectedLayer = map.getLayersBy('drupalID', i);
      if (selectedLayer[0] !== 'undefined') {
        layers.push(selectedLayer[0]);
      }
    }
  }

  // If no layer is selected, just return.
  if (layers.length < 1) {
    return;
  }

  var fpControl = new OpenLayers.Control.FeaturePopups();
  map.addControl(fpControl);

  for (i in layers) {
    var layer = layers[i];
    var drupalID = layer.drupalID;
    layeroptions = options.layers[drupalID];
    var popup = parseInt(layeroptions.popup, 10);
    var tooltip = parseInt(layeroptions.tooltip, 10);
    var templates = {};

    // To avoid errors when they are not set.
    // I'm sure there's a better way to do that.
    layeroptions = layeroptions || {};
    layeroptions.templates = layeroptions.templates || {};
    layeroptions.templates.item = layeroptions.templates.item || '';
    layeroptions.templates.list = layeroptions.templates.list || '';
    layeroptions.templates.single = layeroptions.templates.single || {};
    layeroptions.templates.single.title = layeroptions.templates.single.title || '';
    layeroptions.templates.single.content = layeroptions.templates.single.content || '';
    layeroptions.templates.hover = layeroptions.templates.hover || '';
    layeroptions.templates.hoverlist = layeroptions.templates.hoverlist || '';
    layeroptions.templates.hoveritem = layeroptions.templates.hoveritem || '';

    templates.list = Drupal.theme('olfplist', layeroptions.templates.list);

    if (popup) {
      templates.item = Drupal.theme('olfpitem', layeroptions.templates.item);
      templates.single = Drupal.theme('olfpsingle', layeroptions.templates.single.title, layeroptions.templates.single.content);
    }

    if (tooltip) {
      templates.hover = Drupal.theme('olfphover', layeroptions.templates.hover);
      templates.hoverList = Drupal.theme('olfphoverlist', layeroptions.templates.hoverlist);
      templates.hoverItem = Drupal.theme('olfphoveritem', layeroptions.templates.hoveritem);
    }

    fpControl.addLayer(layer, {
      templates: templates
    });
  }

});
