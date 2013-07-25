<?php

// TODO: Remove $zoom from method args till the very end


class geoPoint {
  protected $lon;
  protected $lat;
  private $proj_x;
  private $proj_y;
  
  function __construct($lon, $lat) {
    $this->lon = $lon;
    $this->lat = $lat;
  }
  
  function getProjCoords($zoom) {
    
    $lon = $this->lon;
    $lat = $this->lat;
    
    $sin_phi = sin( $lat * M_PI / 180 );
    
    $norm_x = $lon / 180;
    $norm_y = (0.5 * log((1 + $sin_phi) / (1 - $sin_phi))) / M_PI;
    
    $this->proj_x = pow(2, $zoom) * (($norm_x + 1) / 2);
    $this->proj_y = pow(2, $zoom) * ((1 - $norm_y) / 2);
    
    return array(
      'x' => $this->proj_x,
      'y' => $this->proj_y,
    );
  }
}

class geoWaypoint extends geoPoint {
  
  //private $lon;
  //private $lat;
  private $radius_km;
  private $proj_radius;
  
  
  function __construct($lon, $lat, $radius_m) {
    $this->lon = $lon;
    $this->lat = $lat;
    $this->radius_km = $radius_m / 1000;
  }
  
  
  
  
  function getProjRadius($zoom) {
    $d2lat = 1 / 110.54; // 1 deg = 110.54 km
    //$d2lon = 1 / (111.320 * cos($waypoint['lat']));
    
    $lat_delta = abs($this->radius_km * $d2lat);
    
    $x0 = new geoPoint($this->lon, $this->lat);
    $x1 = new geoPoint($this->lon, $this->lat + $lat_delta);
    
    $proj_x0 = $x0->getProjCoords($zoom);
    $proj_x1 = $x1->getProjCoords($zoom);
    
    $this->proj_radius = abs($proj_x1['y'] - $proj_x0['y']);
    return $this->proj_radius;
  }
}


class geoRoutepointStruct {
  public $circle;
  public $approximationPoint;
}




class geoShortWayCalc {
  /**
   * Number of cycles of approximation
   */
  CONST APPROXIMATION_CYCLES = 8;
  
  //
  //function calculateShortestWay($startPosition, $waypoints, $zoom) {
  function calculateShortestWay($waypoints, $zoom) {
    $routepoints = array();
    
    // Exclude some waypoints if needed.
    self::excludeWaypoints($waypoints, $zoom);
    $waypoints = array_values($waypoints);
    
    
    
    // Prepare array of Routepoints' structure
    foreach ($waypoints as $waypoint) {
      $rt = new geoRoutepointStruct();
      $wp = new geoWaypoint($waypoint['lon'], $waypoint['lat'], $waypoint['rad']);
      //$rt->circle = $waypoint;
      $rt->circle = $wp;
      $rt->approximationPoint = $wp->getProjCoords($zoom);
      $routepoints[] = $rt;
    }
    
    //dsm($routepoints);
    
    if (self::IsInside($routepoints[0]->approximationPoint, $routepoints[1], $zoom)) {
      unset($routepoints[1]);
      $routepoints = array_values($routepoints);
    }
    
    // TODO: Get opimal route
    $curr = $next = $prev = NULL;
    if (count($routepoints) > 1) {
      //foreach ($routepoints as $k => $routepoint) {
        // TODO:
        for ($counter = 0; $counter < self::APPROXIMATION_CYCLES; $counter++) {
          for ($i = 1; $i < count($routepoints) - 1; $i++) {
            $prev = $routepoints[$i - 1];
            $curr = $routepoints[$i];
            $next = $routepoints[$i + 1];
            $curr->approximationPoint = self::findCenterBetween($curr, $prev->approximationPoint, $next->approximationPoint, $zoom);
          }
        }
      //}
    }
    
    return $routepoints;
  }
  
  
  // TODO:
  function findCenterBetween($center, $prev, $next, $zoom) {
    // TODO:
    // If the next point in our current circle - do not look for it on the point of intersection, immediately return the next point.
    
    //if (self::isInside($next, $center)) {
    if (self::isInside($next, $center, $zoom)) {
      return $prev;
    }
    
    
    // Otherwise - look for the intersection
    $az1 = self::getAzimuth($center->approximationPoint, $prev);
    $az2 = self::getAzimuth($center->approximationPoint, $next);
    $middle = self::getHalfAzimuth($az1, $az2);
    return self::getCoordinates($center, $middle, $zoom);
  }
  
  
  function isInside($next, $center, $zoom) {
    $center_coords = $center->circle->getProjCoords($zoom);
    $radius = $center->circle->getProjRadius($zoom);
    $distance = self::pointsProjDistance($center_coords, $next);
    
    return $distance <= $radius;
  }
  
  
  // Calculate distance between two points (in projection coordinates)
  function pointsProjDistance($p0, $p1) {
    $dx = $p1['x'] - $p0['x'];
    $dy = $p1['y'] - $p0['y'];
    return sqrt(pow($dx, 2) + pow($dy, 2));
  }
  
  
  
