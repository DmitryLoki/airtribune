<?php
/**
 * @file
 * seo.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function seo_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:contest.
  $config['node:contest'] = array(
    'instance' => 'node:contest',
    'config' => array(
      'og:type' => array(
        'value' => 'sport',
      ),
    ),
  );

  // Exported Metatag config instance: node:race.
  $config['node:race'] = array(
    'instance' => 'node:race',
    'config' => array(
      'og:type' => array(
        'value' => 'sport',
      ),
    ),
  );

  // Exported Metatag config instance: node:accommodation.
  $config['node:accommodation'] = array(
    'instance' => 'node:accommodation',
    'config' => array(
      'og:type' => array(
        'value' => 'hotel',
      ),
    ),
  );

  // Exported Metatag config instance: global.
  $config['global'] = array(
    'instance' => 'global',
    'config' => array(
      'title' => array(
        'value' => '[current-page:title] | [site:name]',
      ),
      'description' => array(
        'value' => 'Competition hosting and livetracking service for paragliding competitions organizers and fans.',
      ),
      'keywords' => array(
        'value' => 'Paragliding, live tracking, hang gliding, par ascending, gliding, paramotor, powered paragliding, powered hang gliding, extreme, extreme sports, flying, free flight, airsports, learn to fly, skywings',
      ),
      'canonical' => array(
        'value' => '[current-page:url:absolute]',
      ),
      'shortlink' => array(
        'value' => '[current-page:url:unaliased]',
      ),
      'og:site_name' => array(
        'value' => '[site:name]',
      ),
      'og:title' => array(
        'value' => '[current-page:title]',
      ),
      'og:type' => array(
        'value' => 'website',
      ),
      'og:url' => array(
        'value' => '[current-page:url:absolute]',
      ),
    ),
  );

  // Exported Metatag config instance: user.
  $config['user'] = array(
    'instance' => 'user',
    'config' => array(
      'title' => array(
        'value' => '[user:name] | [site:name]',
      ),
      'og:title' => array(
        'value' => '[user:profile-pilot:field-address:first_name] [user:profile-pilot:field-address:last_name]',
      ),
      'og:type' => array(
        'value' => 'profile',
      ),
    ),
  );

  // Exported Metatag config instance: global:frontpage.
  $config['global:frontpage'] = array(
    'instance' => 'global:frontpage',
    'config' => array(
      'title' => array(
        'value' => '[site:name]',
      ),
      'canonical' => array(
        'value' => '[site:url]',
      ),
      'shortlink' => array(
        'value' => '[site:url]',
      ),
      'og:type' => array(
        'value' => 'website',
      ),
      'og:title' => array(
        'value' => '[site:name]',
      ),
      'og:url' => array(
        'value' => '[site:url]',
      ),
    ),
  );

  // Exported Metatag config instance: node.
  $config['node'] = array(
    'instance' => 'node',
    'config' => array(
      'title' => array(
        'value' => '[node:title] | [site:name]',
      ),
      'description' => array(
        'value' => '[node:summary]',
      ),
      'og:title' => array(
        'value' => '[node:title]',
      ),
      'og:description' => array(
        'value' => '[node:summary]',
      ),
    ),
  );

  return $config;
}
