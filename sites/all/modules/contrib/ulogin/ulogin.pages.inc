<?php
function ulogin_callback() {
  if (!empty($_POST['token']) || !empty($_GET['token'])) {
    $token = !empty($_POST['token']) ? $_POST['token'] : $_GET['token'];
    $data_raw = drupal_http_request('http://ulogin.ru/token.php?token=' . $token . '&host=' . $_SERVER['HTTP_HOST']);
    if (!empty($data_raw->error)) {
      drupal_set_message($data_raw->error, 'error');
      return MENU_ACCESS_DENIED;
    }
    
    $data = json_decode($data_raw->data, TRUE);
    //check for error
    if (!empty($data['error'])) {
      drupal_set_message($data['error'], 'error');
      return MENU_ACCESS_DENIED;
    }
    //validate that returned data contains 'network' and 'uid' keys
    if (empty($data['network']) || empty($data['uid'])) {
      drupal_set_message('something is wrong, try again later', 'error');
      return MENU_ACCESS_DENIED;
    }
    //remove 'access_token' property
    unset($data['access_token']);
  }
  else {
    drupal_set_message('no token given', 'error');
    return MENU_ACCESS_DENIED;
  }
  
  global $user;
  //user is already logged in, tries to add new identity
  if (user_is_logged_in()) {
    //identity is already registered
    if ($identity = _ulogin_identity_load($data)) {
      //registered to this user
      if ($user->uid == $identity['uid']) {
        drupal_set_message(t('You have already registered this identity.'));
        $destination = drupal_get_destination();
        drupal_goto($destination['destination']);
      }
      //registered to another user
      else {
        drupal_set_message(t('This identity is registered to another user.'), 'error');
        $destination = drupal_get_destination();
        drupal_goto($destination['destination']);
      }
    }
    //identity is not registered - register it to the logged in user
    else {
      _ulogin_identity_save($data);
      drupal_set_message(t('New identity added.'));
      //invoke ulogin_identity_added rules event
      if (module_exists('rules')) {
        rules_invoke_event('ulogin_identity_added', $user, $data);
      }
      $destination = drupal_get_destination();
      drupal_goto($destination['destination']);
    }
  }
  
  if ($identity = _ulogin_identity_load($data)) {
    $form_state['uid'] = $identity['uid'];
    user_login_submit(array(), $form_state);
  }
  //handle duplicate email addresses
  elseif (variable_get('ulogin_duplicate_emails', 1) && !empty($data['email']) && $account = user_load_by_mail($data['email'])) {
    drupal_set_message(t('You are trying to login with email address of another user.'), 'error');
    if (!empty($account->data['ulogin'])) {
      $providers = _ulogin_providers_list();
      drupal_set_message(t('If you are completely sure it is your email address, try to login through %network.',
        array('%network' => $providers[$account->data['ulogin']['network']])), 'status');
    }
    else {
      drupal_set_message(t('If you are completely sure it is your email address, try to login using your username and password on this site. If you don\'t remember your password - <a href="@password">request new password</a>.',
        array('@password' => url('user/password'))));
    }
  }
  else {
    global $ulogin_data;
    $ulogin_data = $data;
    user_external_login_register(_ulogin_make_username($data), 'ulogin');
    _ulogin_identity_save($data);
    
    $user_save_trigger = FALSE;
    $edit = array();
    //save user picture
    if (variable_get('user_pictures', 0) && variable_get('ulogin_pictures', 1)) {
      $photo_url = '';
      if (!empty($data['photo_big']) && $data['photo_big'] != 'http://ulogin.ru/img/photo_big.png') {
        $photo_url = $data['photo_big'];
      }
      elseif (!empty($data['photo']) && $data['photo'] != 'http://ulogin.ru/img/photo.png') {
        $photo_url = $data['photo'];
      }
      if ($photo_url) {
        $photo = drupal_http_request($photo_url);
			  $file = file_save_data($photo->data);
			  $file->status = 0; //to make user_save() to process the file and move it
			  $edit['picture'] = $file;
			  $user_save_trigger = TRUE;
      }
    }
    //email_confirm: if email was manually entered - trigger email change confirmation
    if (!empty($data['email']) && !empty($data['manual']) && in_array('email', explode(',', $data['manual'])) &&
      variable_get('ulogin_email_confirm', 0) && module_exists('email_confirm')) {
      $edit['mail'] = $data['email'];
      $user_save_trigger = TRUE;
    }
    
    if ($user_save_trigger) {
      user_save($user, $edit);
    }
  }
  
  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

function ulogin_user_identity($form, &$form_state, $account) {
  drupal_set_title(format_username($account));
  
  $identities = _ulogin_identity_load_by_uid($account->uid);
  $providers = _ulogin_providers_list();
  
  $header = array(t('Authentication provider'), t('Identity'), t('Delete'));
  $rows = array();
  $data_array = array();
  foreach ($identities as $identity) {
    $data = unserialize($identity['data']);
    $data_array[] = $data;
    $rows[] = array(
      $providers[$data['network']],
      l($data['identity'], $data['identity'], array('attributes' => array('target' => '_blank'), 'external' => TRUE)),
      l(t('Delete'), 'user/' . $account->uid . '/ulogin/delete/' . $identity['id']),
    );
  }
  
  $form = array();
  
  $form['identity'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  
  //add more identities
  if (user_access('use ulogin')) {
    $form['ulogin_widget'] = array(
      '#type' => 'ulogin_widget',
      '#title' => t('Add more identities'),
      '#ulogin_destination' => '',
    );
  }
  
  //tokens browser for admins
  if (user_access('administer site configuration') || user_access('administer users')) {
    $form['vtabs'] = array(
      '#type' => 'vertical_tabs',
    );
    
    $header = array(t('Token'), t('Value'));
    //user tokens
    if (!empty($account->data['ulogin'])) {
      $form['vtabs']['fset_user_tokens'] = array(
        '#type' => 'fieldset',
        '#title' => t('User tokens'),
      );
      
      $rows = array();
      foreach ($account->data['ulogin'] as $key => $value) {
        if (!in_array($key, array('manual', 'ulogin'))) {
          $rows[] = array('[user:ulogin:' . $key . ']', $value);
        }
      }
      $form['vtabs']['fset_user_tokens']['tokens'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
      );
    }
    
    //data from auth providers
    foreach ($data_array as $data) {
      $form['vtabs']['fset_' . $data['network'] . '_' . $data['uid']] = array(
        '#type' => 'fieldset',
        '#title' => $providers[$data['network']],
      );
      
      $rows = array();
      foreach ($data as $key => $value) {
        $rows[] = array($key, $value);
      }
      $form['vtabs']['fset_' . $data['network'] . '_' . $data['uid']]['tokens'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
      );
    }
  }
  
  return $form;
}

function ulogin_user_identity_delete($form, &$form_state, $account, $id) {
  $del_identity = _ulogin_identity_load_by_id($id);
  if (!$del_identity || $account->uid != $del_identity['uid']) {
    drupal_set_message(t('You are trying to delete non-existing identity.'), 'error');
    drupal_access_denied();
  }
  $del_identity_data = unserialize($del_identity['data']);
  $username = format_username($account);
  $quetion = t('Are you sure you want to detach the uLogin identity !identity from %user?',
    array(
      '!identity' => l($del_identity_data['identity'], $del_identity_data['identity'], array('attributes' => array('target' => '_blank'), 'external' => TRUE)),
      '%user' => $username));
  
  $form = array();
  $form['#user'] = $account;
  $form['#del_identity_data'] = $del_identity_data;
  $form['question'] = array(
    '#markup' => $quetion,
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );
  
  if (!empty($account->data['ulogin']) && $account->data['ulogin']['network'] == $del_identity_data['network'] &&
    $account->data['ulogin']['uid'] == $del_identity_data['uid']) {
    $identities = _ulogin_identity_load_by_uid($account->uid);
    $providers = _ulogin_providers_list();
    $options = array();
    foreach ($identities as $key => $identity) {
      $data = unserialize($identity['data']);
      if ($key != $id) {
        $options[$key] = $providers[$identity['network']] . ' - ' . l($data['identity'], $data['identity'], array('attributes' => array('target' => '_blank'), 'external' => TRUE));
      }
    }
    
    if (!empty($options)) {
      $form['explanation'] = array(
        '#markup' => t('This identity was used to create your account. Please choose another identity to replace it.'),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      );
      $form['identity_choice'] = array(
        '#type' => 'radios',
        //'#title' => t('Identities'),
        '#options' => $options,
        '#default_value' => count($options) == 1 ? $key : NULL,
        //'#required' => TRUE, //required has bugs with radios http://drupal.org/node/811542
      );
    }
    else {
      $form['explanation'] = array(
        '#markup' => t('This identity was used to create your account. To delete it you should first add another identity to your account.'),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      );
      return $form;
    }
  }
  
  $form = confirm_form($form, '', 'user/' . $account->uid . '/ulogin');
  drupal_set_title($username);
  
  return $form;
}

function ulogin_user_identity_delete_validate($form, &$form_state) {
  if (!empty($form['identity_choice']) && empty($form_state['values']['identity_choice'])) {
    form_set_error('identity_choice', t('Please choose identity for replacement.'));
  }
}

function ulogin_user_identity_delete_submit($form, &$form_state) {
  if (!empty($form_state['values']['identity_choice'])) {
    $identity = _ulogin_identity_load_by_id($form_state['values']['identity_choice']);
    $data = unserialize($identity['data']);
    $name = _ulogin_make_username($data);
    //change name
    $edit['name'] = $name;
    //change ulogin data used for tokens
    $edit['data']['ulogin'] = $data;
    user_save($form_state['build_info']['args'][0], $edit);
    //change authname in authmap DB table
    user_set_authmaps($form_state['build_info']['args'][0], array('authname_ulogin' => $name));
  }
  
  $deleted = _ulogin_identity_delete_by_id($form_state['build_info']['args'][1]);
  if ($deleted) {
    drupal_set_message(t('Identity deleted.'));
    //invoke ulogin_identity_deleted rules event
    if (module_exists('rules')) {
      rules_invoke_event('ulogin_identity_deleted', $form['#user'], $form['#del_identity_data']);
    }
  }
  
  $form_state['redirect'] = 'user/' . $form_state['build_info']['args'][0]->uid . '/ulogin';
}
