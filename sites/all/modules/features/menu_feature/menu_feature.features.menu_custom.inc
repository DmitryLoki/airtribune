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
    'language' => 'und',
    'i18n_mode' => '0',
  );
  // Exported menu: footer-menu.
  $menus['footer-menu'] = array(
    'menu_name' => 'footer-menu',
    'title' => 'Footer menu',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-solutions-organizers.
  $menus['menu-solutions-organizers'] = array(
    'menu_name' => 'menu-solutions-organizers',
    'title' => 'For organizers',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Account');
  t('Footer menu');
  t('For organizers');
  t('The <em>Account</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');


  return $menus;
}
