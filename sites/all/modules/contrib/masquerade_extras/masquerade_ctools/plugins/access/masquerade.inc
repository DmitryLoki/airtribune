<?php
/**
 * @file
 *  Ctools access plugin which checks for masquerading conditions.
 */
$plugin = array(
  // The plugin name as presented in the UI.
  'title' => t('User: Is Masquerading'),
  // A description of the plugin.
  'description' => t('Checks whether or not a user is masquerading as another.'),
  // The function to call when this plugin is evaluated.
  'callback' => 'masquerade_ctools_masquerade_access_check',
  // Provide a default value for the plugin.
  'default' => array(
    'mode' => 'is_masquerading'
  ),
  // The function to call to retrieve a summary of the plugin's configuration.
  'summary' => 'masquerade_ctools_masquerade_access_summary',
  // Evaluate this plugin against users.
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
  // The function to call to retrieve the plugin configuration form.
  'settings form' => 'masquerade_ctools_masquerade_access_settings',
);

/**
 * Provides a cutomizable form for this access check.
 * @param array $form
 *  The form structure.
 * @param array $form_state
 *  The form state.
 * @param array $conf
 *  The current plugin configuration.
 * @returns
 *  A form.
 * @retval array
 */
function masquerade_ctools_masquerade_access_settings(&$form, &$form_state, $conf) {
  $form['settings']['mode'] = array(
    '#title' => t('How should this be evaluated?'),
    '#type' => 'radios',
    '#options' => array(
      'is_masquerading' => t('Is posing as another user'),
      'is_being_masqueraded' => t('Is being used by another user'),
    ),
    '#default_value' => $conf['mode'],
  );

  return $form;
}

/**
 * Checks masquerade conditions.
 * If no context is provided, this will automatically return FALSE.
 * @param array $conf
 *  The plugin configuration.
 * @param array $context
 *  Contexts to evaluate against.
 * @returns
 *  TRUE if the current user is masquerading.
 *  FALSE otherwise.
 * @retval bool
 */
function masquerade_ctools_masquerade_access_check($conf, $context) {
  // If no account was supplied, exit.
  if (empty($context)) {
    return FALSE;
  }

  // The user account will aready be loaded.
  $account = $context[0]->data;

  if (isset($_SESSION['masquerading']) && is_numeric($_SESSION['masquerading'])) {
    ctools_context_create('masquerade', $_SESSION['masquerading']);
  }

  // Check if the user is masquerading.
  if ('is_masquerading' == $conf['mode']) {
    return masquerade_ctools_is_masquerading($account);
  }

  // Check if the user is being masqueraded.
  if ('is_being_masqueraded' == $conf['mode']) {
    return masquerade_ctools_is_being_masqueraded($account);
  }

  // Fallback value if no configuration exists.
  return FALSE;
}

/**
 * Provides a simple access summary to administrators for this plugin.
 * @param array $conf
 *  The plugin configuration.
 * @param array $context
 *  The contexts to evaluate.
 * @returns
 *  A string which states whether or not the current user is masquerading.
 * @retval string
 */
function masquerade_ctools_masquerade_access_summary($conf, $context) {
  $mode = '';

  // Are we evaluating if the user is posing as someone else?
  if ('is_masquerading' == $conf['mode']) {
    $mode = 'posing as another user';
  }

  // Are we evaluating if the user's account is being used by someone else?
  else if ('is_being_masqueraded' == $conf['mode']) {
    $mode = 'in use by another user';
  }

  // Generate a summary string.
  return t('User: "@username" is "@mode".', array(
    '@username' => $context[0]->identifier,
    '@mode' => $mode,
  ));
}
