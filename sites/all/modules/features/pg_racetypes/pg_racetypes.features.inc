<?php
/**
 * @file
 * pg_racetypes.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pg_racetypes_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function pg_racetypes_node_info() {
  $items = array(
    'pg_racetype_od' => array(
      'name' => t('Paragliding Race (Open Distance)'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'pg_racetype_rg' => array(
      'name' => t('Paragliding Race (Race To Goal)'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'pg_racetype_sr' => array(
      'name' => t('Paragliding Race (Speed Run)'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
