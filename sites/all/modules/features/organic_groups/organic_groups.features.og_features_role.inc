<?php
/**
 * @file
 * organic_groups.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function organic_groups_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:pg_contest:co-organizer'.
  $roles['node:pg_contest:co-organizer'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'pg_contest',
    'name' => 'co-organizer',
  );

  // Exported OG Role: 'node:pg_contest:editor'.
  $roles['node:pg_contest:editor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'pg_contest',
    'name' => 'editor',
  );

  // Exported OG Role: 'node:pg_contest:retrieve manager'.
  $roles['node:pg_contest:retrieve manager'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'pg_contest',
    'name' => 'retrieve manager',
  );

  // Exported OG Role: 'node:hg_contest:co-organizer'.
  $roles['node:hg_contest:co-organizer'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'hg_contest',
    'name' => 'co-organizer',
  );

  // Exported OG Role: 'node:hg_contest:editor'.
  $roles['node:hg_contest:editor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'hg_contest',
    'name' => 'editor',
  );

  // Exported OG Role: 'node:hg_contest:retrieve manager'.
  $roles['node:hg_contest:retrieve manager'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'hg_contest',
    'name' => 'retrieve manager',
  );

  return $roles;
}
