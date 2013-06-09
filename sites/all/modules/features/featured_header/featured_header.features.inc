<?php
/**
 * @file
 * featured_header.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function featured_header_ctools_plugin_api() {
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
 * Implements hook_eck_bundle_info().
 */
function featured_header_eck_bundle_info() {
  $items = array(
  'ent_featured_header_ent_featured_header' => array(
  'machine_name' => 'ent_featured_header_ent_featured_header',
  'entity_type' => 'ent_featured_header',
  'name' => 'ent_featured_header',
  'label' => 'Featured header',
),
  );
  return $items;
}
