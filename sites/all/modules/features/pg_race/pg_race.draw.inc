<?php

define('PG_RACE_TILES_PERMISSIONS_MODE', 0777);
define('AT_DRAW_PIXELS_PER_TILE', 256);


function _at_draw_settings() {
  // TODO: Set settings in extra fields settings
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
    'zoom' => 12,
    //'zoom' => 11,
    //https://mts1.google.com/vt/lyrs=t@131,r@223000000&hl=en&src=app&x=1149&y=734&z=11&s=Galil - z11
  );
  
  return $settings;
}



function _at_draw_get_image($race_id) {
  // TODO: Check if file exists.
  
  $settings = _at_draw_settings();
  $canvas = $settings['canvas'];
  $offset = $settings['offset'];
  $canvas_used['width'] = $canvas['width'] - ($offset['right'] + $offset['left']);
  $canvas_used['height'] = $canvas['height'] - ($offset['top'] + $offset['bottom']);
  $settings['canvas_used'] = $canvas_used;
  $settings['race_id'] = $race_id;
  
  // Get waypoints
  $waypoints = _at_draw_get_waypoints($race_id);
  
  if (empty($waypoints)) {
    return;
  }
  
  // Get routepoints
  $routepoints = waypoint_get_optimized_waypoints($waypoints);
  // TODO: There is a bug in optimal poins: lon and lat changed places
  foreach ($routepoints as $k => $v) {
    $tmp = $routepoints[$k]['lon'];
    $routepoints[$k]['lon'] = $routepoints[$k]['lat'];
    $routepoints[$k]['lat'] = $tmp;
    unset($tmp);
  }
  
  // Box that should contain all waipoints with their radiuses
  $box = array(
    'lon_min' => NULL,
    'lon_max' => NULL,
    'lat_min' => NULL,
    'lat_max' => NULL,
  );
  
  
  foreach ($routepoints as $k => $routepoint) {
    $routepoint['lon_min'] = $routepoint['lon_max'] = $routepoint['lon'];
    $routepoint['lat_min'] = $routepoint['lat_max'] = $routepoint['lat'];
    // Get box dimensions in coordinates
    foreach (array('lon_min', 'lon_max', 'lat_min', 'lat_max') as $key_name) {
      if (!isset($box[$key_name])) {
        $box[$key_name] = $routepoint[$key_name];
      }
      else {
        if (in_array($key_name, array('lon_min', 'lat_min')) && $box[$key_name] > $routepoint[$key_name]) {
          $box[$key_name] = $routepoint[$key_name];
        }
        elseif (in_array($key_name, array('lon_max', 'lat_max')) && $box[$key_name] < $routepoint[$key_name]) {
          $box[$key_name] = $routepoint[$key_name];
        }
      }
    }
  }
  
  
  $settings['waypoints'] = $waypoints;
  $settings['routepoints'] = $routepoints;
  $settings['box'] = $box;
  
  
  $path = _at_draw_draw_gmap($settings);
  return $path;
}


// TODO: Check semisphere if needed



