<?php
/**
 * @file
 * ent_track.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_track_eck_entity_type_info() {
$items = array(
       'ent_track' => array(
  'name' => 'ent_track',
  'label' => 'track',
  'properties' => array(
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
