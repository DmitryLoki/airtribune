<?php
/**
 * @file
 * race.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function race_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function race_node_info() {
  $items = array(
    'race' => array(
      'name' => t('Race'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
