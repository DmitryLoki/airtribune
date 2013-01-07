<?php
/**
 * @file
 * menu_feature.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function menu_feature_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: footer-menu.
  $menus['footer-menu'] = array(
    'menu_name' => 'footer-menu',
    'title' => 'Footer menu',
    'description' => NULL,
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer menu');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('User menu');


  return $menus;
}
