<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

abstract class atPointsWidgetFile {
  
  public $filename;
  
  public function __construct($filename) {
    if (self::check($filename)){
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
  public static function check($filename);
}

class atPointsWidgetFSGeoFile extends atPointsWidgetFile {
  
  public function read($filename) {
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
      $point_wrapper->title->set($name);
      $points[] = $point_wrapper->value();
    }
    return $points;
  }
  
  public function extension(){
    return 'wpt';
  }
  
  public static function check($filename) {
    $check_string = file_get_contents($filename, FALSE, NULL, -1, 10);
    return $check_string == '$FormatGEO';
  }
}
