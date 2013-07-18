<?php
/**
 * @file
 * ent_customobject.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_customobject_eck_entity_type_info() {
$items = array(
       'ent_customobject' => array(
  'name' => 'ent_customobject',
  'label' => 'Custom object',
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
