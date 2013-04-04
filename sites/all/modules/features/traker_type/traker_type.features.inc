<?php
/**
 * @file
 * traker_type.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function traker_type_eck_bundle_info() {
  $items = array(
  'ent_traker_type_ent_traker_type' => array(
  'machine_name' => 'ent_traker_type_ent_traker_type',
  'entity_type' => 'ent_traker_type',
  'name' => 'ent_traker_type',
  'label' => 'Traker type',
),
  );
  return $items;
}
