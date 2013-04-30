<?php
/**
 * @file
 * pg_scoring_category.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pg_scoring_category_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function pg_scoring_category_node_info() {
  $items = array(
    'pg_scoring_category' => array(
      'name' => t('Scoring category'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
