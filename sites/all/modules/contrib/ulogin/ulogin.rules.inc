<?php
/**
 * @file
 * Functions for integrating the Rules module with uLogin.
 */

/**
 * Implements hook_rules_action_info().
 */
function ulogin_rules_action_info() {
  return array(
    'ulogin_url_managed_file' => array(
      'label' => t('Save remote file to managed file'),
      'group' => t('uLogin'),
      'parameter' => array(
        'url' => array(
          'label' => t('URL'),
          'type' => 'uri',
          'description' => t('URL to the remote file.'),
        ),
        'directory' => array(
          'label' => t('File directory'),
          'type' => 'text',
          'description' => t('File directory to save remote file to.'),
        ),
      ),
      'provides' => array(
        'file' => array(
          'label' => 'Managed file entity',
          'type' => 'file',
        ), 
      ),
    ),
  );
}

function ulogin_url_managed_file($url, $directory) {
  watchdog('ulogin', $url . $directory);
  if ($url) {
    $url_info = parse_url($url);
    $directory = file_default_scheme() . '://' . $directory . '/' . $url_info['host'] . dirname($url_info['path']);
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $content = drupal_http_request($url);
	  $file = file_save_data($content->data, $directory . '/' . basename($url_info['path']), FILE_EXISTS_REPLACE);
	  
	  $path_info = pathinfo($url);
	  if (empty($path_info['extension'])) {
	    $info = image_get_info($file->uri);
	    $file = file_move($file, $directory . '/' . basename($url_info['path']) . '.' . $info['extension'], FILE_EXISTS_REPLACE);
	  }
  }
  
  return array('file' => $file);
}

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
    'group' => t('uLogin'),
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
    'group' => t('uLogin'),
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
    'group' => t('uLogin'),
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
