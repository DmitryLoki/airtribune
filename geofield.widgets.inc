<?php

/**
 * Implements hook_field_widget_info().
 */
function geofield_field_widget_info() {
  return array(
    'geofield_textfield' => array(
      'label' => t('Geofield'),
      'field types' => array('geofield'),
    ),
  );
}

/**
 * Implements hook_field_widget_settings_form().
 */
function geofield_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];
  
  //TODO: Allow more fine-grained control
  if (module_exists('openlayers_ui')) {
    
    // Get preset options, filtered to those which have the GeoField behavior
    $presets = openlayers_presets();
    $preset_options = array();
    foreach ($presets as $preset) {
      if (array_key_exists('openlayers_behavior_geofield',$preset->data['behaviors'])) {
        $preset_options[$preset->name] = $preset->title;
      }
    }
    
    $form['only_openlayers_map'] = array(
      '#type' => 'checkbox',
      '#title' => t('Only Display Map'),
      '#default_value' => isset($settings['only_openlayers_map']) ? $settings['only_openlayers_map'] : FALSE,
      '#description' => t('Hide all textfields, leaving only the openlayers map'),
    );
    $form['openlayers_preset'] = array(
      '#type' => 'select',
      '#title' => t('Only Display Map'),
      '#default_value' => isset($settings['openlayers_preset']) ? $settings['openlayers_preset'] : 'geofield_map',
      '#options' => $preset_options,
      '#description' => t('Select which OpenLayers map you would like to use. Only maps which have the GeoField behavior may be selected. If your preferred map is not here, add the GeoField behavior to it first.'),
    );
    
  }

  return $form;
}


/**
 * Implements hook_field_widget_form().
 */
function geofield_field_widget_form(&$form, &$form_state, $field, $instance,
  $langcode, $items, $delta, $base) {
  $element = $base;
  $element['wkt'] = array(
    '#title' => 'Well Known Text',
    '#required' => FALSE,
    '#type' => 'textarea',
    '#attributes' => array('id' => 'wkt'),
    '#default_value' => isset($items[$delta]['wkt']) ?
      $items[$delta]['wkt'] : NULL,
  );
  $element['type'] = array(
    '#title' => 'Geometry Type',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'type'),
    '#default_value' => isset($items[$delta]['type']) ?
      $items[$delta]['type'] : NULL,
  );
  $element['lat'] = array(
    '#title' => 'Latitude',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'lat'),
    '#default_value' => isset($items[$delta]['lat']) ?
      $items[$delta]['lat'] : NULL,
  );
  $element['lon'] = array(
    '#title' => 'Longitude',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'lon'),
    '#default_value' => isset($items[$delta]['lon']) ?
      $items[$delta]['lon'] : NULL,
  );
  $element['left'] = array(
    '#title' => 'Left Latitude',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'left'),
    '#default_value' => isset($items[$delta]['left']) ?
      $items[$delta]['left'] : NULL,
  );
  $element['top'] = array(
    '#title' => 'Top Longitude',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'top'),
    '#default_value' => isset($items[$delta]['top']) ?
      $items[$delta]['top'] : NULL,
  );
  $element['right'] = array(
    '#title' => 'Right Latitude',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'right'),
    '#default_value' => isset($items[$delta]['right']) ?
      $items[$delta]['right'] : NULL,
  );
  $element['bottom'] = array(
    '#title' => 'Bottom Longitude',
    '#required' => FALSE,
    '#type' => 'textfield',
    '#attributes' => array('id' => 'bottom'),
    '#default_value' => isset($items[$delta]['bottom']) ?
      $items[$delta]['bottom'] : NULL,
  );
  if (module_exists('openlayers_ui')) {
    $element['helpmap'] = array(
      '#markup' => '<div class="form-item geotaxonomy-latlon-helpmap" style="display:block">'
                      . geofield_form_latlon_map(array(), isset($instance['widget']['settings']['openlayers_preset']) ? $instance['widget']['settings']['openlayers_preset'] : 'geofield_map')
                      .'</div>'
    );
    $element['helpmap_desc'] = array(
      '#markup' => t('Click the map to set a point for this location. Control-click to add lines. Alt-click to add polygons. Shift-click and drag to set bounds. Pan and zoom with arrows and the zoom bar.')
    );
  }
  // TODO Make this a different widget instead
  if (isset($instance['widget']['settings']['only_openlayers_map']) && $instance['widget']['settings']['only_openlayers_map']) {
    $element['wkt']['#type'] = 'hidden';
    $element['type']['#type'] = 'hidden';
    $element['lat']['#type'] = 'hidden';
    $element['lon']['#type'] = 'hidden';
    $element['left']['#type'] = 'hidden';
    $element['right']['#type'] = 'hidden';
    $element['bottom']['#type'] = 'hidden';
    $element['top']['#type'] = 'hidden';
  }
  return $element;
}

/**
 * Create LatLon Helper Map.
 */
function geofield_form_latlon_map($defaults = array(), $preset_name) {
  // Pass variables etc. to javascript
  // Set up our map to help set lat and lon
  // This map will always be projected as 4326 and use just the default map preset
  $preset = openlayers_preset_load($preset_name);
  $map = $preset->data;
  return openlayers_render_map($map);
}