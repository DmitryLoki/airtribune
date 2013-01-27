<?php

/**
 * @file
 * Plugin to handle the primary navigation links as dropdown menu.
 *
 * @see #2443
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtribune primary navigation'),
  'description' => t('Add the primary navigation links as dropdown menu.'),
  'category' => 'Airtribune',
  'render last' => TRUE,
);

/**
 * Outputs the primary_links.
 */
function airtribune_airtribune_primary_navigation_content_type_render($subtype, $conf, $panel_args) {
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_primary_navigation';

  $block = new stdClass();
  // Add $primary_nav variable, unlike built-in
  // $main_menu variable it supports drop-down menus.
  $block->content = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
  $block->content['#attached'] = array(
    'js' => array($plugin_path . '/airtribune_primary_navigation.js'),
    'css' => array($plugin_path . '/airtribune_primary_navigation.css'),
  );

  return $block;
}
