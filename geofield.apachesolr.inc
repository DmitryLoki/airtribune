<?php

/**
 * Implements hook_apachesolr_field_mappings().
 */
function geofield_apachesolr_field_mappings() {
  return array(
    'geofield' => array(
      'indexing_callback' => 'geofield_apachesolr_index',
      'facets' => TRUE,
    )
  );
}

/**
 * Name callback for field name
 */
function geofield_apachesolr_index($node, $field_name, $index_key, $field_info) {
  geophp_load();
  $return = array();
  if (isset($node->$field_name)) {
    // Load the instance settings for the field
    $instance = field_info_instance('node', $field_name, $node->type);
    if (!empty($instance['settings']['solrspatial'])) {
      if ($values = field_get_items('node', $node, $field_name)) {
        $geom = geoPHP::load($values['geom']);
        $return = array(
          array(
            'key' => $instance['settings']['solrspatial']['lat_field'],
            'value' => $values['lat']
          ),
          array(
            'key' => $instance['settings']['solrspatial']['lng_field'],
            'value' =>  $values['lon']
          ),
          array(
            'key' => $instance['settings']['solrspatial']['latlng_field'],
            'value' =>  $values['lat'] . ',' . $values['lon']
          ),
          array(
            'key' => 'ss_geo_wkt',
            'value' => $geom->out('wkt'),
          ),
        );
      }
    }
  }

  return $return;
}

/**
 * Implements hook_apachesolr_query_alter().
 */
function geofield_apachesolr_query_alter($query) {
  // Add the WKT field field
  $query->addParam('fl', 'ss_geo_wkt');
}

