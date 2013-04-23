<?php
/**
 * @file
 * day.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function day_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function day_node_info() {
  $items = array(
    'day' => array(
      'name' => t('Day'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
