<?php
/**
 * Implements hook_field_formatter_info().
 *
 */
function geofield_field_formatter_info() {
  $formatters = array(
    'geofield_wkt' => array(
      'label' => t('Well Known Text (WKT)'),
      'field types' => array('geofield'),
      'settings' => array('data' => ''),
    ),
    'geofield_latlon' => array(
      'label' => t('Latitude/Longitude'),
      'field types' => array('geofield'),
      'settings' => array('data' => '', 'format' => ''),
    ),
    'geofield_geojson' => array(
      'label' => t('GeoJSON'),
      'field types' => array('geofield'),
      'settings' => array('data' => ''),
    )
  );

  // TODO: Figure out if OpenLayers sub-modules should be checked for
  if (module_exists('openlayers')) {  
    $formatters['geofield_openlayers'] = array(
      'label' => t('OpenLayers'),
      'field types' => array('geofield'),
      'settings' => array('map_preset' => '', 'data' => ''),
    );
  }
  return $formatters;
}


function geofield_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {
    case 'geofield_wkt':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => $item['wkt']);
      }
      return $element;
    case 'geofield_latlon':
      foreach ($items as $delta => $item) {
      	$output = t('Latitude: @latitude <br/>Longitude: @longitude', array('@latitude' => $item['lat'], '@longitude' => $item['lon']));
        $element[$delta] = array('#markup' => $output);
      }
      return $element;
    case 'geofield_geojson':
      foreach ($items as $delta => $item) {
        $element[$delta] = array('#markup' => t('Need to convert WKT to GeoJSON before this can be output.'));
      }
      return $element;
    case 'geofield_openlayers':
      // TODO: There should be a better check to determine whether openlayers is running
      if (module_exists('openlayers')) {
        foreach ($items as $delta => $item) {
          $element[$delta] = array('#markup' => t('Cant output openlayers yet.'));
        }
        return $element;
      }
  }

  return $element;
}

function _geofield_formatter_settings_data_options($formatter) {
  return array(
    'full' => t('Use full geometry'),
    'centroid' => t('Use centroid'),
    'bounding' => t('Use bounding box'),
  );
}

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
  
  switch ($display['type']) {
  	case 'geofield_wkt':
  	case 'geofield_latlon':
  	case 'geofield_openlayers':
  	  break;
  }

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
    '#default_value' => $settings['data'],
    '#empty_option' => t('None'),
    '#options' => $data_options,
  );

  if ('geofield_latlon' == $display['type']) {
    $format_options = _geofield_formatter_settings_format_options($display['type']);
  	$element['format'] = array(
      '#title' => t('Format'),
      '#type' => 'select',
      '#default_value' => 'decimal_degrees',
      '#empty_option' => t('None'),
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

