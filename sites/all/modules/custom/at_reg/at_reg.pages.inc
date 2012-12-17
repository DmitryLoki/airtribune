<?php

/**
 * Subscribe the current user to a group.
 *
 * @param $node
 *   The group node entity.
 * @param $uid
 *   Optional; The user ID of the subscribing user. If empty the current user
 *   will be used.
 */
function at_reg_subscribe($entity_type, $etid, $field_name = NULL) {
  
  // Set flag to show pilot profile at registration.
  // see at_reg_entity_load().
  at_reg_show_pilot_profile(TRUE);
  
  module_load_include('inc', 'og_ui', 'og_ui.pages');
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

  $wrapper = entity_metadata_wrapper('user', $user->uid);

  $field_info = field_info_field($field_name);
  if (empty($field_info) || empty($wrapper->{$field_name}) || !$wrapper->{$field_name}->access('view')) {
    // Field name given is incorrect, or user doesn't have access to the field.
    drupal_not_found();
    return;
  }

  /*
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
  */

  $redirect = FALSE;
  
  if($user->uid) {
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
  }

  if ($redirect) {
    drupal_set_message($message);
    $url = entity_uri($entity_type, $entity);
    drupal_goto($url['path'], $url['options']);
  }

  if (og_user_access($entity_type, $id, 'subscribe', $user) || og_user_access($entity_type, $id, 'subscribe without approval', $user)) {
    if($user->uid) {
      // Show the user a subscription confirmation.
      return drupal_get_form('og_ui_confirm_subscribe', $entity_type, $id, $user, $field_name);
    } else {
      // Prepare registration form.
      // og_ui_confirm_subscribe() $user value will be replaced by a new one after user registration.
      
      $subforms = array(
        array('og_ui_confirm_subscribe', $entity_type, $id, $user, $field_name, 'multiform_usage'),
        array('user_register_form', 'multiform_usage'),
      );
      // Add delayed submit.
      $subforms[] = 'delayed_submit';
      $form = call_user_func_array('multiform_get_form', $subforms);
      
      
      $button_keys = array_keys($form['buttons']);
      $form['buttons'][array_pop($button_keys)]['#printed'] = TRUE;
      
      return $form;
    }
  }
}




