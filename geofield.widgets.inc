<?php

/**
 * Geofield Input format - auto-discover.
 */
define('GEOFIELD_INPUT_AUTO_DISCOVER', 'auto-discover');

/**
 * Geofield Input format - WKT.
 */
define('GEOFIELD_INPUT_WKT', 'wkt');

/**
 * Geofield Input format - GeoJSON.
 */
define('GEOFIELD_INPUT_GEOJSON', 'geojson');

/**
 * Geofield Input format - lat/lon.
 */
define('GEOFIELD_INPUT_LAT_LON', 'lat/lon');

/**
 * @file
 * Provides field widget hooks for geofield module.
 */

/**
 * Implements hook_field_widget_info().
 */
function geofield_field_widget_info() {
  $widgets = array();

  // OpenLayers dependant widget
  if (module_exists('openlayers')) {
    $widgets['geofield_openlayers'] = array(
      'label' => t('Openlayers Map'),
      'field types' => array('geofield'),
    );
  }

  $widgets['geofield_wkt'] = array(
    'label' => t('Well Known Text (WKT)'),
    'field types' => array('geofield'),
  );
  $widgets['geofield_geojson'] = array(
    'label' => t('GeoJSON'),
    'field types' => array('geofield'),
  );
  $widgets['geofield_latlon'] = array(
    'label' => t('Latitude / Longitude'),
    'field types' => array('geofield'),
  );
  $widgets['geofield_bounds'] = array(
    'label' => t('Bounds'),
    'field types' => array('geofield'),
  );

  return $widgets;
}

/**
 * Implements hook_field_widget_settings_form().
 */
function geofield_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  $form = array();

  //TODO: Allow more fine-grained control
  if ($widget['type'] == 'geofield_latlon') {
    $form['html5_geolocation'] = array(
      '#type' => 'checkbox',
      '#title' => 'Use HTML5 Geolocation to set default values',
      '#default_value' => (!empty($settings['html5_geolocation'])) ? $settings['html5_geolocation'] : FALSE,
    );
  }

  if ($widget['type'] == 'geofield_openlayers') {

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
  }
  return $form;
}


/**
 * Implements hook_field_widget_form().
 */
function geofield_field_widget_form(&$form, &$form_state, $field, $instance,
  $langcode, $items, $delta, $base) {

  $widget = $instance['widget'];
  $settings = $widget['settings'];
  $element = geofield_get_base_element($base, $items, $delta);

  switch ($widget['type']) {
    case 'geofield_wkt':
      $element['widget'] = array(
        '#type' => 'textarea',
        '#title' => $instance['label'],
        '#description' => $instance['description'],
        '#default_value' => !empty($items[$delta]['wkt']) ? $items[$delta]['wkt'] : '',
        '#required' => $instance['required'],
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_WKT;
      break;
    case 'geofield_geojson':
      $default_value = '';
      if (!empty($items[$delta]['wkt'])) {
        geophp_load();
        $geometry = geoPHP::load($items[$delta]['wkt'], 'wkt');
        $default_value = $geometry->out('json');
      }

      $element['widget'] = array(
        '#type' => 'textarea',
        '#title' => $instance['label'],
        '#description' => $instance['description'],
        '#default_value' => $default_value,
        '#required' => $instance['required'],
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_GEOJSON;
      break;
    case 'geofield_latlon':
      $latlon_value = array(
        'lat' => '',
        'lon' => '',
      );
      if (isset($items[$delta]['lat'])) {
        $latlon_value['lat'] = $items[$delta]['lat'];
      }
      if (isset($items[$delta]['lon'])) {
        $latlon_value['lon'] = $items[$delta]['lon'];
      }
      $element['widget'] = array(
        '#type' => 'geofield_latlon',
        '#title' => $instance['label'],
        '#description' => $instance['description'],
        '#default_value' => $latlon_value,
        '#required' => $instance['required'],
        '#geolocation' => (!empty($instance['widget']['settings']['html5_geolocation'])) ? $instance['widget']['settings']['html5_geolocation'] : FALSE,
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_LAT_LON;
      break;
  }

  return $element;
}

/**
 * Callback for afterbuild for widget for js addition to
 */

function geofield_widget_openlayers_afterbuild($element, &$form_state) {
  drupal_add_js(
    array('geofield' => array(
      'data_storage' => (!empty($settings['data_storage'])) ? $settings['data_storage'] : 'collection',
      ),
    ),
  'setting');

  $defaults = array();
  $element['helpmap'] = array(
    '#markup' => '<div class="form-item geotaxonomy-latlon-helpmap" style="display:block">'
                   . geofield_form_latlon_map(array(), $element['#openlayers_mapname'])
                   . '</div>');

  $element['helpmap_desc'] = array(
    '#markup' => t('<div class="description geofield-help">Use the icons to select what type of feature to draw. Each map can contain one simple feature. Pan and zoom with arrows and the zoom bar.</div>')
  );

  return $element;
}

/**
 * Create LatLon Helper Map.
 */
function geofield_form_latlon_map($defaults = array(), $map_name) {
  // Pass variables etc. to javascript
  // Set up our map to help set lat and lon
  // This map will always be projected as 4326 and use just the default map preset
  $map_data = openlayers_map_load($map_name);
  $map = $map_data->data;
  return openlayers_render_map($map);
}

function geofield_get_base_element($base, $items, $delta) {
  $element = $base;
  // @TODO: This won't be called wkt for long.
  $element['wkt'] = array(
    '#type' => 'value',
    '#value' => isset($items[$delta]['wkt']) ? $items[$delta]['wkt'] : NULL,
  );
  $element['geo_type'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['geo_type']) ? $items[$delta]['geo_type'] : NULL,
  );
  $element['lat'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['lat']) ? $items[$delta]['lat'] : NULL,
  );
  $element['lon'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['lon']) ? $items[$delta]['lon'] : NULL,
  );
  $element['left'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['left']) ? $items[$delta]['left'] : NULL,
  );
  $element['right'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['right']) ? $items[$delta]['right'] : NULL,
  );
  $element['bottom'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['bottom']) ? $items[$delta]['bottom'] : NULL,
  );
  $element['top'] = array(
    '#type' => 'value',
    '#default_value' => isset($items[$delta]['top']) ? $items[$delta]['top'] : NULL,
  );

  // $element['input_format'] is not a db field, but how we determine how to parse/calculate values in our widget.
  $element['input_format'] = array(
    '#type' => 'value',
    '#attributes' => array('class' => array('geofield_input_format')),
    '#value' => GEOFIELD_INPUT_AUTO_DISCOVER,
  );

  // This validate function computes all other columns from the master field
  $element['#element_validate'] = array('geofield_element_validate');

  return $element;
}

