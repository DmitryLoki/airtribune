<?php
/**
 * @file
 * device.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function device_eck_bundle_info() {
  $items = array(
  'ent_tracker_device' => array(
  'machine_name' => 'ent_tracker_device',
  'entity_type' => 'ent_tracker',
  'name' => 'device',
  'label' => 'Device',
),
  );
  return $items;
}
