<?php

/**
 * @file
 * Administrative page callbacks for the Airtribune Core API module.
 */

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
  $form['at_core_sync_custom_settings']['at_core_sync_cron_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Queue'),
    '#default_value' => variable_get('at_core_sync_cron_enabled', 0),
    '#description' => t('Queue requests when Core API is unreacheble'),
  );
  $form['at_core_sync_custom_settings']['at_core_sync_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Core API address'),
    '#default_value' => variable_get('at_core_sync_address', 'http://api.airtribune.com'),
    '#size' => 30,
    '#description' => t('For example: http://api.airtribune.com'),
  );

  $form['at_core_sync_custom_settings']['at_core_sync_version'] = array(
    '#type' => 'select',
    '#title' => t('Core API version'),
    '#multiple' => FALSE,
    '#options' => array(
      'v0.1' => 'v0.1',
      'v0.1.2' => 'v0.1.2',
    ),
    '#default_value' => variable_get('at_core_sync_version', 'v0.1'),
    '#description' => t('For example: v0.1, v0.1.2'),
  );

  $entities = entity_get_info();
  $options = array();
  foreach ($entities as $name => $info) {
    foreach ($info['bundles'] as $bname => $bundle) {
      $options[$name][$bname] = $bundle['label'];
    }
    $options[$name]['#title'] = isset($info['plural label']) ? $info['plural label'] : $info['label'];
  }

  $form['at_core_sync_custom_settings']['at_core_bundles'] = array(
    '#type' => 'nested_checkboxes',
    '#options' => $options,
    '#title' => t('Bundles that need sync'),
    '#title_display' => 'after',
    '#default_value' => variable_get('at_core_bundles'),
  );

  $form['#submit'] = array('at_core_sync_field');
  return system_settings_form($form);
}

function at_core_sync_field($form, &$form_state) {
  $values = $form_state['values']['at_core_bundles'];
  $field_info = field_info_field(AIRTRIBUNE_CORE_ID_FIELD);
  $attached = $field_info['bundles'];
  foreach ($values as $entity => $bundles) {
    if (!empty($bundles)) {
      foreach ($bundles as $bundle => $value) {
        if ((string)$value == $bundle) {
          if (!in_array($value, $attached[$entity])) {
            field_create_instance(array('field_name' => AIRTRIBUNE_CORE_ID_FIELD, 'entity_type' => $entity, 'bundle' => $bundle));
          }
        }
      }
    }
  }
}

function _at_core_page_manage() {
  return '<p></p>';
}
