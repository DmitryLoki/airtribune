<?php

/**
 * @file
 * Provides class for memcached data handling within cache_page bin.
 */

// Define contant that indicates whether external page cache is enabled.
define('MEMCACHE_STORAGE_EXTERNAL_PAGE_CACHE', variable_get('memcache_storage_external_page_cache', FALSE));

// Load include with Memcache API.
// We don't rely here on Drupal autoload mechanism because this include could
// be used before Drupal registry with all classes is loaded.
require_once dirname(__FILE__) . '/memcache_storage.api.inc';


/**
 * Class handles memcached cache objects.
 */
class MemcacheStoragePageCache extends MemcacheStorage implements DrupalCacheInterface {

  /**
   * Ovirrides MemcacheStorage::getMultiple().
   */
  function getMultiple(&$cids) {

    // No direct access to the cache if enabled external integration.
    if (MEMCACHE_STORAGE_EXTERNAL_PAGE_CACHE) {
      return array();
    }

    // Process page cache get as usual.
    return parent::getMultiple($cids);
  }

  /**
   * Ovirrides MemcacheStorage::set().
   */
  function set($cid, $data, $expire = CACHE_PERMANENT) {

    // Some servers (like Nginx) may access page cache directly from memcached pool
    // to avoid passing request to the backend. But they only know how to get
    // simple HTML string, not an objects. So we have to store simple HTML code.
    if (MEMCACHE_STORAGE_EXTERNAL_PAGE_CACHE && !empty($data['body'])) {

      // Developers may set custom expiration for cached pages in settings.php.
      $custom_expiration = variable_get('memcache_storage_page_cache_custom_expiration', FALSE);
      if ($custom_expiration) {
        $expire = variable_get('memcache_storage_page_cache_expire', 0);
      }

      // Memcached supports TTL in second from current timestamp.
      $expire = $expire > REQUEST_TIME ? $expire - REQUEST_TIME : $expire;

      // Memcached doesn't support expiration values less than 0 (CACHE_PERMANENT).
      $expire = $expire < CACHE_PERMANENT ? CACHE_PERMANENT : $expire;

      return MemcacheStorageAPI::set($cid, $data['body'], $expire, $this->bin);
    }

    // Process cache set as usual.
    return parent::set($cid, $data, $expire);
  }

  /**
   * Implements DrupalCacheInterface::clear().
   */
  function clear($cid = NULL, $wildcard = FALSE) {

    // If enabled memcache storage external page cache we only may delete cache by key.
    // This is because memcached doesn't support deletion by wildcard.
    if (MEMCACHE_STORAGE_EXTERNAL_PAGE_CACHE && !empty($cid) && !$wildcard) {

      // Convert string to an array to reduce amount of 'if-else' sections.
      if (!is_array($cid)) {
        $cid = array($cid);
      }

      // Remove HTML page from the cache_page bin.
      foreach ($cid as $cache_id) {
        MemcacheStorageAPI::delete($cache_id, $this->bin);
      }
    }

    // Process cache deletion as usual.
    return parent::clear($cid, $wildcard);
  }

}
