<?php
/**
 * @file
 * Create random data to populate geofields.
 */

/**
 * Implements hook_devel_generate().
 */
function geofield_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_geofield_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _geofield_devel_generate($object, $field, $instance, $bundle);
  }
}

function _geofield_devel_generate($object, $field, $instance, $bundle) {
  include_once(drupal_get_path('module', 'geofield') . '/includes/GeoGenerator.php');
  $generator = new GeoGenerator(); // @TODO: Make this static.
  $object_field = array();
  $type = str_replace('geofield_', '', $instance['widget']['type']);
  $val = array(
    'wkt' => NULL,
    'lat' => NULL,
    'lon' => NULL,
    'top' => NULL,
    'bottom' => NULL,
    'right' => NULL,
    'left' => NULL,
  );
  if ($type == 'latlon' || $type == 'bounds') {
    list($val['lon'], $val['lat']) = $generator->random_point();
    // don't actually need lat/lon but provide a center for our bounds
    if ($type == 'bounds') {
      $lat_diff = $generator->dd_generate(2, 10) / 100;
      $lon_diff = $generator->dd_generate(2, 10) / 100;
      $val['left']   = $val['lon'] - $lon_diff;
      $val['right']  = $val['lon'] + $lon_diff;
      $val['top']    = $val['lat'] - $lat_diff;
      $val['bottom'] = $val['lat'] + $lat_diff;
    }
  }
  else {
    $type = 'wkt';
    $val['wkt'] = $generator->wkt_generate();
  }
  $values = geofield_compute_values($val, $type);
  return $values;
}