function _at_draw_get_waypoints($race_id) {
  $waypoints = array(0 => NULL);
  $entities = entity_load(AIRTRIBUNE_RACE_ENTITY_TYPE, array($race_id));
  
  if (!empty($entities)) {
    $entity = array_shift($entities);
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity);
    
    $pg_racetype_entity = $wrapper->{AIRTRIBUNE_PG_RACETYPE_REF_FIELD}->value();
    
    if (empty($pg_racetype_entity) || !isset($pg_racetype_entity->{AIRTRIBUNE_PG_RACE_POINTS_FIELD})) {
      return;
    }
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
  
  unset($waypoints[0]);
  return $waypoints;
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

/* ============================================================================================= */


function _at_draw_get_tiles($zoom_box) {
  
  $edges = $zoom_box['edges'];
  $corners = $zoom_box['corners'];
  $extra_tiles = $zoom_box['extended']['extra_tiles'];
  $zoom = $zoom_box['zoom'];
  
  // Get zoom_box edge tiles (extended)
  
  // TODO: Check Semisphere bug
  $xtile_min = $corners[$edges['left']]['xtile'] - $extra_tiles['left'];
  $xtile_max = $corners[$edges['right']]['xtile'] + $extra_tiles['right'];
  $ytile_min = $corners[$edges['top']]['ytile'] - $extra_tiles['top'];
  $ytile_max = $corners[$edges['bottom']]['ytile'] + $extra_tiles['bottom'];
  //$ytile_max = $corners[$edges['top']]['ytile'] - $extra_tiles['top'];
  //$ytile_min = $corners[$edges['bottom']]['ytile'] + $extra_tiles['bottom'];
  
  // Create image
  $xtile_count = $xtile_max - $xtile_min + 1;
  $ytile_count = $ytile_max - $ytile_min + 1;
  $img_tiles = imagecreatetruecolor($xtile_count * AT_DRAW_PIXELS_PER_TILE, $ytile_count * AT_DRAW_PIXELS_PER_TILE);
  
  $x_dst = 0;
  $y_dst = 0;
  for ($xtile = $xtile_min; $xtile <= $xtile_max; $xtile++) {
    for ($ytile = $ytile_min; $ytile <= $ytile_max; $ytile++) {
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
      $path = $files_path . "/tile_x{$xtile}_y{$ytile}_z{$zoom}.png";
      
      
      // Check if file exists.
      if (!file_exists ($path)) {
        // TODO: Move into settings
        //$url = 'http://mts0.google.com/vt/lyrs=t@131,r@221010232&hl=x-local&src=app&x=' . $xtile . '&y=' . $ytile . '&z=' . $zoom . '&s=G';  // terrain, zoom 12
        $url = 'http://mts0.google.com/vt/lyrs=m@223000000&hl=en&src=app&x=' . $xtile . '&y=' . $ytile . '&z=' . $zoom . '&s=';  // normal, zoom 12
        //$url = 'http://mts1.google.com/vt/lyrs=t@131,r@223000000&hl=en&src=app&x=' . $xtile . '&y=' . $ytile . '&z=' . $zoom . '&s=Galil'; // terrain, zoom 10
        
        // http://stackoverflow.com/questions/2440729/php-curl-how-can-i-emulate-a-get-request-exactly-like-a-web-browser
        $agent= 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.0.3705; .NET CLR 1.1.4322)';
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_VERBOSE, true);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_USERAGENT, $agent);
        curl_setopt($ch, CURLOPT_URL,$url);
        $result=curl_exec($ch);
        file_put_contents($path, $result);
        chmod($path, PG_RACE_TILES_PERMISSIONS_MODE);
      }
      
      // Tile image
      //$tile_img = imagecreatefromjpeg($path);
      $tile_img = imagecreatefrompng($path);
      // TODO: Check source and destination coordinates (why not -1)
      imagecopy ($img_tiles, $tile_img, $x_dst, $y_dst, 0, 0, AT_DRAW_PIXELS_PER_TILE, AT_DRAW_PIXELS_PER_TILE);
      $y_dst += AT_DRAW_PIXELS_PER_TILE;
    }
    $y_dst = 0;
    $x_dst += AT_DRAW_PIXELS_PER_TILE;
  }
  
  // TODO: Comment 3 lines
  $path_tiles = 'sites/default/files/tiles_image' . rand(1, 10) . '.png';
  imagepng($img_tiles, $path_tiles);
  chmod($path_tiles, PG_RACE_TILES_PERMISSIONS_MODE);
  
  return $img_tiles;
}

