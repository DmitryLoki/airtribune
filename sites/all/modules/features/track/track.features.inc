<?php
/**
 * @file
 * track.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function track_eck_bundle_info() {
  $items = array(
  'ent_track_track' => array(
  'machine_name' => 'ent_track_track',
  'entity_type' => 'ent_track',
  'name' => 'track',
  'label' => 'track',
),
  );
  return $items;
}
