<?php

/**
 * Implements hook_field_widget_info().
 */
function geofield_field_widget_info() {
  $widgets = array();
  $widgets['geofield_textfields'] = array(
    'label' => t('Textfields'),
    'field types' => array('geofield'),
  );
  
  // OpenLayers dependant widget
  if (module_exists('openlayers_ui')) {
    $widgets['geofield_openlayers'] = array(
      'label' => t('Openlayers Map'),
      'field types' => array('geofield'),
    );
  }
  
  return $widgets;
}

/**
 * Implements hook_field_widget_settings_form().
 */
function geofield_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];
  
  //TODO: Allow more fine-grained control
  if ($widget['type'] == 'geofield_openlayers') {
    
    // Get preset options, filtered to those which have the GeoField behavior
    $presets = openlayers_presets();
    $preset_options = array();
    foreach ($presets as $preset) {
      if (array_key_exists('openlayers_behavior_geofield',$preset->data['behaviors'])) {
        $preset_options[$preset->name] = $preset->title;
      }
    }
    
    $form['openlayers_preset'] = array(
      '#type' => 'select',
      '#title' => t('OpenLayers Map'),
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
  
  $widget = $instance['widget'];
  $settings = $widget['settings'];
  $element = geofield_get_base_element($base, $items, $delta);
  
  if ($widget['type'] == 'geofield_textfields') {
    $element['wkt']['#title'] = 'Well Known Text';
    $element['wkt']['#type'] = 'textfield';

    $element['geo_type']['#title'] = 'Geometry Type';
    $element['geo_type']['#type'] = 'textfield';
 
    $element['lat']['#title'] = 'Latitude';
    $element['lat']['#type'] = 'textfield';
    
    $element['lon']['#title'] = 'Longitude';
    $element['lon']['#type'] = 'textfield';

    $element['left']['#title'] = 'Left Longitude';
    $element['left']['#type'] = 'textfield';
    
    $element['top']['#title'] = 'Top Latitude';
    $element['top']['#type'] = 'textfield';
    
    $element['right']['#title'] = 'Right Longitude';
    $element['right']['#type'] = 'textfield';
    
    $element['bottom']['#title'] = 'Bottom Latitude';
    $element['bottom']['#type'] = 'textfield';
  }
  
  if ($widget['type'] == 'geofield_openlayers') {
    $element['helpmap'] = array(
      '#markup' => '<div class="form-item geotaxonomy-latlon-helpmap" style="display:block">'
                      . geofield_form_latlon_map(array(), isset($instance['widget']['settings']['openlayers_preset']) ? $instance['widget']['settings']['openlayers_preset'] : 'geofield_map')
                      .'</div>'
    );
    $element['helpmap_desc'] = array(
      '#markup' => t('Click the map to set a point for this location. Control-click to add lines. Alt-click to add polygons. Shift-click and drag to set bounds. Pan and zoom with arrows and the zoom bar.')
    );
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

function geofield_get_base_element($base, $items, $delta) {
  $element = $base;
  
  $element['wkt'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_wkt'),
    '#default_value' => isset($items[$delta]['wkt']) ? $items[$delta]['wkt'] : NULL,
  );
  $element['geo_type'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_geo_type'),
    '#default_value' => isset($items[$delta]['geo_type']) ? $items[$delta]['geo_type'] : NULL,
  );
  $element['lat'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_lat'),
    '#default_value' => isset($items[$delta]['lat']) ? $items[$delta]['lat'] : NULL,
  );
  $element['lon'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_lon'),
    '#default_value' => isset($items[$delta]['lon']) ? $items[$delta]['lon'] : NULL,
  );
  $element['left'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_left'),
    '#default_value' => isset($items[$delta]['left']) ? $items[$delta]['left'] : NULL,
  );
  $element['right'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_right'),
    '#default_value' => isset($items[$delta]['right']) ? $items[$delta]['right'] : NULL,
  );
  $element['bottom'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_bottom'),
    '#default_value' => isset($items[$delta]['bottom']) ? $items[$delta]['bottom'] : NULL,
  );
  $element['top'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'geofield_top'),
    '#default_value' => isset($items[$delta]['top']) ? $items[$delta]['top'] : NULL,
  );
  
  return $element;
}