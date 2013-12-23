<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

abstract class AtPointsWidgetFile {
  
  public $filename;
  public static $babbel_path = '/usr/local/bin/';
  static public $ext;
  static public $babbel_format;
  // first should go classes that have write method implemented
  public static $classes = array(
    'AtPointsWidgetCompGPSFile' => 'CompGPS',
    'AtPointsWidgetFSGeoFile'   => 'FSGeo',
    'AtPointsWidgetCupFile'     => 'cup', 
    'AtPointsWidgetOziFile'     => 'ozi',
    'AtPointsWidgetKmlFile'     => 'kml'
  );
  
  public function __construct($filename, $new = FALSE) {
    if ($new || static::check($filename)){
      $this->filename = $filename;
      geophp_load();
    }
    else {
      throw new Exception();
    }
  } 
  
  /**
   * Reads file into an array of point entities.
   */
  public function read() {
    $outfile = 'public://points_outfile_' . time() . '.wpt';
    $command = self::$babbel_path . 'gpsbabel -i ' . static::$babbel_format . ' -f ' . drupal_realpath($this->filename) . ' -o compegps -F ' . drupal_realpath($outfile);
    exec($command);    
    $compGPSReader = new AtPointsWidgetCompGPSFile($outfile);
    $points = $compGPSReader->read();
    file_unmanaged_delete($outfile);
    return $points;
  } 
  
  /**
   * Writes points into file in specified format.
   * @param array $points May be ids as well as entities.
   */
  public function write($points){
    return FALSE;
  }
  
  /**
   * Returns the filename extension.
   */
  static public function extension(){
    return static::$ext;
  }
  
  /**
   * Checks the file validity.
   */
  static public function check($filename) {
    $extension = drupal_substr($filename, -(strlen(static::$ext) + 1));
    return $extension == '.' . static::$ext;    
  }
}

class AtPointsWidgetFSGeoFile extends AtPointsWidgetFile {
  
  static public $ext = 'wpt';
  
  public function read() {
    $file_string = file_get_contents($this->filename);
    $strings = preg_split('/\v/', $file_string);
    $points = array(); 
    foreach ($strings as $string) {
      // Parse string.
      if (strlen($string) < 47) continue;
      $name = trim(drupal_substr($string, 0, 8));
      $lat = trim(drupal_substr($string, 12, 2));
      $lat_min = trim(drupal_substr($string, 15, 2));
      $lat_sec = trim(drupal_substr($string, 17, 4));
      $lat = $lat + $lat_min / 60 + $lat_sec / 3600;
      $lat = (drupal_substr($string, 10, 1) == 'N') ? $lat : -$lat;
      $lon = trim(drupal_substr($string, 29, 3));
      $lon_min = trim(drupal_substr($string, 33, 2));
      $lon_sec = trim(drupal_substr($string, 36, 4));
      $lon = $lon + $lon_min / 60 + $lon_sec / 3600;
      $lon = (drupal_substr($string, 27, 1) == 'E') ? $lon : -$lon;
      $alt = trim(drupal_substr($string, 43, 4));
      $comment = trim(drupal_substr($string, 49));
      
      //Create point entity.
      $coords = new Point($lon, $lat);
      //$values = geofield_get_values_from_geometry($coords);
      $point = entity_create(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, array('type' => 'contest_point'));
      $point_wrapper = entity_metadata_wrapper(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, $point);
      $point_wrapper->field_point_location->set(geofield_get_values_from_geometry($coords));
      $point_wrapper->field_point_description->set($comment);
      $point_wrapper->field_altitude->set($alt);
      $point_wrapper->title->set($name);
      $points[] = $point_wrapper->value();
    }
    return $points;
  }
  
  public function write($points) {
    $output = "\$FormatGEO\n";
    foreach ($points as $point) {
      $point_wrapper = entity_metadata_wrapper(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, $point);
      $lat = $point_wrapper->field_point_location->lat->value();
      $lon = $point_wrapper->field_point_location->lon->value();
      $lat_int = floor(abs($lat));
      $lat_min = floor((abs($lat) - $lat_int) * 60);
      $lat_sec = (abs($lat) - $lat_int - $lat_min / 60) * 3600;
      $lon_int = floor(abs($lon));
      $lon_min = floor((abs($lon) - $lon_int) * 60);
      $lon_sec = (abs($lon) - $lon_int - $lon_min / 60) * 3600;
      $line = sprintf("%-8s", $point_wrapper->title->value());
      $line .= '  ';
      $line .= ($lat > 0) ? 'N ' : 'S ';
      $line .= sprintf("%02d ", $lat_int);
      $line .= sprintf("%02d ", $lat_min);
      $line .= sprintf("%05.2F", $lat_sec);
      $line .= '    ';
      $line .= ($lat > 0) ? 'E ' : 'W ';
      $line .= sprintf("%02d ", $lon_int);
      $line .= sprintf("%02d ", $lon_min);
      $line .= sprintf("%05.2F", $lon_sec);
      $line .= '  ';
      $line .= sprintf("%4d", $point_wrapper->field_altitude->value());
      $line .= '  ';
      $line .= $point_wrapper->field_point_description->value();
      $line .= "\n";
      $output .= $line;
    }
    return file_save_data($output, $this->filename, FILE_EXISTS_REPLACE);
  }
  
