<?php

/**
 * @file
 * Page callbacks for Memcache Storage module.
 */

/**
 * Clear cache data from selected cache bin.
 *
 * @param $js
 *   Indicates whether js is enabled or not.
 *
 * @param $cache_bin
 *   Name of cache bin.
 *
 * @param $cache_id
 *   Cache ID.
 *
 * @return array
 *   Array with ajax commands (if js is enabled).
 */
function memcache_storage_clear_cache_ajax_callback($js, $cache_bin, $cache_id) {

  // Check token to avoid CSRF vulnerability.
  if (!drupal_valid_token($_GET['token'], $cache_bin . '-' . $cache_id)) {
    $js == 'ajax' ? ajax_deliver(MENU_ACCESS_DENIED) : drupal_access_denied();
    exit;
  }

  // Delete selected cache id from bin.
  $deleted = MemcacheStorageAPI::delete($cache_id, $cache_bin);

  if ($js == 'ajax') {

    // Output a message depends on action result.
    $message = $deleted ? '<span style="color:green;">' . t('Success') . '<span>' : '<span style="color:red;">' . t('Failed') . '</span>';

    // Replace ajax link with an output message.
    $selector = str_replace(array(' ','_', '/', '[', ']', ':'), '-', $cache_bin . '-' . $cache_id);
    $commands[] = ajax_command_invoke('.' . $selector, 'replaceWith', array($message));
    ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
  }
  else {

    $args = array('%cid' => $cache_id, '%bin' => $cache_bin);
    if ($deleted) {
      drupal_set_message(t('Cache with ID "%cid" was successfully removed from bin "%bin".', $args));
    }
    else {
      drupal_set_message(t('Cache with ID "%cid" is unable to remove from bin "%bin".', $args), 'warning');
    }

    // Try to reload user page.
    $redirect_url = isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '<front>';
    drupal_goto($redirect_url);
  }

}
