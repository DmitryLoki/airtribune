<?php

define('PG_RACE_TILES_PERMISSIONS_MODE', 0775);

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
  $routepoints = array_values($routepoints);
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
  
  // TODO: Take box center instead of $waypoints[0]
  // http://stackoverflow.com/questions/1253499/simple-calculations-for-working-with-lat-lon-km-distance
  $d2lon = (1 / 1000) / (111.320 * cos($waypoints[0]['lat']));
  $d2lat = (1 / 1000) / 110.54; // 1 deg = 110.54 km
  foreach ($waypoints as $k => $waypoint) {
    $rad = $waypoint['rad'];
    $rad_lon = $rad * $d2lon;
    $rad_lat = $rad * $d2lat;
    
    $waypoint['radius']['rad_lon'] = $rad_lon;
    $waypoint['radius']['rad_lat'] = $rad_lat;
    
    $waypoint += array(
      'lon_min' => $waypoint['lon'] - $rad_lon,
      'lon_max' => $waypoint['lon'] + $rad_lon,
      'lat_min' => $waypoint['lat'] - $rad_lat,
      'lat_max' => $waypoint['lat'] + $rad_lat,
    );
    /*
    // Get box dimensions in coordinates
    foreach (array('lon_min', 'lon_max', 'lat_min', 'lat_max') as $key_name) {
      if (!isset($box[$key_name])) {
        $box[$key_name] = $waypoint[$key_name];
      }
      else {
        if (in_array($key_name, array('lon_min', 'lat_min')) && $box[$key_name] > $waypoint[$key_name]) {
          $box[$key_name] = $waypoint[$key_name];
        }
        elseif (in_array($key_name, array('lon_max', 'lat_max')) && $box[$key_name] < $waypoint[$key_name]) {
          $box[$key_name] = $waypoint[$key_name];
        }
      }
    }
    */
    $waypoints[$k] = $waypoint;
  }
  
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
  
  
  // Calculate box center
  $box['center']['lon'] = $box['lon_min'] + ($box['lon_max'] - $box['lon_min']) / 2;
  $box['center']['lat'] = $box['lat_min'] + ($box['lat_max'] - $box['lat_min']) / 2;
  
  
  // Get info for the central tile of the box (pixel2degree ratio)
  $zoom = $settings['zoom'];
  
  $box['center']['xtile'] = _at_draw_get_tile_num($box['center']['lon'], $zoom, 'xtile');
  $box['center']['ytile'] = _at_draw_get_tile_num($box['center']['lat'], $zoom, 'ytile');
  
  // Number of pixels in one tile
  $tile_px_num = 256;
  
  // Central tile edge coordinates
  $central_tile = array(
    'lon_min' => _at_draw_get_tile_coord($box['center']['xtile'], $zoom, 'lon'),
    'lon_max' => _at_draw_get_tile_coord($box['center']['xtile']+1, $zoom, 'lon'),
    'lat_min' => _at_draw_get_tile_coord($box['center']['ytile'], $zoom, 'lat'),
    'lat_max' => _at_draw_get_tile_coord($box['center']['ytile']+1, $zoom, 'lat'),
  );
  // Number of pixels per one degree (lon and lat)
  $central_tile['pdeg_lon'] = abs($tile_px_num / ($central_tile['lon_max'] - $central_tile['lon_min']));
  $central_tile['pdeg_lat'] = abs($tile_px_num / ($central_tile['lat_max'] - $central_tile['lat_min']));
  // Normal pdeg lat/lon ratio for a given location.
  $central_tile['ratio'] = $central_tile['pdeg_lat']/$central_tile['pdeg_lon'];
  
  // Normalize canvas pdeg according to central_tile pdeg
  $box['pdeg_lon'] = $canvas_used['width'] / ($box['lon_max'] - $box['lon_min']);
  $box['pdeg_lat'] = $canvas_used['height'] / ($box['lat_max'] - $box['lat_min']);
  // pdeg can only decrease in a direction, since we have limited number of pixels
  // and fixed number of degrees
  if ($box['pdeg_lat']/$box['pdeg_lon'] > $central_tile['ratio']) {
    $box['pdeg_lat'] = $central_tile['ratio'] * $box['pdeg_lon'];
  }
  else {
    $box['pdeg_lon'] = $central_tile['ratio'] * $box['pdeg_lat'];
  }
  
  $box['height'] = round($box['pdeg_lat'] * ($box['lat_max'] - $box['lat_min']));
  $box['width'] = round($box['pdeg_lon'] * ($box['lon_max'] - $box['lon_min']));
  $box['offset'] = array(
    'top' => floor(($canvas_used['height'] - $box['height']) / 2 + $offset['top']),
    'left' => floor(($canvas_used['width'] - $box['width']) / 2 + $offset['left']),
  );
  
  
  foreach ($waypoints as $k => $waypoint) {
    $waypoints[$k] += array(
      'x' => round(($waypoint['lon'] - $box['lon_min']) * $box['pdeg_lon'] + $box['offset']['left']),
      'y' => round(($waypoint['lat'] - $box['lat_min']) * $box['pdeg_lat'] + $box['offset']['top']),
    );
    
    $radius = $waypoints[$k]['radius'];
    $waypoints[$k]['radius']['pixel'] = round(($radius['rad_lon'] * $box['pdeg_lon'] + $radius['rad_lat'] * $box['pdeg_lat']) / 2);
  }
  
  
  foreach ($routepoints as $k => $routepoint) {
    $routepoints[$k] += array(
      'x' => round(($routepoint['lon'] - $box['lon_min']) * $box['pdeg_lon'] + $box['offset']['left']),
      'y' => round(($routepoint['lat'] - $box['lat_min']) * $box['pdeg_lat'] + $box['offset']['top']),
    );
  }
  
  $settings['waypoints'] = $waypoints;
  $settings['routepoints'] = $routepoints;
  $settings['central_tile'] = $central_tile;
  $settings['box'] = $box;
  
  $path = _at_draw_draw_image($settings);
  
  return $path;
}


