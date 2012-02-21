<?php

/**
 * Implements hook_field_views_data().
 *
 * Views integration for geofields.
 *
 */
function geofield_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'];

  foreach ($data as $table_name => $table_data) {
    if (isset($table_data[$field_name])) {
      $data[$table_name]['field_geofield_distance'] = array(
        'group' => 'Content',
        'title' => $table_data[$field_name]['title'] . ' (' . $table_name . ': Distance from point.)',
        'title short' => $table_data[$field_name]['title short'] . ' (' . $table_name . ':  Distance from point.)',
        'help' => $table_data[$field_name]['help'],
        'sort' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_sort',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
        ),
        'field' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_field',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
          'float' => TRUE,
        ),
        'filter' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_filter',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
        ),
      );
    }

    foreach ($table_data as $field => $field_data) {
      if (substr($field, strlen($field) - 4) == '_wkt') {
        $data[$table_name][$field]['sort'] = array(
          'field' => $field,
          'table' => $table_name,
          'handler' => 'geofield_handler_sort',
          'field_name' => 'field_geofield',
        );
      }
    }
  }
  return $data;
}

/**
 * Haversine formula
 */

function geofield_haversine($origin_lat, $origin_lon, $dest_field_lat, $dest_field_lon, $earth_radius) {
  return sprintf('( %f * acos( cos( radians(%f) ) * cos( radians(%s) ) * cos( radians(%s) - radians(%d) ) + sin( radians(%f) ) * sin( radians(%s) ) ) )', $earth_radius, $origin_lat, $dest_field_lat, $dest_field_lon, $origin_lon, $origin_lat, $dest_field_lat);
}

/**
 * Returns options for radius of the Earth.
 */

function geofield_radius_options() {
  return array(
    '6371' => t('Kilometers'),
    '6371000' => t('Meters'),
    '3959' => t('Miles'),
    '6975175' => t('Yards'),
    '20925525' => t('Feet'),
    '3444' => t('Nautical Miles'),
  );
}
