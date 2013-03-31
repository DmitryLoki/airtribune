<?php
/**
 * @file
 *  Allows the user to access related user info during a masquerade.
 *
 *  To some, this plugin may be confusing. The idea behind it is that we can
 *  provide access to the user on the opposite side of a masquerade based
 *  on an available user. (Most often, the "current" user).
 *
 *  For instance:
 *  - Joe Smith is masquerading as "John Jacobson".
 *  - We want "John Jacobson" to know if, when, and who is using his
 *    account as he browses certain pages.
 *  - So, this plugin would allow you to place information about
 *    "Joe Smith" into the page while "John Jacobson" is browsing.
 */

/**
 * Plugin definition.
 * @todo: I had trouble finding solid documentation around this,
 *        so, we're basically building-by-example.
 */
$plugin = array(
  'title' => t('User from Masquerade'),
  'keyword' => 'masquerade',
  'description' => t('Creates user contexts from a masquerade.'),
  'context' => 'masquerade_ctools_user_from_masquerade_context',
  'edit form' => 'masquerade_ctools_user_from_masquerade_settings_form',
  'defaults' => array(
    'mode' => 'masqueradee',
  ),
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Retrieves the user info from the context.
 *
 * @param bool $context
 *  The current contexts.
 * @param array $conf
 *  The plugin configuration.
 * @param bool $unknown
 *  ??? There is a mystery argument which appears to be a boolean.
 * @returns
 *  Returns a context object containing the user we want.
 * @retval ctools_context
 */
function masquerade_ctools_user_from_masquerade_context($context, $conf) {
  global $user;

  // @todo: This function is database intensive, we either need:
  //  a way to cache results, or a way to use fewer queries.

  if (empty($context[0]->data)
    || !isset($context[0]->data->uid)
    || empty($conf)) {
    return ctools_context_create_empty('user', NULL);
  }

  // We evaluate using isset() to ensure that the "anonymous"
  // user is not passed over.
  $argument = $context[0]->data->uid;

  // NOTE: If we want to know who the masquerader is,
  // we need to check if the current user is BEING masqueraded.
  if ('masquerader' == $conf['mode']
    && masquerade_ctools_is_being_masqueraded($argument)) {
    $query = db_select('masquerade', 'm')
      ->fields('m', array('uid_from'))
      ->condition('uid_as', $argument, '=')
      ->range(0,1)
      ->execute();
  }

  // NOTE: If we want to know who the masqueradee is,
  // we need to check if the current user IS masquerading.
  if ('masqueradee' == $conf['mode']
    && masquerade_ctools_is_masquerading($argument)) {
    $query = db_select('masquerade', 'm')
      ->fields('m', array('uid_as'))
      ->condition('uid_from', $argument, '=')
      ->range(0,1)
      ->execute();
  }

  // If you're not masquerading or being masqueraded,
  // there won't be a query generated. So, return empty.
  if (!isset($query)) {
    return ctools_context_create_empty('user', NULL);
  }

  $account = user_load($query->fetchCol());
  return ctools_context_create('user', $account);
}

/**
 * Allow the user to configure the context in the UI.
 * @param array $form
 *  The form (any inherited form structure or pre-defined properties).
 * @param array $form_state
 *  The form state (current values, security tokens, etc).
 * @returns
 *  A form the user will see when configuring this plugin.
 * @retval array
 */
function masquerade_ctools_user_from_masquerade_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // Move the context source below our settings.
  $form['context']['#weight'] = 1;

  $form['context'][0]['#title'] = t('Source User');
  $form['context'][0]['#description'] = t('Who the masquerade will lookup the target user from.');

  $form['settings']['mode'] = array(
    '#weight' => 0,
    '#title' => t('Target user'),
    '#type' => 'radios',
    '#options' => array(
      'masquerader' => t('The person masquerading'),
      'masqueradee' => t('The person being masqueraded'),
    ),
    '#description' => t('Which person in the masquerade do you need access to?')
      . t('You should only need this relationship if you need the REVERSE of the "current user".'),
    '#default_value' => $conf['mode'],
  );

  // Unless a keyword is already set, we can change the keyword to be something
  // more appropriate based on the selected 'mode'.
  // For instance, if we want access to the person who is using our account,
  // the keyword should be "masquerader".
  // Conversely, if we want access to the person we ARE using, the
  // keyword should be "masqueradee".
  $form['keyword']['#default_value'] = !empty($conf['keyword']) ? $conf['keyword'] : $conf['mode'];

  return $form;
}
