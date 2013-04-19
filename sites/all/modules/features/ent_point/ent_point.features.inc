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
  'properties' => array(),
),
  );
  return $items;
}