function _at_draw_draw_gmap($settings) {
  
  $canvas = $settings['canvas'];
  $canvas_used = $settings['canvas_used'];
  $offset = $settings['offset'];
  
  
  $files_path = variable_get('file_public_path', conf_path() . '/files');
  $files_path .= '/pg_race_preview';
  if (!file_exists($files_path)) {
    mkdir($files_path);
    chmod($files_path, PG_RACE_TILES_PERMISSIONS_MODE);
  }
  $path = $files_path . "/pg_race_{$settings['race_id']}.png";
  
  if (file_exists($path)) {
    return $path;
  }
  
  
  // Create image
  $img = imagecreatetruecolor($canvas['width'], $canvas['height']);
  
  
  
  $zoom_box = _at_draw_get_gmap($settings);
  
  
  $img_tiles = _at_draw_get_tiles($zoom_box);
  
  
  $extra_tiles = $zoom_box['extended']['extra_tiles'];
  $centre = $zoom_box['centre'];
  $corners = $zoom_box['corners'];
  $edges = $zoom_box['edges'];
  $ratio = $zoom_box['ratio'];
  
  // Get zoom_box edge tiles
  $xtile_min = $corners[$edges['left']]['xtile'];
  $xtile_max = $corners[$edges['right']]['xtile'];
  $ytile_min = $corners[$edges['top']]['ytile'];
  $ytile_max = $corners[$edges['bottom']]['ytile'];
  
  
   
  // Copy resampled image.
  
  $dst_image = $img;
  $src_image = $img_tiles;
  $dst_x = 0;
  $dst_y = 0;
  
  
  // TODO: Check $src_x + $src_w (Same for $src_y)
  // TODO: Check ceil. Expecially for case $ratio = 1
  $src_x = $centre['xPixel'] + ($centre['xtile'] - $xtile_min + $extra_tiles['left']) * AT_DRAW_PIXELS_PER_TILE - ceil(($canvas_used['width'] + $offset['left'])/2/$ratio);
  $src_y = $centre['yPixel'] + ($centre['ytile'] - $ytile_min + $extra_tiles['top']) * AT_DRAW_PIXELS_PER_TILE - ceil(($canvas_used['height'] + $offset['top'])/2/$ratio);
  // TODO: Check -1 for $dst_w and $dst_h
  $dst_w = $canvas['width'];
  $dst_h = $canvas['height'];
  $src_w = $canvas['width'] / $ratio;
  $src_h = $canvas['height'] / $ratio;
  
  imagecopyresampled($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h);
  
  $zoom_box['resampling'] = array(
    'src_x' => $src_x,
    'src_y' => $src_y,
  );
  
  $settings['zoom_box'] = $zoom_box;
  
  imageantialias($img, TRUE);
  // Draw Routepoints
  _at_draw_draw_routepoints($img, $settings);
  // Draw Waypoints
  _at_draw_draw_waypoints($img, $settings);
  
  // Save image
  imagepng($img, $path);
  chmod($path, PG_RACE_TILES_PERMISSIONS_MODE);
  
  return $path;
}

function _at_draw_get_canvas_coords($zoom_box, $point) {
  // TODO: Add static cache
  
  $zoom = $zoom_box['zoom'];
  $corners = $zoom_box['corners'];
  $edges = $zoom_box['edges'];
  $ratio = $zoom_box['ratio'];
  $centre = $zoom_box['centre'];
  $extra_tiles = $zoom_box['extended']['extra_tiles'];
  $resampling = $zoom_box['resampling'];
  
  
  $lon = $point['lon'];
  $lat = $point['lat'];
  
  $tile_num = _at_draw_coord_to_gmap_tile($lat, $lon, $zoom);
  $xtile = $tile_num['x'];
  $ytile = $tile_num['y'];
  
  $tile_pixel_coords = _at_draw_coord_to_gmap_tile_pixels($tile_num);
  $xPixel = $tile_pixel_coords['x'];
  $yPixel = $tile_pixel_coords['y'];
  
  $xtile = floor($xtile);
  $ytile = floor($ytile);
  
  // Taken from _at_draw_draw_gmap().
  $src_x = $resampling['src_x'];
  $src_y = $resampling['src_y'];
  
  $xtile_min = $corners[$edges['left']]['xtile'];
  $ytile_min = $corners[$edges['top']]['ytile'];
  
  $coords = array(
    'x' => floor(($xPixel + ($xtile - $xtile_min + $extra_tiles['left']) * AT_DRAW_PIXELS_PER_TILE - $src_x) * $ratio),
    'y' => floor(($yPixel + ($ytile - $ytile_min + $extra_tiles['top']) * AT_DRAW_PIXELS_PER_TILE - $src_y) * $ratio),
  );
  
  return $coords;
}


