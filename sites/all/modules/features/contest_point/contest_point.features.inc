<?php
/**
 * @file
 * contest_point.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function contest_point_eck_bundle_info() {
  $items = array(
  'ent_contest_point_contest_point' => array(
  'machine_name' => 'ent_contest_point_contest_point',
  'entity_type' => 'ent_contest_point',
  'name' => 'contest_point',
  'label' => 'Contest point',
),
  );
  return $items;
}
