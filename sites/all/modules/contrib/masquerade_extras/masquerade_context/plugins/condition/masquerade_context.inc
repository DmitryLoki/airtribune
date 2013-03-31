<?php
/**
 * @file
 *  Expose masquerade as a customizable context condition.
 */
class masquerade_context_condition extends context_condition {
  /**
   * Specifies the condition settings exposed to the user.
   * NOTE: Context will not save this condition if this is left empty.
   * @returns
   *  An array of user conditions that can apply to evaluate this condition.
   * @retval array
   */
  function condition_values() {
    return array(
      'myself' => t('Current User'),
      'other' => t('Displayed User') . t(' (only on user pages)'),
    );
  }

  /**
   * Exposes additonal configuration options for this plugin.
   * @returns
   *  A form.
   * @retval array
   */
  function options_form($context) {
    // Get the current settings from the context provided.
    $defaults = $this->fetch_from_context($context, 'options');
    $form = array();
    $form['mode'] = array(
      '#title' => t('How should this condition be evaluated?'),
      '#type' => 'checkboxes',
      '#default_value' => !empty($defaults['mode']) ? $defaults['mode']
        : array('is_masquerading' => 'is_masquerading'),
      '#options' => array(
        'is_masquerading' => t('This user is posing as someone else.'),
        'is_being_masqueraded' => t('Someone is posing as this user.'),
      ),
    );
    return $form;
  }

  /**
   * Evalutes this context condition.
   * @param stdClass $account
   *  The user account to evaluate.
   */
  function execute($account) {
    // Skip processing if no contexts use this condition.
    // @see context_condition::condition_used()
    if (!$this->condition_used()) {
      return;
    }

    // Evaluate if the user is masquerading.
    $this->execute_is_masquerading($account);

    // Evaluate if the user is being masqueraded by someone else.
    $this->execute_is_being_masqueraded($account);
  }

  /**
   * Evaluates if the account is masquerading.
   * @param stdClass $account
   *  The user account to evaluate.
   */
  function execute_is_masquerading($account) {
    global $user;

    // Evaluate if the current user is masquerading.
    $i_am_masquerading = $this->is_masquerading($user);

    // Evaluate if the account provided is masquerading.
    $you_are_masquerading = $this->is_masquerading($account);

    // Iterate through each context that uses this plugin.
    foreach ($this->get_contexts($account) as $context) {
      // Get the context's settings.
      $values = $this->fetch_from_context($context, 'values');
      $options = $this->fetch_from_context($context, 'options');

      // Skip processing if the context is not checking 'is masquerading'.
      if (empty($options['mode']['is_masquerading'])) {
        continue;
      }

      // Evaluate if we wanted to check against our own account.
      if ($i_am_masquerading
        && $account->uid == $user->uid && !empty($values['myself'])) {
        $this->condition_met($context, 'is_masquerading');
      }

      // Evaluate if we wanted to check against the viewed account.
      if ($you_are_masquerading
        && $account->uid != $user->uid && !empty($values['other'])) {
        $this->condition_met($context, 'is_masquerading');
      }
    }
  }

  /**
   * Evaluates if someone is posing as the account.
   * @param stdClass $account
   *  The user account to evaluate.
   */
  function execute_is_being_masqueraded($account) {
    global $user;

    // Evaluate if the current user is being masqueraded.
    $i_am_being_masqueraded = $this->is_being_masqueraded($user);

    // Evaluate if the account provided is masquerading.
    $you_are_being_masqueraded = $this->is_being_masqueraded($account);

    // Iterate through each context that uses this plugin.
    foreach ($this->get_contexts($account) as $context) {
      // Get the context's settings.
      $values = $this->fetch_from_context($context, 'values');
      $options = $this->fetch_from_context($context, 'options');

      // Skip processing if the context is not checking 'is being masqueraded'.
      if (empty($options['mode']['is_being_masqueraded'])) {
        continue;
      }

      // Evaluate if we wanted to check against our own account.
      if ($i_am_being_masqueraded
        && $account->uid == $user->uid && !empty($values['myself'])) {
        $this->condition_met($context, 'is_being_masqueraded');
      }

      // Evaluate if we wanted to check against the viewed account.
      if ($you_are_being_masqueraded
        && $account->uid != $user->uid && !empty($values['other'])) {
        $this->condition_met($context, 'is_being_masqueraded');
      }
    }
  }

  /**
   * Evaluates if the account is masquerading as someone else.
   * @param stdClass $account
   *  The user account to evaluate.
   * @returns
   *  TRUE if the account is posing as someone else.
   *  FALSE otherwise.
   * @retval bool
   */
  function is_masquerading($account) {
    global $user;

    // If the account is our own, check the user session.
    if ($account->uid == $user->uid) {
      return (isset($_SESSION['masquerading']) && is_numeric($_SESSION['masquerading']));
    }

    // You can override this query with:
    // hook_query_context_is_masquerading_alter().
    // @see hook_query_TAG_alter()
    $query = db_select('masquerade', 'm')
      ->addTag('context_is_masquerading')
      ->fields('m', array('uid_as'))
      ->condition('uid_from', $account->uid, '=')
      ->range(0,1)
      ->execute();
    $result = $query->fetchCol();
    return !empty($result);
  }

  /**
   * Evaluates if the account is being masqueraded by someone else.
   * @param stdClass $account
   *  The user account to evaluate.
   * @returns
   *  TRUE if someone else is posing as account.
   *  FALSE otherwise.
   * @retval bool
   */
  function is_being_masqueraded($account) {
    // You can override this query with:
    // hook_query_context_is_being_masqueraded_alter().
    // @see hook_query_TAG_alter()
    $query = db_select('masquerade', 'm')
      ->addTag('context_is_being_masqueraded')
      ->fields('m', array('uid_from'))
      ->condition('uid_as', $account->uid, '=')
      ->range(0,1)
      ->execute();
    $result = $query->fetchCol();
    return !empty($result);
  }
}
