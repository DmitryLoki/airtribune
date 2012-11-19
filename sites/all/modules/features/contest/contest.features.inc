<?php
/**
 * @file
 * contest.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function contest_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function contest_node_info() {
  $items = array(
    'contest' => array(
      'name' => t('Contest'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
