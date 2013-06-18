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
  $canvas_used['width'] = $canvas['width'] - ($offset['right'] + $offset['left']);
  $canvas_used['hight'] = $canvas['hight'] - ($offset['top'] + $offset['bottom']);
  
  $path = 'sites/default/files/my_new_image.png';
  
  // Create image
  $img = imagecreatetruecolor($canvas['width'], $canvas['hight']);
  
  // Draw canvas background
  $back = imagecolorallocate($img, 255, 255, 255);
  imagefilledrectangle($img, 0, 0, $canvas['width'] - 1, $canvas['hight'] - 1, $back);
  
  
  // Set circle inner and border colours
  $cylinder_inner_color = imagecolorallocatealpha ($img , 127 , 127 , 127 , 75);
  $cylinder_border_color = imagecolorallocate($img, 127, 127, 127);
  
  // Draw circles
  foreach ($waypoints as $waypoint) {
    $x = $waypoint['x'];
    $y = $waypoint['y'];
    $radius = $waypoint['rad'];
    $diameter = 2 * $radius;
    imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color);
    imageellipse($img , $x , $y , $diameter , $diameter , $cylinder_border_color);
  }
  
  
  // Draw a line
  $line_colour = imagecolorallocate($img, 127, 127, 127);
  
  
  // Set line thickness
  imagesetthickness ($img, 5);
  
  $count = count($route_points);
  //dsm($route_points);
  // There should be at least two points to draw a line
  if ($count >= 2) {
    // Draw optimized route
    for ($i = 0; $i < $count - 1; $i++ ) {
      imageline($img, $route_points[$i]['x'], $route_points[$i]['y'], $route_points[$i+1]['x'], $route_points[$i+1]['y'], $line_colour);
    }
  }
  
  
  // Deallocate colors
  imagecolordeallocate($back);
  imagecolordeallocate($cylinder_inner_color);
  imagecolordeallocate($cylinder_border_color);
  imagecolordeallocate($line_colour);
  
  
  // Save image
  imagepng($img, $path);
  
  return $path;
}




function at_helper_prepare_settings() {
  $settings = array(
    'canvas' => array(
      'width' => 500,
      'hight' => 400,
    ),
    'waypoints' => array(
      array('lon' => 50, 'lat' => 100, 'rad' => 30),
      array('lon' => 150, 'lat' => 150, 'rad' => 20),
      array('lon' => 350, 'lat' => 350, 'rad' => 20),
    ),
    'offset' => array(
      'top' => 10,
      'bottom' => 10,
      'right' => 10,
      'left' => 10,
    ),
  );
  
  return $settings;
}


/**
 * Calculate optimized route
 * Return values in pixels
 */
function at_helper_settings_process(&$settings) {
  
  $route_points = waypoint_get_optimized_waypoints($settings['waypoints']);
  $route_points = array_values($route_points);
  //dsm($route_points);
  foreach ($route_points as $k => $v) {
    $route_points[$k]['x'] = (integer) $route_points[$k]['lon'];
    $route_points[$k]['y'] = (integer) $route_points[$k]['lat'];
  }
  //dsm($route_points);
  
  // Optimized route points
  /*
  $route_points = array(
    array('x' => 10, 'y' => 150),
    array('x' => 100, 'y' => 160),
    array('x' => 310, 'y' => 350),
    array('x' => 20, 'y' => 320),
    array('x' => 200, 'y' => 50),
  );
  */
  
  
  
  
  foreach ($settings['waypoints'] as $k => $v) {
    $settings['waypoints'][$k]['x'] = $settings['waypoints'][$k]['lon'];
    $settings['waypoints'][$k]['y'] = $settings['waypoints'][$k]['lat'];
  }
  
  
  
  $settings['route_points'] = $route_points;
  return $settings;
}

/**
 * Check if we need to redraw current image.
 * 
 */
/*
function at_helper_image_exists($etid) {
  // Load task for $etid
  $entities = entity_load(AIRTRIBUNE_RACE_ENTITY_TYPE, array($etid));
  if (!empty($entities)) {
    $entity = array_shift($entities);
  }
  else {
    return;
  }
}
*/



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

$waypoints_opt = waypoint_get_optimized_waypoints($waypoints_sort);

$distance = 0;
if ($waypoints_opt[$id -1]['lat'] == $waypoints_opt[$id]['lat'] && $waypoints_opt[$id -1]['lon'] == $waypoints_opt[$id]['lon']) {
  $distance += (int) abs($waypoints_sort[$id -1]['rad'] - $waypoints_sort[$id]['rad']);
} else {
  $distance += (int) 1000 * sd_abs($waypoints_opt[$id -1]['lat'], $waypoints_opt[$id -1]['lon'], $waypoints_opt[$id]['lat'], $waypoints_opt[$id]['lon']);
}
