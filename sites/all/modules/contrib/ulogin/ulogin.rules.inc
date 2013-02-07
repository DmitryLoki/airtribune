<?php
/**
 * @file
 * Functions for integrating the Rules module with uLogin.
 */

/**
 * Implements hook_rules_data_info().
 * @ingroup rules
 */
function ulogin_rules_data_info() {
  $types = array();
  
  $types['ulogin'] = array(
    'label' => 'uLogin identity data',
    'wrap' => TRUE,
    'property info' => _ulogin_rules_data_properties(),
  );
  
  return $types;
}

function _ulogin_rules_data_properties() {
  $properties = array();
  
  if (function_exists('ulogin_token_info')) {
    $token_info = ulogin_token_info();
  }
  else {
    include_once(drupal_get_path('module', 'ulogin') . '/ulogin.tokens.inc');
    $token_info = ulogin_token_info();
  }
  foreach ($token_info['tokens']['ulogin'] as $key => $value) {
    $properties[$key] = array(
      'label' => $value['name'],
      'type' => 'text',
      'description' => $value['description'],
    );
  }
  
  return $properties;
}

/**
 * Implements hook_rules_event_info().
 * @ingroup rules
 */
function ulogin_rules_event_info() {
  $events = array();
  
  $events['ulogin_identity_added'] = array(
    'label' => t('User added uLogin identity'),
    'group' => t('User'),
    'variables' => array(
      'ulogin_user' => array(
        'label' => t('User adding the identity'),
        'type' => 'user',
      ),
      'ulogin' => array(
        'label' => t('uLogin identity data'),
        'type' => 'ulogin',
      ),
    ),
    'module' => 'ulogin',
  );
  $events['ulogin_identity_deleted'] = array(
    'label' => t('User deleted uLogin identity'),
    'group' => t('User'),
    'variables' => array(
      'ulogin_user' => array(
        'label' => t('User deleting the identity'),
        'type' => 'user',
      ),
      'ulogin' => array(
        'label' => t('uLogin identity data'),
        'type' => 'ulogin',
      ),
    ),
    'module' => 'ulogin',
  );
  
  return $events;
}

/**
 * Implements hook_rules_condition_info().
 * @ingroup rules
 */
function ulogin_rules_condition_info() {
  $conditions = array();
  
  $conditions['ulogin_user_created_ulogin'] = array(
    'label' => t('User created by uLogin'),
    'group' => t('User'),
    'parameter' => array(
      'account' => array('label' => t('User'), 'type' => 'user'),
    ),
  );
  
  return $conditions;
}

function ulogin_user_created_ulogin($account) {
  global $ulogin_data;
  return (!empty($ulogin_data) || !empty($account->data['ulogin']));
}
