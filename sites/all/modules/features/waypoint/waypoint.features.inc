<?php
/**
 * @file
 * waypoint.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function waypoint_eck_bundle_info() {
  $items = array(
  'ent_point_waypoint' => array(
  'machine_name' => 'ent_point_waypoint',
  'entity_type' => 'ent_point',
  'name' => 'waypoint',
  'label' => 'waypoint',
),
  );
  return $items;
}
