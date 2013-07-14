<?php

/**
 * Calculator on the shortest distance between the given points based
 * on their radii
 * @author Roman Kuvaldin
 *
 * PHP implementation
 * @autor Vyacheslav "ValiDoll" Malchik <info@vkey.biz>
 *
 */


/*
 * Degrees class
 */
class degrees {

  /**
   * Value of degrees (in decimal)
   * @var double $degrees
   */
  private $degrees;

  /**
   *
   * @param double $degrees
   */ function __construct($degrees) {
    $this->degrees = $degrees;
  }

  /**
   * Get value in degrees
   *
   * @return double
   */
  public function getDegrees() {
    return $this->degrees;
  }

  /**
   * Get value in radians
   *
   * @return double
   */
  public function getRadians() {
    return deg2rad($this->degrees);
  }
}


/*
 * Class of coordinates
 */
class LatLon {

  /**
   *
   * @var double
   */
  private $latitude;

  /**
   *
   * @var double
   */
  private $longitude;

  /**
   *
   * @param double
   * @param double
   */ function __construct($latitude, $longitude) {
    $this->latitude = new degrees($latitude);
    $this->longitude = new degrees($longitude);
  }

  /**
   * Get latitude
   *
   * @return degrees
   */
  public function getLatitude() {
    return $this->latitude;
  }

  /**
   * Get longitude
   *
   * @return degrees
   */
  public function getLongitude() {
    return $this->longitude;
  }

  /**
   * Get LanLot object on a pair of latitude and longitude values
   *
   * @param double $latitude
   * @param double $longitude
   *
   * @return LatLon
   */
  public function fromDegrees($latitude, $longitude) {
    return new LatLon($latitude, $longitude);
  }
}

/**
 * Waypoint class
 */
class Waypoint {

  /**
   * Number of the point
   * @var int
   */
  private $number;

  /**
   * Name of point
   * @var string
   */
  private $name;

  /**
   * Coordinates of the center of the circle
   * @var LanLot
   */
  private $center;

  /**
   * Radius of circle in meters
   * @var int
   */
  private $radius;

  /**
   *
   * @param int $number
   * @param string $name
   * @param double $latitude
   * @param double $longitude
   * @param int $radius
   */ function __construct($number, $name, $latitude, $longitude, $radius) {
    $this->center = new LatLon($latitude, $longitude);
    $this->radius = $radius;
    $this->number = $number;
    $this->name = $name;
  }

  /**
   * Return the coordinates of the circle center
   *
   * @return LatLon
   */
  function getCenter() {
    return $this->center;
  }

  /**
   * Return the radius of the circle
   *
   * @return int
   */
  function getRadius() {
    return $this->radius;
  }
}

class ShortWayStruct {

  /**
   *
   * @var int
   */
  public $order;

  /**
   *
   * @var Waypoint
   */
  public $circle;

  /**
   *
   * @var LatLon
   */
  public $approximationPoint;
}

