<?php

$plugin = array(
  'title' => 'Default',
  'schema' => 'geofield_backend_default_schema',
  'save' => 'geofield_backend_default_save',
  'load' => 'geofield_backend_default_load',
  'types' => array('Point','LineString','Polygon','MultiPoint','MultiLineString','MultiPolygon','GeometryCollection'),
  'validate' => NULL,     // Additional validation callback. Takes a GeoPHP Geometry object.
  'postinstall' => NULL,  // Callback after installing a new field. Could be used for adding additional geospatial indexes
  'postdelete' => NULL,   // Callback after deleting field. Could be used for removing indexes and other cleanup.
  'requirements' => NULL, // Callback to check system requirements
);

function geofield_backend_default_schema($fielddef) {
  return array(
    'type' => 'blob',
    'size' => 'big',
    'not null' => FALSE,
  );
}

function geofield_backend_default_save($geometry) {
  return $geometry->out('wkb');
}

function geofield_backend_default_load($value) {
  return geoPHP::load($value);
}
