<?php
/**
 * @file
 * ent_tracker_type.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_tracker_type_eck_entity_type_info() {
$items = array(
       'ent_tracker_type' => array(
  'name' => 'ent_tracker_type',
  'label' => 'Tracker type',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