function _at_draw_draw_image($settings) {
  //$path = 'sites/default/files/my_new_image2.png';
  
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
  
  $canvas = $settings['canvas'];
  // Create image
  $img = imagecreatetruecolor($canvas['width'], $canvas['height']);
  
  
  // Draw canvas background
  $back = imagecolorallocate($img, 255, 255, 255);
  imagefilledrectangle($img, 0, 0, $canvas['width'] - 1, $canvas['height'] - 1, $back);
  imagecolordeallocate($img, $back);
  
  
  // Draw map
  _at_draw_draw_map($img, $settings);
  
  imageantialias($img, TRUE);
  // Draw waypoints
  _at_draw_draw_waypoints($img, $settings);
  // Draw routepoints
  _at_draw_draw_routepoints($img, $settings);
  
  // Save image
  imagepng($img, $path);
  chmod($path, PG_RACE_TILES_PERMISSIONS_MODE);
  
  return $path;
}


// TODO: Check semisphere


function _at_draw_draw_waypoints(&$img, $settings) {
  // Set circle inner and border colours
  $cylinder_inner_color = imagecolorallocatealpha ($img , 142 , 142 , 142 , 70); // #8e8e8e
  $cylinder_border_color = imagecolorallocate($img, 51, 51, 51); // #333333
  $cylinder_inner_color_start = imagecolorallocatealpha ($img, 142, 217, 12, 70);  // #8ed90c
  $cylinder_inner_color_finish = imagecolorallocatealpha ($img, 186, 7, 192, 70);  // #ba07d4
  
  $waypoints = $settings['waypoints'];
  $box = $settings['box'];
  $box_offset = $box['offset'];
  
  $count = count($waypoints);
  // Draw circles
  foreach ($waypoints as $k => $waypoint) {
    $x = $waypoint['x'];
    $y = $waypoint['y'];
    $y = $settings['canvas']['height'] - $y;
    
    // TODO: radius
    $radius = $waypoint['radius']['pixel'];
    
    $diameter = 2 * $radius;
    //dsm($k . ' ' . $radius);
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
    /*
    if ($k == $count-1) {
      imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color_finish);
    }
    else {
      imagefilledellipse($img , $x , $y , $diameter , $diameter , $cylinder_inner_color);
    }
    */
    imageellipse($img , $x , $y , $diameter , $diameter , $cylinder_border_color);
  }
  imagecolordeallocate($img, $cylinder_inner_color);
  imagecolordeallocate($img, $cylinder_border_color);
  imagecolordeallocate($img, $cylinder_inner_color_start);
  imagecolordeallocate($img, $cylinder_inner_color_finish);
}

