<?php
/**
 * @file
 * Theme functions for User Links content type plugin.
 *
 * We cannot place preprocess function in plugin file
 * because this file is referenced in airtribune_theme().
 * @see #2896.
 */

/**
 * Preprocess variables for airtribune-user-links.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see airtribune-user-links.tpl.php
 */
function template_preprocess_airtribune_user_links(&$vars) {
  foreach (element_children($vars['elements']) as $key) {
    $vars[$key] = render($vars['elements'][$key]);
  }
  if ($vars['logged_in']) {
    $vars['user_name'] = airtrubune_format_username($vars['user']);
    $vars['user_profile_link'] = url('user/' . $vars['user']->uid);
    $vars['user_picture'] = theme('user_picture', array('account' => $vars['user']));
  }
}
