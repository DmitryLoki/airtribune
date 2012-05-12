<?php

/**
 * @file
 * Hooks for Views integration.
 */

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
        'title'       => $table_data[$field_name]['title'] . ' - proximity',
        'title short' => $table_data[$field_name]['title'] . ' - proximity',
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
          'click sortable' => TRUE,
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
  }
  return $data;
}

/**
 * Haversine formula
 */

function geofield_haversine($origin_lat, $origin_lon, $dest_field_lat, $dest_field_lon, $earth_radius) {
  return sprintf('( %f * acos( cos( radians(%f) ) * cos( radians(%s) ) * cos( radians(%s) - radians(%s) ) + sin( radians(%s) ) * sin( radians(%s) ) ) )', $earth_radius, $origin_lat, $dest_field_lat, $dest_field_lon, $origin_lon, $origin_lat, $dest_field_lat);
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
