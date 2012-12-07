<?php
/**
 * @file
 * advert.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function advert_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function advert_node_info() {
  $items = array(
    'advert' => array(
      'name' => t('Advertisement'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
