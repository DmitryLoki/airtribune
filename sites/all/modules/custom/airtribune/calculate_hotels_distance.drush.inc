<?php

/**
 * @file
 * Drush command to calculate distances from headquarter to hotels.
 */

/**
 * Implements hook_drush_command().
 */
function calculate_hotels_distance_drush_command() {
  $items['calculate-hotels-distance'] = array(
    'description' => 'Calculate distances from headquarter to hotels.',
    'arguments' => array('Event ID' => 'The node ID'),
    'options' => array('limit' => 'Distance limit in kilometers'),
    'examples' => array('drush chd 5364 --limit=250' => 'Find all the objects within a radius of 250 kilometers.'),
    'required-arguments' => TRUE,
    'drupal dependencies' => array('entity'),
    'aliases' => array('chd'),
  );
  return $items;
}

/**
 * Command callback: calculate hotels distances.
 *
 *  @param int $nid
 *   The node ID.
 */
function drush_calculate_hotels_distance($nid) {
  $wrapper = entity_metadata_wrapper('node', (int) $nid);
  if ($wrapper->value() && $wrapper->getBundle() == 'pg_contest') {
    drush_log('Event: ' . $wrapper->title->value(), 'status');
    $location = $wrapper->field_hq_location->value();
    if ($location) {
      drush_log('HQ location: ' . $location['lat'] . ' ' . $location['lon'], 'status');
      $hq_location = array($location['lon'], $location['lat']);
      $limit = (float) drush_get_option('limit');
      if ($limit) {
        drush_log("Limit: $limit km", 'status');
      }
    }
    else {
      return drush_set_error('The node doesn\'t contain valid geographic data.');
    }
  }
  else {
    return drush_set_error('Sorry, it isn\'t a "pg_contest" node.');
  }
  drush_print();

  // Start calculation.
  timer_start(__FUNCTION__);

  $query = db_select('node', 'n');
  $query->join('field_data_field_location', 'l', 'n.nid = l.entity_id');
  $query
    ->fields('n', array('nid', 'title'))
    ->fields('l', array('field_location_lat', 'field_location_lon'))
    ->condition('n.type', 'accommodation')
    ->isNotNull('l.field_location_lat')
    ->isNotNull('l.field_location_lon');

  $result = $query->execute();

  $title_maxlength = 10;
  foreach ($result as $index => $record) {
    $location = array($record->field_location_lon, $record->field_location_lat);
    $distance = airtribune_calculate_distance($hq_location, $location) / 1000;
    if (!$limit || $limit > $distance) {
      $record->distance = str_pad(number_format($distance, 2), 9, ' ', STR_PAD_LEFT);
      $rows[] = (array) $record;
      $distances[$index] = $record->distance;
      $title_length = drupal_strlen($record->title);
      $title_maxlength = $title_length > $title_maxlength ? $title_length : $title_maxlength;
    }
  }

  if ($rows) {
    $header[] = array('Id', 'Title', 'Latitude', 'Longitude', 'Distance');
    $header[] = array(
      '-----',
      str_repeat('-', $title_maxlength),
      '---------------',
      '---------------',
      '---------',
    );

    array_multisort($distances, SORT_ASC, $rows);
    array_unshift($rows, $header[0], $header[1]);
    drush_print_table($rows, TRUE);
  }

  drush_log('Found hotels: ' . count($rows), 'status');
  drush_log('Execution time: ' . timer_read(__FUNCTION__) . ' ms', 'status');
}