function _at_draw_draw_routepoints(&$img, $settings) {
  // Draw a line
  $line_colour = imagecolorallocate($img, 51, 51, 51);  // #333333
  // Set line thickness
  imagesetthickness ($img, 2);
  
  $routepoints = $settings['routepoints'];
  $count = count($routepoints);
  
  // There should be at least two points to draw a line
  if ($count >= 2) {
    // Draw optimized route
    for ($i = 1; $i < $count - 1; $i++ ) {
      $x0 = $routepoints[$i]['x'];
      $y0 = $routepoints[$i]['y'];
      $y0 = $settings['canvas']['height'] - $y0;  // TODO: Convert upside down
      
      $x1 = $routepoints[$i+1]['x'];
      $y1 = $routepoints[$i+1]['y'];
      $y1 = $settings['canvas']['height'] - $y1;
      
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
        
        $p1 = array(
          'x' => round($arrow_length * cos($a1)),
          'y' => round($arrow_length * sin($a1)),
        );
        
        $p2 = array(
          'x' => round($arrow_length * cos($a2)),
          'y' => round($arrow_length * sin($a2)),
        );
        
        //imageline($img, $x_m, $y_m, $x_m + $p1['x'], $y_m + $p1['y'], $line_colour);
        //imageline($img, $x_m, $y_m, $x_m + $p2['x'], $y_m + $p2['y'], $line_colour);
        
        $points = array(
          $x_m, $y_m,
          $x_m + $p1['x'], $y_m + $p1['y'],
          $x_m + $p2['x'], $y_m + $p2['y'],
        );
        
        //dsm($points);
        imagefilledpolygon($img , $points , 3 , $line_colour);
      }
    }
  }
  
  imagecolordeallocate($img, $line_colour);
}





function _at_draw_draw_map(&$img, $settings) {
  // Get zoom from settings
  $zoom = $settings['zoom'];
  $box = $settings['box'];
  $canvas = $settings['canvas'];
  $central_tile = $settings['central_tile'];
  
  // Canvas box center
  $x = round($box['width'] / 2 + $box['offset']['left']);
  $y = round($box['height'] / 2 + $box['offset']['top']);
  
  $canvas += array(
    'lon_min' => $box['center']['lon'] - ($x - 1) / $box['pdeg_lon'],
    'lon_max' => $box['center']['lon'] + ($canvas['width'] - $x) / $box['pdeg_lon'],
    'lat_min' => $box['center']['lat'] - ($y - 1) / $box['pdeg_lat'],
    'lat_max' => $box['center']['lat'] + ($canvas['height'] - $y) / $box['pdeg_lat'],
  );
  
  
  $corner_tiles = array(
    'xtile_min' => NULL,
    'xtile_max' => NULL,
    'ytile_min' => NULL,
    'ytile_max' => NULL,
  );
  
  // http://wiki.openstreetmap.org/wiki/Slippy_map_tilenames
  $corner_tiles['xtile_min'] = _at_draw_get_tile_num($canvas['lon_min'], $zoom, 'xtile');
  $corner_tiles['xtile_max'] = _at_draw_get_tile_num($canvas['lon_max'], $zoom, 'xtile');
  // TODO: min and max changed
  $ytile_min = _at_draw_get_tile_num($canvas['lat_min'], $zoom, 'ytile');
  $ytile_max = _at_draw_get_tile_num($canvas['lat_max'], $zoom, 'ytile');
  $corner_tiles['ytile_min'] = min($ytile_min, $ytile_max);
  $corner_tiles['ytile_max'] = max($ytile_min, $ytile_max);
  
  $settings['corner_tiles'] = $corner_tiles;
  
  // Download tiles. Get image resource.
  $img_tiles_res = _at_draw_get_tiles($settings, $zoom);
  
  
  // TODO: Check semisphere
  // Get top left $img_tiles offset
  //$img_tiles['offset']['left'] = round(($canvas['lon_min'] - _at_draw_get_tile_coord($corner_tiles['xtile_min'], $zoom, 'lon')) * $central_tile['pdeg_lon']);
  //$img_tiles['offset']['top'] = - round(($canvas['lat_min'] - _at_draw_get_tile_coord($corner_tiles['ytile_min'], $zoom, 'lat')) * $central_tile['pdeg_lat']);
  $img_tiles['offset']['left'] = round(($canvas['lon_min'] - _at_draw_get_tile_coord($corner_tiles['xtile_min'], $zoom, 'lon')) * $central_tile['pdeg_lon']);
  $img_tiles['offset']['top'] = - round(($canvas['lat_max'] - _at_draw_get_tile_coord($corner_tiles['ytile_min'], $zoom, 'lat')) * $central_tile['pdeg_lat']);
  // Get bottom right $img_tiles offset
  //$img_tiles['offset']['right'] = round(($canvas['lon_max'] - _at_draw_get_tile_coord($corner_tiles['xtile_max'], $zoom, 'lon')) * $central_tile['pdeg_lon']);
  //$img_tiles['offset']['bottom'] = round(($canvas['lat_max'] - _at_draw_get_tile_coord($corner_tiles['ytile_max'], $zoom, 'lat')) * $central_tile['pdeg_lat']);
  $img_tiles['offset']['right'] = round(($canvas['lon_max'] - _at_draw_get_tile_coord($corner_tiles['xtile_max'], $zoom, 'lon')) * $central_tile['pdeg_lon']);
  $img_tiles['offset']['bottom'] = - round(($canvas['lat_min'] - _at_draw_get_tile_coord($corner_tiles['ytile_max'], $zoom, 'lat')) * $central_tile['pdeg_lat']);
  
  /*
  dsm(_at_draw_get_tile_coord($corner_tiles['ytile_min'], $zoom, 'lat') . ' ' . _at_draw_get_tile_coord($corner_tiles['xtile_min'], $zoom, 'lon'));
  dsm(_at_draw_get_tile_coord($corner_tiles['ytile_max'], $zoom, 'lat') . ' ' . _at_draw_get_tile_coord($corner_tiles['xtile_max'], $zoom, 'lon'));
  dsm($canvas['lat_min'] . ' ' . $canvas['lon_min']);
  dsm($canvas['lat_max'] . ' ' . $canvas['lon_max']);
  */
  
  $img_tiles['width'] = ($corner_tiles['xtile_max'] - $corner_tiles['xtile_min'] + 1) * 256;
  $img_tiles['height'] = ($corner_tiles['ytile_max'] - $corner_tiles['ytile_min'] + 1) * 256;
  
  $img_tiles += array(
    'xmin' => $img_tiles['offset']['left'],
    'xmax' => $img_tiles['width'] - $img_tiles['offset']['right'] - 1,
    // TODO:
    'ymin' => $img_tiles['offset']['top'],
    'ymax' => $img_tiles['height'] - $img_tiles['offset']['bottom'] - 1,
  );
  
  $dst_image = $img;
  $src_image = $img_tiles_res;
  $dst_x = 0;
  $dst_y = 0;
  $src_x = $img_tiles['xmin'];
  $src_y = $img_tiles['ymin'];
  $dst_w = $canvas['width'] - 1;
  $dst_h = $canvas['height'] - 1;
  $src_w = $img_tiles['xmax'] - $img_tiles['xmin'];
  $src_h = $img_tiles['ymax'] - $img_tiles['ymin'];
  
  //imagecopyresized($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h);
  imagecopyresampled($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h);
}


