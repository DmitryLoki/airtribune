<?php
/**
 * @file
 * roles_and_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function roles_and_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration menu.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: access all views.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: access relations.
  $permissions['access relations'] = array(
    'name' => 'access relations',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: access site in maintenance mode.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: access site reports.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: access user profiles.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'editor',
    ),
    'module' => 'user',
  );

  // Exported permission: administer actions.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: administer advanced pane settings.
  $permissions['administer advanced pane settings'] = array(
    'name' => 'administer advanced pane settings',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: administer blocks.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(),
    'module' => 'block',
  );

  // Exported permission: administer content types.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: administer ctools access ruleset.
  $permissions['administer ctools access ruleset'] = array(
    'name' => 'administer ctools access ruleset',
    'roles' => array(),
    'module' => 'ctools_access_ruleset',
  );

  // Exported permission: administer custom content.
  $permissions['administer custom content'] = array(
    'name' => 'administer custom content',
    'roles' => array(),
    'module' => 'ctools_custom_content',
  );

  // Exported permission: administer entity translation.
  $permissions['administer entity translation'] = array(
    'name' => 'administer entity translation',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: administer features.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: administer field collections.
  $permissions['administer field collections'] = array(
    'name' => 'administer field collections',
    'roles' => array(),
    'module' => 'field_collection',
  );

  // Exported permission: administer filters.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: administer google analytics.
  $permissions['administer google analytics'] = array(
    'name' => 'administer google analytics',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: administer group.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(),
    'module' => 'og',
  );

  // Exported permission: administer image styles.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(),
    'module' => 'image',
  );

  // Exported permission: administer languages.
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: administer masquerade.
  $permissions['administer masquerade'] = array(
    'name' => 'administer masquerade',
    'roles' => array(),
    'module' => 'masquerade',
  );

  // Exported permission: administer media.
  $permissions['administer media'] = array(
    'name' => 'administer media',
    'roles' => array(),
    'module' => 'media',
  );

  // Exported permission: administer meta tags.
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'metatag',
  );

  // Exported permission: administer modules.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: administer nodes.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: administer openlayers.
  $permissions['administer openlayers'] = array(
    'name' => 'administer openlayers',
    'roles' => array(),
    'module' => 'openlayers_ui',
  );

  // Exported permission: administer page manager.
  $permissions['administer page manager'] = array(
    'name' => 'administer page manager',
    'roles' => array(),
    'module' => 'page_manager',
  );

  // Exported permission: administer pane access.
  $permissions['administer pane access'] = array(
    'name' => 'administer pane access',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: administer panels layouts.
  $permissions['administer panels layouts'] = array(
    'name' => 'administer panels layouts',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: administer panels styles.
  $permissions['administer panels styles'] = array(
    'name' => 'administer panels styles',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: administer pathauto.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: administer permissions.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: administer profile types.
  $permissions['administer profile types'] = array(
    'name' => 'administer profile types',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: administer profiles.
  $permissions['administer profiles'] = array(
    'name' => 'administer profiles',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: administer relation types.
  $permissions['administer relation types'] = array(
    'name' => 'administer relation types',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: administer relations.
  $permissions['administer relations'] = array(
    'name' => 'administer relations',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: administer robots.txt.
  $permissions['administer robots.txt'] = array(
    'name' => 'administer robots.txt',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'robotstxt',
  );

  // Exported permission: administer site configuration.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: administer software updates.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: administer themes.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: administer url aliases.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(),
    'module' => 'path',
  );

  // Exported permission: administer users.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: administer views.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: administer xmlsitemap.
  $permissions['administer xmlsitemap'] = array(
    'name' => 'administer xmlsitemap',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'xmlsitemap',
  );

  // Exported permission: block IP addresses.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: bypass node access.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: cancel account.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: change layouts in place editing.
  $permissions['change layouts in place editing'] = array(
    'name' => 'change layouts in place editing',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: change own username.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: create accommodation content.
  $permissions['create accommodation content'] = array(
    'name' => 'create accommodation content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create advert content.
  $permissions['create advert content'] = array(
    'name' => 'create advert content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create newsblog content.
  $permissions['create newsblog content'] = array(
    'name' => 'create newsblog content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create pg_contest content.
  $permissions['create pg_contest content'] = array(
    'name' => 'create pg_contest content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create pg_race content.
  $permissions['create pg_race content'] = array(
    'name' => 'create pg_race content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: create relations.
  $permissions['create relations'] = array(
    'name' => 'create relations',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: create url aliases.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(),
    'module' => 'path',
  );

  // Exported permission: delete any accommodation content.
  $permissions['delete any accommodation content'] = array(
    'name' => 'delete any accommodation content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any advert content.
  $permissions['delete any advert content'] = array(
    'name' => 'delete any advert content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any newsblog content.
  $permissions['delete any newsblog content'] = array(
    'name' => 'delete any newsblog content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any pg_contest content.
  $permissions['delete any pg_contest content'] = array(
    'name' => 'delete any pg_contest content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any pg_race content.
  $permissions['delete any pg_race content'] = array(
    'name' => 'delete any pg_race content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own accommodation content.
  $permissions['delete own accommodation content'] = array(
    'name' => 'delete own accommodation content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own advert content.
  $permissions['delete own advert content'] = array(
    'name' => 'delete own advert content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own newsblog content.
  $permissions['delete own newsblog content'] = array(
    'name' => 'delete own newsblog content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own pg_contest content.
  $permissions['delete own pg_contest content'] = array(
    'name' => 'delete own pg_contest content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own pg_race content.
  $permissions['delete own pg_race content'] = array(
    'name' => 'delete own pg_race content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete relations.
  $permissions['delete relations'] = array(
    'name' => 'delete relations',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: display drupal links.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(),
    'module' => 'admin_menu',
  );

  // Exported permission: eck add bundles.
  $permissions['eck add bundles'] = array(
    'name' => 'eck add bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_point bundles.
  $permissions['eck add ent_point bundles'] = array(
    'name' => 'eck add ent_point bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_point waypoint entities.
  $permissions['eck add ent_point waypoint entities'] = array(
    'name' => 'eck add ent_point waypoint entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_track bundles.
  $permissions['eck add ent_track bundles'] = array(
    'name' => 'eck add ent_track bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_track track entities.
  $permissions['eck add ent_track track entities'] = array(
    'name' => 'eck add ent_track track entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_tracker bundles.
  $permissions['eck add ent_tracker bundles'] = array(
    'name' => 'eck add ent_tracker bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_tracker device entities.
  $permissions['eck add ent_tracker device entities'] = array(
    'name' => 'eck add ent_tracker device entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_trackerset bundles.
  $permissions['eck add ent_trackerset bundles'] = array(
    'name' => 'eck add ent_trackerset bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add ent_trackerset trackerset entities.
  $permissions['eck add ent_trackerset trackerset entities'] = array(
    'name' => 'eck add ent_trackerset trackerset entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add entities.
  $permissions['eck add entities'] = array(
    'name' => 'eck add entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add entity types.
  $permissions['eck add entity types'] = array(
    'name' => 'eck add entity types',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer bundles.
  $permissions['eck administer bundles'] = array(
    'name' => 'eck administer bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_point bundles.
  $permissions['eck administer ent_point bundles'] = array(
    'name' => 'eck administer ent_point bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_point waypoint entities.
  $permissions['eck administer ent_point waypoint entities'] = array(
    'name' => 'eck administer ent_point waypoint entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_track bundles.
  $permissions['eck administer ent_track bundles'] = array(
    'name' => 'eck administer ent_track bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_track track entities.
  $permissions['eck administer ent_track track entities'] = array(
    'name' => 'eck administer ent_track track entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_tracker bundles.
  $permissions['eck administer ent_tracker bundles'] = array(
    'name' => 'eck administer ent_tracker bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_tracker device entities.
  $permissions['eck administer ent_tracker device entities'] = array(
    'name' => 'eck administer ent_tracker device entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_trackerset bundles.
  $permissions['eck administer ent_trackerset bundles'] = array(
    'name' => 'eck administer ent_trackerset bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer ent_trackerset trackerset entities.
  $permissions['eck administer ent_trackerset trackerset entities'] = array(
    'name' => 'eck administer ent_trackerset trackerset entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer entities.
  $permissions['eck administer entities'] = array(
    'name' => 'eck administer entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer entity types.
  $permissions['eck administer entity types'] = array(
    'name' => 'eck administer entity types',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete bundles.
  $permissions['eck delete bundles'] = array(
    'name' => 'eck delete bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_point bundles.
  $permissions['eck delete ent_point bundles'] = array(
    'name' => 'eck delete ent_point bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_point waypoint entities.
  $permissions['eck delete ent_point waypoint entities'] = array(
    'name' => 'eck delete ent_point waypoint entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_track bundles.
  $permissions['eck delete ent_track bundles'] = array(
    'name' => 'eck delete ent_track bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_track track entities.
  $permissions['eck delete ent_track track entities'] = array(
    'name' => 'eck delete ent_track track entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_tracker bundles.
  $permissions['eck delete ent_tracker bundles'] = array(
    'name' => 'eck delete ent_tracker bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_tracker device entities.
  $permissions['eck delete ent_tracker device entities'] = array(
    'name' => 'eck delete ent_tracker device entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_trackerset bundles.
  $permissions['eck delete ent_trackerset bundles'] = array(
    'name' => 'eck delete ent_trackerset bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete ent_trackerset trackerset entities.
  $permissions['eck delete ent_trackerset trackerset entities'] = array(
    'name' => 'eck delete ent_trackerset trackerset entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete entities.
  $permissions['eck delete entities'] = array(
    'name' => 'eck delete entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete entity types.
  $permissions['eck delete entity types'] = array(
    'name' => 'eck delete entity types',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit bundles.
  $permissions['eck edit bundles'] = array(
    'name' => 'eck edit bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_point bundles.
  $permissions['eck edit ent_point bundles'] = array(
    'name' => 'eck edit ent_point bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_point waypoint entities.
  $permissions['eck edit ent_point waypoint entities'] = array(
    'name' => 'eck edit ent_point waypoint entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_track bundles.
  $permissions['eck edit ent_track bundles'] = array(
    'name' => 'eck edit ent_track bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_track track entities.
  $permissions['eck edit ent_track track entities'] = array(
    'name' => 'eck edit ent_track track entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_tracker bundles.
  $permissions['eck edit ent_tracker bundles'] = array(
    'name' => 'eck edit ent_tracker bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_tracker device entities.
  $permissions['eck edit ent_tracker device entities'] = array(
    'name' => 'eck edit ent_tracker device entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_trackerset bundles.
  $permissions['eck edit ent_trackerset bundles'] = array(
    'name' => 'eck edit ent_trackerset bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit ent_trackerset trackerset entities.
  $permissions['eck edit ent_trackerset trackerset entities'] = array(
    'name' => 'eck edit ent_trackerset trackerset entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit entities.
  $permissions['eck edit entities'] = array(
    'name' => 'eck edit entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit entity types.
  $permissions['eck edit entity types'] = array(
    'name' => 'eck edit entity types',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list bundles.
  $permissions['eck list bundles'] = array(
    'name' => 'eck list bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_point bundles.
  $permissions['eck list ent_point bundles'] = array(
    'name' => 'eck list ent_point bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_point waypoint entities.
  $permissions['eck list ent_point waypoint entities'] = array(
    'name' => 'eck list ent_point waypoint entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_track bundles.
  $permissions['eck list ent_track bundles'] = array(
    'name' => 'eck list ent_track bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_track track entities.
  $permissions['eck list ent_track track entities'] = array(
    'name' => 'eck list ent_track track entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_tracker bundles.
  $permissions['eck list ent_tracker bundles'] = array(
    'name' => 'eck list ent_tracker bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_tracker device entities.
  $permissions['eck list ent_tracker device entities'] = array(
    'name' => 'eck list ent_tracker device entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_trackerset bundles.
  $permissions['eck list ent_trackerset bundles'] = array(
    'name' => 'eck list ent_trackerset bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list ent_trackerset trackerset entities.
  $permissions['eck list ent_trackerset trackerset entities'] = array(
    'name' => 'eck list ent_trackerset trackerset entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list entities.
  $permissions['eck list entities'] = array(
    'name' => 'eck list entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list entity types.
  $permissions['eck list entity types'] = array(
    'name' => 'eck list entity types',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view ent_point waypoint entities.
  $permissions['eck view ent_point waypoint entities'] = array(
    'name' => 'eck view ent_point waypoint entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view ent_track track entities.
  $permissions['eck view ent_track track entities'] = array(
    'name' => 'eck view ent_track track entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view ent_tracker device entities.
  $permissions['eck view ent_tracker device entities'] = array(
    'name' => 'eck view ent_tracker device entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view ent_trackerset trackerset entities.
  $permissions['eck view ent_trackerset trackerset entities'] = array(
    'name' => 'eck view ent_trackerset trackerset entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view entities.
  $permissions['eck view entities'] = array(
    'name' => 'eck view entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: edit any accommodation content.
  $permissions['edit any accommodation content'] = array(
    'name' => 'edit any accommodation content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any advert content.
  $permissions['edit any advert content'] = array(
    'name' => 'edit any advert content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any main profile.
  $permissions['edit any main profile'] = array(
    'name' => 'edit any main profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit any newsblog content.
  $permissions['edit any newsblog content'] = array(
    'name' => 'edit any newsblog content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any organizer_profile profile.
  $permissions['edit any organizer_profile profile'] = array(
    'name' => 'edit any organizer_profile profile',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: edit any pg_contest content.
  $permissions['edit any pg_contest content'] = array(
    'name' => 'edit any pg_contest content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any pg_race content.
  $permissions['edit any pg_race content'] = array(
    'name' => 'edit any pg_race content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any pilot profile.
  $permissions['edit any pilot profile'] = array(
    'name' => 'edit any pilot profile',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: edit field_pg_contestant_status.
  $permissions['edit field_pg_contestant_status'] = array(
    'name' => 'edit field_pg_contestant_status',
    'roles' => array(
      0 => 'admin',
      1 => 'administrator',
      2 => 'organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: edit field_tracker.
  $permissions['edit field_tracker'] = array(
    'name' => 'edit field_tracker',
    'roles' => array(
      0 => 'admin',
      1 => 'administrator',
      2 => 'organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: edit media.
  $permissions['edit media'] = array(
    'name' => 'edit media',
    'roles' => array(),
    'module' => 'media',
  );

  // Exported permission: edit meta tags.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'metatag',
  );

  // Exported permission: edit node original values.
  $permissions['edit node original values'] = array(
    'name' => 'edit node original values',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: edit node translation shared fields.
  $permissions['edit node translation shared fields'] = array(
    'name' => 'edit node translation shared fields',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: edit og_roles_permissions.
  $permissions['edit og_roles_permissions'] = array(
    'name' => 'edit og_roles_permissions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: edit original values.
  $permissions['edit original values'] = array(
    'name' => 'edit original values',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: edit own accommodation content.
  $permissions['edit own accommodation content'] = array(
    'name' => 'edit own accommodation content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own advert content.
  $permissions['edit own advert content'] = array(
    'name' => 'edit own advert content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own main profile.
  $permissions['edit own main profile'] = array(
    'name' => 'edit own main profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit own newsblog content.
  $permissions['edit own newsblog content'] = array(
    'name' => 'edit own newsblog content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own organizer_profile profile.
  $permissions['edit own organizer_profile profile'] = array(
    'name' => 'edit own organizer_profile profile',
    'roles' => array(
      0 => 'organizer',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit own pg_contest content.
  $permissions['edit own pg_contest content'] = array(
    'name' => 'edit own pg_contest content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own pg_race content.
  $permissions['edit own pg_race content'] = array(
    'name' => 'edit own pg_race content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own pilot profile.
  $permissions['edit own pilot profile'] = array(
    'name' => 'edit own pilot profile',
    'roles' => array(
      0 => 'pilot',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit relations.
  $permissions['edit relations'] = array(
    'name' => 'edit relations',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: edit translation shared fields.
  $permissions['edit translation shared fields'] = array(
    'name' => 'edit translation shared fields',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: export relation types.
  $permissions['export relation types'] = array(
    'name' => 'export relation types',
    'roles' => array(),
    'module' => 'relation',
  );

  // Exported permission: flush caches.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(),
    'module' => 'admin_menu',
  );

  // Exported permission: geocoder_service_all_handlers.
  $permissions['geocoder_service_all_handlers'] = array(
    'name' => 'geocoder_service_all_handlers',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_exif.
  $permissions['geocoder_service_handler_exif'] = array(
    'name' => 'geocoder_service_handler_exif',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_google.
  $permissions['geocoder_service_handler_google'] = array(
    'name' => 'geocoder_service_handler_google',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_gpx.
  $permissions['geocoder_service_handler_gpx'] = array(
    'name' => 'geocoder_service_handler_gpx',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_json.
  $permissions['geocoder_service_handler_json'] = array(
    'name' => 'geocoder_service_handler_json',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_kml.
  $permissions['geocoder_service_handler_kml'] = array(
    'name' => 'geocoder_service_handler_kml',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_latlon.
  $permissions['geocoder_service_handler_latlon'] = array(
    'name' => 'geocoder_service_handler_latlon',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_mapquest_nominatim.
  $permissions['geocoder_service_handler_mapquest_nominatim'] = array(
    'name' => 'geocoder_service_handler_mapquest_nominatim',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_wkt.
  $permissions['geocoder_service_handler_wkt'] = array(
    'name' => 'geocoder_service_handler_wkt',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_yahoo.
  $permissions['geocoder_service_handler_yahoo'] = array(
    'name' => 'geocoder_service_handler_yahoo',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: geocoder_service_handler_yandex.
  $permissions['geocoder_service_handler_yandex'] = array(
    'name' => 'geocoder_service_handler_yandex',
    'roles' => array(),
    'module' => 'geocoder',
  );

  // Exported permission: import media.
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(),
    'module' => 'media',
  );

  // Exported permission: manage ent_point properties.
  $permissions['manage ent_point properties'] = array(
    'name' => 'manage ent_point properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: manage ent_track properties.
  $permissions['manage ent_track properties'] = array(
    'name' => 'manage ent_track properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: manage ent_tracker properties.
  $permissions['manage ent_tracker properties'] = array(
    'name' => 'manage ent_tracker properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: manage ent_trackerset properties.
  $permissions['manage ent_trackerset properties'] = array(
    'name' => 'manage ent_trackerset properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: manage features.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: masquerade as admin.
  $permissions['masquerade as admin'] = array(
    'name' => 'masquerade as admin',
    'roles' => array(),
    'module' => 'masquerade',
  );

  // Exported permission: masquerade as user.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(),
    'module' => 'masquerade',
  );

  // Exported permission: notify of path changes.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: opt-in or out of tracking.
  $permissions['opt-in or out of tracking'] = array(
    'name' => 'opt-in or out of tracking',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: select account cancellation method.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: toggle field translatability.
  $permissions['toggle field translatability'] = array(
    'name' => 'toggle field translatability',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: translate admin strings.
  $permissions['translate admin strings'] = array(
    'name' => 'translate admin strings',
    'roles' => array(),
    'module' => 'i18n_string',
  );

  // Exported permission: translate any entity.
  $permissions['translate any entity'] = array(
    'name' => 'translate any entity',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: translate interface.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: translate node entities.
  $permissions['translate node entities'] = array(
    'name' => 'translate node entities',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: translate user-defined strings.
  $permissions['translate user-defined strings'] = array(
    'name' => 'translate user-defined strings',
    'roles' => array(),
    'module' => 'i18n_string',
  );

  // Exported permission: use PHP for title patterns.
  $permissions['use PHP for title patterns'] = array(
    'name' => 'use PHP for title patterns',
    'roles' => array(),
    'module' => 'auto_nodetitle',
  );

  // Exported permission: use PHP for tracking visibility.
  $permissions['use PHP for tracking visibility'] = array(
    'name' => 'use PHP for tracking visibility',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: use page manager.
  $permissions['use page manager'] = array(
    'name' => 'use page manager',
    'roles' => array(),
    'module' => 'page_manager',
  );

  // Exported permission: use panels caching features.
  $permissions['use panels caching features'] = array(
    'name' => 'use panels caching features',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: use panels dashboard.
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: use panels in place editing.
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: use panels locks.
  $permissions['use panels locks'] = array(
    'name' => 'use panels locks',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: view any main profile.
  $permissions['view any main profile'] = array(
    'name' => 'view any main profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view any organizer_profile profile.
  $permissions['view any organizer_profile profile'] = array(
    'name' => 'view any organizer_profile profile',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view any pilot profile.
  $permissions['view any pilot profile'] = array(
    'name' => 'view any pilot profile',
    'roles' => array(
      0 => 'authenticated user',
      1 => 'pilot',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view field_pg_contestant_status.
  $permissions['view field_pg_contestant_status'] = array(
    'name' => 'view field_pg_contestant_status',
    'roles' => array(
      0 => 'admin',
      1 => 'administrator',
      2 => 'organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: view field_tracker.
  $permissions['view field_tracker'] = array(
    'name' => 'view field_tracker',
    'roles' => array(
      0 => 'admin',
      1 => 'administrator',
      2 => 'organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: view media.
  $permissions['view media'] = array(
    'name' => 'view media',
    'roles' => array(
      0 => 'admin',
      1 => 'anonymous user',
      2 => 'authenticated user',
      3 => 'organizer',
      4 => 'pilot',
    ),
    'module' => 'media',
  );

  // Exported permission: view og_roles_permissions.
  $permissions['view og_roles_permissions'] = array(
    'name' => 'view og_roles_permissions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: view own main profile.
  $permissions['view own main profile'] = array(
    'name' => 'view own main profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view own organizer_profile profile.
  $permissions['view own organizer_profile profile'] = array(
    'name' => 'view own organizer_profile profile',
    'roles' => array(
      0 => 'editor',
      1 => 'organizer',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view own pilot profile.
  $permissions['view own pilot profile'] = array(
    'name' => 'view own pilot profile',
    'roles' => array(
      0 => 'pilot',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: view pane admin links.
  $permissions['view pane admin links'] = array(
    'name' => 'view pane admin links',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      0 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(),
    'module' => 'system',
  );

  return $permissions;
}
