<?php
/**
 * @file
 * waypoint.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function waypoint_field_default_fields() {
  $fields = array();

  // Exported field: 'ent_point-waypoint-field_cylinder_radius'.
  $fields['ent_point-waypoint-field_cylinder_radius'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_cylinder_radius',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'number',
      'settings' => array(
        'entity_translation_sync' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'field_instance' => array(
      'bundle' => 'waypoint',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'number',
          'settings' => array(
            'decimal_separator' => '.',
            'prefix_suffix' => TRUE,
            'scale' => 0,
            'thousand_separator' => ' ',
          ),
          'type' => 'number_integer',
          'weight' => 1,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ent_point',
      'field_name' => 'field_cylinder_radius',
      'label' => 'cylinder radius',
      'required' => 1,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'max' => '',
        'min' => '',
        'prefix' => '',
        'suffix' => 'm',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'html5_tools',
        'settings' => array(),
        'type' => 'numberfield',
        'weight' => '2',
      ),
    ),
  );

  // Exported field: 'ent_point-waypoint-field_point_center'.
  $fields['ent_point-waypoint-field_point_center'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_point_center',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'geofield',
      'settings' => array(
        'entity_translation_sync' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'geofield',
    ),
    'field_instance' => array(
      'bundle' => 'waypoint',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'geofield',
          'settings' => array(
            'data' => 'full',
          ),
          'type' => 'geofield_wkt',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ent_point',
      'field_name' => 'field_point_center',
      'label' => 'point center',
      'required' => 1,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'local_solr' => array(
          'enabled' => FALSE,
          'lat_field' => 'lat',
          'lng_field' => 'lng',
        ),
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'geofield',
        'settings' => array(
          'data_storage' => 'collection',
          'openlayers_map' => 'geofield_widget_map',
        ),
        'type' => 'geofield_openlayers',
        'weight' => '1',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('cylinder radius');
  t('point center');

  return $fields;
}
