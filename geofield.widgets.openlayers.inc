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
    'behaviors' => array(
      'multiple values' => FIELD_BEHAVIOR_CUSTOM,
    ),
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
      'single' => 'Store each simple feature as a separate field.',
      'collection' => 'Store as a single collection.',
    ),
    '#default_value' => (isset($settings['data_storage'])) ? $settings['data_storage'] : 'single',
  );
  $form['feature_types'] = array(
    '#title' => t('Available Features'),
    '#type' => 'checkboxes',
    '#options' => array(
      'point' => t('Point'),
      'path' => t('Path'),
      'polygon' => t('Polygon'),
    ),
    '#description' => t('Select what features are available to draw.'),
    '#default_value' => isset($settings['feature_types']) ? $settings['feature_types'] : array('point' => 'point', 'path' => 'path', 'polygon' => 'polygon'),
  );
  $form['allow_edit'] = array(
    '#title' => t('Allow shape modification'),
    '#type' => 'checkbox',
    '#description' => t('Can you edit and delete shapes.'),
    '#default_value' => isset($settings['allow_edit']) ? $settings['allow_edit'] : 1,
  );
  return $form;
}

/**
 * Implements hook_field_widget_form().
 */
function openlayers_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $base) {
  geophp_load();
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  // Compress all the WKT elements into a single WKT object to pass to the map.
  // Essentially we compress all the elements into delta 0, then deconstruct them on the other side when it comes time to validate them
  $geoms = array();
  foreach ($items as $delta => $item) {
    $geoms[] = geoPHP::load($item['wkt'], 'wkt');
  }
  $combined_geom = geoPHP::geometryReduce($geoms);

  // We want to force the combined_geom into a geometryCollection
  $geom_type = $combined_geom->geometryType();
  if ($geom_type == 'MultiPolygon' || $geom_type == 'MultiLineString' || $geom_type == 'MultiPoint') {
    $combined_geom = new GeometryCollection($combined_geom->getComponents());
  }

  $combined_wkt = $combined_geom->out('wkt');
  $items = array(array('wkt' => $combined_wkt));

  // Create the geofield element. See function geofield_get_base_element for reference
  $element = geofield_get_base_element($base, $items, 0);

  $element['widget'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class' => array('geofield_wkt')),
    '#default_value' => $combined_wkt,
    '#required' => (isset($instance['required'])) ? $instance['required'] : FALSE,
  );

  $element['input_format']['#value'] = GEOFIELD_INPUT_WKT;

  $openlayers_map_id = !empty($instance['widget']['settings']['openlayers_map']) ? $instance['widget']['settings']['openlayers_map'] : 'geofield_widget_map';
  $element['#openlayers_mapname'] = $openlayers_map_id;
  $element['#after_build']= array('openlayers_geofield_widget_afterbuild');

  // This validate function computes all other columns from the master field
  $element['#element_validate'] = array('geofield_element_validate');

  // Attach the widget and field settings so they can be accesses by JS and validate functions
  $element['#widget_settings'] = $settings;
  $element['#widget_settings']['allow_edit'] = (bool) $settings['allow_edit'];
  $element['#widget_settings']['feature_types'] = array();
  foreach ($settings['feature_types'] as $feature => $feature_setting) {
    if ($feature_setting) {
      $element['#widget_settings']['feature_types'][] = $feature;
    }
  }
  $element['#widget_settings']['cardinality'] = $field['cardinality'];

  // Add the element to an array, because it's the format that FIELD_BEHAVIOR_CUSTOM expects
  $full_element = array($element);

  // Override the element_validate as we need to deal with deltas
  unset($full_element[0]['#element_validate']);
  $full_element['#element_validate'][] = 'openlayers_geofield_widget_element_validate';

  return $full_element;
}

/**
 * Callback for afterbuild for widget for js addition to
 */
function openlayers_geofield_widget_afterbuild($element, &$form_state) {
  $defaults = array();
  $element['geofield_openlayers_map'] = array(
    '#markup' => '<div class="form-item geofield-openlayers-map" style="display:block">'
                   . openlayers_geofield_form_latlon_map(array(), $element['#openlayers_mapname'])
                   . '</div>');

  $element['geofield_openlayers_map_desc'] = array(
    '#markup' => t('<div class="description geofield-help">Use the icons to select what type of feature to draw. Each map can contain one simple feature. Pan and zoom with arrows and the zoom bar.</div>')
  );

  drupal_add_js(
    array(
      'geofield' => array(
        'widget_settings' => $element['#widget_settings'],
      ),
    ),
    'setting'
  );

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

function openlayers_geofield_widget_element_validate($element, &$form_state) {
  geophp_load();
  $container_delta = $element[0];

  $combined_geom = geoPHP::load($container_delta['widget']['#value'], 'wkt');
  $combined_geom = geoPHP::geometryReduce($combined_geom);

  // Check to make sure they only saved the allowed types
  $geom_type = $combined_geom->geometryType();
  if ($geom_type == 'GeometryCollection' || $geom_type == 'MultiPoint' || $geom_type == 'MultiLineString' || $geom_type == 'MultiPolygon') {
    $geoms = $combined_geom->getComponents();
  }
  else {
    $geoms = array($combined_geom);
  }
  foreach ($geoms as $item) {
    $allowed = FALSE;
    foreach ($container_delta['#widget_settings']['feature_types'] as $type) {
      $geometry_type = strtolower($item->geometryType());
      if ($geometry_type == 'linestring') {
        $geometry_type = 'path';
      }
      if (strpos(strtolower($geometry_type), $type) !== FALSE) {
        $allowed = TRUE;
        break;
      }
    }
    if (!$allowed) {
      form_set_error($container_delta['#field_name'], 'Not allowed to submit a geometry of type ' . $item->geometryType());
      return;
    }
  }

  //Check the number deltas
  $cardinality = $container_delta['#widget_settings']['cardinality'];
  if ($cardinality > 0 && $container_delta['#widget_settings']['data_storage'] == 'single') {
    if (count($geoms) > $cardinality) {
      form_set_error($container_delta['#field_name'], 'Too many geometries submitted. Max allowed is ' .$cardinality);
      return;
    }
  }

  // Checks pass, lets load this up into deltas
  if ($container_delta['#widget_settings']['data_storage'] == 'collection') {
    $element[0]['wkt']['#value'] = $combined_geom->out('wkt');
    geofield_element_validate($element[0], $form_state);
  }

  if ($container_delta['#widget_settings']['data_storage'] == 'single') {
    foreach ($geoms as $delta => $geom) {
      // Clone delta-0
      $element = $container_delta;

      // Override the delta
      openlayers_geofield_override_element_delta($element, 0, $delta);

      // Apply the WKT
      $wkt = $geom->out('wkt');
      $element['wkt']['#value'] = $wkt;
      $element['widget']['#value'] = $wkt;

      // Assign the value in the form_state
      geofield_element_validate($element, $form_state);
    }
  }
}

function openlayers_geofield_override_element_delta(&$element, $source_delta, $delta) {
  if (isset($element['#parents'])) {
    foreach ($element['#parents'] as $index => $item) {
      if (is_numeric($item) && $item == $source_delta) {
        $element['#parents'][$index] = $delta;
      }
    }
  }
  if (isset($element['#array_parents'])) {
    foreach ($element['#array_parents'] as $index => $item) {
      if ($item == $source_delta) {
        $element['#array_parents'][$index] = $delta;
      }
    }
  }
  foreach ($element as $key => &$item) {
    if (substr($key, 0,1) != '#') {
      openlayers_geofield_override_element_delta($item, $source_delta, $delta);
    }
  }
}
