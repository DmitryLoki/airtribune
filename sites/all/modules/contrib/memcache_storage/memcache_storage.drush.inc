<?php

/**
 * @file
 * This is the drush integration for the Memcache Storage module.
 */

/**
 * Implements hook_drush_command().
 */
function memcache_storage_drush_command() {

  $items['memcache-storage-flush'] = array(
    'description' => 'Flushes all memcached data',
    'examples' => array(
      'drush memcached-flush' => 'Flushes all data stored in memcached.',
      'drush ms-flush' => 'Flushes all data stored in memcached.',
    ),
    'aliases' => array('ms-flush'),
    'drupal dependencies' => array('memcache_storage'),
    'callback' => 'drush_memcache_storage_flush',
  );

  $items['memcache-storage-clear-cache'] = array(
    'description' => 'Removes cache item from cache bin.',
    'examples' => array(
      'drush memcache-storage-clear-cache panels:223' => 'Remove cache with id "panels:223" from bin named "cache".',
      'drush ms-cc module_implements cache_bootstrap' => 'Remove cache with id "module_implements" from bin named "cache_bootstrap".',
    ),
    'aliases' => array('ms-cc'),
    'drupal dependencies' => array('memcache_storage'),
    'callback' => 'drush_memcache_storage_clear_cache',
  );

  $items['memcache-storage-flush-bin'] = array(
    'description' => 'Invalidates all data stored in the selected cache bin.',
    'examples' => array(
      'drush memcache-storage-flush-bin' => 'Invalidate all data in the cache bin named "cache".',
      'drush ms-fb cache_bootstrap' => 'Invalidate all data in the cache bin named "cache_bootstrap".',
    ),
    'aliases' => array('ms-fb'),
    'drupal dependencies' => array('memcache_storage'),
    'callback' => 'drush_memcache_storage_flush_bin',
  );

  return $items;
}

/**
 * Callback for flushing all memcached data.
 */
function drush_memcache_storage_flush() {
  memcache_storage_flush_all_cache();
}

/**
 * Callback for invalidation of all data stored in cache bin.
 */
function drush_memcache_storage_flush_bin() {
  $arguments = drush_get_arguments();

  $cache_bin = isset($arguments[1]) ? $arguments[1] : 'cache';
  $result = cache_clear_all('*', $cache_bin, TRUE);

  if ($result) {
    drupal_set_message(dt('Cache bin "@bin" was successfully flushed.', array('@bin' => $cache_bin)));
  }
  else {
    drupal_set_message(dt('Unable to flush cache bin "@bin".', array('@bin' => $cache_bin)), 'warning');
  }
}

/**
 * Callback for removing cache object from cache bin.
 */
function drush_memcache_storage_clear_cache() {

  $arguments = drush_get_arguments();

  if (empty($arguments[1])) {
    drupal_set_message(dt('No cache ID passed.'), 'warning');
    return;
  }

  $cache_id = $arguments[1];

  $cache_bin = isset($arguments[2]) ? $arguments[2] : 'cache';
  $result = cache_clear_all($cache_id, $cache_bin);

  if ($result) {
    drupal_set_message(dt('Cache with id "@id" was successfully removed from bin "@bin".',
      array('@id' => $cache_id, '@bin' => $cache_bin)));
  }
  else {
    drupal_set_message(dt('Cache with id "@id" was not found in bin "@bin".',
      array('@id' => $cache_id, '@bin' => $cache_bin)), 'warning');
  }
}
