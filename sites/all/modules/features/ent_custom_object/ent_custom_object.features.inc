<?php
/**
 * @file
 * ent_custom_object.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function ent_custom_object_eck_bundle_info() {
  $items = array(
  'custom_object_custom_object' => array(
  'machine_name' => 'custom_object_custom_object',
  'entity_type' => 'custom_object',
  'name' => 'custom_object',
  'label' => 'Custom object',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_custom_object_eck_entity_type_info() {
$items = array(
       'custom_object' => array(
  'name' => 'custom_object',
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