  static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 10);
    return $check_string == '$FormatGEO';
  }
}

class AtPointsWidgetCompGPSFile extends AtPointsWidgetFile {
  
  static public $ext = 'wpt';
  
  static public $babbel_format = 'compegps';
  
  public function read() {
    $file_string = file_get_contents($this->filename);
    $strings = preg_split('/\v/', $file_string);
    $points = array(); 
    foreach ($strings as $string) {
      // Parse string.
      if (strlen($string) < 47) continue;
      $elements = preg_split('/\s+/', $string);
      if ($elements[0] != 'W') {
        continue;
      }
      $let1 = substr($elements[3], -1);
      $let2 = substr($elements[4], -1);
      if (strpos('EW', $let1) !== FALSE && strpos('NS', $let2) !== FALSE) {
        $lon = ($let1 == 'E') ? floatval($elements[3]) : -floatval($elements[3]);
        $lat = ($let2 == 'N') ? floatval($elements[4]) : -floatval($elements[4]);
      }
      elseif (strpos('EW', $let2) !== FALSE && strpos('NS', $let1) !== FALSE) {
        $lon = ($let2 == 'E') ? floatval($elements[4]) : -floatval($elements[4]);
        $lat = ($let1 == 'N') ? floatval($elements[3]) : -floatval($elements[3]);
      }
      else {
        continue;
      }
      
      //Create point entity.
      $coords = new Point($lon, $lat);
      $point = entity_create(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, array('type' => 'contest_point'));
      $point_wrapper = entity_metadata_wrapper(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, $point);
      $point_wrapper->field_point_location->set(geofield_get_values_from_geometry($coords));
      $point_wrapper->field_altitude->set(intval($elements[7]));
      $point_wrapper->field_point_description->set(isset($elements[8]) ? 
        implode(' ', array_slice($elements, 8)) : '');
      $point_wrapper->title->set($elements[1]);
      $points[] = $point_wrapper->value();
    }
    return $points;
  }
  
  public function write($points) {
    $output = "G  WGS 84\n";
    $output .= "U 1\n";
    foreach ($points as $point) {
      $point_wrapper = entity_metadata_wrapper(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, $point);
      $line = "W  ";
      $line .= $point_wrapper->title->value() . " ";
      $line .= "A ";
      $lat = $point_wrapper->field_point_location->lat->value();
      $lon = $point_wrapper->field_point_location->lon->value();
      $line .= abs($lat);
      $line .= ($lat > 0) ? 'N' : 'S';
      $line .= " ";
      $line .= abs($lon);
      $line .= ($lon > 0) ? 'E' : 'W';
      $line .= " ";
      $line .= date('d-M-Y') . " " . date('H:i:s') . " ";
      $line .= $point_wrapper->field_altitude->value() . " ";
      $line .= $point_wrapper->field_point_description->value() . "\n";
      $output .= $line;
    }
    return file_save_data($output, $this->filename, FILE_EXISTS_REPLACE);
  }
  
  static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 20);
    $strings = explode("\n", $check_string);
    return (trim($strings[0]) == 'G  WGS 84' && trim($strings[1]) == 'U  1');
  }
  
}

class AtPointsWidgetOziFile extends AtPointsWidgetFile {
 
  static public $ext = 'wpt';
  static public $babbel_format = 'ozi';
  
  static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 25);
    return $check_string == 'OziExplorer Waypoint File';    
  }
}

class AtPointsWidgetCupFile extends AtPointsWidgetFile {
  static public $ext = 'cup'; 
  static public $babbel_format = 'cup';
}

class AtPointsWidgetKmlFile extends AtPointsWidgetFile {
  static public $ext = 'kml';  
  static public $babbel_format = 'kml';
}