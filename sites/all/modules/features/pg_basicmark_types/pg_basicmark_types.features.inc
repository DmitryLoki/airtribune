<?php
/**
 * @file
 * pg_basicmark_types.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function pg_basicmark_types_eck_bundle_info() {
  $items = array(
  'ent_basicmark_pg_basicmark_lz' => array(
  'machine_name' => 'ent_basicmark_pg_basicmark_lz',
  'entity_type' => 'ent_basicmark',
  'name' => 'pg_basicmark_lz',
  'label' => 'Landing zone',
),
  'ent_basicmark_pg_basicmark_takeoff' => array(
  'machine_name' => 'ent_basicmark_pg_basicmark_takeoff',
  'entity_type' => 'ent_basicmark',
  'name' => 'pg_basicmark_takeoff',
  'label' => 'Take Off',
),
  );
  return $items;
}