function _at_draw_draw_waypoints(&$img, $settings) {
  
  $zoom_box = $settings['zoom_box'];
  $waypoints = $settings['waypoints'];
  
  // Set circle inner and border colours
  $cylinder_inner_color = imagecolorallocatealpha ($img , 142 , 142 , 142 , 70); // #8e8e8e
  $cylinder_border_color = imagecolorallocate($img, 51, 51, 51); // #333333
  $cylinder_inner_color_start = imagecolorallocatealpha ($img, 142, 217, 12, 70);  // #8ed90c
  $cylinder_inner_color_finish = imagecolorallocatealpha ($img, 186, 7, 192, 70);  // #ba07d4
  
  
  
  $count = count($waypoints);
  
  // Draw circles
  foreach ($waypoints as $k => $waypoint) {
    $p = _at_draw_get_canvas_coords($zoom_box, $waypoint);
    
    // http://stackoverflow.com/questions/1253499/simple-calculations-for-working-with-lat-lon-km-distance
    //$d2lon = (1 / 1000) / (111.320 * cos($waypoint['lat']));
    $d2lat = (1 / 1000) / 110.54; // 1 deg = 110.54 km
    $rad = array(
      'lon' => $waypoint['lon'],
      'lat' => $waypoint['lat'] + $waypoint['rad'] * $d2lat,
    );
    $r = _at_draw_get_canvas_coords($zoom_box, $rad);
    
    $radius = abs($p['y'] - $r['y']);
    $diameter = 2 * $radius;
    
    $x = $p['x'];
    $y = $p['y'];
    
    switch ($k) {
      case 2 :
        imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color_start);
        break;
      case $count :
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




// TEMP FUNCTION
function _at_draw_coords_tmp($settings, $p) {
      $zoom_box = $settings['zoom_box'];
      $resampling = $zoom_box['resampling'];
      $corners = $zoom_box['corners'];
      $edges = $zoom_box['edges'];
      $extra_tiles = $zoom_box['extended']['extra_tiles'];
      $ratio = $zoom_box['ratio'];
      
      $xtile_min = $corners[$edges['left']]['xtile'];
      $ytile_min = $corners[$edges['top']]['ytile'];
      
      // Taken from _at_draw_draw_gmap().
      $src_x = $resampling['src_x'];
      $src_y = $resampling['src_y'];
      
      $xtile = floor($p['x']);
      $ytile = floor($p['y']);
      
      //xPixel
      //xPixel
      //xtile
      $xPixel = round(($p['x'] - $xtile) * AT_DRAW_PIXELS_PER_TILE);
      $yPixel = round(($p['y'] - $ytile) * AT_DRAW_PIXELS_PER_TILE);
      
      $coords = array(
        'x' => floor(($xPixel + ($xtile - $xtile_min + $extra_tiles['left']) * AT_DRAW_PIXELS_PER_TILE - $src_x) * $ratio),
        'y' => floor(($yPixel + ($ytile - $ytile_min + $extra_tiles['top']) * AT_DRAW_PIXELS_PER_TILE - $src_y) * $ratio),
      );
      
      return $coords;
/*
  $zoom = $zoom_box['zoom'];
  $corners = $zoom_box['corners'];
  $edges = $zoom_box['edges'];
  $ratio = $zoom_box['ratio'];
  $centre = $zoom_box['centre'];
  $extra_tiles = $zoom_box['extended']['extra_tiles'];
  $resampling = $zoom_box['resampling'];
  
  
  $lon = $point['lon'];
  $lat = $point['lat'];
  
  $tile_num = _at_draw_coord_to_gmap_tile($lat, $lon, $zoom);
  $xtile = $tile_num['x'];
  $ytile = $tile_num['y'];
  
  $tile_pixel_coords = _at_draw_coord_to_gmap_tile_pixels($tile_num);
  $xPixel = $tile_pixel_coords['x'];
  $yPixel = $tile_pixel_coords['y'];
  
  $xtile = floor($xtile);
  $ytile = floor($ytile);
  
  // Taken from _at_draw_draw_gmap().
  $src_x = $resampling['src_x'];
  $src_y = $resampling['src_y'];
  
  $xtile_min = $corners[$edges['left']]['xtile'];
  $ytile_min = $corners[$edges['top']]['ytile'];
  
  $coords = array(
    'x' => floor(($xPixel + ($xtile - $xtile_min + $extra_tiles['left']) * AT_DRAW_PIXELS_PER_TILE - $src_x) * $ratio),
    'y' => floor(($yPixel + ($ytile - $ytile_min + $extra_tiles['top']) * AT_DRAW_PIXELS_PER_TILE - $src_y) * $ratio),
  );
*/
}



// TEMP FUNCTION
function _at_draw_rt_tmp(&$img, $settings) {
  module_load_include('inc', 'pg_race', 'pg_race.class');
  
  $zoom_box = $settings['zoom_box'];
  $zoom = $zoom_box['zoom'];
  $waypoints = $settings['waypoints'];
  $routepoints = $settings['routepoints'];
  foreach ($routepoints as $k => $routepoint) {
    $routepoints[$k] += _at_draw_coord_to_gmap_tile($routepoint['lat'], $routepoint['lon'], $zoom);
  }
  
  $sw = new geoShortWayCalc();
  $res = $sw->calculateShortestWay($waypoints, $zoom);
  
  $routepoints_new = array();
  foreach($res as $k => $v) {
    $routepoints_new[] = $v->approximationPoint;
  }
  
  //dsm(' . . . . . .');
  
  
  $count = count($routepoints_new);
  if (count($routepoints_new) >= 2) {
    $new_line_colour = imagecolorallocate($img, 255, 0, 0);
    
    //
    for ($i = 0; $i < $count - 1; $i++ ) {
      //$p0 = $routepoints_new[$i];
      //$p1 = $routepoints_new[$i+1];
      $p0 = _at_draw_coords_tmp($settings, $routepoints_new[$i]);
      $p1 = _at_draw_coords_tmp($settings, $routepoints_new[$i+1]);
      
      
      $x0 = $p0['x'];
      $y0 = $p0['y'];
      $x1 = $p1['x'];
      $y1 = $p1['y'];
      
      // Set line thickness
      imagesetthickness ($img, 2);
      imageline($img, $x0, $y0, $x1, $y1, $new_line_colour);
      
    }
    
    imagecolordeallocate($img, $new_line_colour);
  }
}

// TODO:
function _at_draw_draw_routepoints(&$img, $settings) {
  
  //_at_draw_rt_tmp($img, $settings);
  
  $zoom_box = $settings['zoom_box'];
  
  
  // NOTE: Get NEW waypoints
  // TODO: Remove OLD routepoints code
  //$routepoints = $settings['routepoints'];
  $routepoints = _at_draw_new_routepoints($settings['waypoints'], $zoom_box['zoom']);
  
  
  // Draw a line
  $line_colour = imagecolorallocate($img, 51, 51, 51);  // #333333
  
  $count = count($routepoints);
  
  // There should be at least two points to draw a line
  if ($count >= 2) {
    // Draw optimized route
    //for ($i = 1; $i <= $count - 1; $i++ ) {
    for ($i = 0; $i < $count - 1; $i++ ) {
      $p0 = _at_draw_get_canvas_coords($zoom_box, $routepoints[$i]);
      $p1 = _at_draw_get_canvas_coords($zoom_box, $routepoints[$i+1]);
      
      $x0 = $p0['x'];
      $y0 = $p0['y'];
      $x1 = $p1['x'];
      $y1 = $p1['y'];
      
      // Set line thickness
      imagesetthickness ($img, 2);
      imageline($img, $x0, $y0, $x1, $y1, $line_colour);
      
      
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
  }
  
  imagecolordeallocate($img, $line_colour);
}

// TODO:
function _at_draw_get_gmap($settings) {
  $canvas_used = $settings['canvas_used'];
  
  // TODO: Check if zoom is fixed, or get optimal
  $optimal_zoom_settings = _at_draw_get_optimal_zoom_settings($settings);
  
  // Get $zoom_box for zoom used.
  
  $zoom_optimal = $optimal_zoom_settings['zoom_optimal'];
  $zoom_box = $optimal_zoom_settings['zoom_boxes'][$zoom_optimal];
  
  // Get ratio for $canvas_used / $zoom_box dimensions
  $ratio = min($canvas_used['width'] / $zoom_box['width'], $canvas_used['height'] / $zoom_box['height']);
  
  $ratio = $ratio < 1 ? $ratio : 1;
  
  $zoom_box['ratio'] = $ratio;
  $zoom_box['extended'] = _at_draw_extend_zoom_box($settings, $zoom_box);
  return $zoom_box;
}

// TODO:
function _at_draw_extend_zoom_box($settings, $zoom_box) {
  $canvas_used = $settings['canvas_used'];
  $offset = $settings['offset'];
  $ratio = $zoom_box['ratio'];
  $edges = $zoom_box['edges'];
  $corners = $zoom_box['corners'];
  $centre = $zoom_box['centre'];
  
  // Get zoom_box edge tiles
  $xtile_min = $corners[$edges['left']]['xtile'];
  $xtile_max = $corners[$edges['right']]['xtile'];
  $ytile_min = $corners[$edges['top']]['ytile'];
  $ytile_max = $corners[$edges['bottom']]['ytile'];
  
  $xtiles_count = $xtile_max - $xtile_min + 1;
  $ytiles_count = $ytile_max - $ytile_min + 1;
  
  // Get dimensions of zoom_box tiles
  // TODO: get from get_zoom_box
  $full_width = $xtiles_count * AT_DRAW_PIXELS_PER_TILE;
  $full_height = $ytiles_count * AT_DRAW_PIXELS_PER_TILE;
  
  // Get zoom_box pixels outside canvas_used
  // TODO:
  $left = $corners[$edges['left']]['xPixel'];
  $right = AT_DRAW_PIXELS_PER_TILE - $corners[$edges['right']]['xPixel'];
  $top = $corners[$edges['top']]['yPixel'];
  $bottom = AT_DRAW_PIXELS_PER_TILE - $corners[$edges['bottom']]['yPixel'];
  
  // Get extra number of tiles if needed
  // Pixels for offset minus Pixels in tiles (considering $ratio)
  $pixels_to_add = array(
    'left' => ceil((($canvas_used['width'] + $offset['left']) / 2) / $ratio) - (($centre['xtile'] - $xtile_min) * AT_DRAW_PIXELS_PER_TILE + $centre['xPixel']),
    'right' => ceil((($canvas_used['width'] + $offset['right']) / 2) / $ratio) - (($xtile_max - $centre['xtile'] + 1) * AT_DRAW_PIXELS_PER_TILE - $centre['xPixel']),
    'top' => ceil((($canvas_used['height'] + $offset['top']) / 2) / $ratio) - (($centre['ytile'] - $ytile_min) * AT_DRAW_PIXELS_PER_TILE + $centre['yPixel']),
    'bottom' => ceil((($canvas_used['width'] + $offset['bottom']) / 2) / $ratio) - (($ytile_max - $centre['ytile'] + 1) * AT_DRAW_PIXELS_PER_TILE - $centre['yPixel']),
    //'left' => ceil($offset['left'] / $ratio) - $left,
    //'right' => ceil($offset['right'] / $ratio) - $right,
    //'top' => ceil($offset['top'] / $ratio) - $top,
    //'bottom' => ceil($offset['bottom'] / $ratio) - $bottom,
  );
  
  /*
  $tiles_extended = array(
    'xtile_min' => $pixels_to_add['left'] > 0 ? $xtile_min - (floor($pixels_to_add['left'] / AT_DRAW_PIXELS_PER_TILE) + 1) : $xtile_min,
    'xtile_max' => $pixels_to_add['right'] > 0 ? $xtile_max + (floor($pixels_to_add['right'] / AT_DRAW_PIXELS_PER_TILE) + 1) : $xtile_max,
    'ytile_min' => $pixels_to_add['top'] > 0 ? $ytile_min - (floor($pixels_to_add['top'] / AT_DRAW_PIXELS_PER_TILE) + 1) : $ytile_min,
    'ytile_max' => $pixels_to_add['bottom'] > 0 ? $ytile_max + (floor($pixels_to_add['bottom'] / AT_DRAW_PIXELS_PER_TILE) + 1) : $ytile_max,
  );
  */
  
  // Here floor() is used to get integer number of tiles
  $extra_tiles = array(
    'left' => $pixels_to_add['left']   > 0 ? floor($pixels_to_add['left']    / AT_DRAW_PIXELS_PER_TILE) + 1 : 0,
    'right' => $pixels_to_add['right']  > 0 ? floor($pixels_to_add['right']   / AT_DRAW_PIXELS_PER_TILE) + 1 : 0,
    'top' => $pixels_to_add['top']    > 0 ? floor($pixels_to_add['top']     / AT_DRAW_PIXELS_PER_TILE) + 1 : 0,
    'bottom' => $pixels_to_add['bottom'] > 0 ? floor($pixels_to_add['bottom']  / AT_DRAW_PIXELS_PER_TILE) + 1 : 0,
  );
  
  
  // TODO: This is a temporary solution for found bugs (black edges on final images).
  // Add extra extra_tile to each side if something goes wrong.
  foreach ($extra_tiles as $k => $v) {
    $extra_tiles[$k] ++;
  }
  
  $extended['extra_tiles'] = $extra_tiles;
  return $extended;
}



// TODO: Add option to set optimal zoom to zoom_optimal+1 or more advanced settings (i.e. zoom not greater than or zoom between that and that)
// Zoom must not be lower than optimal in any case.




// TODO: Check if this returns right values.
function _at_draw_get_optimal_zoom_settings($settings) {
  // TODO: Take zoom_min from settings
  $zoom_min = 8;
  $box = $settings['box'];
  $canvas_used = $settings['canvas_used'];
  
  $zoom_boxes = array();
  
  $zoom_optimal = $zoom_min - 1;
  do {
    $zoom_optimal ++;
    $zoom_box = _at_draw_get_zoom_box($box, $zoom_optimal);
    $zoom_boxes[$zoom_optimal] = $zoom_box;
  } while ($zoom_box['width'] <= $canvas_used['width'] && $zoom_box['height'] <= $canvas_used['height']);
  
  // Roll back last increament.
  // Since we need $zoom_optimal+1, this line is commented.
  //$zoom_optimal --;
  
  return array(
    'zoom_optimal' => $zoom_optimal,
    'zoom_boxes' => $zoom_boxes,
  );
}


// TODO: Check if this returns right values.
/**
 * Get dimensions of box in pixels for a given zoom.
 */
function _at_draw_get_zoom_box($box, $zoom) {
  // NOTE: Actually, box isn't a square when drawn on tiles (because of latitude).
  
  // Points' box edge coordinates
  $lon_min = $box['lon_min'];
  $lon_max = $box['lon_max'];
  $lat_min = $box['lat_min'];
  $lat_max = $box['lat_max'];
  
  // Zoom-box corner points
  // Actually, it is a prism. Use $edges for box.
  // NOTE: $lat_max is at the top of GMap, i.e. coordinates decrease from the Noth Pole to the South Pole
  $corners = array(
    'left_top' => array('lon' => $lon_min, 'lat' => $lat_max),
    'left_bottom' => array('lon' => $lon_min, 'lat' => $lat_min),
    'right_top' => array('lon' => $lon_max, 'lat' => $lat_max),
    'right_bottom' => array('lon' => $lon_max, 'lat' => $lat_min),
  );
  
  // Corner tile Numbers and Pixel coordinates
  foreach ($corners as $k => $corner) {
    $tile_num = _at_draw_coord_to_gmap_tile($corner['lat'], $corner['lon'], $zoom);
    $corners[$k]['xtile'] = floor($tile_num['x']);
    $corners[$k]['ytile'] = floor($tile_num['y']);
    
    $tile_pixel_coords = _at_draw_coord_to_gmap_tile_pixels($tile_num);
    $corners[$k]['xPixel'] = $tile_pixel_coords['x'];
    $corners[$k]['yPixel'] = $tile_pixel_coords['y'];
  }
  
  // Since two points with the same longitude (but different longitude) can have different xtile numbers (aha!),
  // do additional checks before calculating zoom_box dimensions
  $edges = array();
  
  $edges['left'] = ($corners['left_top']['xtile'] < $corners['left_bottom']['xtile']
                    || ($corners['left_top']['xtile'] == $corners['left_bottom']['xtile']
                        && $corners['left_top']['xPixel'] < $corners['left_bottom']['xPixel']))
                 ? 'left_top'
                 : 'left_bottom';
  
  $edges['right'] = ($corners['right_top']['xtile'] > $corners['right_bottom']['xtile']
                    || ($corners['right_top']['xtile'] == $corners['right_bottom']['xtile']
                        && $corners['right_top']['xPixel'] > $corners['right_bottom']['xPixel']))
                 ? 'right_top'
                 : 'right_bottom';
  
  // For top and bottom edges we can take either left or right corners.
  $edges['top'] = 'left_top';
  $edges['bottom'] = 'left_bottom';
  
  // Calculate Zoom-box centre
  $centre = array(
    'lon' => $corners[$edges['left']]['lon'] + ($corners[$edges['right']]['lon'] - $corners[$edges['left']]['lon']) / 2,
    'lat' => $corners[$edges['top']]['lat'] + ($corners[$edges['bottom']]['lat'] - $corners[$edges['top']]['lat']) / 2,
  );
  $centre_tile = _at_draw_coord_to_gmap_tile($centre['lat'], $centre['lon'], $zoom);
  $centre_tile_pixel_coords = _at_draw_coord_to_gmap_tile_pixels($centre_tile);
  $centre += array(
    'xtile' => floor($centre_tile['x']),
    'ytile' => floor($centre_tile['y']),
    'xPixel' => $centre_tile_pixel_coords['x'],
    'yPixel' => $centre_tile_pixel_coords['y'],
  );
  
  // Zoom-box
  $zoom_box = array(
    'zoom' => $zoom,
    'corners' => $corners,
    'edges' => $edges,
    'width' => $corners[$edges['right']]['xPixel'] - $corners[$edges['left']]['xPixel'] + ($corners[$edges['right']]['xtile'] - $corners[$edges['left']]['xtile']) * AT_DRAW_PIXELS_PER_TILE,
    'height' => $corners[$edges['bottom']]['yPixel'] - $corners[$edges['top']]['yPixel'] + ($corners[$edges['bottom']]['ytile'] - $corners[$edges['top']]['ytile']) * AT_DRAW_PIXELS_PER_TILE,
    'centre' => $centre,
  );
  
  // TODO: Add semisphere check
  $zoom_box['height'] = $zoom_box['height'];
  
  return $zoom_box;
}


// TODO: Add check for calculations error in _at_draw_coord_to_gmap_tile() + _at_draw_coord_to_gmap_tile()
// since because of calculation error (inaccuracy) we can get pixels for a tile different from _at_draw_coord_to_gmap_tile() one.


// TODO: Check if this returns right values.
// TODO: Change returned value keys to 'xtile', 'ytile'

/**
 * Get tile numbers for lat/lon
 * 
 * see https://metacpan.org/module/Geo::Coordinates::GMap#___pod
 */
function _at_draw_coord_to_gmap_tile($lat, $lon, $zoom) {
  
  $sin_phi = sin( $lat * M_PI / 180 );
  
  $norm_x = $lon / 180;
  $norm_y = (0.5 * log((1 + $sin_phi) / (1 - $sin_phi))) / M_PI;
  
  $tile_x = pow(2, $zoom) * (($norm_x + 1) / 2);
  $tile_y = pow(2, $zoom) * ((1 - $norm_y) / 2);
  
  return array(
    'x' => $tile_x,
    'y' => $tile_y,
  );
}

function _at_draw_coord_to_gmap_tile_pixels($tile_num) {
  $tile_x = $tile_num['x'];
  $tile_y = $tile_num['y'];
  return array(
    'x' => round(($tile_x - floor($tile_x)) * AT_DRAW_PIXELS_PER_TILE),
    'y' => round(($tile_y - floor($tile_y)) * AT_DRAW_PIXELS_PER_TILE),
  );
}


/*
sub coord_to_gmap_tile {
    my ($lat, $lon, $zoom) = @_;

    # The C# code did this, but I don't know why, so I'm not going to enable it.
    #return if abs($lat) > 85.0511287798066;

    my $sin_phi = sin( $lat * pi / 180 );

    my $norm_x = $lon / 180;
    my $norm_y = (0.5 * log((1 + $sin_phi) / (1 - $sin_phi))) / pi;

    my $tile_x = (2 ** $zoom) * (($norm_x + 1) / 2);
    my $tile_y = (2 ** $zoom) * ((1 - $norm_y) / 2);

    return(
        $tile_x,
        $tile_y,
    );
}
*/

// http://wiki.openstreetmap.org/wiki/Slippy_map_tilenames
function _at_draw_gmap_tile_to_coords($xtile, $ytile, $zoom) {
  $n = pow(2, $zoom);
  $lon_deg = $xtile / $n * 360.0 - 180.0;
  $lat_deg = rad2deg(atan(sinh(pi() * (1 - 2 * $ytile / $n))));
  return array(
    'lon' => $lon_deg,
    'lat' => $lat_deg,
  );
}

function _at_draw_new_routepoints($waypoints, $zoom) {
  module_load_include('inc', 'pg_race', 'pg_race.class');
  
  $sw = new geoShortWayCalc();
  $res = $sw->calculateShortestWay($waypoints, $zoom);
  
  
  $routepoints_new = array();
  foreach($res as $k => $v) {
    $routepoints_new[] = _at_draw_gmap_tile_to_coords($v->approximationPoint['x'], $v->approximationPoint['y'], $zoom);
  }
  return $routepoints_new;
}
