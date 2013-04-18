<?php
/**
 * @file
 * ent_racetype.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_racetype_eck_entity_type_info() {
$items = array(
       'ent_racetype' => array(
  'name' => 'ent_racetype',
  'label' => 'Race type',
  'properties' => array(),
),
  );
  return $items;
}
