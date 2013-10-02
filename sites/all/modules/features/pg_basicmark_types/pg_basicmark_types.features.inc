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
  'ent_basicmark_pg_landing' => array(
  'machine_name' => 'ent_basicmark_pg_landing',
  'entity_type' => 'ent_basicmark',
  'name' => 'pg_landing',
  'label' => 'Landing zone',
),
  'ent_basicmark_pg_takeoff' => array(
  'machine_name' => 'ent_basicmark_pg_takeoff',
  'entity_type' => 'ent_basicmark',
  'name' => 'pg_takeoff',
  'label' => 'Take Off',
),
  );
  return $items;
}
