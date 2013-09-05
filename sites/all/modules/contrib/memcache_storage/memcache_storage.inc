<?php

/**
 * @file
 * Provides class for memcached data handling.
 */

// Load include with Memcache API.
// We don't rely here on Drupal autoload mechanism because this include could
// be used before Drupal registry with all classes is loaded.
require_once dirname(__FILE__) . '/memcache_storage.api.inc';

/**
 * Class handles memcached cache objects.
 */
class MemcacheStorage implements DrupalCacheInterface {

  /**
   * Name of cache bin.
   * Example: 'cache' or 'cache_page', etc.
   */
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

    $cache_bin = $this->preprocessCacheBinName();
    $data = MemcacheStorageAPI::getMultiple($cids, $cache_bin);

    // Build a new array with cached data using normal cache id.
    $cache = array();
    if (empty($data)) {
      return $cache;
    }

    foreach ($data as $item) {
      // Check expiration for every cache item recieved from memcached pool.
      if ($this->validateItem($item)) {
        $cache[$item->cid] = $item;
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

    // We should always keep in storage temporary cache data.
    // Such cached data are invalidates during cache_get() operations.
    if ($expire == CACHE_TEMPORARY) {

      // We should set expiration to 0 for temporary cache.
      // This type of cache could be expired after fetching from memcached storage.
      // @see MemcacheStorage::validateItem().
      $expire = 0;

      // Process custom cache expiration for pages.
      if ($this->bin == 'cache_page') {

        // Developers may set custom expiration for cached pages in settings.php.
        $custom_expiration = variable_get('memcache_storage_page_cache_custom_expiration', FALSE);
        if ($custom_expiration) {
          $expire = variable_get('memcache_storage_page_cache_expire', 0);
        }
      }
    }
    // Otherwise simply convert default drupal expire time to memcache expire time.
    elseif ($expire > REQUEST_TIME) {
      $expire -= REQUEST_TIME;
    }

    // Save data into memcached pool.
    $cache_bin = $this->preprocessCacheBinName();
    return MemcacheStorageAPI::set($cid, $cache, $expire, $cache_bin);
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
          // @see $this::preprocessCacheID();
          $this->increaseBinIndex();
        }
        else {

          // Load array with all wildcards.
          $wildcards = variable_get('memcache_storage_wildcards', array());

          // Add / replace wildcard.
          // Every cache item after load from memcached pool checks wildcard matches.
          $wildcards[$this->bin][$cid] = REQUEST_TIME;
          $this->variableSet('memcache_storage_wildcards', $wildcards);
        }
      }
      elseif (is_array($cid)) {
        $cache_bin = $this->preprocessCacheBinName();
        foreach ($cid as $cache_id) {
          MemcacheStorageAPI::delete($cache_id, $cache_bin);
        }
      }
      else {
        $cache_bin = $this->preprocessCacheBinName();
        MemcacheStorageAPI::delete($cid, $cache_bin);
      }
    }

    return TRUE;
  }

  /**
   * Implements DrupalCacheInterface::isEmpty().
   */
  function isEmpty() {
    // It is unable to get empty state of memcached pool,
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

    // Check if cache object is valid.
    if (empty($cache->cid) || empty($cache->created) || !isset($cache->expire)) {
      return FALSE;
    }

    // Load array with all wildcards.
    $wildcards = variable_get('memcache_storage_wildcards', array());
    $current_wildcards = !empty($wildcards[$this->bin]) ? $wildcards[$this->bin] : array();

    foreach ($current_wildcards as $wildcard => $flush_timestamp) {

      // See if wildcard is actual for current cache item.
      if ($cache->created <= $flush_timestamp) {

        // See if current cache id matches wildcard.
        if (strpos($cache->cid, $wildcard) === 0) {

          // Remove expired item from memcache.
          $cache_bin = $this->preprocessCacheBinName();
          MemcacheStorageAPI::delete($cache->cid, $cache_bin);

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

      // Custom behavior for cached pages.
      if ($this->bin == 'cache_page') {

        // Get timestamp of last page cache flush only if custom expiration is disabled.
        // In other case memcached will handle expiration of this cache itself.
        $custom_expiration = variable_get('memcache_storage_page_cache_custom_expiration', FALSE);
        if ($custom_expiration == FALSE) {

          // We should load variables for page cache earlier.
          // Drupal variables are load only during 4th bootstrap phase,
          // while page cache loads during 2th bootstrap phase.
          $variables = cache_get('variables', 'cache_bootstrap');
          if (!empty($variables->data) && !empty($variables->data['cache_flush_cache_page'])) {
            $last_bin_flush = $variables->data['cache_flush_cache_page'];
          }
        }
      }

      if ($cache->created <= $last_bin_flush) {

        // Remove expired item from memcache.
        $cache_bin = $this->preprocessCacheBinName();
        MemcacheStorageAPI::delete($cache->cid, $cache_bin);

        // Return no value from cache.
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Add a number to the name of cache bin.
   * This small feature allows to manage flushing of entire cache bin.
   * To flush bin we only need to change this number (bin index).
   */
  protected function preprocessCacheBinName() {
    return $this->bin . '_' . $this->getBinIndex();
  }

  /**
   * Increase cache bin index.
   * This operation changes all memcache keys in selected cache bin
   * so we simulate cache flush for it.
   */
  protected function increaseBinIndex() {

    $currentIndex = $this->getBinIndex();

    $indexes = &drupal_static('memcache_storage_bin_indexes', array());
    $indexes[$this->bin] = ++$currentIndex;

    MemcacheStorageAPI::set('memcache_storage_bin_indexes', $indexes, 0);
  }

  /**
   * Load cache bin index.
   * This index is part of memcache key and changes if cache bin should be cleared.
   */
  protected function getBinIndex() {

    $indexes = &drupal_static('memcache_storage_bin_indexes', array());

    if (empty($indexes)) {
      $indexes = array();

      // Try to get bin indexes from cache.
      $cache = MemcacheStorageAPI::get('memcache_storage_bin_indexes');
      if (!empty($cache)) {
        $indexes = $cache;
      }
    }

    if (empty($indexes[$this->bin])) {
      $indexes[$this->bin] = 1; // Initial index value.
      MemcacheStorageAPI::set('memcache_storage_bin_indexes', $indexes, 0);
    }

    return $indexes[$this->bin];
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
