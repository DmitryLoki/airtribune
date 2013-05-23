<?php
/**
 * @file
 * roles_and_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function roles_and_permissions_user_default_roles() {
  $roles = array();

  // Exported role: editor.
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => '5',
  );

  // Exported role: organizer.
  $roles['organizer'] = array(
    'name' => 'organizer',
    'weight' => '3',
  );

  // Exported role: pilot.
  $roles['pilot'] = array(
    'name' => 'pilot',
    'weight' => '2',
  );

  return $roles;
}
