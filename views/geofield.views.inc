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
          /**
           * @TODO: We should probably do 3 different handlers for input of distance. Attempting to swap out the widget for
           *   exposed fields is going to be very problematic.
           */
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
