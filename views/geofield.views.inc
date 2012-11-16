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
      $group_name = $table_data[$field_name]['group'];
      $data[$table_name]['field_geofield_distance'] = array(
        'group' => $group_name,
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
 * Mini-plugins for geofield proximity views plugins.
 */

function geofield_proximity_views_handlers() {
  return array(
    'manual' => array(
      'name' => t('Manually Enter Point'),
      'class' => 'geofieldProximityManual',
    ),
    // @TODO: Check for geocoder module first. :-/
    'geocoder' => array(
      'name' => t('Geocoded Location'),
      'class' => 'geofieldProximityGeocoder',
    ),
  );
}

function geofield_proximity_load_plugin($plugin) {
  $handlers = geofield_proximity_views_handlers();
  module_load_include('inc', 'geofield', 'views/proximity_plugins/geofieldProximityManual');
  module_load_include('inc', 'geofield', 'views/proximity_plugins/' . $handlers[$plugin]['class']);
  if (class_exists($handlers[$plugin]['class'])) {
    return new $handlers[$plugin]['class'];
  }
  else {
    return FALSE;
  }
}
