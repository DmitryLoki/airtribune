<?php
/**
 * @file
 * Provides some drush commands for masquerade.
 */

/**
 * Implements hook_drush_command().
 *
 * Specifies our custom commands.
 *
 * @see hook_drush_command()
 */
function masquerade_drush_drush_command() {
  $items = array();
  $items['masquerade'] = array(
    'description' => 'Manipulates masquerades.',
    'arguments' => array(
      'command' => 'The masquerade command to execute.',
      'account' => 'The user account to execute as.',
      'target' => 'The user account to pretend to be.',
    ),
    'options' => array(
    ),
    'aliases' => array(
      'msq'
    ),
    'examples' => array(
      'drush masquerade [list|show]' => 'Lists the active masquerades in the site.',
      'drush masquerade [terminate|end|stop|term] <source:username>' =>
        'Terminates any active masquerades for username|user ID|email address',
      'drush masquerade [start|begin] <source:username> <target:username>' =>
        'Initializes a masquerade for <username|user ID|email address>.' . "\n"
        . 'On the next page, they will become the "target" account.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_SITE,
  );
  $items['sessions'] = array(
    'description' => 'Manipulates user sessions.',
    'arguments' => array(
      'command' => 'The command to execute.',
      'account' => 'The user account to manipulate.',
    ),
    'examples' => array(
      'drush sessions [list]' => 'Lists all users logged in to the site.',
      'drush sessions <user>' => 'Lists any sessions belonging to <user>.',
      'drush sessions terminate <user>' => 'Ends the session for <user>.',
    ),
    'aliases' => array(
      'sess',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_SITE,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * @see hook_drush_help()
 */
function masquerade_drush_drush_help($section) {
  switch ($section) {
    // drush masquerade
    case 'drush:masquerade':
      return dt('Allows you to initialize, terminate, and list masquerades in the current site.');
    case 'meta:masquerade:title':
      return dt('Masquerade Commands');
    case 'meta:masquerade:summary':
      return dt('Manipulates masquerades within a Drupal site.');

    // drush sessions
    case 'drush:sessions':
      return dt('Allows you to view and terminate active user sessions in the site.');
    case 'meta:sessions:title':
      return dt('User Sesssions');
    case 'meta:sessions:summary':
      return dt('Manipulates user sessions in your Drupal site.');
  }
}

/**
 * Implements drush_HOOK_COMMAND().
 *
 * @param string $command
 *  Command to execute.
 * @param string $param1
 *  A property to pass in.
 *
 * @see drush_invoke()
 * @see drush_HOOK_COMMAND()
 */
function drush_masquerade_drush_sessions($command = NULL, $param1 = NULL) {
  switch ($command) {
    // Terminates a user's session.
    case 'terminate':
    case 'end':
    case 'stop':
    case 'term':
      return _masquerade_drush_sessions_terminate($param1);

    // Lists active masquerades.
    case 'list':
    case 'show':
    default:
      return _masquerade_drush_sessions($param1);
  }
}

/**
 * Implements drush_HOOK_COMMAND().
 *
 * @param string $command
 *  The command to execute.
 * @param string $param1
 *  A property to pass in.
 * @param string $param2
 *  An additional property to pass in.
 *
 * @see drush_invoke()
 * @see drush_HOOK_COMMAND()
 */
function drush_masquerade_drush_masquerade($command = NULL, $param1 = NULL, $param2 = NULL) {
  switch ($command) {
    // Terminates a masquerade from the source account.
    case 'terminate':
    case 'end':
    case 'stop':
    case 'term':
      return _masquerade_drush_terminate_masquerade($param1);

    // Starts a masquerade.
    case 'start':
    case 'begin':
      return _masquerade_drush_start_masquerade($param1, $param2);

    // Lists active masquerades.
    case 'list':
    case 'show':
    default:
      return _masquerade_drush_list($param1);
  }
}

/**
 * Retrieves a user account.
 * @param string $account
 *  The user ID, email address, or account name we want to load.
 * @return
 *  Loads the base user.
 * @retval stdClass
 */
function _masquerade_drush_get_user($account) {
  $or = db_or()
    ->condition('name', $account, '=')
    ->condition('mail', $account, '=')
    ->condition('uid', $account, '=');
  $user = db_select('users', 'u')
    ->fields('u')
    ->condition($or)
    ->execute()
    ->fetchObject();
  if (!empty($user)) {
    return user_load($user->uid);
  }
  return FALSE;
}

/**
 * Deletes active masquerades from the database.
 * This is exceptionally useful when an active masquerade is causing
 * a development problem and the user can't end the masquerade.
 * @param string $account
 *  The source account name whose masquerade(s) need to be stopped.
 */
function _masquerade_drush_terminate_masquerade($account) {
  $account = _masquerade_drush_get_user($account);

  // Make sure the user provided exists.
  if (empty($account)) {
    return drush_print("You must specify a valid user account. You can provide an email address, user ID, or username.");
  }

  $masquerades = db_select('masquerade', 'm')
    ->fields('m')
    ->condition('uid_from', $account->uid, '=')
    ->execute()
    ->fetchAll();

  // Check that the user specified is actually masquerading.
  if (empty($masquerades)) {
    return drush_log("The specified account is not currently masquerading.", 'warning');
  }

  // Loop over each masquerade the user currently has active.
  foreach ($masquerades as $masquerade) {
    // Restore the session owner to its originator.
    $upd = db_update('sessions')
      ->fields(array(
        'uid' => $masquerade->uid_from,
      ))
      ->condition('sid', $masquerade->sid, '=')
      ->execute();
  }

  // Terminate all masquerades in the masquerade table from this user.
  $num_ended = db_delete('masquerade')
    ->condition('uid_from', $account->uid, '=')
    ->execute();

  if ($num_ended > 0) {
    return drush_log('Ended "' . $num_ended . '" masquerades from account "'. $account->name . '"', 'success');
  }

  drush_log('No active masquerades for "' . $account->name . '" were located.', 'warning');
}

/**
 * Initializes a masquerade on the user's behalf.
 * This is useful when developing and you want the user to start masquerading
 * as soon as they login to the site.
 * @param string $account
 *  The (source) username.
 * @param string $target
 *  The (target) username.
 */
function _masquerade_drush_start_masquerade($account, $target) {
  drupal_session_initialize();
  $account = _masquerade_drush_get_user($account);
  $target = _masquerade_drush_get_user($target);

  // Ensure the user specified the account they want to begin the masquerade with.
  if (empty($account)) {
    return drush_log("You must specify the source user. You can provide an email address, user ID, or username.", 'error');
  }

  // Ensure the user specified the account they want to masquerade as.
  if (empty($target)) {
    return drush_log("You must specify the target user. You can provide an email address, user ID, or username.", 'error');
  }

  // Lookup the requested account's session.
  $s = db_select('sessions', 's')
         ->fields('s')
         ->condition('s.uid', $account->uid, '=')
         ->execute()
         ->fetchObject();

  // If the requested user doesn't have a session, this won't work...just exit.
  if (empty($s)) {
    return drush_log("The requested masquerader is not currently logged into the site.", 'error');
  }

  // Take over our own session with the session ID of the real user.
  session_id($s->sid);

  // Change ownership of the session to the target user.
  $upd = db_update('sessions')
    ->fields(array(
      'uid' => $target->uid,
      'session' => serialize($_SESSION),
      'cache' => 0
    ))
    ->condition('uid', $account->uid, '=')
    ->execute();

  if (empty($upd)) {
    return drush_log("Crap");
  }

  // Update the masquerade table.
  $added = db_insert('masquerade')
    ->fields(array(
      'uid_as' => $target->uid,
      'uid_from' => $account->uid,
      'sid' => $s->sid,
    ))->execute();

  // Inform the user the masquerade has begun.
  if (!empty($added)) {
    return drush_log('Initialized masquerade for "' . $account->name . '" as "' . $target->name . '"', 'success');
  }

  // There was a problem initializing the masquerade.
  drush_log('There was a problem initalizing the masquerade.', 'error');
}

/**
 * Displays a table of active masquerades in the site.
 * @param string $account
 *  An optional username, user ID, or email address to filter
 *  the list down to.
 */
function _masquerade_drush_list($account = NULL) {
  $account = _masquerade_drush_get_user($account);

  // @todo: There is a strange PHP chaining problem which 
  //        won't allow us to db_select()->join()->fields()
  //        as expected. Instead, we'll just step through
  //        each part...
  //        This only happens in this function...
  $query = db_select('masquerade', 'm');
  $query->join('users', 'u', 'm.uid_from = u.uid');
  $query->join('users', 'u2', 'm.uid_as = u2.uid');
  // $query->fields('m', array('sid')); // Hidden
  $query->fields('u', array('name', 'uid'));
  $query->fields('u2', array('name', 'uid'));

  // If a user account was provided, we can whittle down
  // the list to just masquerades with this account.
  if (!empty($account)) {
    $query->condition('m.uid_as', $account->uid, '=');
  }

  // Request the list of active masquerades.
  $list = $query->execute()->fetchAll();

  // Check if no masquerades were found.
  if (empty($list)) {
    return drush_log('No one is masquerading at this time.', 'ok');
  }

  // Fill in the rows.
  $rows = array();
  $rows[] = array(
    'Source User',
    'UserId',
    'Posing As',
    'UserId',
  );

  // Just a helpful display trick.
  $rows[] = array(
    '-------------------------',
    '----------',
    '-------------------------',
    '----------',
  );

  // Loop through the active masquerades and turn them into rows.
  foreach ($list as $m) {
    $rows[] = array(
      $m->name,
      // $m->sid, // Hidden
      $m->uid,
      $m->u2_name,
      $m->u2_uid
    );
  }

  // Display the list.
  drush_print_table($rows, TRUE);
}

/**
 * Utility command to dump the active sessions table from the site.
 * @param string $account
 *  An account name, user ID, or email address to search for.
 */
function _masquerade_drush_sessions($account = NULL) {
  // Grab all the sessions!
  $sessions = db_select('sessions', 's')
    ->fields('s')
    ->fields('u', array('name'));
  $sessions->join('users', 'u', 'u.uid = s.uid');

  // If an account was provided, load it.
  $user = _masquerade_drush_get_user($account);

  // If the account was found, limit the results to just that account.
  if (!empty($user)) {
    $sessions->condition('uid', $user->uid, '=');
  }
  else if (empty($user) && !empty($account)) {
    return drush_log(sprintf('The account "%s" could not be found.', $account), 'error');
  }

  // Execute the query.
  $sessions = $sessions->execute()->fetchAll();

  // If there are no active sessions, just quit.
  if (empty($account) && empty($sessions)) {
    return drush_log('No one is logged into the site right now.', 'ok');
  }
  else if (!empty($user) && empty($sessions)) {
    return drush_log('The user "' . $user->name . '" is not logged in right now.', 'ok');
  }

  // Dump a list of headers so the table actually makes sense.
  $list = array(
    array(
      'uid',
      'username',
      'hostname',
      'timestamp',
    ),
    array(
      '----------',
      '-----------',
      '---------------',
      '-----------',
    ),
  );
  foreach ($sessions as $s) {
    $list[] = array(
       $s->uid,
       $s->name,
       $s->hostname,
       $s->timestamp,
    );
  }
  drush_print_table($list, TRUE);
}


/**
 * Ends a user's session.
 * @param string $param1
 *  The account name, user id, or email address to lookup.
 */
function _masquerade_drush_sessions_terminate($param1 = NULL) {
  if (empty($param1)) {
    return drush_log("Please specify an account.", 'error');
  }

  // Try to lookup the user account.
  $account = _masquerade_drush_get_user($param1);

  // Make sure we found the account we wanted.
  if (empty($account)) {
    return drush_log(sprintf('The account "%s" could not be found.', $param1), 'error');
  }

  // Check which command we wanted to execute.
  $response = drush_prompt(sprintf('Are you sure you want to terminate "%s"\'s session? (y/n)', $account->name), NULL);
  $response = strtoupper(trim($response));

  if (!in_array($response, array('Y','YES'))) {
    return drush_log('Cancelled action.', 'ok');
  }
  
  $terminated = db_delete('sessions')->condition('uid', $account->uid, '=')->execute();
  drush_log(sprintf('Terminated %d sessions for "%s".', $terminated, $account->name), 'ok');
}
