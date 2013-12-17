<?php

// module_load_include('inc', 'og_ui', 'og_ui.pages');

// Based on og_ui_subscribe() version 7.x-2.0-rc2
function at_reg_og_ui_subscribe($entity_type, $etid, $field_name = NULL) {
  global $user;
  $entity_info = entity_get_info($entity_type);
  if (!$entity_type || !$entity_info) {
    // Not a valid entity type.
    drupal_not_found();
    return;
  }
  $entity = entity_load_single($entity_type, $etid);
  if (!$entity || !og_is_group($entity_type, $entity)) {
    // Not a valid entity, or not a group.
    drupal_not_found();
    return;
  }

  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);

  if (empty($field_name)) {
    $field_name = og_get_best_group_audience_field('user', $user->uid, $entity_type, $bundle);
    if (empty($field_name)) {
      // User entity has no group audience field.
      drupal_not_found();
      return;
    }
  }

  $field = field_info_field($field_name);
  $instance = field_info_instance('user', $field_name, 'user');
  $account = user_load($user->uid);

  if (empty($instance) || !field_access('view', $field, 'user', $account)) {
    // Field name given is incorrect, or user doesn't have access to the field.
    drupal_not_found();
    return;
  }

  if (!$user->uid) {
    // Anonymous user can't request membership.
    $dest = drupal_get_destination();
    if (variable_get('user_register', 1)) {
      drupal_set_message(t('In order to join any group, you must <a href="!login">login</a>. After you have successfully done so, you will need to request membership again.', array('!login' => url("user/login", array('query' => $dest)))));
    }
    else {
      drupal_set_message(t('In order to join any group, you must <a href="!login">login</a> or <a href="!register">register</a> a new account. After you have successfully done so, you will need to request membership again.', array('!register' => url("user/register", array('query' => $dest)), '!login' => url("user/login", array('query' => $dest)))));
    }
    drupal_goto('user');
  }

  $redirect = FALSE;
  $message = '';

  $params = array();
  $params['@user'] = format_username($user);
  // Show the group name only if user has access to it.
  $params['@group'] = entity_access('view', $entity_type, $entity) ?  entity_label($entity_type, $entity) : t('Private group');

  if (og_is_member($entity_type, $id, 'user', $user, array(OG_STATE_BLOCKED))) {
    // User is blocked, access denied.
    drupal_access_denied();
    return;
  }
  if (og_is_member($entity_type, $id, 'user', $user, array(OG_STATE_PENDING))) {
    // User is pending, return them back.
    $message = $user->uid == $user->uid ? t('You already have a pending membership for the group @group.', $params) : t('@user already has a pending membership for the  the group @group.', $params);
    $redirect = TRUE;
  }

  if (og_is_member($entity_type, $id, 'user', $user, array(OG_STATE_ACTIVE))) {
    // User is already a member, return them back.
    $message = $user->uid == $user->uid ? t('You are already a member of the group @group.', $params) : t('@user is already a member of the group @group.', $params);
    $redirect = TRUE;
  }

  if (!$message && $field['cardinality'] != FIELD_CARDINALITY_UNLIMITED) {
    // Check if user is already registered as active or pending in the maximum
    // allowed values.
    $wrapper = entity_metadata_wrapper('user', $account->uid);
    if ($field['cardinality'] == 1) {
      $count = $wrapper->{$field_name}->value() ? 1 : 0;
    }
    else {
      $count = $wrapper->{$field_name}->count();
    }
    if ($count >= $field['cardinality']) {
      $message = t('You cannot register to this group, as you have reached your maximum allowed subscriptions.');
      $redirect = TRUE;
    }
  }

  if ($redirect) {
    drupal_set_message($message, 'warning');
    $url = entity_uri($entity_type, $entity);
    drupal_goto($url['path'], $url['options']);
  }

  if (og_user_access($entity_type, $id, 'subscribe', $user) || og_user_access($entity_type, $id, 'subscribe without approval', $user)) {
    // Show the user a subscription confirmation.
    return drupal_get_form('og_ui_confirm_subscribe', $entity_type, $id, $user, $field_name);
  }
}
