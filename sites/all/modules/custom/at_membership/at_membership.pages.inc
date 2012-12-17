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
  $values = &$form_state['values'];

  $og_membership = $values['og_membership'];


  field_attach_submit('og_membership', $og_membership, $form, $form_state);
  $og_membership = og_membership_save($og_membership);
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
