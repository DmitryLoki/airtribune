<?php

/**
 * @file
 * Provides OG membership edit form.
 */

/**
 * Form function to edit og_membership entity.
 */
function at_membership_form($form, &$form_state, $og_membership = FALSE) {
  // OG membership does not exist or it is not user membership.
  if (!$og_membership || $og_membership->entity_type != 'user') {
    drupal_not_found();
  }

  at_membership_set_breadcrumb($og_membership);
  field_attach_form('og_membership', $og_membership, $form, $form_state);

  // Load all available OG membership types & remove from array default OG membership.
  $all_memberships = at_membership_type_get_types();
  unset($all_memberships[OG_MEMBERSHIP_TYPE_DEFAULT]);
  // assign to array, which will be used in select element in form
  foreach ($all_memberships as $key => $value) {
    $select_membership[$key] = $value->description;
  }

  $form['og_membership_select'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => $select_membership,
    '#default_value' => $og_membership->type,
    '#weight' => 0,
  );

  // Markup some info about pilot.
  $membership = $form['#entity'];
  if ($membership->type == 'pg_contestant' && $membership->entity_type == 'user') {
    $user = user_load($membership->etid);

    $profile2 = profile2_load_by_user($membership->etid, 'main');
    $field = field_get_items('profile2', $profile2, 'field_full_name');
    $name = field_view_value('profile2', $profile2, 'field_full_name', $field[0]);

    $form['og_membership_info'] = array(
      '#type' => 'markup',
      '#markup' => '<p><strong>' . render($name) . '</strong> ' . $user->mail . '</p>',
      '#weight' => -1,
    );
  }

  $form['og_membership'] = array(
    '#type' => 'value',
    '#value' => $og_membership,
  );

  $form['actions']['#weight'] = 99;
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form submit handler: submits og_membership_edit_form information
 */
function at_membership_form_submit($form, &$form_state) {
  $values = & $form_state['values'];

  $og_membership = $values['og_membership'];
  // user change membership in form
  if ($values['og_membership_select'] != $og_membership->type) {
    // load values from old membership, to use for create new
    $gid = $og_membership->gid;
    $etid = $og_membership->etid;
    $og_membership_values['type'] = $values['og_membership_select'];

    // delete old membership
    og_membership_delete($og_membership->id);
    // assign new
    $og_membership = airtribune_og_membership_create('node', $gid, 'user', $etid, 'og_user_node', $og_membership_values);
  }

  field_attach_submit('og_membership', $og_membership, $form, $form_state);
  og_membership_save($og_membership);

  // If user change type of membership, we delete and create new membership,
  // also we need to change redirect after form submit, using new id.
  // If membership doesn't updated - user will be redirected on old url.
  $form_state['redirect'] = 'group-membership/' . $og_membership->id . '/edit';
  drupal_set_message('Membership data has been updated.');
}

/**
 * Helper function for OG membership breadcrumb.
 */
function at_membership_set_breadcrumb($og_membership) {
  $gid = $og_membership->gid;
  $group_type = $og_membership->group_type;

  if ($group_type == 'node') {
    $node = node_load($gid);
    $breadcrumb = array(
      l(t('Home'), '<front>'),
      l($node->title, 'node/' . $node->nid),
    );
  }
  else {
    $breadcrumb = array(
      l(t('Home'), '<front>'),
    );
  }
  drupal_set_breadcrumb($breadcrumb);
}

/**
 * Delete og_membership entity.
 */
function at_membership_delete($og_membership) {
  if (!empty($_POST['js']) && at_membership_access($og_membership, 'delete')) {
    og_membership_delete($og_membership->id);
    drupal_json_output(array('message' => t('Your participation has been successfully canceled.')));
  }
  else {
    drupal_access_denied();
  }
}
