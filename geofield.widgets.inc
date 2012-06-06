<?php

/**
 * @file
 * Provides field widget hooks for geofield module.
 */

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
 * Geofield Input format - bounds.
 */
define('GEOFIELD_INPUT_BOUNDS', 'bounds');

// If we have the Openlayers module installed, include their widget code.

if (module_exists('openlayers')) {
  require_once(drupal_get_path('module', 'geofield') . '/geofield.widgets.openlayers.inc');
}

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

  if ($widget['type'] == 'geofield_latlon') {
    $form['html5_geolocation'] = array(
      '#type' => 'checkbox',
      '#title' => 'Use HTML5 Geolocation to set default values',
      '#default_value' => (!empty($settings['html5_geolocation'])) ? $settings['html5_geolocation'] : FALSE,
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
        '#title' => check_plain($instance['label']),
        '#description' => check_plain($instance['description']),
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
        '#title' => check_plain($instance['label']),
        '#description' => check_plain($instance['description']),
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
        '#title' => check_plain($instance['label']),
        '#description' => check_plain($instance['description']),
        '#default_value' => $latlon_value,
        '#required' => $instance['required'],
        '#geolocation' => (!empty($instance['widget']['settings']['html5_geolocation'])) ? $instance['widget']['settings']['html5_geolocation'] : FALSE,
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_LAT_LON;
      break;
    case 'geofield_bounds':
      $bounds_value = array(
        'top' => '',
        'right' => '',
        'bottom' => '',
        'left' => '',
      );
      if (isset($items[$delta]['top'])) {
        $bounds_value['top'] = $items[$delta]['top'];
      }
      if (isset($items[$delta]['right'])) {
        $bounds_value['right'] = $items[$delta]['right'];
      }
      if (isset($items[$delta]['bottom'])) {
        $bounds_value['bottom'] = $items[$delta]['bottom'];
      }
      if (isset($items[$delta]['left'])) {
        $bounds_value['left'] = $items[$delta]['left'];
      }
      $element['widget'] = array(
        '#type' => 'geofield_bounds',
        '#title' => check_plain($instance['label']),
        '#description' => check_plain($instance['description']),
        '#default_value' => $bounds_value,
        '#required' => $instance['required'],
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_BOUNDS;
      break;
  }

  return $element;
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
    case GEOFIELD_INPUT_BOUNDS:
      geophp_load();
      if (!empty($element['widget']['top']['#value']) && !empty($element['widget']['right']['#value']) && !empty($element['widget']['bottom']['#value']) && !empty($element['widget']['left']['#value'])) {
        $wkt_bounds_format = 'POLYGON((left bottom,right bottom,right top,left top,left bottom))';
        $wkt = strtr($wkt_bounds_format, array('top' => $element['widget']['top']['#value'],
          'right' => $element['widget']['right']['#value'],
          'bottom' => $element['widget']['bottom']['#value'],
          'left' => $element['widget']['left']['#value']));
        $geometry = geoPHP::load($wkt, 'wkt');
      }
      break;
  }

  $values = array();

  if (!empty($geometry)) {
    $values = geofield_get_values_from_geometry($geometry);
  }
  else {
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
