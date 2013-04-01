<?php
/**
 * @file
 *  Configures Context plugins for Masquerade.
 */

/**
 * Implements hook_context_plugins().
 *
 * Adds a masquerading condition to the context module.
 *
 * @see hook_context_plugins()
 */
function masquerade_context_context_plugins() {
  return array(
    'masquerade_context' => array(
      'handler' => array(
        'path' => drupal_get_path('module', 'masquerade_context') .'/plugins/condition',
        'file' => 'masquerade_context.inc',
        'class' => 'masquerade_context_condition',
        'parent' => 'context_condition',
      ),
    ),
  );
}

/**
 * Implements hook_context_registry().
 *
 * Tells the Context module to look for our custom plugins.
 *
 * @see hook_context_registry()
 */
function masquerade_context_context_registry() {
  return array(
    'conditions' => array(
      'masquerade_context' => array(
        'title' => t('Masquerade'),
        'description' => t('Sets this context when a user is posing as someone else.'),
        'plugin' => 'masquerade_context',
      ),
    ),
  );
}

/**
 * Implements hook_context_page_condition().
 *
 * Triggers our custom context conditions.
 *
 * @see hook_context_page_condition()
 */
function masquerade_context_context_page_condition() {
  global $user;

  if ($plugin = context_get_plugin('condition', 'masquerade_context')) {
    // Evalutes this context plugin.
    $plugin->execute($user);
  }
}
