<?php
/**
 * @file
 * pg_racetypes.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function pg_racetypes_eck_bundle_info() {
  $items = array(
  'ent_racetype_pg_racetype_od' => array(
  'machine_name' => 'ent_racetype_pg_racetype_od',
  'entity_type' => 'ent_racetype',
  'name' => 'pg_racetype_od',
  'label' => 'Paragliding race (Open Distance)',
),
  'ent_racetype_pg_racetype_rtg' => array(
  'machine_name' => 'ent_racetype_pg_racetype_rtg',
  'entity_type' => 'ent_racetype',
  'name' => 'pg_racetype_rtg',
  'label' => 'Paragliding race (Race to Goal)',
),
  'ent_racetype_pg_racetype_sr' => array(
  'machine_name' => 'ent_racetype_pg_racetype_sr',
  'entity_type' => 'ent_racetype',
  'name' => 'pg_racetype_sr',
  'label' => 'Paragliding race (Speed Run)',
),
  );
  return $items;
}
