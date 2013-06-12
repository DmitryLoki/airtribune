<?php
/**
 * @file
 * pilot.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pilot_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function pilot_default_profile2_type() {
  $items = array();
  $items['pilot'] = entity_import('profile2_type', '{
    "userCategory" : false,
    "userView" : false,
    "type" : "pilot",
    "label" : "Pilot profile",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 1 },
    "rdf_mapping" : []
  }');
  return $items;
}
