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
    'field_open_class',
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
  if (module_exists('at_points_widget')) {
    $form['at_points_widget'] = array(
      '#weight' => 6,
      '#type' => 'item',
      '#title' => t('Contest points input widget'),
      '#markup' => l(t('Edit contest points'), 'points/' . $event->nid, 
        array('attributes' => array ('target' => '_blank'))),
    );
  }
  $form['field_country']['#weight'] = 0;
  $form['field_flying_site_ref']['#weight'] = 1;
  $form['field_tiny_path']['#weight'] = 2;
  $form['field_logo']['#weight'] = 3;
  $form['field_dates']['#weight'] = 4;
  $form['field_fai_category']['#weight'] = 5;
  $form['setting_registration'] = array(
    '#type' => 'radios',
    '#title' => t('Registration'),
    '#options' => array(1 => 'Open', 0 => 'Closed'),
    '#default_value' => $event->status,
    '#weight' => 7,
  );
  $form['setting_status'] = array(
    '#type' => 'radios',
    '#title' => t('Publication settings'),
    '#options' => array(1 => 'Published', 0 => 'Unpublished'),
    '#default_value' => $event->status,
    '#weight' => 8,
  );
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
  $event->status = $values['setting_status'];
  node_save($event);
}
