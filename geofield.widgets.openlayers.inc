<?php

/**
 * @file
 * Provides widget hooks on behalf of Openlayers.
 */

/**
 * Implements hook_field_widget_info().
 */
function openlayers_field_widget_info() {
  $widgets = array();

  $widgets['geofield_openlayers'] = array(
    'label' => t('Openlayers Map'),
    'field types' => array('geofield'),
  );

  return $widgets;
}

/**
 * Implements hook_field_widget_settings_form().
 */
function openlayers_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  $form = array();

  // Get preset options, filtered to those which have the GeoField behavior and *don't* have the draw features behavior, which is incompatible
  $maps = openlayers_maps();
  $map_options = array();
  foreach ($maps as $map) {
    if (array_key_exists('openlayers_behavior_geofield', $map->data['behaviors']) && !array_key_exists('openlayers_behavior_drawfeatures', $map->data['behaviors'])) {
      $map_options[$map->name] = $map->title;
    }
  }

  if (empty($map_options)) {
    form_set_error('openlayers_map', "Error: You have no compatible openlayers maps. Make sure that at least one preset has the 'GeoField' behavior enabled and that it does not have the 'Draw Features' behavior enabled (which is incompatible).");
  }

  $form['openlayers_map'] = array(
    '#type' => 'select',
    '#title' => t('OpenLayers Map'),
    '#default_value' => isset($settings['openlayers_map']) ? $settings['openlayers_map'] : 'geofield_widget_map',
    '#options' => $map_options,
    '#description' => t('Select which OpenLayers map you would like to use. Only maps which have the GeoField behavior may be selected. If your preferred map is not here, add the GeoField behavior to it first. The "Draw Features" bahavior is incompatible - presets with this behavior are not shown.'),
  );

  $form['data_storage'] = array(
    '#type' => 'radios',
    '#title' => t('Storage Options'),
    '#description' => t('Should the widget only allow simple features (points, lines, or polygons), or should the widget allow for complex features? Note that changing this setting from complex to simple after data has been entered can lead to data loss.'),
    '#options' => array(
      'collection' => 'Store as a single collection.',
      'single' => 'Store each simple feature as a separate field.',
    ),
    '#default_value' => (isset($settings['data_storage'])) ? $settings['data_storage'] : 'collection',
  );
  return $form;
}

/**
 * Implements hook_field_widget_form().
 */
function openlayers_field_widget_form(&$form, &$form_state, $field, $instance,
  $langcode, $items, $delta, $base) {

  $widget = $instance['widget'];
  $settings = $widget['settings'];
  $element = geofield_get_base_element($base, $items, $delta);

  $geo_value = $element['wkt']['#value'];
  $element['geom'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class' => array('geofield_wkt')),
    '#default_value' => $geo_value,
    '#required' => (isset($instance['required'])) ? $instance['required'] : FALSE,
  );

  $element['input_format']['#value'] = GEOFIELD_INPUT_WKT;

  $openlayers_map_id = !empty($instance['widget']['settings']['openlayers_map']) ? $instance['widget']['settings']['openlayers_map'] : 'geofield_widget_map';
  $element['#openlayers_mapname'] = $openlayers_map_id;
  $element['#after_build']= array('openlayers_geofield_widget_afterbuild');

  // This validate function computes all other columns from the master field
  $element['#element_validate'] = array('geofield_element_validate');
  $element['#data_storage'] = (!empty($settings['data_storage'])) ? $settings['data_storage'] : 'collection';

  return $element;
}

/**
 * Callback for afterbuild for widget for js addition to
 */

function openlayers_geofield_widget_afterbuild($element, &$form_state) {
  $defaults = array();
  $element['helpmap'] = array(
    '#markup' => '<div class="form-item geotaxonomy-latlon-helpmap" style="display:block">'
                   . openlayers_geofield_form_latlon_map(array(), $element['#openlayers_mapname'])
                   . '</div>');

  $element['helpmap_desc'] = array(
    '#markup' => t('<div class="description geofield-help">Use the icons to select what type of feature to draw. Each map can contain one simple feature. Pan and zoom with arrows and the zoom bar.</div>')
  );

  drupal_add_js(
    array('geofield' => array(
      'data_storage' => (!empty($element['#data_storage'])) ? $element['#data_storage'] : 'collection',
      ),
    ),
  'setting');

  return $element;
}

/**
 * Create LatLon Helper Map.
 */
function openlayers_geofield_form_latlon_map($defaults = array(), $map_name) {
  // Pass variables etc. to javascript
  // Set up our map to help set lat and lon
  // This map will always be projected as 4326 and use just the default map preset
  $map_data = openlayers_map_load($map_name);
  $map = $map_data->data;
  return openlayers_render_map($map);
}
