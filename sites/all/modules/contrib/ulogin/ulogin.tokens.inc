<?php

/**
 * @file
 * Builds placeholder replacement tokens for ulogin-related data.
 */

/**
 * Implements hook_token_info().
 */
function ulogin_token_info() {
  $types = array();
  $types['ulogin'] = array(
    'name' => t('uLogin data'),
    'description' => t('Information about the user from the uLogin service.'),
    'needs-data' => 'user',
  );
  
  $tokens = array();
  $tokens['user']['ulogin'] = array(
    'name' => t('uLogin information'),
    'description' => t('Information from uLogin service.'),
    'type' => 'ulogin',
  );
  
  $tokens['ulogin'] = array (
    'network' => array(
      'name' => t('Authentication provider'),
      'description' => t('Network providing authentication.'),
    ),
    'uid' => array(
      'name' => t('UID'),
      'description' => t('UID') . ' ' . t('provided by uLogin.'),
    ),
    'identity' => array(
      'name' => t('Identity'),
      'description' => t('Identity') . ' ' . t('provided by uLogin.'),
    ),
  );
  
  foreach (_ulogin_fields_list() as $key => $value) {
    $tokens['ulogin'][$key] = array(
      'name' => $value,
      'description' => $value . ' ' . t('provided by uLogin.'),
    );
  }
  
  return array(
    'types' => $types,
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function ulogin_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();
  
  if ($type == 'user' && !empty($data['user'])) {
    if (!empty($data['user']->data['ulogin'])) {
      $ulogin_tokens = token_find_with_prefix($tokens, 'ulogin');
      $replacements += token_generate('ulogin', $ulogin_tokens, array('ulogin' => $data['user']->data['ulogin']), $options);
    }
  }
  
  if ($type == 'ulogin' && !empty($data['ulogin'])) {
    foreach ($tokens as $name => $original) {
      $replacements[$original] = $sanitize ? check_plain($data['ulogin'][$name]) : $data['ulogin'][$name];
    }
  }
  
  return $replacements;
}
