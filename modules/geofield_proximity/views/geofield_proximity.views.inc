<?php

/**
 * @file
 * Hooks for Views integration
 */

/*
 * Two needed functions are contained in geofield.views.inc
 * geofield_haversine() for distance calculations
 * geofield_radius_options() for the options for the radius of the earth
 */

/**
 * Implmentation of hook_field_views_data_alter();
 */
function geofield_proximity_field_views_data_alter(&$result, $field, $module) {
  if ($module == 'geofield') {
    
    //Will loop through the revision and data tables created by geofield.
    foreach ($result as $table => $data) {
      $field_name = $field['field_name'];
      if (isset($data[$field_name])) {

        //Add the field_geofield_proximity to the data
        $result[$table]['field_geofield_proximity'] = array(
          'group'       => t('Content'),
          'title'       => $data[$field_name]['title'] . ' - proximity',
          'title short' => $data[$field_name]['title'] . ' - proximity',
          'help'        => $data[$field_name]['help'],
          'filter' => array(
            'field'      => 'field_geofield_proximity',
            'handler'    => 'geofield_proximity_handler_filter',
            'table'      => $table,
            'field_name' => $field_name,
            'real_field' => $table,
          ),
          'argument' => array(
            'field'      => 'field_geofield_proximity',
            'handler'    => 'geofield_proximity_handler_argument',
            'table'      => $table,
            'field_name' => $field_name,
            'real_field' => $table,
          ),
          'field' => array(
            'field'      => 'field_geofield_proximity',
            'handler'    => 'geofield_proximity_handler_field',
            'table'      => $table,
            'field_name' => $field_name,
            'real_field' => $table,
            'float'      => TRUE,
            'click sortable' => TRUE,
          ),
          'sort' => array(
            'field'      => 'field_geofield_proximity',
            'handler'    => 'geofield_proximity_handler_sort',
            'table'      => $table,
            'field_name' => $field_name,
            'real_field' => $table,
          ),
        );
      }
    }
  }
}
