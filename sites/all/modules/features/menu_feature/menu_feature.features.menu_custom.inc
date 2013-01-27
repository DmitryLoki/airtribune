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

  // Exported menu: account.
  $menus['account'] = array(
    'menu_name' => 'account',
    'title' => 'Account',
    'description' => 'The <em>Account</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
  );
  // Exported menu: footer-menu.
  $menus['footer-menu'] = array(
    'menu_name' => 'footer-menu',
    'title' => 'Footer menu',
    'description' => NULL,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Account');
  t('Footer menu');
  t('The <em>Account</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');


  return $menus;
}
