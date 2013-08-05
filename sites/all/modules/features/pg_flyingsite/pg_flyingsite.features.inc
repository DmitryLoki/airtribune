<?php
/**
 * @file
 * pg_flyingsite.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pg_flyingsite_ctools_plugin_api() {
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
 * Implements hook_node_info().
 */
function pg_flyingsite_node_info() {
  $items = array(
    'pg_flyingsite' => array(
      'name' => t('Flying site'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
