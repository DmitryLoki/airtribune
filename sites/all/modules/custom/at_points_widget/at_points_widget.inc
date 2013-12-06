<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

abstract class AtPointsWidgetFile {
  
  public $filename;
  public $babbel_path = '/usr/local/bin/';
  
  public function __construct($filename) {
    if (static::check($filename)){
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
  public function read($filename){}
  
  /**
   * Returns the filename extension.
   */
  public function extension(){}
  
  /**
   * Checks the file validity.
   */
  static public function check($filename){}
}

class AtPointsWidgetFSGeoFile extends AtPointsWidgetFile {
  
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
  
  public function extension(){
    return 'wpt';
  }
  
  static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 10);
    return $check_string == '$FormatGEO';
  }
}

class AtPointsWidgetCompGPSFile extends AtPointsWidgetFile {
  
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
  
  public function extension() {
    return 'wpt';
  }
  
  static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 9);
    return $check_string == 'G  WGS 84';
  }
  
}

class AtPointsWidgetOziFile extends AtPointsWidgetFile {
  
  public function read() {
    $outfile = $this->filename . '.mod';
    $command = $this->babbel_path . 'gpsbabel -i ozi -f ' . $this->filename . ' -o compegps -F ' . $outfile;
    exec($command);
    rename($outfile, $this->filename);
    $compGPSReader = new AtPointsWidgetCompGPSFile($this->filename);
    return $compGPSReader->read();
  }
  
  public function extension() {
    return 'wpt';
  }
  
  static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 25);
    return $check_string == 'OziExplorer Waypoint File';    
  }
}

class AtPointsWidgetCupFile extends AtPointsWidgetFile {
  
  public function read() {
    $outfile = substr($this->filename, 0, drupal_strlen($this->filename) - 4) . '.wpt';
    $command = $this->babbel_path . 'gpsbabel -i cup -f ' . $this->filename . ' -o compegps -F ' . $outfile;
    exec($command);
    $compGPSReader = new AtPointsWidgetCompGPSFile($outfile);
    $points = $compGPSReader->read();
    unlink($outfile);
    return $points;
  }
  
  public function extension() {
    return 'cup';
  }
  
  static function check($filename) {
    $extension = drupal_substr($filename, -4);
    return $extension == '.cup';    
  }
}