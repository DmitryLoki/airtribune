<?php

/**
 * @file
 * Provides Event settings form.
 */

/**
 * Form function to edit og_membership entity.
 */
function airtribune_event_settings_form($form, &$form_state, $event = FALSE) {
  // Event does not exist
  if (!$event) {
    drupal_not_found();
  }

  field_attach_form('node', $event, $form, $form_state);
  $unset_fields = array(
    'field_city',
    'group_group',
    'field_time_zone',
    'field_info',
    'field_contest_photos',
    'field_flying_site_photos',
    'field_collection_organizers',
    'field_selection',
    'field_contest_rules',
    'field_prizes',
    'field_schedule',
    'field_sample_schedule',
    'field_downloads',
    'field_hq_location',
    'field_address',
    'field_headquarter_info',
    'field_registration_sw',
    'field_points_file',
    'field_social_links',
    'field_twitter_widget_code',
    'field_headquarter_hotel',
    'og_roles_permissions',
    'group_contacs',
    '#fieldgroups',
    '#attached',
    '#group_children',
    '#groups',
    '#field_group_multiple',
    '#metatags',
    'field_contacts_email',
    'field_contacts_name',
    'field_position',
    'field_contacts_phone',    
    'fgm_node_pg_contest_form_group_contacs',
    'field_results_title',
    'field_results_summary',
    'field_core_id',
    'field_max_number_contestants',
    'field_gt_general',
    'field_gt_plane',
    'field_gt_train',
    'field_gt_car',
    'field_gt_bus',
    'field_gt_taxi',
    'field_device_id',
    'field_is_offline',
    'field_flying_info',
  );
  foreach ($unset_fields as $unset_field) {
    unset($form[$unset_field]);
  }
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Event name'),
    '#default_value' => $event->title,
    '#weight' => -1,
  );
  $form['field_country']['#weight'] = 0;
  $form['field_flying_site_ref']['#weight'] = 1;
  $form['field_tiny_path']['#weight'] = 2;
  $form['field_logo']['#weight'] = 3;
  $form['field_dates']['#weight'] = 4;
  $form['field_fai_category']['#weight'] = 5;
  $form['field_open_class']['#weight'] = 6;
  //$form['field_fai_category']['#type'] = 'select';
  /*// Load all available OG membership types & remove from array default OG membership.
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
  );*/
  
  $form['event'] = array(
    '#type' => 'value',
    '#value' => $event,
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
function airtribune_event_settings_form_submit($form, &$form_state) {
  $values = & $form_state['values'];
  $event = $values['event'];
  field_attach_submit('node', $event, $form, $form_state);
  drupal_set_message(t('Event settings updated.'));
  $event->title = $values['name'];
  node_save($event);
  //drupal_set_message(print_r(array_keys($form), TRUE));
  /*
  
  field_attach_submit('og_membership', $og_membership, $form, $form_state);
  og_membership_save($og_membership);
  /*$values = & $form_state['values'];

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
  $form_state['redirect'] = 'group-membership/' . $og_membership->id . '/edit';*/
}
