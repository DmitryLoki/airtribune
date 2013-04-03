<?php
/**
 * @file
 * maps.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function maps_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'accommodation_map';
  $openlayers_maps->title = 'Accommodation/activity map';
  $openlayers_maps->description = 'Map used to show accommodations and activities in context of events.';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '380px',
    'image_path' => 'sites/all/themes/airtribune2/plugins/openlayers/tribune/img/',
    'css_path' => 'sites/all/themes/airtribune2/plugins/openlayers/tribune/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_attribution' => array(
        'seperator' => '',
      ),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => '0',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'event_map_overlay_accommodations' => 'event_map_overlay_accommodations',
          'event_map_overlay_activities' => 'event_map_overlay_activities',
          'event_map_accommodation_active' => 'event_map_accommodation_active',
          'event_map_openlayers_1' => 'event_map_openlayers_1',
          'event_map_overlay_hq' => 'event_map_overlay_hq',
        ),
        'panMapIfOutOfView' => 1,
        'keepInMap' => 1,
      ),
      'openlayers_behavior_zoompanel' => array(),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'event_map_accommodation_active' => 'event_map_accommodation_active',
          'google_hybrid_at_edition' => 0,
          'google_normal_at_edition' => 0,
          'google_satellite' => 0,
          'google_physical' => 0,
          'event_map_overlay_accommodations' => 0,
          'event_map_overlay_activities' => 0,
          'event_map_openlayers_1' => 0,
          'event_map_overlay_hq' => 0,
        ),
        'point_zoom_level' => '15',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'google_normal_at_edition',
    'layers' => array(
      'google_hybrid_at_edition' => 'google_hybrid_at_edition',
      'google_normal_at_edition' => 'google_normal_at_edition',
      'google_satellite' => 'google_satellite',
      'google_physical' => 'google_physical',
      'event_map_overlay_accommodations' => 'event_map_overlay_accommodations',
      'event_map_overlay_activities' => 'event_map_overlay_activities',
      'event_map_accommodation_active' => 'event_map_accommodation_active',
      'event_map_openlayers_1' => 'event_map_openlayers_1',
      'event_map_overlay_hq' => 'event_map_overlay_hq',
    ),
    'layer_weight' => array(
      'event_map_overlay_accommodations' => '-5',
      'event_map_overlay_activities' => '-1',
      'openlayers_kml_example' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'events_map_overlay' => '0',
      'event_map_accommodation_active' => '2',
      'event_map_openlayers_1' => '6',
      'event_map_overlay_hq' => '10',
    ),
    'layer_styles' => array(
      'geofield_formatter' => 'marker_events',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => 'marker_events',
      'events_map_overlay' => 'marker_events',
      'event_map_overlay_accommodations' => 'marker_accommodations',
      'event_map_overlay_activities' => 'marker_activity',
      'event_map_accommodation_active' => 'marker_accommodations_hover',
      'event_map_openlayers_1' => 'marker_headquarters',
      'event_map_overlay_hq' => 'marker_hqacc',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => 'clone_of_marker_events',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => 'clone_of_marker_events',
      'events_map_overlay' => 'clone_of_marker_events',
      'event_map_overlay_accommodations' => 'marker_accommodations_hover',
      'event_map_overlay_activities' => 'marker_activity_hover',
      'event_map_accommodation_active' => 'marker_accommodations_hover',
      'event_map_openlayers_1' => 'marker_headquarters_hover',
      'event_map_overlay_hq' => 'marker_hqacc_hover',
    ),
    'layer_activated' => array(
      'event_map_overlay_accommodations' => 'event_map_overlay_accommodations',
      'event_map_overlay_activities' => 'event_map_overlay_activities',
      'event_map_accommodation_active' => 'event_map_accommodation_active',
      'event_map_openlayers_1' => 'event_map_openlayers_1',
      'event_map_overlay_hq' => 'event_map_overlay_hq',
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'events_map_overlay' => 0,
    ),
    'layer_switcher' => array(
      'event_map_overlay_accommodations' => 0,
      'event_map_overlay_activities' => 0,
      'event_map_accommodation_active' => 0,
      'event_map_openlayers_1' => 0,
      'event_map_overlay_hq' => 0,
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'events_map_overlay' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'marker_events',
      'select' => 'clone_of_marker_events',
      'temporary' => 'marker_events',
    ),
  );
  $export['accommodation_map'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'event_hq';
  $openlayers_maps->title = 'Event info HQ';
  $openlayers_maps->description = 'A Map Used for Geofield Output';
  $openlayers_maps->data = array(
    'width' => '445px',
    'height' => '215px',
    'image_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '34.791297322254195, 31.77487713467286',
        'zoom' => '13',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => '0',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_zoompanel' => array(),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'geofield_formatter' => 'geofield_formatter',
          'google_satellite' => 0,
          'google_normal_at_edition' => 0,
          'google_hybrid_at_edition' => 0,
        ),
        'point_zoom_level' => '13',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'google_hybrid_at_edition',
    'layers' => array(
      'google_satellite' => 'google_satellite',
      'google_normal_at_edition' => 'google_normal_at_edition',
      'google_hybrid_at_edition' => 'google_hybrid_at_edition',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'events_map_overlay' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'events_map_overlay' => '0',
      'geofield_formatter' => 'marker_events',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'events_map_overlay' => '0',
      'geofield_formatter' => 'clone_of_marker_events',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
      'events_map_overlay' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'events_map_overlay' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['event_hq'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'event_hq_details';
  $openlayers_maps->title = 'Event info HQ details';
  $openlayers_maps->description = 'A Map Used for Geofield Output';
  $openlayers_maps->data = array(
    'width' => '460px',
    'height' => '220px',
    'image_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0, 0',
        'zoom' => '13',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => '0',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_zoompanel' => array(),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'geofield_formatter' => 'geofield_formatter',
          'google_satellite' => 0,
          'google_hybrid_at_edition' => 0,
          'google_normal_at_edition' => 0,
        ),
        'point_zoom_level' => '13',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'google_hybrid_at_edition',
    'layers' => array(
      'google_satellite' => 'google_satellite',
      'google_hybrid_at_edition' => 'google_hybrid_at_edition',
      'google_normal_at_edition' => 'google_normal_at_edition',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'events_map_overlay' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
    ),
    'layer_styles' => array(
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => '0',
      'events_map_overlay' => '0',
      'geofield_formatter' => 'marker_events',
    ),
    'layer_styles_select' => array(
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => '0',
      'events_map_overlay' => '0',
      'geofield_formatter' => 'clone_of_marker_events',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'events_map_overlay' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'events_map_overlay' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['event_hq_details'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'event_map';
  $openlayers_maps->title = 'Event map';
  $openlayers_maps->description = 'Map used to display events places';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '380px',
    'image_path' => 'sites/all/themes/airtribune2/plugins/openlayers/tribune/img/',
    'css_path' => 'sites/all/themes/airtribune2/plugins/openlayers/tribune/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_attribution' => array(
        'seperator' => '',
      ),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => '0',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'event_map_overlay_accommodations' => 'event_map_overlay_accommodations',
          'event_map_overlay_activities' => 'event_map_overlay_activities',
          'event_map_openlayers_1' => 'event_map_openlayers_1',
          'event_map_overlay_hq' => 'event_map_overlay_hq',
        ),
        'panMapIfOutOfView' => 1,
        'keepInMap' => 1,
      ),
      'openlayers_behavior_zoompanel' => array(),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'event_map_overlay_accommodations' => 0,
          'event_map_overlay_activities' => 0,
          'event_map_overlay_hq' => 0,
          'google_hybrid_at_edition' => 0,
          'google_normal_at_edition' => 0,
          'google_satellite' => 0,
          'google_physical' => 0,
          'event_map_openlayers_1' => 'event_map_openlayers_1',
        ),
        'point_zoom_level' => '15',
        'zoomtolayer_scale' => '5',
      ),
    ),
    'default_layer' => 'google_normal_at_edition',
    'layers' => array(
      'google_hybrid_at_edition' => 'google_hybrid_at_edition',
      'google_normal_at_edition' => 'google_normal_at_edition',
      'google_satellite' => 'google_satellite',
      'google_physical' => 'google_physical',
      'event_map_overlay_accommodations' => 'event_map_overlay_accommodations',
      'event_map_overlay_activities' => 'event_map_overlay_activities',
      'event_map_openlayers_1' => 'event_map_openlayers_1',
      'event_map_overlay_hq' => 'event_map_overlay_hq',
    ),
    'layer_weight' => array(
      'event_map_overlay_accommodations' => '-5',
      'event_map_overlay_activities' => '-1',
      'events_map_overlay' => '0',
      'test_geo_openlayers_1' => '0',
      'test_geo_openlayers_2' => '0',
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => '0',
      'openlayers_kml_example' => '0',
      'event_map_openlayers_1' => '5',
      'event_map_overlay_hq' => '10',
    ),
    'layer_styles' => array(
      'test_geo_openlayers_1' => '0',
      'geofield_formatter' => 'marker_events',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => 'marker_events',
      'test_geo_openlayers_2' => '0',
      'events_map_overlay' => 'marker_events',
      'event_map_overlay_accommodations' => 'marker_accommodations',
      'event_map_overlay_activities' => 'marker_activity',
      'event_map_openlayers_1' => 'marker_headquarters',
      'event_map_overlay_hq' => 'marker_hqacc',
    ),
    'layer_styles_select' => array(
      'test_geo_openlayers_1' => '0',
      'geofield_formatter' => 'clone_of_marker_events',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => 'clone_of_marker_events',
      'test_geo_openlayers_2' => '0',
      'events_map_overlay' => 'clone_of_marker_events',
      'event_map_overlay_accommodations' => 'marker_accommodations_hover',
      'event_map_overlay_activities' => 'marker_activity_hover',
      'event_map_openlayers_1' => 'marker_headquarters_hover',
      'event_map_overlay_hq' => 'marker_hqacc_hover',
    ),
    'layer_activated' => array(
      'event_map_overlay_accommodations' => 'event_map_overlay_accommodations',
      'event_map_overlay_activities' => 'event_map_overlay_activities',
      'event_map_openlayers_1' => 'event_map_openlayers_1',
      'event_map_overlay_hq' => 'event_map_overlay_hq',
      'test_geo_openlayers_1' => 0,
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'test_geo_openlayers_2' => 0,
      'events_map_overlay' => 0,
    ),
    'layer_switcher' => array(
      'event_map_overlay_accommodations' => 0,
      'event_map_overlay_activities' => 0,
      'event_map_openlayers_1' => 0,
      'event_map_overlay_hq' => 0,
      'test_geo_openlayers_1' => 0,
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'test_geo_openlayers_2' => 0,
      'events_map_overlay' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'marker_events',
      'select' => 'clone_of_marker_events',
      'temporary' => 'marker_events',
    ),
  );
  $export['event_map'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'events_map';
  $openlayers_maps->title = 'events_map';
  $openlayers_maps->description = 'Map used to display events\' HQ locations';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '380px',
    'image_path' => 'sites/all/themes/airtribune2/plugins/openlayers/tribune/img/',
    'css_path' => 'sites/all/themes/airtribune2/plugins/openlayers/tribune/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_geofield' => array(),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_attribution' => array(
        'seperator' => '',
      ),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => '0',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'events_map_overlay' => 'events_map_overlay',
        ),
        'panMapIfOutOfView' => 1,
        'keepInMap' => 1,
      ),
      'openlayers_behavior_zoompanel' => array(),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'events_map_overlay' => 'events_map_overlay',
          'google_hybrid_at_edition' => 0,
          'google_normal_at_edition' => 0,
          'google_satellite' => 0,
          'google_physical' => 0,
        ),
        'point_zoom_level' => '5',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'google_physical',
    'layers' => array(
      'google_hybrid_at_edition' => 'google_hybrid_at_edition',
      'google_normal_at_edition' => 'google_normal_at_edition',
      'google_satellite' => 'google_satellite',
      'google_physical' => 'google_physical',
      'events_map_overlay' => 'events_map_overlay',
    ),
    'layer_weight' => array(
      'events_map_overlay' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => 'marker_events',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => 'marker_events',
      'events_map_overlay' => 'marker_events',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => 'clone_of_marker_events',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => 'clone_of_marker_events',
      'events_map_overlay' => 'clone_of_marker_events',
    ),
    'layer_activated' => array(
      'events_map_overlay' => 'events_map_overlay',
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'events_map_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'marker_events',
      'select' => 'clone_of_marker_events',
      'temporary' => 'marker_events',
    ),
  );
  $export['events_map'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'geofield_formatter_map2';
  $openlayers_maps->title = 'Geofield Formatter Map 2';
  $openlayers_maps->description = 'Second Map Used for Geofield Output';
  $openlayers_maps->data = array(
    'width' => '600px',
    'height' => '400px',
    'image_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '68.99413945429406, -68.78519922743666',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_cluster' => array(
        'clusterlayer' => array(
          'geofield_formatter' => 'geofield_formatter',
        ),
        'distance' => '20',
        'threshold' => '',
      ),
      'openlayers_behavior_fullscreen' => array(
        'activated' => 0,
      ),
      'openlayers_behavior_geofield' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
      ),
      'openlayers_behavior_dragpan' => array(),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 0,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'geofield_formatter' => 'geofield_formatter',
        ),
      ),
      'openlayers_behavior_scaleline' => array(),
      'openlayers_behavior_tooltip' => array(
        'layers' => array(
          'geofield_formatter' => 'geofield_formatter',
        ),
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => 'geofield_formatter',
        'point_zoom_level' => '5',
      ),
    ),
    'default_layer' => 'google_normal',
    'layers' => array(
      'google_hybrid' => 'google_hybrid',
      'google_normal' => 'google_normal',
      'google_physical' => 'google_physical',
      'google_satellite' => 'google_satellite',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => 'default_marker_green',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => 'default_marker_blue',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['geofield_formatter_map2'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'geofield_widget_map2';
  $openlayers_maps->title = 'Geofield Widget 2';
  $openlayers_maps->description = 'Second Map Used for Geofield Input';
  $openlayers_maps->data = array(
    'width' => '600px',
    'height' => '400px',
    'image_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '103.35937324617977, 39.716198763382664',
        'zoom' => '1',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_geofield' => array(),
      'openlayers_behavior_geolocate' => array(
        'bind' => '1',
        'zoom_level' => '12',
        'watch' => '0',
      ),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
      ),
      'openlayers_behavior_dragpan' => array(),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 0,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
      'openlayers_behavior_scaleline' => array(),
    ),
    'default_layer' => 'google_normal',
    'layers' => array(
      'google_hybrid' => 'google_hybrid',
      'google_normal' => 'google_normal',
      'google_physical' => 'google_physical',
      'google_satellite' => 'google_satellite',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => 'default_marker_green',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => 'default_marker_blue',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['geofield_widget_map2'] = $openlayers_maps;

  return $export;
}
