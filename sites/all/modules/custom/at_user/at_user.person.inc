<?php

// @todo: Add access callback

/**
 * User "Person" page callback.
 *
 * @todo
 */
function at_user_person_page($user) {
  module_load_include('inc', 'user', 'user.pages');
  $main_profile = profile2_load_by_user($user, AIRTRIBUNE_USER_MAIN_PROFILE);
  $wrapper = entity_metadata_wrapper('profile2', $main_profile);
  $full_name = $wrapper->{AIRTRIBUNE_USER_FULLNAME_FIELD}->value();
  drupal_set_title($user->name);
  drupal_set_title($full_name['given'] . ' ' . $full_name['family']);
  return drupal_get_form('at_user_person_form', $user);
}


/**
 * Based on user_profile_form().
 *
 * @todo
 * Validate Optional URL field.
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


  $form['field_account_tiny_path']['#weight'] = $form['field_header_image']['#weight'] - 1;
  $form['field_account_tiny_path']['und'][0]['value']['#post_render'] = array('at_user_person_tiny_url_post_render');
  if (!empty($account->field_account_tiny_path['und'][0]['value'])) {
    $form['optional_url'] = array(
      '#type' => 'item',
      '#title' => t('Optional URL'),
      '#markup' => 'airtribune.com/' . $account->field_account_tiny_path['und'][0]['value'],
      '#weight' => $form['field_account_tiny_path']['#weight'],
    );
    $form['field_account_tiny_path']['#access'] = FALSE;
  }

  return $form;
}

/**
 * Form #after_build for at_user_person_form().
 */
function at_user_person_form_after_build($form, &$form_state) {
  $form['metatags']['#access'] = FALSE;
  return $form;
}

function at_user_person_tiny_url_post_render($content, $element) {
  $content = str_replace('<input', '<span id="optional-url-prefix">airtribune.com/ </span><input', $content);
  return $content;
}
