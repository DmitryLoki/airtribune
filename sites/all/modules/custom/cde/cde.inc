<?php

// TODO:
function cde_user_register_before_execute(&$multiform, $index) {
  //
}


// TODO:
function cde_user_register_after_execute(&$multiform, $index) {
  // User register form and form_state
  $reg__form = $multiform['#subforms'][$index]['form'];
  $reg__form_state = $multiform['#subforms'][$index]['form_state'];
  
  // Newly added user uid
  $uid = $reg__form_state['values']['uid'];
  $user = user_load($uid);
  
  // TODO: Check for "if (!$user->uid)" error
  // TODO: Get OG form by tag
  
  $og_ui_confirm_subscribe_index = 'og_ui_confirm_subscribe';
  $og__form = $multiform['#subforms'][$og_ui_confirm_subscribe_index]['form'];
  $og__form_state = $multiform['#subforms'][$og_ui_confirm_subscribe_index]['form_state'];
  
  $og__args = $og__form_state['build_info']['args'];
  $group_type = $og__args[0];
  $gid = $og__args[1];
  // Arg in $og_args[2] contains $user data
  $field_name = $og__args[3];
  
  
  // TODO: Check
  // See og_ui_confirm_subscribe().
  $values = array('state' => og_user_access($group_type, $gid, 'subscribe without approval') ? OG_STATE_ACTIVE : OG_STATE_PENDING);
  $og_membership = og_membership_create($group_type, $gid, 'user', $uid, $field_name, $values);
  $og__form_state['og_membership'] = $og_membership;
  $og__form_state['build_info']['args'][2] = $user;
  $og__form['#entity'] = $og_membership;

  // TODO: Remove?
  /*
  if (og_user_access($group_type, $gid, 'subscribe without approval')) {
    // Hide the user request field.
    if (!empty($og__form[OG_MEMBERSHIP_REQUEST_FIELD])) {
      $og__form[OG_MEMBERSHIP_REQUEST_FIELD]['#access'] = FALSE;
    }
  }
  */
  
  $multiform['#subforms'][$og_ui_confirm_subscribe_index]['form'] = $og__form;
  $multiform['#subforms'][$og_ui_confirm_subscribe_index]['form_state'] = $og__form_state;
}
