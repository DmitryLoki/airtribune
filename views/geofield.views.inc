<?php

/**
 * Implements hook_field_views_data().
 *
 * Views integration for geofields.
 *
 */
function geofield_field_views_data($field) {
  $data = field_views_field_default_views_data($field);

  foreach ($data as $table_name => $table_data) {
    $data[$table_name]['field_geofield_distance'] = array(
      'group' => 'Content',
      'title' => $table_data[$field['field_name']]['title'] . ' (' . $table_name . ': Distance from point.)',
      'title short' => $table_data[$field['field_name']]['title short'] . ' (' . $table_name . ':  Distance from point.)',
      'help' => $table_data[$field['field_name']]['help'],
      'sort' => array(
        'field' => 'field_geofield_distance',
        'table' => $table_name,
        'handler' => 'geofield_sort',
        'field_name' => $field['field_name'],
        'real_field' => $table_name,
      ),
      'field' => array(
        'field' => 'field_geofield_distance',
        'table' => $table_name,
        'handler' => 'geofield_handler_field',
        'field_name' => $field['field_name'],
        'real_field' => $table_name,
      ),
      'filter' => array(
        'field' => 'field_geofield_distance',
        'table' => $table_name,
        'handler' => 'geofield_handler_filter',
        'field_name' => $field['field_name'],
        'real_field' => $table_name,
      ),
    );
    foreach ($table_data as $field => $field_data) {
      if (substr($field, strlen($field) - 4) == '_wkt') {
        $data[$table_name][$field]['sort'] = array(
          'field' => $field,
          'table' => $table_name,
          'handler' => 'geofield_sort',
          'field_name' => 'field_geofield',
        );
      }
    }
  }

  return $data;
}
