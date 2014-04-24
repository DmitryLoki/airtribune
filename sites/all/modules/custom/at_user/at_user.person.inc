<?php

// @todo: Add access callback

/**
 * User "Person" page callback.
 *
 * @todo
 */
function at_user_person_page($user) {
  module_load_include('inc', 'user', 'user.pages');
  drupal_set_title($user->name);
  // dsm($user);
  //~ return drupal_get_form('user_profile_form', $user);
  return drupal_get_form('at_user_person_form', $user);
  //~ return t('Comming soon.');
}


/**
 * Based on user_profile_form().
 *
 * @todo
 */
function at_user_person_form($form, &$form_state, $account, $category = 'account') {
  $field_names = array_keys(field_info_instances('user', 'user'));
  $field_allowed = array('field_account_tiny_path', 'field_header_image');
  $field_diff = array_diff($field_names, $field_allowed);



  global $user;




  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  // @todo Legacy support. Modules are encouraged to access the entity using
  //   $form_state. Remove in Drupal 8.
  $form['#user'] = $account;
  $form['#user_category'] = $category;

  if ($category == 'account') {
    // user_account_form($form, $form_state);
    // Attach field widgets.

    $langcode = entity_language('user', $account);
    field_attach_form('user', $account, $form, $form_state, $langcode);
  }
  foreach ($field_diff as $k => $field_name) {
    $form[$field_name]['#access'] = FALSE;
  }


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['basic_url'] = array(
    '#type' => 'item',
    '#title' => t('Basic URL'),
    '#markup' => 'airtribune.com/' . $user->uid,
  );
  // Add #after_build to hide metatags element.
  $form['#after_build'][] = 'at_user_person_form_after_build';

  $form['#validate'][] = 'user_profile_form_validate';
  // Add the final user profile form submit handler.
  $form['#submit'][] = 'user_profile_form_submit';



  return $form;
}

/**
 * Form #after_build for at_user_person_form().
 */
function at_user_person_form_after_build($form, &$form_state) {
  $form['metatags']['#access'] = FALSE;
  return $form;
}
