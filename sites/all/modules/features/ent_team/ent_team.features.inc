<?php
/**
 * @file
 * ent_team.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function ent_team_eck_bundle_info() {
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

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_team_eck_entity_type_info() {
$items = array(
       'ent_team' => array(
  'name' => 'ent_team',
  'label' => 'Team',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'changed' => array(
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
  ),
),
  );
  return $items;
}
