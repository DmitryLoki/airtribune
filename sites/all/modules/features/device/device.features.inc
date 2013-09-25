<?php
/**
 * @file
 * device.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function device_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function device_eck_bundle_info() {
  $items = array(
  'ent_tracker_device' => array(
  'machine_name' => 'ent_tracker_device',
  'entity_type' => 'ent_tracker',
  'name' => 'device',
  'label' => 'Device',
),
  );
  return $items;
}
