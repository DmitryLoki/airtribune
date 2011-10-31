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
  $object_field = array();
  $type = str_replace('geofield_', '', $instance['widget']['type']);
  switch ($type) {
    case 'wkt':
      $object_field['wkt'] = _wkt_generate();
      break;

    case 'latlon':
      $object_field['lat'] = _dd_generate(-84, 84);
      $object_field['lon'] = _dd_generate(-180, 180);
      break;

    case 'bounds':
      $object_field['left']   = _dd_generate(-180, 180);
      $object_field['right']  = _dd_generate($object_field['left'], 180);
      $object_field['top']    = _dd_generate(-83, 84);
      $object_field['bottom'] = _dd_generate(-84, $object_field['top'] - 1);
      $object_field['lat']    = _dd_generate($object_field['bottom'], $object_field['top']);
      $object_field['lon']    = _dd_generate($object_field['left'], $object_field['right']);
      break;
  }
  $values = geofield_compute_values($object_field, $type);
  return $values;
}

/**
 * Helper to generate DD coordinates
 */
function _dd_generate($min, $max) {
  $func = 'rand';
  if (function_exists('mt_rand')) {
    $func = 'mt_rand';
  }
  $decimal = $func(0, pow(10, 5)) / pow(10, 5);
  $number = $func($min, $max) + $decimal;
  return round($number, 5);
}

/**
 * Helper to generate a random WKT string
 */
function _wkt_generate() {
  $types = array(
    'point',
    'linestring',
    'polygon',
  );
  $wkt = array();
  $type = $types[rand(0, 2)];
  $func = '_wkt_generate_' . $type;
  $wkt[] = drupal_strtoupper($type) . ' (' . $func() . ')';
  return implode("\n", $wkt);
}

function _wkt_generate_point() {
  $lat = _dd_generate(-84, 84);
  $lon = _dd_generate(-180, 180);
  return $lon . ' ' . $lat;
}

function _wkt_generate_linestring() {
  $lines = array();
  foreach (range(0, rand(1, 4)) as $i) {
    $lines[] = _wkt_generate_point();
  }
  return implode(", ", $lines);
}

function _wkt_generate_polygon() {
  $poly = array();
  foreach (range(0, rand(1, 5)) as $i) {
    $poly[] = _wkt_generate_point();
  }
  $poly[] = $poly[0]; // close it
  return '(' . implode(", ", $poly) . ')';
}