/**
 *
 */ class ShortWayCalculator {

  /**
   *
   * @var array of LanLot
   */
  static $lengthCache;

  /**
   * Earth's radius in meters
   */
   CONST EARTH_RADIUS = 6378100.0;

  /**
   * Number of cycles of approximation
   */
   CONST APPROXIMATION_CYCLES = 8;

  /**
   * Calculate shortest way
   *
   * @param LatLon $startPosition
   * @param array of Waypoint $waypoints
   *
   * @return array of LatLon
   */
  public static function calculateShortestWay($startPosition, $waypoints) {
    $coords = array();
    $ref = NULL;
    $counter = 1;


    // Add start position as first waypoint
    $wp = new Waypoint(0, "START", $startPosition->getLatitude()->getDegrees(), $startPosition->getLongitude()->getDegrees(), 1.0);
    array_unshift($waypoints, $wp);
    // Looping through all the points
    for ($i = 0; $i < count($waypoints); $i++) {
      // Get two points lying near
      $curr = $waypoints[$i];
      $skip = FALSE;
      if ($i != 0) {
        // If the next waypoint is within the current waypoint, and it is smaller than the radius - that exclude from the calculation of its shortest path
        $prev = $waypoints[$i - 1];
        $skip = (
          self::isInside($prev->getCenter(), $curr) &&
          ($prev->getRadius() > $curr->getRadius())
        );
      }
      if (!$skip) {
        $ref = new ShortWayStruct();
        $ref->order = $counter;
        $ref->circle = $curr;
        $ref->approximationPoint = $curr->getCenter();
        $coords[] = $ref;
        $counter++;
      }
      else {
        $coords[] = $coords[count($coords) - 1];
        $counter++;
      }
    }

    $curr = NULL;
    $next = NULL;
    $prev = NULL;
    if (count($coords) > 1) {
      for ($counter = 0; $counter < self::APPROXIMATION_CYCLES; $counter++) {
        for ($i = 1; $i < count($coords) - 1; $i++) {
          $prev = $coords[$i - 1];
          $curr = $coords[$i];
          $next = $coords[$i + 1];
          $curr->approximationPoint = self::findCenterBetween($curr->circle, $prev->approximationPoint, $next->approximationPoint);
        }
      }
    }

    $result = array();
    foreach ($coords as $coord) {
      $result[] = $coord->approximationPoint;
    }
    return $result;
  }

  /**
   * Find the point on the circle equidistant from the points
   * of intersection of the circle with a radius of
   * $radius straight "prev - center" and "center - next"
   *
   * @param Waypoint $center - coordinates of the circle center
   * @param LatLon $prev - coordinates of the previous point approximation
   * @param LatLon $next - coordinates of the next point approximation
   *
   * @return LatLon
   */
  public static function findCenterBetween($center, $prev, $next) {
    // If the next point in our current circle - do not look for it on the point of intersection, immediately return the next point.
    if (self::isInside($next, $center)) {
      return $prev;
    }
    // Otherwise - look for the intersection
    $az1 = self::getAzimuth($center, $prev);
    $az2 = self::getAzimuth($center, $next);
    $middle = self::getHalfAzimuth($az1, $az2);
    return self::getCoordinates($center, $middle);
  }

  /**
   * Returns the bearing from the $waypoint on the point $pos
   *
   * @param Waypoint $center
   * @param LatLon $pos
   *
   * @return int
   */
  public static function getAzimuth($center, $pos) {
    $latDiff = $pos->getLatitude()->getDegrees() - $center->getCenter()->getLatitude()->getDegrees();
    $lonDiff = $pos->getLongitude()->getDegrees() - $center->getCenter()->getLongitude()->getDegrees();
    // Тут оптимизация - быстрая проверка на 0, 90, 180 и 270 градусов.
    if ($latDiff == 0.0) {
      if ($lonDiff > 0) {
        return 0.0;
      }
      else {
        return 180.0;
      }
    }
    if ($lonDiff == 0.0) {
      if ($latDiff > 0) {
        return 90.0;
      }
      else {
        return 270.0;
      }
    }
    $tg = $latDiff / $lonDiff;
    $azimuth = 180.0 * atan($tg) / M_PI;
    if ($lonDiff < 0) {
      $azimuth = $azimuth + 180.0;
    }
    else {
      if ($latDiff < 0) {
        $azimuth = 360 + $azimuth;
      }
    }
    return $azimuth;
  }

  /**
   *
   * @param double $azimuth1
   * @param double $azimuth2
   *
   * @return double
   */
  public static function getHalfAzimuth($azimuth1, $azimuth2) {
    // Get the arithmetic mean between the bearings
    $halfAzimuth = ($azimuth1 + $azimuth2) / 2.0;
    // If it greater than 180 - take symmetric point
    if (abs($azimuth1 - $azimuth2) > 180.0) {
      $halfAzimuth -= 180.0;
    }
    // If you get a negative symmetric point - increase it to 360
    if ($halfAzimuth < 0) {
      $halfAzimuth += 360;
    }
    return $halfAzimuth;
  }

  /**
   * Returns the coordinates of the point on the circle that intersects
   * the line at a given bearing
   *
   * @param Waypoint center
   * @param double azimuth
   *
   * @return LatLon
   */
  public static function getCoordinates($center, $azimuth) {
    $latlon = $center->getCenter();

    $centerLat = $latlon->getLatitude()->getDegrees();
    $centerLon = $latlon->getLongitude()->getDegrees();

    $length = self::lengthForLatitude($centerLat);

    $radius = $center->getRadius();

    $latRadius = $radius / self::lengthForLatitude(0);
    $lonRadius = $radius / $length;

    if ($azimuth == 0.0) {
      return LatLon::fromDegrees($centerLat, $centerLon + $lonRadius);
    }
    if ($azimuth == 90.0) {
      return LatLon::fromDegrees($centerLat + $latRadius, $centerLon);
    }
    if ($azimuth == 180.0) {
      return LatLon::fromDegrees($centerLat, $centerLon - $lonRadius);
    }
    if ($azimuth == 270.0) {
      return LatLon::fromDegrees($centerLat - $latRadius, $centerLon);
    }

    $angleInRadians = M_PI * $azimuth / 180.0;

    $sin = sin($angleInRadians);
    $cos = cos($angleInRadians);

    $latDiff = $latRadius * $sin;
    $lonDiff = $lonRadius * $cos;

    $approxLat = $centerLat + $latDiff;
    $approxLon = $centerLon + $lonDiff;
    return LatLon::fromDegrees($approxLat, $approxLon);
  }

  /**
   *
   * @param Waypoint $position
   * @param LatLon $waypoint
   *
   * @return boolean
   */
  public static function isInside($position, $waypoint) {
    $center = $waypoint->getCenter();
    $latDiff = ($position->getLatitude()->getDegrees() - $center->getLatitude()->getDegrees()) * self::lengthForLatitude($position->getLatitude()->getDegrees());
    // Degree of latitude is always the same
    $lonDiff = ($position->getLongitude()->getDegrees() - $center->getLongitude()->getDegrees()) * self::lengthForLatitude(0);

    $distance = sqrt($latDiff * $latDiff + $lonDiff * $lonDiff);
    return $distance <= $waypoint->getRadius();
  }

  /**
   *
   * @param double $latitude
   *
   * @return double
   */
  public static function lengthForLatitude($latitude) {
    $latRounded = (int) abs($latitude);
    $result = isset(self::$lengthCache[$latRounded]) ? self::$lengthCache[$latRounded] : 0.0;
    if ($result == 0.0) {
      $result = self::distanceBetween($latRounded, 0.0, $latRounded, 1.0);
      self::$lengthCache[$latRounded] = $result;
    }
    return $result;
  }

  /**
   * Distance between two points
   *
   * @param $lt1 - latitude of the 1st point
   * @param $ln1 - longitude of the 1st point
   * @param $lt2 - latitude of the 2nd point
   * @param $ln2 - longitude of the 2nd point
   * @see http://gis-lab.info/qa/great-circles.html
   * @autor Michail Kobzarev <kobzarev@inforos.ru>
   */
  public function distanceBetween($lt1, $ln1, $lt2, $ln2) {

    // convert coordinates to radians
    $lat1 = $lt1 * M_PI / 180;
    $lat2 = $lt2 * M_PI / 180;
    $long1 = $ln1 * M_PI / 180;
    $long2 = $ln2 * M_PI / 180;

    // cosine and sine of the latitude and longitude difference
    $cl1 = cos($lat1);
    $cl2 = cos($lat2);
    $sl1 = sin($lat1);
    $sl2 = sin($lat2);
    $delta = $long2 - $long1;
    $cdelta = cos($delta);
    $sdelta = sin($delta);

    // calculating the length of a great circle
    $y = sqrt(pow($cl2 * $sdelta, 2) + pow($cl1 * $sl2 - $sl1 * $cl2 * $cdelta, 2));
    $x = $sl1 * $sl2 + $cl1 * $cl2 * $cdelta;

    //
    $ad = atan2($y, $x);
    $dist = $ad * self::EARTH_RADIUS;

    return $dist;
  }
}

