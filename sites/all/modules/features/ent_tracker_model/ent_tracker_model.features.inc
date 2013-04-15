<?php
/**
 * @file
 * ent_tracker_model.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_tracker_model_eck_entity_type_info() {
$items = array(
       'ent_tracker_model' => array(
  'name' => 'ent_tracker_model',
  'label' => 'Tracker model',
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
