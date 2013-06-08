<?php

/**
 * @file
 * Provides class for memcache data handling.
 */

// Load include with memcache manager class.
// We don't rely here on Drupal autoload mechanism because this include could
// be used before Drupal registry with all classes is loaded.
require_once dirname(__FILE__) . '/memcache_storage.api.inc';

/**
 * Class handles memcache data.
 */
class MemcacheStorage implements DrupalCacheInterface {

  protected $bin;

  /**
   * Constructs a new MemcacheStorage object.
   */
  function __construct($bin) {
    $this->bin = $bin;
  }

  /**
   * Implements DrupalCacheInterface::get().
   */
  function get($cid) {
    $cids = array($cid);
    $cache = $this->getMultiple($cids);
    return isset($cache[$cid]) ? $cache[$cid] : FALSE;
  }

  /**
   * Implements DrupalCacheInterface::getMultiple().
   */
  function getMultiple(&$cids) {

    $data = MemcacheStorageAPI::getMultiple($cids, $this->bin);

    // Build a new array with cached data using normal cache id.
    $cache = array();
    if ($data !== FALSE) {
      foreach ($data as $item) {
        // Check expiration for every cache item recieved from memcache.
        if ($item = $this->validateItem($item)) {
          $cache[$item->cid] = $item;
        }
      }
    }

    // Leave cache ids that was unable to get data from memcache.
    $cids = array_diff($cids, array_keys($cache));

    return $cache;
  }

  /**
   * Implements DrupalCacheInterface::set().
   */
  function set($cid, $data, $expire = CACHE_PERMANENT) {

    // Build cache object (as Drupal always does).
    $cache = new stdClass;
    $cache->cid = $cid;
    $cache->data = $data;
    $cache->created = REQUEST_TIME;
    $cache->expire = $expire;

    // We should always keep in storage permanent and temporary cache data.
    // Such cached data are invalidates during cache_get() operations.
    if ($expire == CACHE_PERMANENT || $expire == CACHE_TEMPORARY) {
      $expire = 0;
    }
    // Otherwise simply convert default drupal expire time to memcache expire time.
    elseif ($expire > REQUEST_TIME) {
      $expire -= REQUEST_TIME;
    }

    // Save data in memcache pool.
    return MemcacheStorageAPI::set($cid, $cache, $expire, $this->bin);
  }

  /**
   * Implements DrupalCacheInterface::clear().
   */
  function clear($cid = NULL, $wildcard = FALSE) {

    // Function like cache_clear_all(NULL, 'cache_bin');
    // We should invalidate all old cache.
    if (empty($cid)) {

      $cache_min_lifetime = variable_get('cache_lifetime', 0);
      if (!empty($cache_min_lifetime)) {
        // Load timestamp of last cache flush for this bin.
        $cache_last_flush = variable_get('cache_flush_' . $this->bin, 0);
        if (empty($cache_last_flush) || REQUEST_TIME > ($cache_last_flush + $cache_min_lifetime)) {
          // Set timestamp when cache bin was flushed.
          // Actually, before cache load we will check this variable.
          $this->variableSet('cache_flush_' . $this->bin, REQUEST_TIME);
        }
      }
      else {
        // No minimum cache lifetime, flush all temporary cache entries now.
        $this->variableSet('cache_flush_' . $this->bin, REQUEST_TIME);
      }
    }
    else {
      if ($wildcard) {
        if ($cid == '*') {
          // Simple changing index for bin storage will flushes the whole cache bin,
          // because it is used for building memcache key.
          // @see MemcacheStorageAPI::buildCacheKey();
          MemcacheStorageAPI::increaseBinIndex($this->bin);
        }
        else {

          // Load array with all wildcards.
          $wildcards = variable_get('memcache_storage_wildcards', array());

          // Add / replace wildcard.
          // Every cache item after load from memcache checks wildcard matches .
          $wildcards[$this->bin][$cid] = REQUEST_TIME;
          $this->variableSet('memcache_storage_wildcards', $wildcards);
        }
      }
      elseif (is_array($cid)) {
        foreach ($cid as $cache_id) {
          MemcacheStorageAPI::delete($cache_id, $this->bin);
        }
      }
      else {
        MemcacheStorageAPI::delete($cid, $this->bin);
      }
    }

  }

