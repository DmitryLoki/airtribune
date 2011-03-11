<?php

/**
 * Implements hook_field_widget_info().
 */
function geofield_field_widget_info() {
  $widgets = array();
  $widgets['geofield_wkt'] = array(
    'label' => t('Well Known Text (WKT)'),
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
  $widgets['geofield_textfields'] = array(
    'label' => t('All Textfields'),
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
  
  $form = array();
  
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

  if ($widget['type'] == 'geofield_wkt') {
    $element['wkt']['#title'] = 'Well Known Text';
    $element['wkt']['#type'] = 'textarea';
    
    $element['master_column']['#value'] = 'wkt';
  }

  if ($widget['type'] == 'geofield_latlon') {
    $element['lat']['#title'] = 'Latitude';
    $element['lat']['#type'] = 'textfield';
    
    $element['lon']['#title'] = 'Longitude';
    $element['lon']['#type'] = 'textfield';
    
    $element['master_column']['#value'] = 'latlon';
  }

  if ($widget['type'] == 'geofield_bounds') {
    $element['left']['#title'] = 'Left Longitude';
    $element['left']['#type'] = 'textfield';
    
    $element['top']['#title'] = 'Top Latitude';
    $element['top']['#type'] = 'textfield';
    
    $element['right']['#title'] = 'Right Longitude';
    $element['right']['#type'] = 'textfield';
    
    $element['bottom']['#title'] = 'Bottom Latitude';
    $element['bottom']['#type'] = 'textfield';
    
    $element['master_column']['#value'] = 'bounds';
  }
  
  if ($widget['type'] == 'geofield_textfields') {
    $element['wkt']['#title'] = 'Well Known Text';
    $element['wkt']['#type'] = 'textarea';

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
  
  // Master column is used by element-validate to decide which set of columns it should use to compute all other values.
  // By default, wkt is the master-column, all we compute all other values from it. For other widget (such as lat/lon) this will be different
  $element['master_column'] = array(
    '#type' => 'hidden',
    '#value' => 'wkt',
  );
  
  // This validate function computes all other columns from the master field
  $element['#element_validate'] = array('geofield_element_validate');
  
  return $element;
}

/**
 * Geofield Element Validate
 *
 * Compute all dependant values. We compute all other values from whichever
 * column is specified in the master_column value
 *
 * Steps:
 * 1. Determine which set of columns comprise the master-column set
 * 2. Load the geoPHP library
 * 3. Load the Geometry object from the master-column
 * 4. Get out all the computer values from the Geometry object
 * 5. Set all the values 
 */
function geofield_element_validate($element, &$form_state) {
  
  $master_column = $element['master_column']['#value'];
  
  // Load up geoPHP to do the conversions
  // ------------------------------------
  
  $geophp = geofield_load_geophp();
  if (!$geophp) {
    drupal_set_message("Unable to load geoPHP library. Not all values will be computer correctly",'error');
    return;
  }
  
  // Load up the geometry object from the master-column data
  // -------------------------------------------------------
  
  if ($master_column == 'wkt') {
    $wkt = $element['wkt']['#value']; 
    $geometry = GeometryLoader::load($wkt,'wkt');
  }

  if ($master_column == 'latlon') {
    $lat = $element['lat']['#value']; 
    $lon = $element['lon']['#value']; 
    $geometry = new Point($lon, $lat);
  }

  if ($master_column == 'bounds') {
    $top = $element['top']['#value'];
    $bottom = $element['bottom']['#value'];
    $right = $element['right']['#value'];
    $left = $element['left']['#value'];
    
    $wkt_bounds_format = 'POLYGON((left bottom,right bottom,right top,left top,left bottom))';
    $wkt = strtr($wkt_bounds_format, array('top' => $top, 'bottom' => $bottom, 'right' => $right, 'left' => $left));
    $geometry = GeometryLoader::load($wkt,'wkt');
  }
  
  // Get values from geometry
  // ------------------------
  
  $centroid = $geometry->getCentroid();
  $bounding = $geometry->getBBox();
  
  $wkt = $geometry->out('wkt');
  $geo_type = strtolower($geometry->getGeomType());
  
  $lat = $centroid->getY();
  $lon = $centroid->getX();
  
  $top = $bounding['maxy'];
  $bottom = $bounding['miny'];
  $right = $bounding['maxx'];
  $left = $bounding['minx'];
  
  
  // Set form values
  // ---------------
  form_set_value($element['wkt'], $wkt, $form_state);
  form_set_value($element['geo_type'], $geo_type, $form_state);
  form_set_value($element['lat'], $lat, $form_state);
  form_set_value($element['lon'], $lon, $form_state);
  form_set_value($element['top'], $top, $form_state);
  form_set_value($element['bottom'], $bottom, $form_state);
  form_set_value($element['right'], $right, $form_state);
  form_set_value($element['left'], $left, $form_state);
}