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

  // Delete selected cache id from bin.
  $deleted = MemcacheStorageAPI::delete($cache_id, $cache_bin);

  if ($js == 'ajax') {

    // Output a message depends on action result.
    $message = $deleted ? t('Success') : t('Failed');

    // Replace ajax link with an output message.
    $selector = str_replace(array(' ','_', '/', '[', ']', ':'), '-', $cache_bin . '-' . $cache_id);
    $commands[] = ajax_command_replace('.' . $selector, $message);
    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {

    if ($deleted) {
      drupal_set_message(t('Cache with ID "%cid" was successfully removed from bin "%bin".', array('%cid' => $cache_id, '%bin' => $cache_bin)));
    }
    else {
      drupal_set_message(t('Cache with ID "%cid" is unable to remove from bin "%bin".', array('%cid' => $cache_id, '%bin' => $cache_bin)), 'warning');
    }

    // Try to reload user page.
    $redirect_url = isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '<front>';
    drupal_goto($redirect_url);
  }

}