  /**
   * Implements DrupalCacheInterface::isEmpty().
   */
  function isEmpty() {
    // It is unable to get empty state of memcache pool,
    // so we assume it is never empty.
    return FALSE;
  }

  /**
   * Validates cache item.
   * Checks if it is still valid and not expired.
   *
   * @param $cache
   *   Cache item loaded from memcache pool.
   *
   * @return bool|object
   *   Return FALSE if object is not valid.
   *   Return cache item otherwise.
   */
  protected function validateItem($cache) {

    // Load array with all wildcards.
    $wildcards = variable_get('memcache_storage_wildcards', array());
    $current_wildcards = !empty($wildcards[$this->bin]) ? $wildcards[$this->bin] : array();

    foreach ($current_wildcards as $wildcard => $flush_timestamp) {

      // See if wildcard is actual for current cache item.
      if ($cache->created < $flush_timestamp) {

        // See if current cache id matches wildcard.
        if (strpos($cache->cid, $wildcard) === 0) {

          // Remove expired item from memcache.
          MemcacheStorageAPI::delete($cache->cid, $this->bin);

          // Return no value from cache.
          return FALSE;
        }
      }
    }

    // For temporary cache we should check last bin flush.
    // If temporary cache was created earlier than last cache flush - cache is invalid.
    if ($cache->expire == CACHE_TEMPORARY) {

      // Timestamp when cache bin was flushed last time.
      $last_bin_flush = variable_get('cache_flush_' . $this->bin, 0);

      // Custom behavior for cache page.
      if ($this->bin == 'cache_page') {

        // Developers may set custom expiration time for cached pages in settings.php.
        $custom_expiration = variable_get('memcache_storage_page_cache_custom_expiration', FALSE);
        if ($custom_expiration) {
          $expire_time = variable_get('memcache_storage_page_cache_expire', 0);
          $last_bin_flush = $expire_time ? REQUEST_TIME - $expire_time : 0;
        }
        else {
          // We should load variables for page cache earlier.
          // Drupal variables are load only during 4th bootstrap phase,
          // while page cache loads during 2th bootstrap phase.
          $variables = cache_get('variables', 'cache_bootstrap');
          if (!empty($variables->data) && !empty($variables->data['cache_flush_' . $this->bin])) {
            $last_bin_flush = $variables->data['cache_flush_' . $this->bin];
          }
        }
      }

      if ($cache->created < $last_bin_flush) {

        // Remove expired item from memcache.
        MemcacheStorageAPI::delete($cache->cid, $this->bin);

        // Return no value from cache.
        return FALSE;
      }
    }

    return $cache;
  }

  /**
   * Internal function for setting new variable's value.
   * It skips two extra steps of variable_set() function:
   *   1. Avoid execution of cache_clear_all('variables', 'cache_bootstrap').
   *   2. Avoid extra load of `variable` table on next Drupal bootstrap.
   */
  protected function variableSet($name, $value) {
    global $conf;

    // If the name already matches the value, ignore the variable set.
    if (isset($conf[$name]) && $conf[$name] === $value) {
      return;
    }

    db_merge('variable')
      ->key(array('name' => $name))
      ->fields(array('value' => serialize($value)))
      ->execute();

    // If the variables are cached, get a fresh copy, update with the new value
    // and set it again.
    if ($cached = cache_get('variables', 'cache_bootstrap')) {
      $variables = $cached->data;
      $variables[$name] = $value;
      cache_set('variables', $variables, 'cache_bootstrap');
    }

    // If the variables aren't cached, there's no need to do anything.
    $conf[$name] = $value;
  }

}