  // TODO: Check case of START Cylinder
  private function excludeWaypoints(&$waypoints, $zoom) {
    $waypoints = array_values($waypoints);
    
    $count = count($waypoints);
    
    for ($i = 0; $i < $count-1; $i++) {
      $curr = $waypoints[$i];
      $next = $waypoints[$i+1];
      
      $curr = new geoWaypoint($curr['lon'], $curr['lat'], $curr['rad']);
      $next = new geoWaypoint($next['lon'], $next['lat'], $next['rad']);
      
      //$curr_radius = $curr->getProjRadius($zoom);
      //$next_radius = $next->getProjRadius($zoom);
      
      $p0 = $curr->getProjCoords($zoom);
      $p1 = $next->getProjCoords($zoom);
      
      //$curr->getProjRadius($zoom);
      //$next->getProjRadius($zoom);
      
      // If next cylinder is inside current one, remove current from waypoints.
      if (self::pointsProjDistance($p0, $p1) <= $curr->getProjRadius($zoom) - $next->getProjRadius($zoom)) {
        unset($waypoints[$i]);
      }
    }
  }
  
  function getAzimuth($origin, $pos) {
    $dx = $pos['x'] - $origin['x'];
    // Inverse since tile numbers increase from top to bottom
    $dy = - $pos['y'] + $origin['y'];
    
    
    if ($dx != 0.0) {
      $k = $dx >= 0 ? 0 : 1;
      //$tg = $dy / $dx;
      $tg = $dy / $dx;
      
      $azimuth = atan($tg) + M_PI * $k;
    }
    else {
      $k = $dy >= 0 ? 0 : 1;
      $azimuth = M_PI * (0.5 + $k);
    }
    
    if ($azimuth < 0) {
      $azimuth += 2 * M_PI;
    }
    
    return $azimuth;
  }
  
  
  // TODO:
  function getHalfAzimuth($azimuth1, $azimuth2) {
    
    $sum = $azimuth1 + $azimuth2;
    //$sum = $sum - intval($sum / (2 * M_PI)) * 2 * M_PI;
    
    // Get the arithmetic mean between the bearings
    //$halfAzimuth = ($azimuth1 + $azimuth2) / 2.0;
    $halfAzimuth = $sum / 2.0;
    
    // TODO: subtract 2 * M_PI if needed
    
    // If it greater than M_PI - take symmetric point
    if (abs($azimuth1 - $azimuth2) > M_PI) {
      $halfAzimuth -= M_PI;
    }
    
    $az = array(
      'az1' => $azimuth1,
      'az2' => $azimuth2,
      'half' => $halfAzimuth,
    );
    //dsm($az);
    
    /*
    $abs = abs($halfAzimuth);
    if ($abs - floor($abs) > 0.5 * M_PI) {
      //$halfAzimuth += M_PI;
    }
    */
    
    
    return $halfAzimuth;
  }
  
  function getCoordinates($center, $azimuth, $zoom) {
    $wp = $center->circle;
    $center_coords = $wp->getProjCoords($zoom);
    
    $proj_radius = $wp->getProjRadius($zoom);
    $dx = $proj_radius * cos($azimuth);
    $dy = $proj_radius * sin($azimuth);
    
    //dsm('coords:: dx: ; dy: ');
    
    // Subract $dy because tile numbers increase from top to bottom
    // whereas coordinates - from bottom to top
    return array(
      'x' => $center_coords['x'] + $dx,
      //'y' => $center_coords['y'] + $dy,
      'y' => $center_coords['y'] - $dy,
    );
  }
}
