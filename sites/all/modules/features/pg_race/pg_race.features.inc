<?php
/**
 * @file
 * pg_race.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function pg_race_eck_bundle_info() {
  $items = array(
  'ent_race_pg_race' => array(
  'machine_name' => 'ent_race_pg_race',
  'entity_type' => 'ent_race',
  'name' => 'pg_race',
  'label' => 'Paragliding race',
),
  );
  return $items;
}
