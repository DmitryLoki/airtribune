<?php


/**
 * Draw an image for waypoints
 */
function at_helper_draw($settings = array()) {
  $settings = at_helper_prepare_settings();
  at_helper_settings_process($settings);
  
  $route_points = $settings['route_points'];
  $waypoints = $settings['waypoints'];
  
  
  // TODO: Check if GD is enabled
  
  
  // Get canvas dimensions without offset.
  $offset = $settings['offset'];
  $canvas = $settings['canvas'];
  
  
  $path = 'sites/default/files/my_new_image.png';
  
  // Create image
  $img = imagecreatetruecolor($canvas['width'], $canvas['height']);
  
  // Draw canvas background
  $back = imagecolorallocate($img, 255, 255, 255);
  imagefilledrectangle($img, 0, 0, $canvas['width'] - 1, $canvas['height'] - 1, $back);
  
  
  // Set circle inner and border colours
  $cylinder_inner_color = imagecolorallocatealpha ($img , 127 , 127 , 127 , 75);
  $cylinder_border_color = imagecolorallocate($img, 127, 127, 127);
  
  // Draw circles
  foreach ($waypoints as $waypoint) {
    
    $x = $waypoint['x'] + $offset['left'];
    $y = $waypoint['y'] + $offset['top'];
    
    $radius = $waypoint['radius_pixel'];
    
    $diameter = 2 * $radius;
    imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color);
    imageellipse($img , $x , $y , $diameter , $diameter , $cylinder_border_color);
  }
  
  
  // Draw a line
  $line_colour = imagecolorallocate($img, 127, 127, 127);
  
  
  // Set line thickness
  imagesetthickness ($img, 1);
  
  $count = count($route_points);
  
  // There should be at least two points to draw a line
  if ($count >= 2) {
    // Draw optimized route
    for ($i = 0; $i < $count - 1; $i++ ) {
      $x0 = $route_points[$i]['x'] + $offset['left'];
      $y0 = $route_points[$i]['y'] + $offset['top'];
      $x1 = $route_points[$i+1]['x'] + $offset['left'];
      $y1 = $route_points[$i+1]['y'] + $offset['top'];
      imageline($img, $x0, $y0, $x1, $y1, $line_colour);
    }
  }
  
  
  // Deallocate colors
  imagecolordeallocate($img, $back);
  imagecolordeallocate($img, $cylinder_inner_color);
  imagecolordeallocate($img, $cylinder_border_color);
  imagecolordeallocate($img, $line_colour);
  
  
  // Save image
  imagepng($img, $path);
  
  return $path;
}




function at_helper_prepare_settings($race_id = NULL) {
  $settings = array(
    'canvas' => array(
      'width' => 500,
      'height' => 400,
    ),
    'waypoints' => array(
      array('lon' => 21.9237862, 'lat' => 43.324075, 'rad' => 1000),
      array('lon' => 22.0048972, 'lat' => 43.1310528, 'rad' => 1000),
      array('lon' => 21.9131333, 'lat' => 43.2568972, 'rad' => 1000),
    ),
    
     
     
     
    'offset' => array(
      'top' => 30,
      'bottom' => 30,
      'right' => 30,
      'left' => 30,
    ),
  );
  $settings['waypoints'] = at_helper_get_waypoints(3);
  
  return $settings;
}


function at_helper_get_waypoints($race_id) {
  $waypoints = array();
  $entities = entity_load(AIRTRIBUNE_RACE_ENTITY_TYPE, array($race_id));
  
  if (!empty($entities)) {
    $entity = array_shift($entities);
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity);
    
    $pg_racetype_entity = $wrapper->{AIRTRIBUNE_PG_RACETYPE_REF_FIELD}->value();
    $pg_racetype_wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACETYPE_ENTITY_TYPE, $pg_racetype_entity);
    
    $waypoint_entities = $pg_racetype_wrapper->{AIRTRIBUNE_PG_RACE_POINTS_FIELD}->value();
    //dsm($waypoint_entities);
    foreach ($waypoint_entities as $waypoint_entity) {
      //$waypoint_entity
      $waypoint_wrapper = entity_metadata_wrapper(AIRTRIBUNE_POINT_ENTITY_TYPE, $waypoint_entity);
      $waypoint_radius = $waypoint_wrapper->{AIRTRIBUNE_POINT_RADIUS_FIELD}->value();
      $point_entity = $waypoint_wrapper->{AIRTRIBUNE_POINT_REF_FIELD}->value();
      $point_wrapper = entity_metadata_wrapper(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, $point_entity);
      $location = $point_wrapper->{AIRTRIBUNE_POINT_LOCATION_FIELD}->value();
      $waypoints[] = array(
        'lon' => $location['lon'],
        'lat' => $location['lat'],
        'rad' => $waypoint_radius,
      );
    }
  }
  
  return $waypoints;
}


/**
 * Calculate optimized route
 * Return values in pixels
 */
