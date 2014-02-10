<?php
/**
 * @file
 * pg_nation_team.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function pg_nation_team_eck_bundle_info() {
  $items = array(
  'ent_team_pg_nation_team' => array(
  'machine_name' => 'ent_team_pg_nation_team',
  'entity_type' => 'ent_team',
  'name' => 'pg_nation_team',
  'label' => 'Paragliding Nation team',
),
  );
  return $items;
}
