<?php
/**
 * @file
 * tracker_type.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function tracker_type_eck_bundle_info() {
  $items = array(
  'ent_tracker_type_tracker_type' => array(
  'machine_name' => 'ent_tracker_type_tracker_type',
  'entity_type' => 'ent_tracker_type',
  'name' => 'tracker_type',
  'label' => 'Tracker type',
),
  );
  return $items;
}