function at_helper_settings_process(&$settings) {
  
  // Get canvas dimensions without offset.
  $offset = $settings['offset'];
  $canvas = $settings['canvas'];
  $canvas_used['width'] = $canvas['width'] - ($offset['right'] + $offset['left']);
  $canvas_used['height'] = $canvas['height'] - ($offset['top'] + $offset['bottom']);
  $settings['canvas_used'] = $canvas_used;
  
  // Coefficients to translate radius (distance) into coordinates.
  $d2coord = 360 / (40 * pow(10, 6));
  
  // Get optimized route points.
  $route_points = waypoint_get_optimized_waypoints($settings['waypoints']);
  $route_points = array_values($route_points);
  
  
  // TODO:
  // Convert radius for each point into lon/lat
  // Find dimensions of the frame in lon/lat
  // Find ratio pixel dimensions/coordinate dimensions
  
  
  // Get all points' coordinates for the frame.
  $frame_dim = array(
    'lon_min' => NULL,
    'lon_max' => NULL,
    'lat_min' => NULL,
    'lat_max' => NULL,
  );
  
  foreach ($settings['waypoints'] as $k => $v) {
    $radius = $settings['waypoints'][$k]['rad'];
    // Get radius in degrees
    $radius = $radius * $d2coord;
    $settings['waypoints'][$k]['radius_degree'] = $radius;
    
    $waypoint = $settings['waypoints'][$k];
    $waypoint += array(
      'lon_min' => $waypoint['lon'] - $radius,
      'lon_max' => $waypoint['lon'] + $radius,
      'lat_min' => $waypoint['lat'] - $radius,
      'lat_max' => $waypoint['lat'] + $radius,
    );
    
    // Get frame dimensions in coordinates
    foreach (array('lon_min', 'lon_max', 'lat_min', 'lat_max') as $key_name) {
      if (!isset($frame_dim[$key_name])) {
        $frame_dim[$key_name] = $waypoint[$key_name];
      }
      else {
        if (in_array($key_name, array('lon_min', 'lat_min')) && $frame_dim[$key_name] > $waypoint[$key_name]) {
          $frame_dim[$key_name] = $waypoint[$key_name];
        }
        elseif (in_array($key_name, array('lon_max', 'lat_max')) && $frame_dim[$key_name] < $waypoint[$key_name]) {
          $frame_dim[$key_name] = $waypoint[$key_name];
        }
      }
    }
    
    // TODO: Check semisphere
    
    
  }
  
  
  $pdeg = $canvas_used['width']/$canvas_used['height'] > ($frame_dim['lon_max'] - $frame_dim['lon_min'])/($frame_dim['lat_max'] - $frame_dim['lat_min'])
        ? $canvas_used['height'] / ($frame_dim['lat_max'] - $frame_dim['lat_min'])
        : $canvas_used['width'] / ($frame_dim['lon_max'] - $frame_dim['lon_min']);
  
  // Get pixels-for-degree ration for a given canvas_used and waypoints+radius
  /*
  $pixel_degree_ratio = array(
    'width' => $canvas_used['width'] / ($frame_dim['lon_max'] - $frame_dim['lon_min']),
    'height' => $canvas_used['height'] / ($frame_dim['lat_max'] - $frame_dim['lat_min']),
  );
  */
  // Convert lon/lat coordinates into pixel coordinates
  // Waypoints
  foreach ($settings['waypoints'] as $k => $v) {
    // Get coordinates relative to the frame boarders.
    $settings['waypoints'][$k]['x'] = round(($settings['waypoints'][$k]['lon'] - $frame_dim['lon_min']) * $pdeg);
    $settings['waypoints'][$k]['y'] = round(($settings['waypoints'][$k]['lat'] - $frame_dim['lat_min']) * $pdeg);
    $settings['waypoints'][$k]['radius_pixel'] = round($settings['waypoints'][$k]['radius_degree'] * $pdeg);
  }
  // Optimale Waypoints (routepoints)
  foreach ($route_points as $k => $v) {
    // Get coordinates relative to the frame boarders.
    $route_points[$k]['x'] = round(($route_points[$k]['lat'] - $frame_dim['lon_min']) * $pdeg);
    $route_points[$k]['y'] = round(($route_points[$k]['lon'] - $frame_dim['lat_min']) * $pdeg);
  }
  
  //$settings['pixel_degree_ratio'] = $pixel_degree_ratio;
  $settings['route_points'] = $route_points;
  
  //dsm($settings);
  
  return $settings;
}



function waypoint_get_optimized_waypoints($_allwp) {
  module_load_include('inc', 'waypoint', 'waypoint.class');
  $waypoints = array();
  $result = array();
  $startPosition = LatLon::fromDegrees($_allwp[1]['lon'], $_allwp[1]['lat']);
  foreach ($_allwp as $n => $wp) {
    if ($n != 1) {
      $waypoints[] = new Waypoint($n, $n, $_allwp[$n]['lon'], $_allwp[$n]['lat'], $_allwp[$n]['rad']);
    }
  }
  $calc = new ShortWayCalculator;
  $optimized_waypoints = $calc->calculateShortestWay($startPosition, $waypoints);
  $i = 1;
  foreach ($optimized_waypoints as $point) {
    $result[$i++] = array('lat' => $point->getLatitude()->getDegrees(), 'lon' => $point->getLongitude()->getDegrees());
  }
  return $result;
}

/**
 * Calculate distance between two waypoints
 * @return float
*/
function sd_abs($lon1, $lat1, $lon2, $lat2) {
  module_load_include('inc', 'waypoint', 'waypoint.class');
  //Return distance in km
  return ShortWayCalculator::distanceBetween($lon1, $lat1, $lon2, $lat2) / 1000;
}

/*
$waypoints_opt = waypoint_get_optimized_waypoints($waypoints_sort);

$distance = 0;
if ($waypoints_opt[$id -1]['lat'] == $waypoints_opt[$id]['lat'] && $waypoints_opt[$id -1]['lon'] == $waypoints_opt[$id]['lon']) {
  $distance += (int) abs($waypoints_sort[$id -1]['rad'] - $waypoints_sort[$id]['rad']);
} else {
  $distance += (int) 1000 * sd_abs($waypoints_opt[$id -1]['lat'], $waypoints_opt[$id -1]['lon'], $waypoints_opt[$id]['lat'], $waypoints_opt[$id]['lon']);
}
*/
