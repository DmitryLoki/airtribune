<?php
/**
 * @file
 * organic_groups.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function organic_groups_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:pg_contest:add user'
  $permissions['node:pg_contest:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:administer group'
  $permissions['node:pg_contest:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:approve and deny subscription'
  $permissions['node:pg_contest:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:create advert content'
  $permissions['node:pg_contest:create advert content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:create day content'
  $permissions['node:pg_contest:create day content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:create newsblog content'
  $permissions['node:pg_contest:create newsblog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:pg_contest:create pg_scoring_category content'
  $permissions['node:pg_contest:create pg_scoring_category content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:delete any advert content'
  $permissions['node:pg_contest:delete any advert content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:delete any day content'
  $permissions['node:pg_contest:delete any day content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:delete any newsblog content'
  $permissions['node:pg_contest:delete any newsblog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:pg_contest:delete any pg_scoring_category content'
  $permissions['node:pg_contest:delete any pg_scoring_category content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:delete own advert content'
  $permissions['node:pg_contest:delete own advert content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:delete own day content'
  $permissions['node:pg_contest:delete own day content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:delete own newsblog content'
  $permissions['node:pg_contest:delete own newsblog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:pg_contest:delete own pg_scoring_category content'
  $permissions['node:pg_contest:delete own pg_scoring_category content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:manage members'
  $permissions['node:pg_contest:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:manage permissions'
  $permissions['node:pg_contest:manage permissions'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:manage roles'
  $permissions['node:pg_contest:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:subscribe'
  $permissions['node:pg_contest:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:pg_contest:subscribe without approval'
  $permissions['node:pg_contest:subscribe without approval'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:pg_contest:unsubscribe'
  $permissions['node:pg_contest:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:pg_contest:update any advert content'
  $permissions['node:pg_contest:update any advert content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:update any day content'
  $permissions['node:pg_contest:update any day content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:update any newsblog content'
  $permissions['node:pg_contest:update any newsblog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:pg_contest:update any pg_scoring_category content'
  $permissions['node:pg_contest:update any pg_scoring_category content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:update group'
  $permissions['node:pg_contest:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:update own advert content'
  $permissions['node:pg_contest:update own advert content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:pg_contest:update own day content'
  $permissions['node:pg_contest:update own day content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:pg_contest:update own newsblog content'
  $permissions['node:pg_contest:update own newsblog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:pg_contest:update own pg_scoring_category content'
  $permissions['node:pg_contest:update own pg_scoring_category content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
