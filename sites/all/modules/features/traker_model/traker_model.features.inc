<?php
/**
 * @file
 * traker_model.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function traker_model_eck_bundle_info() {
  $items = array(
  'ent_traker_model_ent_traker_model' => array(
  'machine_name' => 'ent_traker_model_ent_traker_model',
  'entity_type' => 'ent_traker_model',
  'name' => 'ent_traker_model',
  'label' => 'Traker model',
),
  );
  return $items;
}
