<?php
/**
 * @file
 * ent_trackerset.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_trackerset_eck_entity_type_info() {
$items = array(
       'ent_trackerset' => array(
  'name' => 'ent_trackerset',
  'label' => 'Trackers set',
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
    'uuid' => array(
      'label' => 'UUID',
      'type' => 'uuid',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}
