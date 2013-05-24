<?php

/**
 * @file
 * Plugin to provide access control to pilot's memberships.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Access to view pilot\'s memberships'),
  'description' => t('Control access to "My registrations" page.'),
  'callback' => 'at_membership_memberships_view_access_check',
  'summary' => 'at_membership_memberships_view_access_summary',
  'required context' => new ctools_context_required(t('User'), 'user'),
);

/**
 * Check for access.
 */
function at_membership_memberships_view_access_check($conf, $context) {
  global $user;
  return user_access('view any og memberships') || (user_access('view own og memberships') && $user->uid == $context->data->uid);
}

/**
 * Provide a summary description.
 */
function at_membership_memberships_view_access_summary($conf, $context) {
  return t('Logged in user can view pilot\'s memberships.');
}
