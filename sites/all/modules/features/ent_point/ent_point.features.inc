<?php
/**
 * @file
 * ent_point.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_point_eck_entity_type_info() {
$items = array(
       'ent_point' => array(
  'name' => 'ent_point',
  'label' => 'point',
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
