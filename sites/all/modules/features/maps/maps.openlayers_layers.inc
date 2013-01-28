<?php
/**
 * @file
 * maps.openlayers_layers.inc
 */

/**
 * Implements hook_openlayers_layers().
 */
function maps_openlayers_layers() {
  $export = array();

  $openlayers_layers = new stdClass();
  $openlayers_layers->disabled = FALSE; /* Edit this to true to make a default openlayers_layers disabled initially */
  $openlayers_layers->api_version = 1;
  $openlayers_layers->name = 'google_hybrid_at_edition';
  $openlayers_layers->title = 'Hybrid';
  $openlayers_layers->description = 'Google Maps with roads and terrain.';
  $openlayers_layers->data = array(
    'type' => 'hybrid',
    'layer_type' => 'openlayers_layer_type_google',
    'numZoomLevels' => '21',
    'animationEnabled' => 1,
  );
  $export['google_hybrid_at_edition'] = $openlayers_layers;

  $openlayers_layers = new stdClass();
  $openlayers_layers->disabled = FALSE; /* Edit this to true to make a default openlayers_layers disabled initially */
  $openlayers_layers->api_version = 1;
  $openlayers_layers->name = 'google_normal_at_edition';
  $openlayers_layers->title = 'Normal';
  $openlayers_layers->description = 'Standard Google Maps Roads';
  $openlayers_layers->data = array(
    'type' => 'normal',
    'layer_type' => 'openlayers_layer_type_google',
    'numZoomLevels' => '21',
    'animationEnabled' => 1,
  );
  $export['google_normal_at_edition'] = $openlayers_layers;

  return $export;
}
