<?php
/**
 * @file
 * activity.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function activity_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function activity_node_info() {
  $items = array(
    'activity' => array(
      'name' => t('Activity'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
