<?php
/**
 * @file
 * ulogin_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ulogin_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: use ulogin.
  $permissions['use ulogin'] = array(
    'name' => 'use ulogin',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
    ),
    'module' => 'ulogin',
  );

  return $permissions;
}
