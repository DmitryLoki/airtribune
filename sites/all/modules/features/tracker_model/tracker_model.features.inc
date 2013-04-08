<?php
/**
 * @file
 * tracker_model.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function tracker_model_eck_bundle_info() {
  $items = array(
  'ent_tracker_model_ent_tracker_model' => array(
  'machine_name' => 'ent_tracker_model_ent_tracker_model',
  'entity_type' => 'ent_tracker_model',
  'name' => 'ent_tracker_model',
  'label' => 'Tracker model',
),
  );
  return $items;
}
