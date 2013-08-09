<?php

define('PG_RACE_TILES_PERMISSIONS_MODE', 0775);
define('AT_DRAW_PIXELS_PER_TILE', 256);

// Get image settings
function _at_draw_settings() {
  $settings = array(
    'canvas' => array(
      'width' => 320,
      'height' => 210,
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

// Central function. Get image path.
function _at_draw_image_path($race_id) {
  $settings = _at_draw_settings();
  
  // Check if preview image already exists
  $files_path = variable_get('file_public_path', conf_path() . '/files');
  $files_path .= '/pg_race_preview';
  if (!file_exists($files_path)) {
    mkdir($files_path);
    chmod($files_path, PG_RACE_TILES_PERMISSIONS_MODE);
  }
  $path = $files_path . "/pg_race_{$race_id}.png";
  if (file_exists($path)) {
    return $path;
  }
  
  
  // Get waypoints
  $waypoints = _at_draw_get_waypoints($race_id);
  if(empty($waypoints)) {
    return NULL;
  }
  
  // Get routepoints
  $routepoints = _at_draw_get_routepoints($waypoints);
  
  // Get projection_box (min and max edges in projection coordinates)
  $projection_box = _at_draw_projection_box($routepoints);
  
  // Get canvas_used
  $canvas_used = _at_draw_canvas_used($settings);
  
  // Get optimal zoom, zoom_box, ratio and center (projection_box for the given zoom value)
  $zoom_box = _at_draw_get_zoom_box($projection_box, $canvas_used);
  
  // Get canvas_box
  $canvas_box = _at_draw_get_canvas_box($settings, $canvas_used, $zoom_box);
  
  // Get final image resource
  $img = _at_draw_image_resource($settings, $waypoints, $routepoints, $canvas_box, $zoom_box);
  
  // Save image
  imagepng($img, $path);
  chmod($path, PG_RACE_TILES_PERMISSIONS_MODE);
  
  return $path;
}



// Get waypoints by race id
function _at_draw_get_waypoints($race_id) {
  $entities = entity_load(AIRTRIBUNE_RACE_ENTITY_TYPE, array($race_id));
  
  if (!empty($entities)) {
    $entity = array_shift($entities);
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity);
    
    $pg_racetype_entity = $wrapper->{AIRTRIBUNE_PG_RACETYPE_REF_FIELD}->value();
    
    if (empty($pg_racetype_entity) || !isset($pg_racetype_entity->{AIRTRIBUNE_PG_RACE_POINTS_FIELD}) || $pg_racetype_entity->type == 'pg_racetype_od') {
      return;
    }
    $pg_racetype_wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACETYPE_ENTITY_TYPE, $pg_racetype_entity);
    
    $waypoint_entities = $pg_racetype_wrapper->{AIRTRIBUNE_PG_RACE_POINTS_FIELD}->value();
    foreach ($waypoint_entities as $waypoint_entity) {
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

// Get routepoints
function _at_draw_get_routepoints($waypoints) {
  module_load_include('inc', 'pg_race', 'pg_race.class');
  $routepoints = array();
  
  $sw = new geoShortWayCalc();
  $routepoints_structs = $sw->calculateShortestWay($waypoints);
  
  foreach ($routepoints_structs as $struct) {
    $routepoints[] = $struct->approximationPoint;
  }
  
  return $routepoints;
}

// Get projection_box (min and max edges in projection coordinates)
function _at_draw_projection_box($routepoints) {
  // Rest index
  $routepoints = array_values($routepoints);
  foreach ($routepoints as $k => $routepoint) {
    $x = $routepoint['x'];
    $y = $routepoint['y'];
    
    $x_min = $k != 0 ? min($x_min, $x) : $x;
    $x_max = $k != 0 ? max($x_max, $x) : $x;
    $y_min = $k != 0 ? min($y_min, $y) : $y;
    $y_max = $k != 0 ? max($y_max, $y) : $y;
  }
  $projection_box = array(
    'x_min'   => $x_min,
    'x_max'   => $x_max,
    'y_min'   => $y_min,
    'y_max'   => $y_max,
    'width'   => $x_max - $x_min,
    'height'  => $y_max - $y_min,
  );
  return $projection_box;
}

// Get canvas_used
function _at_draw_canvas_used($settings) {
  $canvas = $settings['canvas'];
  $offset = $settings['offset'];
  $canvas_used['width'] = $canvas['width'] - ($offset['right'] + $offset['left']);
  $canvas_used['height'] = $canvas['height'] - ($offset['top'] + $offset['bottom']);
  return $canvas_used;
}

// Get optimal zoom, zoom_box, ratio and center (projection_box for the given zoom value)
function _at_draw_get_zoom_box($projection_box, $canvas_used) {
  $zoom_min = 8;
  $zoom_boxes = array();
  $zoom_optimal = $zoom_min - 1;
  
  do {
    $zoom_optimal ++;
    $pow = pow(2, $zoom_optimal);
    foreach (array('x_min', 'x_max', 'y_min', 'y_max') as $key) {
      $zoom_box[$key] = $projection_box[$key] * $pow;
    }
    
    $zoom_box['width']   = floor($projection_box['width'] * $pow * AT_DRAW_PIXELS_PER_TILE);
    $zoom_box['height']  = floor($projection_box['height'] * $pow * AT_DRAW_PIXELS_PER_TILE);
    $zoom_boxes[$zoom_optimal] = $zoom_box;
  } while ($zoom_box['width'] <= $canvas_used['width'] && $zoom_box['height'] <= $canvas_used['height']);
  
  // Roll back last increament.
  // Since we need $zoom_optimal+1, this line is commented.
  // $zoom_optimal --;
  
  // Return zoom_box for optimal zoom value.
  $zoom_box = $zoom_boxes[$zoom_optimal];
  $zoom_box['zoom'] = $zoom_optimal;
  
  // Get ratio canvas_used/zoom_box
  $zoom_box['ratio'] = min($canvas_used['width'] / $zoom_box['width'], $canvas_used['height'] / $zoom_box['height']);
  
  // Get zoom_box center (zoom_box central point coordinates)
  $zoom_box['center'] = array(
    'x' => ($zoom_box['x_min'] + $zoom_box['x_max']) / 2,
    'y' => ($zoom_box['y_min'] + $zoom_box['y_max']) / 2,
  );
  return $zoom_box;
}

// Get canvas_box
function _at_draw_get_canvas_box($settings, $canvas_used, $zoom_box) {
  $canvas = $settings['canvas'];
  $offset = $settings['offset'];
  $ratio = $zoom_box['ratio'];
  
  // Get canvas center
  $center = array(
    'x' => $canvas_used['width'] / 2 + $offset['left'],
    'y' => $canvas_used['height'] / 2 + $offset['top'],
  );
  
  $canvas_box['zoom_projection'] = array(
    'x_min'   => $zoom_box['center']['x'] - $center['x'] / $ratio / AT_DRAW_PIXELS_PER_TILE,
    'x_max'   => $zoom_box['center']['x'] + ($canvas['width'] - $center['x']) / $ratio / AT_DRAW_PIXELS_PER_TILE,
    'y_min'   => $zoom_box['center']['y'] - $center['y'] / $ratio / AT_DRAW_PIXELS_PER_TILE,
    'y_max'   => $zoom_box['center']['y'] + ($canvas['height'] - $center['y']) / $ratio / AT_DRAW_PIXELS_PER_TILE,
  );
  
  return $canvas_box;
}

// Get final image resource
function _at_draw_image_resource($settings, $waypoints, $routepoints, $canvas_box, $zoom_box) {
  $canvas = $settings['canvas'];
  
  // Create image
  $img = imagecreatetruecolor($canvas['width'], $canvas['height']);
  
  // Attach background from GMap tiles
  _at_draw_attach_gmap_background($img, $settings, $canvas_box, $zoom_box);
  imageantialias($img, TRUE);
  
  // Draw waypoints
  _at_draw_draw_waypoints($img, $waypoints, $canvas_box, $zoom_box);
  
  // Draw routepoints
  _at_draw_draw_routepoints($img, $routepoints, $canvas_box, $zoom_box);
  
  return $img;
}

// Attach background from GMap tiles
function _at_draw_attach_gmap_background(&$img, $settings, $canvas_box, $zoom_box) {
  $canvas = $settings['canvas'];
  $zoom = $zoom_box['zoom'];
  
  $xtile_min = floor($canvas_box['zoom_projection']['x_min']);
  $xtile_max = floor($canvas_box['zoom_projection']['x_max']);
  $ytile_min = floor($canvas_box['zoom_projection']['y_min']);
  $ytile_max = floor($canvas_box['zoom_projection']['y_max']);
  
  // Prepare temporary resource for tiles initial background
  $img_tiles = imagecreatetruecolor(($xtile_max - $xtile_min + 1) * AT_DRAW_PIXELS_PER_TILE, ($ytile_max - $ytile_min + 1) * AT_DRAW_PIXELS_PER_TILE);
  
  
  
  // Get GMap tiles
  for ($i = $xtile_min; $i <= $xtile_max; $i++) {
    for ($j = $ytile_min; $j <= $ytile_max; $j++) {
      // New tile path
      $files_path = variable_get('file_public_path', conf_path() . '/files');
      $files_path .= '/pg_race_preview';
      if (!file_exists($files_path)) {
        mkdir($files_path);
        chmod($files_path, PG_RACE_TILES_PERMISSIONS_MODE);
      }
      $files_path .= '/tiles';
      if (!file_exists($files_path)) {
        mkdir($files_path);
        chmod($files_path, PG_RACE_TILES_PERMISSIONS_MODE);
      }
      
      // TODO: Add filetype detection
      //$path = $files_path . "/tile_x{$xtile}_y{$ytile}_z{$zoom}.jpg";
      $path = $files_path . "/tile_x{$i}_y{$j}_z{$zoom}.png";
      
      // Download tile if it doesn't exist.
      if (!file_exists ($path)) {
        _at_draw_download_gmap_tile($i, $j, $zoom, $path);
      }
      
      $tile_img = imagecreatefrompng($path);
      
      // TODO: Check source and destination coordinates (why not -1)
      imagecopy($img_tiles, $tile_img, ($i-$xtile_min)*AT_DRAW_PIXELS_PER_TILE, ($j-$ytile_min)*AT_DRAW_PIXELS_PER_TILE, 0, 0, AT_DRAW_PIXELS_PER_TILE, AT_DRAW_PIXELS_PER_TILE);
    }
  }
  
  // Copy resampled image.
  $src_image = $img_tiles;
  $dst_x = 0;
  $dst_y = 0;
  
  $src_x = floor(($canvas_box['zoom_projection']['x_min'] - $xtile_min) * AT_DRAW_PIXELS_PER_TILE);
  $src_y = floor(($canvas_box['zoom_projection']['y_min'] - $ytile_min) * AT_DRAW_PIXELS_PER_TILE);
  
  $dst_w = $canvas['width'];
  $dst_h = $canvas['height'];
  
  $src_w = floor(($canvas_box['zoom_projection']['x_max'] - $canvas_box['zoom_projection']['x_min']) * AT_DRAW_PIXELS_PER_TILE);
  $src_h = floor(($canvas_box['zoom_projection']['y_max'] - $canvas_box['zoom_projection']['y_min']) * AT_DRAW_PIXELS_PER_TILE);
  
  imagecopyresampled($img, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h);
}

// Draw routepoints
function _at_draw_draw_routepoints(&$img, $routepoints, $canvas_box, $zoom_box) {
  $zoom = $zoom_box['zoom'];
  $ratio = $zoom_box['ratio'];
  $count = count($routepoints);
  
  // There should be at least two points to draw a line
  if ($count >= 2) {
    $pow = pow(2, $zoom);
    $canvas_routepoints = array();
    foreach ($routepoints as $routepoint) {
      $canvas_routepoints[] = array(
        'x' => floor(($routepoint['x'] * $pow - $canvas_box['zoom_projection']['x_min']) * AT_DRAW_PIXELS_PER_TILE * $ratio),
        'y' => floor(($routepoint['y'] * $pow - $canvas_box['zoom_projection']['y_min']) * AT_DRAW_PIXELS_PER_TILE * $ratio),
      );
    }
    
    // Draw optimized route
    $line_colour = imagecolorallocate($img, 51, 51, 51);  // #333333
    for ($i = 0; $i < $count - 1; $i++ ) {
      $p0 = $canvas_routepoints[$i];
      $p1 = $canvas_routepoints[$i+1];
      $x0 = $p0['x'];
      $y0 = $p0['y'];
      $x1 = $p1['x'];
      $y1 = $p1['y'];
      imageline($img, $x0, $y0, $x1, $y1, $line_colour);
      
      
      // Draw line arrows
      $line_length = round(abs(sqrt(($x1-$x0)*($x1-$x0) + ($y1-$y0)*($y1-$y0))));
      // Draw arrows only if length is greater than 100px.
      if ($line_length > 70) {
        $x_m = round(abs(($x1 + $x0) / 2));
        $y_m = round(abs(($y1 + $y0) / 2));
        $arrow_length = 10;  // px
        
        $atan = atan(($y1 - $y0)/($x1 - $x0));
        $k = min(0, ($x1 - $x0)/abs($x1 - $x0));
        $k = abs($k);
        
        $a1 = $atan + 5/6 * M_PI + $k * M_PI;
        $a2 = $atan - 5/6 * M_PI + $k * M_PI;
        
        $d1 = array(
          'x' => round($arrow_length * cos($a1)),
          'y' => round($arrow_length * sin($a1)),
        );
        
        $d2 = array(
          'x' => round($arrow_length * cos($a2)),
          'y' => round($arrow_length * sin($a2)),
        );
        
        //imageline($img, $x_m, $y_m, $x_m + $d1['x'], $y_m + $d1['y'], $line_colour);
        //imageline($img, $x_m, $y_m, $x_m + $d2['x'], $y_m + $d2['y'], $line_colour);
        
        $points = array(
          $x_m, $y_m,
          $x_m + $d1['x'], $y_m + $d1['y'],
          $x_m + $d2['x'], $y_m + $d2['y'],
        );
        
        // Set line thickness
        imagesetthickness ($img, 1);
        imagefilledpolygon($img , $points , 3 , $line_colour);
        
      }
    }
    imagecolordeallocate($img, $line_colour);
  }
}

// Draw waypoints
function _at_draw_draw_waypoints(&$img, $waypoints, $canvas_box, $zoom_box) {
  $zoom = $zoom_box['zoom'];
  $ratio = $zoom_box['ratio'];
  
  // Set circle inner and border colours
  $cylinder_inner_color = imagecolorallocatealpha ($img , 142 , 142 , 142 , 70); // #8e8e8e
  $cylinder_border_color = imagecolorallocate($img, 51, 51, 51); // #333333
  $cylinder_inner_color_start = imagecolorallocatealpha ($img, 142, 217, 12, 70);  // #8ed90c
  $cylinder_inner_color_finish = imagecolorallocatealpha ($img, 186, 7, 192, 70);  // #ba07d4
  
  $pow = pow(2, $zoom);
  
  $count = count($waypoints);
  foreach ($waypoints as $k => $waypoint) {
    $wp = new geoWaypoint($waypoint['lon'], $waypoint['lat'], $waypoint['rad']);
    
    
    $p = $wp->getProjCoords();
    $r = $wp->getProjRadius();
    
    $x = floor(($p['x'] * $pow - $canvas_box['zoom_projection']['x_min']) * AT_DRAW_PIXELS_PER_TILE * $ratio);
    $y = floor(($p['y'] * $pow - $canvas_box['zoom_projection']['y_min']) * AT_DRAW_PIXELS_PER_TILE * $ratio);
    $diameter = 2 * floor($r * $pow * AT_DRAW_PIXELS_PER_TILE * $ratio);
    
    switch ($k) {
      case 1 :
        imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color_start);
        break;
      case $count-1 :
        imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color_finish);
        break;
      default :
        imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color);
        break;
    }
    imageellipse($img , $x , $y , $diameter , $diameter , $cylinder_border_color);
  }
  
  imagecolordeallocate($img, $cylinder_inner_color);
  imagecolordeallocate($img, $cylinder_border_color);
  imagecolordeallocate($img, $cylinder_inner_color_start);
  imagecolordeallocate($img, $cylinder_inner_color_finish);
}


// Download GMap tile
function _at_draw_download_gmap_tile($i, $j, $zoom, $new_path) {
  $url = 'http://mts0.google.com/vt/lyrs=m@223000000&hl=en&src=app&x=' . $i . '&y=' . $j . '&z=' . $zoom . '&s=';
  
  // http://stackoverflow.com/questions/2440729/php-curl-how-can-i-emulate-a-get-request-exactly-like-a-web-browser
  $agent= 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.0.3705; .NET CLR 1.1.4322)';
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  curl_setopt($ch, CURLOPT_VERBOSE, true);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_USERAGENT, $agent);
  curl_setopt($ch, CURLOPT_URL,$url);
  $result=curl_exec($ch);
  file_put_contents($new_path, $result);
  chmod($new_path, PG_RACE_TILES_PERMISSIONS_MODE);
  //return $path;
}
