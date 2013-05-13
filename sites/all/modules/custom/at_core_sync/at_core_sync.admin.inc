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
    '#default_value' => variable_get('at_core_sync_address', 'http://api.airtribune.com/v0.1/'),
    '#size' => 30,
    '#description' => t('For example: http://api.airtribune.com/v0.1/, with slash at end'),
  );
  return system_settings_form($form);
}

