<?php

/**
 * @file
 * Simple, extensible user import from a CSV file.
 */

/**
 * User import multi-part form.
 */
function uif_import_form($form, &$form_state) {
  // Cause return to beginning if we just completed an import
  if (isset($form_state['storage']['step']) && $form_state['storage']['step'] >= 3) {
    unset($form_state['storage']);    
  }
  
  $step = empty($form_state['storage']['step']) ? 1 : $form_state['storage']['step'];
  $form_state['storage']['step'] = $step;

  switch ($step) {
    case 1:
      $form['instructions'] = array(
        '#type' => 'fieldset',
        '#title' => t('User import help'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['instructions']['help'] = array(
        '#markup' => theme('uif_form_help'),
      );
      $file_size_msg = t('Your PHP settings limit the maximum file size per upload to %size. Depending on your server environment, these settings may be changed in the system-wide php.ini file, a php.ini file in your Drupal root directory, in your Drupal site\'s settings.php file, or in the .htaccess file in your Drupal root directory.', array('%size' => format_size(file_upload_max_size())));

      $form['user_upload'] = array(
        '#type' => 'file',
        '#title' => t('Import file'),
        '#size' => 40,
        '#description' => t('Select the CSV file to be imported.') . '<br />' . $file_size_msg,
      );
  
      $form['field_delimiter'] = array(
        '#type' => 'select',
        '#title' => t('Field delimiter'),
        '#default_value' => variable_get('uif_field_delimiter', ','),
        '#options' => uif_field_delimiters(),
        '#description' => t('Select field delimiter. Comma is typical for CSV export files.'),
      );
      $form['value_delimiter'] = array(
        '#type' => 'select',
        '#title' => t('Value delimiter'),
        '#default_value' => variable_get('uif_value_delimiter', '|'),
        '#options' => uif_value_delimiters(),
        '#description' => t('Select value delimiter for fields receiving multiple values.'),
      );
  
      $preview_count = drupal_map_assoc(array(0, 1, 10, 100, 1000, 10000, 9999999));
      $preview_count[0] = t('None - just do it');
      $preview_count[9999999] = t('Preview all');

      $form['preview_count'] = array(
        '#type' => 'select',
        '#title' => t('Users to preview'),
        '#default_value' => 10,
        '#options' => $preview_count,
        '#description' => t('Number of users to preview before importing. Note: If you run out of memory set this lower or increase your memory.')
      );

      $form['notify'] = array(
        '#type' => 'checkbox',
        '#title' => t('Notify new users of account'),
        '#description'   => t('If checked, each newly created user will receive the <em>Welcome, new user created by administrator</em> email using the template on the <a href="@url1">user settings page</a>. This is the same email sent for <a href="@url2">admin-created accounts</a>.', array('@url1' => url('admin/user/settings'), '@url2' => url('admin/user/user/create'))),
      );

      $form['next'] = array(
        '#type' => 'submit',
        '#value' => t('Next')
      );    
  
      // Set form parameters so we can accept file uploads.
      $form['#attributes'] = array('enctype' => 'multipart/form-data');
      break;
      
    case 2:
      $form['instructions'] = array(
        '#markup' => t('Preview these records and when ready to import click Import users.'),
        '#prefix' => '<div id="uif_form_instructions">',
        '#suffix' => '</div>',
      );
      $form['user_preview'] = array(
        '#markup' => $form_state['storage']['user_preview'],
        '#prefix' => '<div id="uif_user_preview">',
        '#suffix' => '</div>',
      );
      $form['back'] = array(
        '#type' => 'submit',
        '#value' => t('Back'),
        '#submit' => array('uif_import_form_back'),
      );
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Import users'),
      );
      break;
  }

  return $form;    
}

/**
 * Validate the import data.
 */
function uif_import_form_validate($form, &$form_state) {
  $step = empty($form_state['storage']['step']) ? 1 : $form_state['storage']['step'];
  
  switch ($step) {
    case 1:      
      // Validate the upload file
      $validators = array(
        'file_validate_extensions' => array('csv'),
        'file_validate_size' => array(file_upload_max_size()),
      );

      if ($user_file = file_save_upload('user_upload', $validators)) {
        $errors = uif_validate_user_file($user_file->uri, $data, $form_state);
        if (!empty($errors)) {
          form_set_error('user_upload', '<ul><li>' . implode('</li><li>', $errors) . '</li></ul>');
          return;
        }
      }
      else {
        form_set_error('user_upload', t('Cannot save the import file to temporary storage.  Please try again.'));
        return;
      }

      // Save the validated data to avoid reparsing
      $form_state['storage']['data'] = $data;
      break;
  }
}

/**
 * Form submission handler.
 */
function uif_import_form_submit($form, &$form_state) {
  $step = empty($form_state['storage']['step']) ? 1 : $form_state['storage']['step'];
  
  if (1 == $step) {
    $form_state['rebuild'] = TRUE;
    $form_state['storage']['notify'] = isset($form_state['values']['notify']) ? $form_state['values']['notify'] : FALSE;
    $form_state['storage']['field_delimiter'] = $form_state['values']['field_delimiter'];
    $form_state['storage']['value_delimiter'] = $form_state['values']['value_delimiter'];
    
    $preview_count = $form_state['values']['preview_count'];
    if ($preview_count) {
      $form_state['storage']['preview_count'] = $preview_count;
      $form_state['storage']['user_preview'] = theme('uif_preview_users', array('data' => $form_state['storage']['data'], 'limit' => $preview_count));
    }
    else {
      $step = 2;
    }
  }

  if (2 == $step) {
    $form_state['rebuild'] = TRUE;
    uif_batch_import_users($form_state);
  }
  
  $form_state['storage']['step'] = $step + 1;
}

/**
 * Read the user import file and validate on the way.
 *
 *  @param $uri
 *    filepath to the user import file
 *  @param $data
 *    returns with array of users
 *  @return
 *    FALSE if no errors found
 *    array of error strings if error found
 */
function uif_validate_user_file($uri, &$data, $form_state) {
  $data = array();
  $data['user'] = array();
  $line = 0;
  $delimiter = $form_state['values']['field_delimiter'];

  // Without this fgetcsv() fails for Mac-created files
  ini_set('auto_detect_line_endings', TRUE);  
  
  if ($fp = fopen($uri, 'r')) {
    // Read the header and allow alterations
    $header_row = fgetcsv($fp, NULL, $delimiter);
    $header_row = uif_normalize_header($header_row);
    uif_adjust_header_values($header_row);
    drupal_alter('uif_header', $header_row);
    $line++;

    $errors = module_invoke_all('uif_validate_header', $header_row, $form_state);
    uif_add_line_number($errors, $line);
    if (!empty($errors)) {
      return $errors;
    }
    $data['header'] = $header_row;
    
    // Gather core and entity field info
    $data['fields'] = uif_get_field_info($header_row);
    
    // Read the data
    $errors = array();
    while (!feof($fp) && (count($errors) < 20)) {
      // Read a row and allow alterations
      $row = fgetcsv($fp, NULL, $delimiter);
      drupal_alter('uif_row', $row, $header_row);
      $line++;

      if (uif_row_has_data($row)) {
        $user_row = uif_clean_and_key_row($header_row, $row, $line);
        $args = array(':mail' => db_like($user_row['mail']));
        $uid = db_query_range('SELECT uid FROM {users} WHERE mail LIKE :mail', 0, 1, $args)->fetchField();
        
        $more_errors = module_invoke_all('uif_validate_user', $user_row, $uid, $header_row, $form_state);
        uif_add_line_number($more_errors, $line);
        $errors = array_merge($errors, $more_errors);
        $data['user'][] = $user_row;
      }
    }
    
    // Any errors?
    if (!empty($errors)) {
      return $errors;
    }
  }
  else {
    return t('Cannot open that import file.');
  }
  
  // Final validation opportunity after header and all users validated individually.
  $errors = module_invoke_all('uif_validate_all_users', $data['user'], $form_state);
  if (!empty($errors)) {
    return $errors;
  }
}

/**
 * Trim all elements of $row, and pad $row out to the number of columns in the 
 * $header.  Then replace keys in $row with $header values.
 */
function uif_clean_and_key_row($header, $row, $line) {
  $row = array_map('trim', $row);
  
  $raw_row = $row;
  $row = array_map('uif_clean_value', $row);
  
  for ($i = 0; $i < count($row); $i++) {
    if ($raw_row[$i] !== $row[$i]) {
      $vars = array('@line' => $line, '@column' => $header[$i]);
      drupal_set_message(t('Warning on row @line: Non UTF-8 characters were removed from @column column.', $vars), 'warning');
    }
  }
  
  if (count($row) < count($header)) {
    $row = array_merge($row, array_fill(count($row), count($header) - count($row), ''));    
    drupal_set_message(t('Warning on row @line: Empty values added for missing data.', array('@line' => $line)), 'warning');
  }
  elseif (count($row) > count($header)) {
    array_splice($row, count($header));
    drupal_set_message(t('Warning on row @line: Data values beyond header were truncated.', array('@line' => $line)), 'warning');
  }
  
  $row = array_combine($header, $row);
  return $row;
}

/**
 * Check that input is UTF-8.
 */
function uif_clean_value($value) {
  if (!drupal_validate_utf8($value)) {
    // Remove all chars except LF, CR, and basic ascii
    return preg_replace('/[^\x0A\x0D\x20-\x7E]/', '', $value);    
  }
  
  return $value;
}

/**
 * Is there data in the row?
 */
function uif_row_has_data($row) {
  if (isset($row) && is_array($row)) {
    foreach ($row as $value) {
      $value = trim($value);
      if (!empty($value)) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Normalize the header columns.
 */
function uif_normalize_header($header) {
  $header = array_map('trim', $header);
  $normal_header = array();
  foreach ($header as $column) {
    $normal_header[] = strtolower($column);
  }
  return $normal_header;
}

/**
 * Implementation of hook_uif_validate_header().
 */
function uif_uif_validate_header($header) {
  $errors = array();

  if (!in_array('mail', $header)) {
    $errors[] = t('There is no email column in the import file.');
  }
  
  $labels = array();
  foreach ($header as $label) {
    if (isset($labels[$label])) {
      $errors[] = t('Repeated columns in input file are not allowed: %label', array('%label' => $label));
    }
    $labels[$label] = 1;
  }
  
  return $errors;
}

/**
 * Implementation of hook_uif_validate_user().
 */
function uif_uif_validate_user($user_data, $uid, $header = NULL) {
  $errors = array();
  
  if (!valid_email_address($user_data['mail'])) {
    $errors[] = t('Missing or invalid email address: %mail', array('%mail' => $user_data['mail']));
  }
  if (isset($user_data['roles'])) {
    uif_parse_roles($user_data['roles'], $roles_errors);
    $errors = array_merge($errors, $roles_errors);
  }
  
  return $errors;
}

/**
 * Prepend the line number on the error.
 */
function uif_add_line_number(&$errors, $line) {
  foreach ($errors as &$error) {
    $error = t('Error on row !line:', array('!line' => $line)) . ' ' . $error;
  }
}

/**
 * Return user to starting point on template multi-form.
 */
function uif_import_form_back($form, &$form_state) {
  $form_state['storage']['step'] = 1;
}

/**
 * Theme preview of all users.
 */
function theme_uif_preview_users($variables) {
  $data = $variables['data'];
  $limit = $variables['limit'];
  $current = 0;
  $output = '';
  
  foreach ($data['user'] as $user_data) {
    $current++;
    if ($current > $limit) {
      break;
    }
    $output .= theme('uif_preview_one_user', array('data' => $user_data));
  }
  
  if (!$output) {
    $output = t('There are no users to import.');
  }
  
  return $output;
}

/**
 * Theme preview of a single user.
 */
function theme_uif_preview_one_user($variables) {
  $user_data = $variables['data'];
  $rows = array();
  foreach ($user_data as $field => $value) {
    $rows[] = array($field, $value);
  }
  
  $args = array(':mail' => db_like($user_data['mail']));
  $user_exists = db_query('SELECT COUNT(*) FROM {users} WHERE mail LIKE :mail', $args)->fetchField();
  $annotation = $user_exists ? t('update') : t('create');
  $heading = $user_data['mail'] . ' (' . $annotation . ')';
  
  return '<h3>' . $heading . '</h3>' . theme('table', array('rows' => $rows));
}

/**
 * Batch import all users.
 */
function uif_batch_import_users($form_state) {
  $batch = array(
    'title' => t('Importing users'),
    'operations' => array(
      array('uif_batch_import_users_process', array($form_state))
    ),
    'progress_message' => '', // uses count(operations) which is irrelevant in this case
    'finished' => 'uif_batch_import_users_finished',
    'file' => drupal_get_path('module', 'uif') . '/uif.admin.inc',
  );
  batch_set($batch);
}

/**
 * User import batch processing.
 */
function uif_batch_import_users_process($form_state, &$context) {
  // Initialize
  if (empty($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($form_state['storage']['data']['user']);
    $context['results']['created'] = 0;
    $context['results']['updated'] = 0;
  }
  
  // Process max 20 users at a time
  $processed = 0;
  $notify = $form_state['storage']['notify'];
  while ($context['sandbox']['progress'] < $context['sandbox']['max'] && $processed < 20) {
    $index = $context['sandbox']['progress'];
    uif_import_user($form_state['storage']['data']['user'][$index], $notify, $context['results'], $form_state);
    $context['sandbox']['progress']++;
    $processed++;
  }
  
  // Finished yet?
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * User import batch completion.
 */
function uif_batch_import_users_finished($success, $results, $operations) {
  if ($success) {
    global $user;
    if (isset($results['self'])) {
      uif_update_user($results['self'], $user->uid);
      $results['updated']++;
      unset($results['self']);
    }      
    $done = t('User import complete.');
    $created = $results['created'] ? 
      ' ' . format_plural($results['created'], 'One user was created.', '@count users were created.') . ' ' : 
      '';
    $updated = $results['updated'] ? 
      ' ' . format_plural($results['updated'], 'One user was updated.', '@count users were updated.') . ' ' : 
      '';
    $more = t('View the <a href="@url">user list</a>.', array('@url' => url('admin/people')));
    drupal_set_message($done . $created . $updated . $more);
  }
  else {
    drupal_set_message(t('An error occurred and processing did not complete.'), 'error');
  }
}

/**
 * Import one user.
 */
function uif_import_user($user_data, $notify, &$results, $form_state) {
  $args = array(':mail' => db_like($user_data['mail']));
  if ($uid = db_query('SELECT uid FROM {users} WHERE mail LIKE :mail', $args)->fetchField()) {
    global $user;
    if ($uid === $user->uid) {
      $results['self'] = $user_data;
      return;
     }
    $account = uif_update_user($user_data, $uid, $form_state);
    $results['updated']++;
  }
  else {
    $account = uif_create_user($user_data, $notify, $form_state);
    $results['created']++;
  }
}

/**
 * Create a new user.
 */
function uif_create_user($user_data, $notify, $form_state) {
  $account = array();
  $account['mail'] = $user_data['mail'];
  $account['init'] = $user_data['mail'];
  $account['status'] = 1;
  
  // Use the provided username if any, or derive it from the email
  $username = empty($user_data['name']) ? preg_replace('/@.*$/', '', $user_data['mail']) : $user_data['name'];
  $account['name'] = uif_unique_username($username);
  
  // Use the provided password if any, otherwise a random one
  $pass = !empty($user_data['pass']) ? $user_data['pass'] : user_password();
  $account['pass'] = $pass;
  
  // Add roles if present
  if (isset($user_data['roles'])) {
    $account['roles'] = uif_parse_roles($user_data['roles']);
  }
  
  $account = array_merge($account, module_invoke_all('uif_pre_create', $account, $user_data, $form_state));
  $account = user_save('', $account);
  module_invoke_all('uif_post_create', $account, $user_data, $form_state);
  
  if ($notify) {
    $account->password = $pass;    // For mail token; _user_mail_notify() expects this
    _user_mail_notify('register_admin_created', $account);
  }

  return $account;
}

/**
 * Update an existing user.
 */
function uif_update_user($user_data, $uid, $form_state) {
  $account = user_load($uid);
  
  // todo: Support update of user mail. This requires optional inclusion of uid column,
  // which would override use of email column as uid lookup method.
  $changes = module_invoke_all('uif_pre_update', $account, $user_data, $form_state);
  
  // Update the username if it has changed
  if (!empty($user_data['name'])) {
    $username = uif_unique_username($user_data['name'], $uid);
    if ($username != $account->name) {
      $changes['name'] = $username;
    }
  }

  // Update the password if one is provided
  if (!empty($user_data['pass'])) {
    $changes['pass'] = $user_data['pass'];
  }
  
  // Update roles if present
  if (isset($user_data['roles'])) {
    $changes['roles'] = uif_parse_roles($user_data['roles']);
  }
  
  $account = user_save($account, $changes);
  module_invoke_all('uif_post_update', $account, $user_data, $form_state);
  
  return $account;
}

/**
 * Implements hook_uif_pre_create().
 */
function uif_uif_pre_create($account, $user_data, $form_state) {
  return uif_assign_presave_fields($account, $user_data, $form_state);
}

/**
 * Implements hook_uif_pre_update().
 */
function uif_uif_pre_update($account, $user_data, $form_state) {
  return uif_assign_presave_fields($account, $user_data, $form_state);
}

/**
 * Given a starting point for a Drupal username (e.g. the name portion of an email address) return
 * a legal, unique Drupal username.
 *
 * @param $name
 *   A name from which to base the final user name.  May contain illegal characters; these will be stripped.
 *
 * @param $uid
 *   (optional) Uid to ignore when searching for unique user (e.g. if we update the username after the 
 *   {users} row is inserted) 
 *
 * @return
 *   A unique user name based on $name.
 *
 */
function uif_unique_username($name, $uid = 0) {
  // Strip illegal characters
  $name = preg_replace('/[^\x{80}-\x{F7} a-zA-Z0-9@_.\'-]/', '', $name);
  
  // Strip leading and trailing whitespace
  $name = trim($name);
  
  // Convert any other series of spaces to a single space
  $name = preg_replace('/ +/', ' ', $name);
  
  // If there's nothing left use a default
  $name = ('' === $name) ? t('user') : $name;
  
  // Truncate to reasonable size
  $name = (drupal_strlen($name) > (USERNAME_MAX_LENGTH - 10)) ? drupal_substr($name, 0, USERNAME_MAX_LENGTH - 11) : $name;
  
  // Iterate until we find a unique name
  $i = 0;
  do {
    $newname = empty($i) ? $name : $name . '_' . $i;
    $args = array(':uid' => $uid, ':name' => $newname);
    $found = db_query_range('SELECT uid from {users} WHERE uid <> :uid AND name = :name', 0, 1, $args)->fetchField();
    $i++;
  } while ($found);
  
  return $newname;
}

/**
 * Theme function for import form help.
 */
function theme_uif_form_help() {
  $basic_help = '<p>' . t('Choose an import file. You\'ll have a chance to preview the data before doing the import. The import file must have a header row with a name in each column for the value you are importing. Importable fields include the following:') . '</p>';
  $items = array();
  
  // Core user table fields
  $supported_fields = uif_get_supported_fields();
  foreach ($supported_fields as $name => $data) {
    if ($data['type'] == 'core') {
      $required = uif_isset_or($data['required']) ? t('required') : t('optional');
      $subs = array('@name' => $name, '@required' => $required, '!description' => $data['description']);
      $items[] = t('@name (@required) - !description', $subs);
    }
  }
  
  // Entity fields
  foreach (uif_field_info_instances('user', 'user') as $name => $data) {
    $field_type = uif_lookup_field_type($name);
    if (uif_is_supported_field($field_type)) {
      $subs = array(
        '@name' => $name,
        '@required' => $data['required'] ? t('required') : t('optional'),
        '%label' => $data['label'],
        '%type' => $field_type,
        '@description' => $data['description'] ? $data['description'] : uif_isset_or($supported_fields[$field_type]['description']),
      );
      $items[] = t('@name (@required) - @description (type is %type, human name is %label)', $subs);
    }
  }
  
  $basic_help .= theme('item_list', array('items' => $items));
  
  if (!module_exists('uif_plus')) {
    $basic_help .= '<p>' . t('If you need support for entity reference, file, or image fields, or support for modules such profile2 and organic groups, try adding and enabling the <a href="http://drupal.org/project/uif_plus">User Import Framework Plus</a> module.') . '</p>';
  }
  
  // Add other modules' help
  $helps = module_invoke_all('uif_help');
  array_unshift($helps, $basic_help);
  $output = '';
  foreach ($helps as $help) {
    $output .= '<div class="uif_help_section">' . $help . '</div>';
  }
  
  return $output;
}

/**
 * Field delimiter options.
 */
function uif_field_delimiters() {
  return array(
    ',' => ',',
    ';' => ';',
    '|' => '|',
  );
}

/**
 * Value delimiter options.
 */
function uif_value_delimiters() {
  return array(
    '|' => '|',
    ':' => ':',
    '_:_' => '_:_',
    '-*-' => '-*-',
  );
}

/**
 * Parse input roles if any.
 */
function uif_parse_roles($roles_string, &$errors = array()) {
  $roles = array();
  $errors = array();
  
  if ($roles_string) {
    $role_names = explode(variable_get('uif_value_delimiter', '|'), $roles_string);
    foreach ($role_names as $name) {
      $rid = db_query('SELECT rid FROM {role} WHERE name = :name', array(':name' => $name))->fetchField();
      if (is_numeric($rid) && $rid < 2) {
        $errors[] = t('System-managed roles are not allowed: %name', array('%name' => $name));
      }
      elseif ($rid) {
        $roles[$rid] = $name;
      }
      else {
        $errors[] = t('Unrecognized role: %name', array('%name' => $name));
      }
    }
  }
  
  return $roles;
}

/**
 * Perform header adjustments.
 */
function uif_adjust_header_values(&$header_row) {
  foreach ($header_row as &$label) {
    if ('email' == $label) {
      $label = 'mail';
      drupal_set_message(t('Header label <em>mail</em> substituted for deprecated label <em>email</em>.'), 'warning');
    }
    if ('username' == $label) {
      $label = 'name';
      drupal_set_message(t('Header label <em>name</em> substituted for deprecated label <em>username</em>.'), 'warning');
    }
    if ('password' == $label) {
      $label = 'pass';
      drupal_set_message(t('Header label <em>pass</em> substituted for deprecated label <em>password</em>.'), 'warning');
    }
  }
}

/**
 * Prepare core and entity user fields for user_save().
 */
function uif_assign_presave_fields($account, $user_data, $form_state) {
  $value_delimiter = $form_state['storage']['value_delimiter'];
  $timestamp_fields = array('created', 'access', 'login');
  $user_fields = array();
  
  foreach ($form_state['storage']['data']['fields'] as $label => $info) {
    if (!$info['supported']) {
      continue;
    }
    
    $parser = uif_isset_or($info['import']['parser']) ? $info['import']['parser'] : 'uif_get_raw_value';
    
    if ($info['type'] == 'core') {
      $user_fields[$label] = $parser($account, $info['data'], $user_data[$label]);
    }
    elseif ($info['type'] == 'entity') {
      $field_values = array();
      $values = explode($value_delimiter, $user_data[$label]);
      $key = uif_isset_or($info['import']['key']) ? $info['import']['key'] : 'value';
      
      foreach ($values as $value) {
        $value = trim($value);
        if (drupal_strlen($value)) {
          $parsed_value = $parser($account, $info['data'], $value);
          if (!is_null($parsed_value)) {
            $field_values[] = $parsed_value;
          }
        }
      }
      
      for ($delta = 0; $delta < count($field_values); $delta++) {
        if (($info['data']['cardinality'] == 1) && ($delta > 0)) {
          break;
        }

        if (drupal_strlen($field_values[$delta])) {
          $user_fields[$label][LANGUAGE_NONE][$delta][$key] = $field_values[$delta];
        }
      }
    }
  }
  
  return $user_fields;
}

/**
 * Read and store field info relevant to the import.
 */
function uif_get_field_info($header) {
  $field_info = array();
  
  $users_table = drupal_get_schema('users');
  $instance_fields = uif_field_info_instances('user', 'user');
  $supported_fields = uif_get_supported_fields();
  
  foreach ($header as $label) {
    if (isset($users_table['fields'][$label])) {
      $supported = isset($supported_fields[$label]);

      $field_info[$label] = array(
        'type' => 'core',
        'supported' => $supported,
        'data' => $users_table['fields'][$label],
      );

      if ($supported) {
        $field_info[$label]['import'] = $supported_fields[$label];
      }
    }
    elseif (isset($instance_fields[$label])) {
      $data = uif_field_info_field($label);
      $supported = isset($supported_fields[$data['type']]);
      
      $field_info[$label] = array(
        'type' => 'entity',
        'supported' => $supported,
        'data' => $data,
      );
      
      if ($supported) {
        $field_info[$label]['import'] = $supported_fields[$data['type']];
      }
    }
    else {
      $supported = FALSE;
      $field_info[$label] = array(
        'type' => 'unknown',
        'supported' => $supported,
      );
    }
    
    if (!$supported) {
      drupal_set_message(t('Unknown column @field in the import file. Data in this column will be ignored.', array('@field' => $label)), 'warning');
    }
  }
  
  return $field_info;
}

/**
 * Given a field's machine name look up the field type.
 */
function uif_lookup_field_type($field_name) {
  if ($info = uif_field_info_field($field_name)) {
    return $info['type'];
  }
}

/**
 * Return TRUE if this module supports import of the passed field type.
 */
function uif_is_supported_field($field_type) {
  $supported_fields = uif_get_supported_fields();
  return isset($supported_fields[$field_type]);
}

/**
 * Return list of supported fields.
 */
function uif_get_supported_fields() {
  $supported_fields = &drupal_static(__FUNCTION__);
  if (!isset($supported_fields)) {
    $supported_fields = module_invoke_all('uif_supported_fields');
    drupal_alter('uif_supported_fields', $supported_fields);
  }
  return $supported_fields;
}

/**
 * Implementation of hook_uif_supported_fields().
 *
 * Provide out-of-box supported fields.
 */
function uif_uif_supported_fields() {
  $subs = array(
    '@strtotime_url' => 'http://php.net/manual/en/function.strtotime.php',
    '@tz_url' => url('admin/config/regional/settings'),
    '@mods_url' => url('admin/modules'),
    '@flds_url' => url('admin/config/people/accounts/fields'),
  );

  return array(
    'mail' => array(
      'type' => 'core',
      'required' => TRUE,
      'description' => t('the user\'s email address'),
    ),
    'name' => array(
      'type' => 'core',
      'description' => t('a name for the user. If not provided, a name is created based on the email.'),
    ),
    'pass' => array(
      'type' => 'core',
      'description' => t('a password for the user. If not provided, a password is generated.'),
    ),
    'roles' => array(
      'type' => 'core',
      'description' => t('roles for the user as delimited text, e.g. "admin|editor" (without quotes).'),
    ),
    'created' => array(
      'type' => 'core',
      'description' => t('the creation date for the user in <a href="@strtotime_url">strtotime()</a> format.', $subs),
      'parser' => 'uif_get_strtotime_value',
    ),
    'access' => array(
      'type' => 'core',
      'description' => t('the last access date for the user in <a href="@strtotime_url">strtotime()</a> format.', $subs),
      'parser' => 'uif_get_strtotime_value',
    ),
    'login' => array(
      'type' => 'core',
      'description' => t('the last login date for the user in <a href="@strtotime_url">strtotime()</a> format.', $subs),
      'parser' => 'uif_get_strtotime_value',
    ),
    'status' => array(
      'type' => 'core',
      'description' => t('the account status (1 = active (default) 0 = blocked).'),
    ),
    'timezone' => array(
      'type' => 'core',
      'description' => t('the time zone to use for this user. You should <a href="@tz_url">let users set their time zone</a> if you import this.', $subs),
    ),
    'language' => array(
      'type' => 'core',
      'description' => t('the language to use for this user. You should <a href="@mods_url">enable the locale module</a> if you import this.', $subs),
    ),
    'list_boolean' => array(
      'type' => 'entity',
      'label' => t('Boolean'),
      'description' => t('true/false. Use 0 for false, 1 for true.'),
    ),
    'number_float' => array(
      'type' => 'entity',
      'label' => t('Float'),
      'description' => t('floating point number'),
    ),
    'number_decimal' => array(
      'type' => 'entity',
      'label' => t('Decimal'),
      'description' => t('decimal number'),
    ),
    'number_integer' => array(
      'type' => 'entity',
      'label' => t('Integer'),
      'description' => t('integer number'),
    ),
    'list_float' => array(
      'type' => 'entity',
      'label' => t('List (float)'),
      'description' => t('list of floating point values'),
    ),
    'list_integer' => array(
      'type' => 'entity',
      'label' => t('List (integer)'),
      'description' => t('list of integers'),
    ),
    'list_text' => array(
      'type' => 'entity',
      'label' => t('List (text)'),
      'description' => t('list of text values'),
    ),
    'text' => array(
      'type' => 'entity',
      'label' => t('Text'),
      'description' => t('text'),
    ),
    'text_long' => array(
      'type' => 'entity',
      'label' => t('Long text'),
      'description' => t('long text'),
    ),
    'text_with_summary' => array(
      'type' => 'entity',
      'label' => t('Long text and summary'),
      'description' => t('long text and summary'),
    ),
    'taxonomy_term_reference' => array(
      'type' => 'entity',
      'label' => t('Taxonomy term reference'),
      'parser' => 'uif_get_taxonomy_value',
      'key' => 'tid',
      'description' => t('taxonomy term ID or name'),
    ),
  );
}

/**
 * Helper function to process import data for core supported fields.
 */
function uif_get_raw_value($account, $field_info, $value) {
  return $value;
}

/**
 * Helper function to process import data for core supported fields.
 */
function uif_get_taxonomy_value($account, $field_info, $value) {
  if (uif_is_natural($value)) {
    return $value;
  }

  if (drupal_strlen($field_info['settings']['allowed_values'][0]['vocabulary'])) {
    $terms = taxonomy_get_term_by_name($value, $field_info['settings']['allowed_values'][0]['vocabulary']);
    if (count($terms)) {
      $tids = array_keys($terms);
      return $tids[0];
    }
  }
}

/**
 * Helper function to convert date string to timestamp.
 */
function uif_get_strtotime_value($account, $field_info, $value) {
  // BUG: do strtotime() check in validation?
  $timestamp = strtotime($value);
  return ($timestamp < 1) ? strtotime('now') : $timestamp; 
}

/**
 * Return TRUE if a $val is a natural number (integer 1, 2, 3, ...).  Base can
 * be changed to zero if desired.
 */
function uif_is_natural($val, $base = 1) {
  if (!isset($val)) {
    return FALSE;
  }
  $return = ((string)$val === (string)(int)$val);
  if ($return && intval($val) < $base) {
    $return = FALSE;
  }
  return $return;
}

/**
 * Check if a variable is set and return it if so, otherwise the alternative.
 */
function uif_isset_or(&$val, $alternate = NULL) {
  return isset($val) ? $val : $alternate;
}

/**
 * Wrapper for field_info_instances() to avoid module dependency.
 */
function uif_field_info_instances($entity_type = NULL, $bundle_name = NULL) {
  return function_exists('field_info_instances') ? field_info_instances($entity_type, $bundle_name) : array();
}

/**
 * Wrapper for field_info_field() to avoid module dependency.
 */
function uif_field_info_field($field_name) {
  return function_exists('field_info_field') ? field_info_field($field_name) : array();
}
