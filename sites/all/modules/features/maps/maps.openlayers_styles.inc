<?php
/**
 * @file
 * maps.openlayers_styles.inc
 */

/**
 * Implements hook_openlayers_styles().
 */
function maps_openlayers_styles() {
  $export = array();

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'clone_of_marker_events';
  $openlayers_styles->title = 'Marker events hover';
  $openlayers_styles->description = 'Used for events maps';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/map_marker_hover.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 14,
    'graphicHeight' => 18,
    'graphicOpacity' => 1,
    'graphicXOffset' => -7,
    'graphicYOffset' => -18,
    'labelAlign' => 'cm',
  );
  $export['clone_of_marker_events'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_events';
  $openlayers_styles->title = 'Marker events';
  $openlayers_styles->description = 'Used for events maps';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/map_marker.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 14,
    'graphicHeight' => 18,
    'graphicOpacity' => 1,
    'graphicXOffset' => -7,
    'graphicYOffset' => -18,
    'labelAlign' => 'cm',
  );
  $export['marker_events'] = $openlayers_styles;

  return $export;
}
