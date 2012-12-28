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
    'link_title' => 'Project',
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
    'link_title' => 'For Organizers',
    'options' => array(),
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
    'link_title' => 'For Pilots',
    'options' => array(),
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
    'link_title' => 'For the Viewers',
    'options' => array(),
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
    'link_title' => 'For Sponsors',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
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
  // Exported menu link: main-menu:events
  $menu_links['main-menu:events'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'events',
    'router_path' => 'events',
    'link_title' => 'Next events',
    'options' => array(),
    'module' => 'system',
    'hidden' => '1',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: main-menu:node/2
  $menu_links['main-menu:node/2'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
    'link_title' => 'Project',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: main-menu:node/3
  $menu_links['main-menu:node/3'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'Organizers',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: main-menu:node/4
  $menu_links['main-menu:node/4'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'Pilots',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: main-menu:node/5
  $menu_links['main-menu:node/5'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'Viewers',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: main-menu:node/6
  $menu_links['main-menu:node/6'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/6',
    'router_path' => 'node/%',
    'link_title' => 'Sponsors',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: user-menu:profile-main
  $menu_links['user-menu:profile-main'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'profile-main',
    'router_path' => 'profile-main',
    'link_title' => 'My main profile',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-main-profile-link',
        ),
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: user-menu:profile-organizer_profile
  $menu_links['user-menu:profile-organizer_profile'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'profile-organizer_profile',
    'router_path' => 'profile-organizer_profile',
    'link_title' => 'My organizer profile',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-organizer-profile-link',
        ),
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: user-menu:profile-pilot
  $menu_links['user-menu:profile-pilot'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'profile-pilot',
    'router_path' => 'profile-pilot',
    'link_title' => 'My pilot profile',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-pilot-profile-link',
        ),
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: user-menu:user
  $menu_links['user-menu:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'class' => array(
          0 => 'user-account-link',
        ),
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-10',
  );
  // Exported menu link: user-menu:user/logout
  $menu_links['user-menu:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'user-logout-link',
        ),
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('For Organizers');
  t('For Pilots');
  t('For Sponsors');
  t('For the Viewers');
  t('Home');
  t('Log out');
  t('My main profile');
  t('My organizer profile');
  t('My pilot profile');
  t('Organizers');
  t('Pilots');
  t('Project');
  t('Sponsors');
  t('User account');
  t('Viewers');


  return $menu_links;
}
