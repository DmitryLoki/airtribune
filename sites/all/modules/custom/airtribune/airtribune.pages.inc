<?php

/**
 * @file
 * Provides Event settings form.
 */

/**
 * Form function to edit og_membership entity.
 */
function airtribune_event_settings_form($form, &$form_state, $event = FALSE) {
  global $base_url;
  // Event does not exist
  if (!$event) {
    drupal_not_found();
  }
  drupal_set_title(t('Settings') . ' | ' . $event->title);
  field_attach_form('node', $event, $form, $form_state);
  $fields = array(
    '#parents',
    '#entity',
    'field_flying_info',
    'field_flying_site_ref',
    'field_take_offs',
    'field_landing_zones',
    'field_tiny_path',
    'field_dates',
    'field_logo',
    'field_fai_category',
    'field_open_class',
    'field_country',
    'field_time_zone',
    'field_sequence',
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
  $form['field_time_zone']['#weight'] = 0;
  $form['field_flying_info']['#weight'] = 10;
  $form['field_flying_site_ref']['#weight'] = 20;
  $form['field_take_offs']['#weight'] = 30;
  $form['alias'] = array(
    '#type' => 'textfield',
    '#title' => t('URL address'),
    '#field_prefix' => $base_url . '/',
    '#default_value' => drupal_get_path_alias('event/' . $event->nid),
    '#weight' => 40,
  );
  $form['field_tiny_path']['#weight'] = 50;
  for ($i = 0; $i<=$form['field_tiny_path'][LANGUAGE_NONE]['#max_delta']; $i++ ) {
    $form['field_tiny_path'][LANGUAGE_NONE][$i]['value']['#field_prefix'] = $base_url . '/';
    if (!empty($form['field_tiny_path'][LANGUAGE_NONE][$i]['value']['#default_value']) &&
        !user_access('bypass node access')) {
      // Disable field for organizer if not empty alias value
      $form['field_tiny_path'][LANGUAGE_NONE][$i]['#disabled'] = TRUE;
    }
  }
  $lang = $form['field_tiny_path']['#language'];
  $form['field_tiny_path'][$lang]['add_more']['#prefix'] = '<div class="form-actions">';
  $form['field_tiny_path'][$lang]['add_more']['#suffix'] = '</div>';
  //print_r($form['field_tiny_path']);
  $form['field_logo']['#weight'] = 60;
  $form['field_dates']['#weight'] = 70;
  $form['field_fai_category']['#weight'] = 80;
  $form['field_open_class']['#weight'] = 90;
  if (module_exists('at_points_widget')) {
    $form['at_points_widget'] = array(
      '#weight' => 100,
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
    '#weight' => 110,
  );
  $form['field_sequence']['#weight'] = 115;
  $form['setting_status'] = array(
    '#type' => 'radios',
    '#title' => t('Publication settings'),
    '#options' => array(1 => 'Published', 0 => 'Unpublished'),
    '#default_value' => $event->status,
    '#weight' => 120,
  );
  $form['event'] = array(
    '#type' => 'value',
    '#value' => $event,
  );
  $form['actions']['#weight'] = 999;
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="form-actions">',
    '#suffix' => '</div>',
  );
  $form['#attached']['js'][] =  drupal_get_path('module', 'at_user') . '/js/auto_upload.js';
  drupal_add_js('Drupal.behaviors.updateForm = {attach:function(){updateForm(false, {disableChoiceOfFirstItemInSelection:true, file_bt:Drupal.t("Add image")})}}', 'inline');
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