/**
 * Geofield Element Validate
 *
 * In this function, we set all the values from our various widgets to what the FieldAPI expects from us
 * based on our schema declaration.
 */
function geofield_element_validate($element, &$form_state) {
  // @TODO: convert this from a switch statement to various function calls (like a boss).
  switch ($element['input_format']['#value']) {
    case GEOFIELD_INPUT_WKT:
      geophp_load();
      if (!empty($element['widget']['#value'])) {
        $geometry = geoPHP::load($element['widget']['#value'], 'wkt');
      }
      break;
    case GEOFIELD_INPUT_GEOJSON:
      geophp_load();
      if (!empty($element['widget']['#value'])) {
        $geometry = geoPHP::load($element['widget']['#value'], 'json');
      }
      break;
    case GEOFIELD_INPUT_LAT_LON:
      geophp_load();
      if (!empty($element['widget']['lat']['#value']) && !empty($element['widget']['lon']['#value'])) {
        $geometry = new Point($element['widget']['lat']['#value'], $element['widget']['lon']['#value']);
      }
      break;
  }

  $values = array();

  if (!empty($geometry)) {
    $values = geofield_get_values_from_geometry($geometry);
  } else {
    $values['wkt'] = '';
    $values['geo_type'] = '';
    $values['lat'] = '';
    $values['lon'] = '';
    $values['top'] = '';
    $values['bottom'] = '';
    $values['right'] = '';
    $values['left'] = '';
  }

  if (isset($values['wkt']))       form_set_value($element['wkt'], $values['wkt'], $form_state);
  if (isset($values['geo_type']))  form_set_value($element['geo_type'], $values['geo_type'], $form_state);
  if (isset($values['lat']))       form_set_value($element['lat'], $values['lat'], $form_state);
  if (isset($values['lon']))       form_set_value($element['lon'], $values['lon'], $form_state);
  if (isset($values['top']))       form_set_value($element['top'], $values['top'], $form_state);
  if (isset($values['bottom']))    form_set_value($element['bottom'], $values['bottom'], $form_state);
  if (isset($values['right']))     form_set_value($element['right'], $values['right'], $form_state);
  if (isset($values['left']))      form_set_value($element['left'], $values['left'], $form_state);
}
