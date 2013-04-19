<?php
/**
 * @file
 * ent_race.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_race_eck_entity_type_info() {
$items = array(
       'ent_race' => array(
  'name' => 'ent_race',
  'label' => 'Race',
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
