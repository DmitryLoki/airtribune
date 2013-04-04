<?php
/**
 * @file
 * ent_traker_type.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_traker_type_eck_entity_type_info() {
$items = array(
       'ent_traker_type' => array(
  'name' => 'ent_traker_type',
  'label' => 'Traker type',
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
