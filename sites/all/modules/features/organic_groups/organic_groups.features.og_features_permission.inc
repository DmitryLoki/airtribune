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

  // Exported og permission: 'node:contest:add user'
  $permissions['node:contest:add user'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:administer group'
  $permissions['node:contest:administer group'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:approve and deny subscription'
  $permissions['node:contest:approve and deny subscription'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:create race content'
  $permissions['node:contest:create race content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:delete any race content'
  $permissions['node:contest:delete any race content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:delete own race content'
  $permissions['node:contest:delete own race content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:manage members'
  $permissions['node:contest:manage members'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:manage permissions'
  $permissions['node:contest:manage permissions'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:manage roles'
  $permissions['node:contest:manage roles'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:subscribe'
  $permissions['node:contest:subscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:subscribe without approval'
  $permissions['node:contest:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:unsubscribe'
  $permissions['node:contest:unsubscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:update any race content'
  $permissions['node:contest:update any race content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:update group'
  $permissions['node:contest:update group'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:contest:update own race content'
  $permissions['node:contest:update own race content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
