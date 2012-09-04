<?php

$plugin = array(
  'title' => 'PostGIS',
  'schema' => 'geofield_backend_postgis_schema',
  'save' => 'geofield_backend_postgis_save',
  'types' => array('Point','LineString','Polygon','MultiPoint','MultiLineString','MultiPolygon','GeometryCollection'),
  'validate' => NULL,     // Additional validation callback. Takes a GeoPHP Geometry object.
  'postinstall' => NULL,  // Callback after installing a new field. Could be used for adding additional geospatial indexes
  'postdelete' => NULL,   // Callback after deleting field. Could be used for removing indexes and other cleanup.
  'requirements' => 'geofield_backend_postgis_requirements',
);

function geofield_backend_postgis_schema($field) {
  //@@TODO: type could vary depending on type of geometry chosen
  return array(
    'type' => 'blob',
    'pgsql_type' => 'geometry',
    'not null' => FALSE,
  );
}

function geofield_backend_postgis_save($geometry) {
  $unpacked = unpack('H*', $geometry->out('ewkb'));
  return $unpacked[1];
}

function geofield_backend_postgis_requirements() {
  try {
    $value = db_query('SELECT substring(PostGIS_Version() from 1 for 3)')->fetchField();
    if (empty($value)) return FALSE;

    $comparisson = version_compare($value, '1.5');
    if ($comparisson === FALSE) {
      return FALSE;
    }
    if ($comparisson == -1) {
      return FALSE;
    }
    return TRUE;
  }
  catch (PDOException $e) {
    return FALSE;
  }
}