function _at_draw_get_tiles($settings, $zoom) {
  $central_tile = $settings['central_tile'];
  $corner_tiles = $settings['corner_tiles'];
  
  // Create image
  $xtile_count = $corner_tiles['xtile_max'] - $corner_tiles['xtile_min'] + 1;
  $ytile_count = $corner_tiles['ytile_max'] - $corner_tiles['ytile_min'] + 1;
  $img_tiles = imagecreatetruecolor($xtile_count * 256, $ytile_count * 256);
  
  $x_dst = 0;
  $y_dst = 0;
  for ($xtile = $corner_tiles['xtile_min']; $xtile <= $corner_tiles['xtile_max']; $xtile++) {
    for ($ytile = $corner_tiles['ytile_min']; $ytile <= $corner_tiles['ytile_max']; $ytile++) {
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
      
      // TODO: Add file detection
      //$path = $files_path . "/tile_x{$xtile}_y{$ytile}_z{$zoom}.jpg";
      $path = $files_path . "/tile_x{$xtile}_y{$ytile}_z{$zoom}.png";
      
      
      

      
      // Check if file exists.
      if (!file_exists ($path)) {
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
      imagecopy ($img_tiles, $tile_img, $x_dst, $y_dst, 0, 0, 256, 256);
      $y_dst += 256;
    }
    $y_dst = 0;
    $x_dst += 256;
  }
  
  //$path_tiles = 'sites/default/files/tiles_image2.png';
  //imagepng($img_tiles, $path_tiles);
  //chmod($path_tiles, PG_RACE_TILES_PERMISSIONS_MODE);
  
  return $img_tiles;
}


function _at_draw_get_max_zoom() {
  //
}



function _at_draw_get_tile_num($lonlat, $zoom, $type) {
  switch ($type) {
    case 'xtile' :
      $return = floor((($lonlat + 180) / 360) * pow(2, $zoom));
      break;
    case 'ytile' :
      $return = floor((1 - log(tan(deg2rad($lonlat)) + 1 / cos(deg2rad($lonlat))) / pi()) /2 * pow(2, $zoom));
      break;
  }
  return $return;
}

function _at_draw_get_tile_coord($tile_number, $zoom, $type) {
  $n = pow(2, $zoom);
  switch ($type) {
    case 'lon' :
      $return = $tile_number / $n * 360.0 - 180.0;
      break;
    case 'lat' :
      $return = rad2deg(atan(sinh(pi() * (1 - 2 * $tile_number / $n))));
      break;
  }
  return $return;
}



function _at_draw_get_waypoints($race_id) {
  $waypoints = array();
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
