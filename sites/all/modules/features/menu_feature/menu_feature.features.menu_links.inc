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

  // Exported menu link: account:<front>
  $menu_links['account:<front>'] = array(
    'menu_name' => 'account',
    'link_path' => '<front>',
    'router_path' => '',
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
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: account:node/5363
  $menu_links['account:node/5363'] = array(
    'menu_name' => 'account',
    'link_path' => 'node/5363',
    'router_path' => 'node/%',
    'link_title' => 'My events',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: account:node/add/pg_contest
  $menu_links['account:node/add/pg_contest'] = array(
    'menu_name' => 'account',
    'link_path' => 'node/add/pg_contest',
    'router_path' => 'node/add',
    'link_title' => 'Create event',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-create-event-link',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: account:user
  $menu_links['account:user'] = array(
    'menu_name' => 'account',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My profile',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(),
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
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: footer-menu:<front>
  $menu_links['footer-menu:<front>'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '1',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: footer-menu:node/2
  $menu_links['footer-menu:node/2'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => 'The project is aimed at uniting paragliding community, viewers and sponsors.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: footer-menu:node/3
  $menu_links['footer-menu:node/3'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'For organizers',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: footer-menu:node/4
  $menu_links['footer-menu:node/4'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'For pilots',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: footer-menu:node/5
  $menu_links['footer-menu:node/5'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'For the viewers',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: footer-menu:node/6
  $menu_links['footer-menu:node/6'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'node/6',
    'router_path' => 'node/%',
    'link_title' => 'For sponsors',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('Create event');
  t('For organizers');
  t('For pilots');
  t('For sponsors');
  t('For the viewers');
  t('Home');
  t('My events');
  t('My profile');
  t('My registrations');
  t('Sign out');


  return $menu_links;
}
