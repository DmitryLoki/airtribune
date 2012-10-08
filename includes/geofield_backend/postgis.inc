<?php

$plugin = array(
  'title' => 'PostGIS',
  'schema' => 'geofield_backend_postgis_schema',
  'save' => 'geofield_backend_postgis_save',
  'types' => array('Point','LineString','Polygon','MultiPoint','MultiLineString','MultiPolygon','GeometryCollection'),
  'validate' => NULL,     //@@TODO: Additional validation callback. Takes a GeoPHP Geometry object.
  'postinstall' => NULL,  //@@TODO: Callback after installing a new field. Could be used for adding additional geospatial indexes
  'postdelete' => NULL,   //@@TODO: Callback after deleting field. Could be used for removing indexes and other cleanup.
  'requirements' => 'geofield_backend_postgis_requirements',
  'settings' => 'geofield_backend_postgis_settings',
);

function geofield_backend_postgis_schema($field) {
  //@@TODO: Geometry vs. Geography
  //@@TODO: SRID
  $settings = $field['settings']['postgis'];
  return array(
    'type' => 'blob',
    'pgsql_type' => $settings['geomtype'],
    'not null' => FALSE,
  );
}

function geofield_backend_postgis_save($geometry) {
  $unpacked = unpack('H*', $geometry->out('ewkb'));
  return $unpacked[1];
}

function geofield_backend_postgis_requirements(&$error) {
  try {
    $value = db_query('SELECT substring(PostGIS_Version() from 1 for 3)')->fetchField();
    if (empty($value)) {
      $error = 'Could not detect postGIS version';
      return FALSE;
    }

    $comparisson = version_compare($value, '1.5');
    if ($comparisson === FALSE) {
      $error = 'Could not detect postGIS version';
      return FALSE;
    }
    if ($comparisson == -1) {
      $error = 'PostGIS 1.5 or later required';
      return FALSE;
    }
    return TRUE;
  }
  catch (PDOException $e) {
    $error = 'Could not detect postGIS';
    return FALSE;
  }
}

function geofield_backend_postgis_settings($field, $instance, $has_data) {
  $defaults = (isset($field['settings']['postgis'])) ? $field['settings']['postgis'] : array();
  $form = array();
  $form['fieldtype'] = array(
    '#title' => 'PostGIS Type',
    '#type' => 'select',
    '#options' => array(
      'geometry' => 'Geometry',
      'geography' => 'Geography',
    ),
    '#default_value' => isset($defaults['fieldtype']) ? $defaults['fieldtype'] : 'geometry',
    '#disabled' => $has_data,
  );
  $form['geomtype'] = array(
    '#title' => 'Geometry Type',
    '#type' => 'select',
    '#options' => array(
      'geometry' => 'All Types',
      'point' => 'Points Only',
      'line' => 'Lines Only',
      'polygon' => 'Polygons Only',
    ),
    '#default_value' => isset($defaults['geomtype']) ? $defaults['geomtype'] : 'geometry',
    '#disabled' => $has_data,
  );
  return $form;
}
