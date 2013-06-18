<?php
/**
 * @file
 * customobject.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function customobject_eck_bundle_info() {
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
