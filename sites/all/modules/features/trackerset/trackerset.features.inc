<?php
/**
 * @file
 * trackerset.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function trackerset_eck_bundle_info() {
  $items = array(
  'ent_trackerset_trackerset' => array(
  'machine_name' => 'ent_trackerset_trackerset',
  'entity_type' => 'ent_trackerset',
  'name' => 'trackerset',
  'label' => 'Trackers set',
),
  );
  return $items;
}
