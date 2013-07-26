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
  'ent_customobject_customobject' => array(
  'machine_name' => 'ent_customobject_customobject',
  'entity_type' => 'ent_customobject',
  'name' => 'customobject',
  'label' => 'Custom object',
),
  );
  return $items;
}
