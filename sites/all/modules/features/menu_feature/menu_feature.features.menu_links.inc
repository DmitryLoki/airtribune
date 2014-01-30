<?php
/**
 * @file
 * menu_feature.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function menu_feature_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: account:account/events
  $menu_links['account:account/events'] = array(
    'menu_name' => 'account',
    'link_path' => 'account/events',
    'router_path' => 'account/events',
    'link_title' => 'My events',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-my-events-link',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: account:account/registrations
  $menu_links['account:account/registrations'] = array(
    'menu_name' => 'account',
    'link_path' => 'account/registrations',
    'router_path' => 'account/registrations',
    'link_title' => 'My registrations',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-my-registrations-link',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: account:user
  $menu_links['account:user'] = array(
    'menu_name' => 'account',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My profile',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'class' => array(
          0 => 'user-account-link',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: account:user/logout
  $menu_links['account:user/logout'] = array(
    'menu_name' => 'account',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Sign out',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-logout-link',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My events');
  t('My profile');
  t('My registrations');
  t('Sign out');


  return $menu_links;
}
