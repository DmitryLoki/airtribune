<?php

/**
 * @file
 * Administrative page callbacks for the Airtribune Core API module.
 */

define('CORE_ID_FIELD', 'field_core_id');

/**
 * General configuration form for controlling the Airtribune Core API synchronization behaviour.
 */
function at_core_sync_admin_settings() {
  $form['at_core_sync_custom_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Core API settings'),
  );

  $form['at_core_sync_custom_settings']['at_core_sync_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => variable_get('at_core_sync_enabled', 0),
    '#description' => t('Enable integration with Core API'),
  );
  $form['at_core_sync_custom_settings']['at_core_sync_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Core API address'),
    '#default_value' => variable_get('at_core_sync_address', 'http://airtribune.com/'),
    '#size' => 30,
    '#description' => t('For example: http://airtribune.com/'),
  );
  $form['at_core_sync_custom_settings']['at_core_sync_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Core API port'),
    '#default_value' => variable_get('at_core_sync_port', '8085'),
    '#size' => 30,
    '#description' => t('For example: 8085'),
  );
  $entities = entity_get_info();
  $options = array();
  foreach ($entities as $name => $info) {
    foreach ($info['bundles'] as $bname => $bundle) {
      $options[$name][$bname] = $bundle['label'];
    }
  }
  
  $form['at_core_sync_custom_settings']['at_core_bundles'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#title' => t('Bundles that need sync'),
    '#default_value' => variable_get('at_core_bundles'),
  );
  
  $form['#submit'] = array('at_core_sync_field');
  return system_settings_form($form);
}

function at_core_sync_field($form, &$form_state) {
  dpm(field_info_field(CORE_ID_FIELD));
  dpm($form);
  dpm($form_state);
}