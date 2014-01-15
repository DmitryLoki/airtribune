<?php
/**
 * @file
 * hg_contest.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function hg_contest_ctools_plugin_api() {
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
function hg_contest_node_info() {
  $items = array(
    'hg_contest' => array(
      'name' => t('Hang Gliding Contest'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
