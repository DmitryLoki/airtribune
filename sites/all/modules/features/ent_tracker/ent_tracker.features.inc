<?php
/**
 * @file
 * ent_tracker.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_tracker_eck_entity_type_info() {
$items = array(
       'ent_tracker' => array(
  'name' => 'ent_tracker',
  'label' => 'Tracker',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'identifier' => array(
      'label' => 'Identifier',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
