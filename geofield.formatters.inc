<?php

/**
 * Implements hook_field_formatter_info().
 */
function geofield_field_formatter_info() {
  $formatters = array(
    'geofield_wkt' => array(
      'label' => t('Well Known Text (WKT)'),
      'field types' => array('geofield'),
      'settings' => array('data' => ''),
    ),
    'geofield_geojson' => array(
      'label' => t('GeoJSON'),
      'field types' => array('geofield'),
      'settings' => array('data' => ''),
    ),
    'geofield_latlon' => array(
      'label' => t('Latitude/Longitude'),
      'field types' => array('geofield'),
      'settings' => array('data' => '', 'format' => ''),
    ),
    'geofield_lat' => array(
      'label' => t('Latitude Only'),
      'field types' => array('geofield'),
      'settings' => array('data' => '', 'format' => ''),
    ),
    'geofield_lon' => array(
      'label' => t('Longitude Only'),
      'field types' => array('geofield'),
      'settings' => array('data' => '', 'format' => ''),
    ),
    'geofield_geo_type' => array(
      'label' => t('Geometry Type'),
      'field types' => array('geofield'),
      'settings' => array('data' => '', 'format' => ''),
    ),
  );

  if (module_exists('openlayers')) {  
    $formatters['geofield_openlayers'] = array(
      'label' => t('OpenLayers'),
      'field types' => array('geofield'),
      'settings' => array('map_preset' => '', 'data' => ''),
    );
  }
  return $formatters;
}

/**
 * Implements hook_field_formatter_view().
 */
function geofield_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  
  // Transform into centroid or bouding if needed
  if ($display['settings']['data'] != 'full') {
    geofield_load_geophp();
    if ($display['settings']['data'] == 'centroid') {
      foreach ($items as $delta => $item) {
        $centroid = GeometryLoader::load($item['wkt'],'wkt')->getCentroid();
        $items[$delta] = get_values_from_geometry($centroid);
      }
    }
    if ($display['settings']['data'] == 'bounding') {
      //TODO: Bouding -- needs envelope function in geoPHP
    }
  }
  
  // If we are a lat, lon, or latlon, and we are using degrees-minutes-seconds (instead of decimal degrees), then do a transformation
  if ($display['settings']['format'] == 'degrees_minutes_seconds') {
    foreach ($items as $delta => $item) {
      $items[$delta]['lat'] = geofield_latlon_DECtoDMS($item['lat'],'lat');
      $items[$delta]['lon'] = geofield_latlon_DECtoDMS($item['lon'],'lon');
    }
  }

  switch ($display['type']) {
    case 'geofield_wkt':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => $item['wkt']);
      }
      return $element;
    case 'geofield_geojson':
      geofield_load_geophp();
      foreach ($items as $delta => $item) {
        $geometry = GeometryLoader::load($item['wkt'],'wkt');
        $json = $geometry->out('json');
        $element[$delta] = array('#markup' => $json);
      }
      return $element;
    case 'geofield_latlon':
      foreach ($items as $delta => $item) {
      	$output = t('Latitude: !latitude <br/>Longitude: !longitude', array('!latitude' => $item['lat'], '!longitude' => $item['lon']));
        $element[$delta] = array('#markup' => $output);
      }
      return $element;
    case 'geofield_lat':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => $item['lat']);
      }
      return $element;
    case 'geofield_lon':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => $item['lon']);
      }
      return $element;
    case 'geofield_geo_type':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => $item['geo_type']);
      }
      return $element;
    case 'geofield_openlayers':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => t('Cant output openlayers yet.'));
      }
      return $element;
  }

  return $element;
}

/**
 * Helper function for getting data options
 */
function _geofield_formatter_settings_data_options($formatter) {
  return array(
    'full' => t('Use full geometry'),
    'centroid' => t('Use centroid'),
    'bounding' => t('Use bounding box -- does not work yet'),
  );
}

/**
 * Helper function for getting format options
*/
function _geofield_formatter_settings_format_options($formatter) {
  return array(
    'decimal_degrees' => t('Decimal degress'),
    'degrees_minutes_seconds' => t('Degrees minutes seconds'),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function geofield_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  // TODO: Pull in all map presets for option list
  /*
  if ('geofield_openlayers' == $display['type']) {
    $element['map_preset'] = array(
      '#title' => t('Map preset'),
      '#type' => 'select',
//      '#default_value' => 'decimal_degrees',
      '#empty_option' => t('None'),
      '#options' => array(
        'decimal_degrees' => t('Decimal degress'),
        'degrees_minutes_seconds' => t('Degrees minutes seconds'),
      ),
    );	
  }
  */
  
  $data_options = _geofield_formatter_settings_data_options($display['type']);
  $element['data'] = array(
    '#title' => t('Data options'),
    '#type' => 'select',
    '#default_value' => $settings['data'] ? $settings['data'] : 'full',
    '#required' => TRUE,
    '#options' => $data_options,
  );

  if ($display['type'] == 'geofield_latlon' || $display['type'] == 'geofield_lat' || $display['type'] == 'geofield_lon') {
    $format_options = _geofield_formatter_settings_format_options($display['type']);
  	$element['format'] = array(
      '#title' => t('Format'),
      '#type' => 'select',
      '#default_value' => $settings['format'] ? $settings['format'] : 'decimal_degrees',
      '#required' => TRUE,
      '#options' => $format_options,
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function geofield_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  $data_options = _geofield_formatter_settings_data_options($display['type']);
  
  // TODO: Not sure if this unset is needed
  // Unset possible 'No defined styles' option.
  unset($data_options['']);

  // Styles could be lost because of enabled/disabled modules that defines
  // their styles in code.
  if (isset($data_options[$settings['data']])) {
    $summary[] = t('Data options: @data', array('@data' => $data_options[$settings['data']]));
  }
  else {
    $summary[] = t('No data options set');
  }

  if ('geofield_latlon' == $display['type']) {
    $format_options = _geofield_formatter_settings_format_options($display['type']);
    // Display this setting only if image is linked.
    if (isset($format_options[$settings['format']])) {
      $summary[] = $format_options[$settings['format']];
    }
  }

  return implode('<br />', $summary);
}

