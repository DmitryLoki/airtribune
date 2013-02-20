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
  $openlayers_styles->title = 'Marker events active';
  $openlayers_styles->description = 'Used for events maps';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/map_marker_active.png',
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
  $openlayers_styles->name = 'marker_accommodations';
  $openlayers_styles->title = 'Marker accommodations';
  $openlayers_styles->description = 'Accommodations';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marker_accommodations.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );
  $export['marker_accommodations'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_accommodations_hover';
  $openlayers_styles->title = 'Marker accommodations active';
  $openlayers_styles->description = 'Accommodations active';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marker_accommodations_active.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );
  $export['marker_accommodations_hover'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_events';
  $openlayers_styles->title = 'Marker events';
  $openlayers_styles->description = 'Used for events maps';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/map_marker.png',
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

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_headquarters';
  $openlayers_styles->title = 'Marker headquarters';
  $openlayers_styles->description = 'Headquarters';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marker_hq.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );
  $export['marker_headquarters'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_headquarters_hover';
  $openlayers_styles->title = 'Marker headquarters active';
  $openlayers_styles->description = 'Headquarters active';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marker_hq_active.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );
  $export['marker_headquarters_hover'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_landing_zone';
  $openlayers_styles->title = 'Marker landing zone';
  $openlayers_styles->description = 'Landing zone';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marke_landing.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );
  $export['marker_landing_zone'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_activity';
  $openlayers_styles->title = 'Marker activity';
  $openlayers_styles->description = 'Activities';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marker_info.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );

  $export['marker_activity'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_activity_hover';
  $openlayers_styles->title = 'Marker activity active';
  $openlayers_styles->description = 'Activity active';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/airtribune2/images/markers/marker_info_active.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 28,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -28,
    'labelAlign' => 'cm',
  );

  $export['marker_activity_hover'] = $openlayers_styles;

  return $export;
}
