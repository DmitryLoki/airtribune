<?php
/**
 * @file
 * user_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function user_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: use hybridauth.
  $permissions['use hybridauth'] = array(
    'name' => 'use hybridauth',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
    ),
    'module' => 'hybridauth',
  );

  return $permissions;
}
