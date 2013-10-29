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
  $fields = array(
    '#parents',
    '#entity',
    'field_flying_site_ref',
    'field_tiny_path',
    'field_dates',
    'field_logo',
    'field_fai_category',
    'field_open_class',
    'field_country',
    'field_registration_sw',
    '#pre_render',
    '#entity_type',
    '#bundle'
  );
  foreach ($form as $id => $value) {
    if(!in_array($id, $fields))
      unset($form[$id]);
  }
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Event name'),
    '#default_value' => $event->title,
    '#weight' => -1,
  );
  $form['field_country']['#weight'] = 0;
  $form['field_flying_site_ref']['#weight'] = 1;
  $form['alias'] = array(
    '#type' => 'textfield',
    '#title' => t('URL address'),
    '#default_value' => drupal_get_path_alias('event/' . $event->nid),
    '#weight' => 2,
  );
  $form['field_tiny_path']['#weight'] = 4;
  $form['field_logo']['#weight'] = 6;
  $form['field_dates']['#weight'] = 8;
  $form['field_fai_category']['#weight'] = 10;
  $form['field_open_class']['#weight'] = 12;
  if (module_exists('at_points_widget')) {
    $form['at_points_widget'] = array(
      '#weight' => 13,
      '#type' => 'item',
      '#title' => t('Contest points input widget'),
      '#markup' => l(t('Edit contest points'), 'points/' . $event->nid, 
        array('attributes' => array ('target' => '_blank'))),
    );
  }
  $form['setting_registration'] = array(
    '#type' => 'radios',
    '#title' => t('Registration'),
    '#options' => array(1 => 'Open', 0 => 'Closed'),
    '#default_value' => $event->field_registration_sw['und'][0]['value'],
    '#weight' => 14,
  );
  $form['setting_status'] = array(
    '#type' => 'radios',
    '#title' => t('Publication settings'),
    '#options' => array(1 => 'Published', 0 => 'Unpublished'),
    '#default_value' => $event->status,
    '#weight' => 16,
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
  $event->field_registration_sw['und'][0]['value'] = $values['setting_registration'];

  /* Manage URL aliases */
  $source = 'event/' . $event->nid;
  path_delete(array('source' => $source));
  $path = array('source' => $source, 'alias' => $values['alias']);
  path_save($path);

  node_save($event);
}
