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

  // Exported Metatag config instance: global.
  $config['global'] = array(
    'instance' => 'global',
    'config' => array(
      'title' => array(
        'value' => '[current-page:title] | [site:slogan]',
      ),
      'description' => array(
        'value' => 'Sports event on-line presentation. Full support with registrations, live tracking, 2D and 3D live view and replay.',
      ),
      'keywords' => array(
        'value' => 'live tracking, live-tracking, livetracking, sports events on-line, competitions live tracking',
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

  // Exported Metatag config instance: global:frontpage.
  $config['global:frontpage'] = array(
    'instance' => 'global:frontpage',
    'config' => array(
      'title' => array(
        'value' => 'Paragliding competition GPS live tracking | [site:name]',
      ),
      'description' => array(
        'value' => 'Create your competition site here! It\'s free! Full support with registrations, live tracking, 2D & 3D live view and replay.',
      ),
      'keywords' => array(
        'value' => 'live tracking, live-tracking, sports events on-line, paragliding competitions, paragliding live tracking',
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
        'value' => 'On-line sports events presentation. | [site:slogan]',
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
        'value' => '[node:title] | [site:slogan]',
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

  // Exported Metatag config instance: node:accommodation.
  $config['node:accommodation'] = array(
    'instance' => 'node:accommodation',
    'config' => array(
      'og:type' => array(
        'value' => 'hotel',
      ),
      'title' => array(
        'value' => '[node:title] | [site:slogan]',
      ),
    ),
  );

  // Exported Metatag config instance: node:newsblog.
  $config['node:newsblog'] = array(
    'instance' => 'node:newsblog',
    'config' => array(
      'title' => array(
        'value' => '[node:title]. [node:og-group-ref:0:title] | [site:slogan]',
      ),
    ),
  );

  // Exported Metatag config instance: node:pg_contest.
  $config['node:pg_contest'] = array(
    'instance' => 'node:pg_contest',
    'config' => array(
      'og:type' => array(
        'value' => 'sport',
      ),
      'title' => array(
        'value' => '[node:title] | [site:slogan]',
      ),
      'description' => array(
        'value' => 'Watch [node:title] on-line in 2D and 3D, photo and video. [node:summary]',
      ),
      'keywords' => array(
        'value' => '[node:title], paragliding, [node:field_location]',
      ),
    ),
  );

  // Exported Metatag config instance: node:pg_race.
  $config['node:pg_race'] = array(
    'instance' => 'node:pg_race',
    'config' => array(
      'og:type' => array(
        'value' => 'sport',
      ),
      'title' => array(
        'value' => '[node:title] | [node:og-group-ref:0:title] | [site:slogan]',
      ),
      'description' => array(
        'value' => 'Latest news from [node:og-group-ref:0:title] on [node:title]. Paragliding. [node:summary]',
      ),
      'keywords' => array(
        'value' => '[node:og-group-ref:0:title], paragliding, [node:field_location], live tracking, live-tracking, livetracking, sports events on-line, competitions live tracking',
      ),
    ),
  );

  // Exported Metatag config instance: user.
  $config['user'] = array(
    'instance' => 'user',
    'config' => array(
      'title' => array(
        'value' => '[user:profile-pilot:field_name_in_national_alphabet] | [site:slogan]',
      ),
      'og:title' => array(
        'value' => '[user:profile-pilot:field_name_in_national_alphabet]',
      ),
      'og:type' => array(
        'value' => 'profile',
      ),
    ),
  );

  return $config;
}
