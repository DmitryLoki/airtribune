<?php

/**
 * @file
 * Provide class that manages memcache connections.
 */

/**
 * Integrates with memcache API.
 */
class MemcacheStorageAPI {

  // List of available memcache connections.
  private static $connections;

  // Unique debug key.
  private static $debug_key = 0;

  /**
   * Connect to memcache clustes and returns memcache object on success.
   *
   * @param $bin
   *   Cache bin name. i.e. 'cache' or 'cache_bootstrap'.
   *
   * @return bool|object
   *   Memcache or memcached object is connection was successfull. Otherwise FALSE.
   */
  public static function openConnection($bin = '') {

    // Get name of cluster for selected cache bin storage.
    $bin_cluster = self::getCacheBinCluster($bin);

    if (empty(self::$connections[$bin_cluster])) {

      // Load available servers and its clusters from settings.php.
      $server_list = variable_get('memcache_servers', array('127.0.0.1:11211' => 'default'));

      // Search for all servers matching bin cluster.
      $cluster_servers = array();
      foreach ($server_list as $server => $cluster_name) {
        if ($cluster_name == $bin_cluster) {
          $cluster_servers[] = $server;
        }
      }

      // No servers found for this cache bin.
      if (empty($cluster_servers)) {

        // Log error.
        self::logError('Could not find server(s) for cluster %cluster (bin %bin). Check your settings.php configuration.',
          array('%cluster' => $bin_cluster, '%bin' => $bin));

        // Return not initialized value.
        return FALSE;
      }

      $preferred = variable_get('memcache_extension');
      if (isset($preferred) && class_exists($preferred)) {
        $extension = $preferred;
      }
      // If no extension is set, default to PECL Memcache.
      elseif (class_exists('Memcache')) {
        $extension = 'Memcache';
      }
      elseif (class_exists('Memcached')) {
        $extension = 'Memcached';
      }

      // Check if Memcache extension enabled.
      if (empty($extension)) {

        // Log error.
        self::logError('<a href="@url_memcache">Memcache</a> or <a href="@url_memcached">Memcached</a> extension is not available.',
          array('@url_memcache' => 'http://pecl.php.net/package/memcache', '@url_memcached' => 'http://pecl.php.net/package/memcache'));

        return FALSE;
      }

      // Create new memcache connection.
      $memcache = new $extension();

      // Collect all servers thas is unable to connect.
      $failed_connections = array();

      // Connect to every server.
      foreach ($cluster_servers as $server) {

        list($host, $port) = explode(':', $server);

        // Support unix sockets in the format 'unix:///path/to/socket'.
        if ($host == 'unix') {

          // PECL Memcache supports 'unix:///path/to/socket' path in ::addServer function,
          // while PECL Memcached use only '/path/to/socket' string for the same purpose.
          if ($extension == 'Memcache') {
            $host = $server;
          }
          elseif ($extension == 'Memcached') {
            $host = substr($server, 7);
          }

          // Port is always 0 for unix sockets.
          $port = 0;
        }

        // Adding new server for memcache connection.
        $persistent = variable_get('memcache_storage_persistent_connection', FALSE);
        $connected = @$memcache->addServer($host, $port, $persistent);

        if (!$connected) {

          // Mark connection to this server as 'failed'.
          $failed_connections[] = $server;

          // Log error if unable to connect to server.
          self::logError('Could not connect to server %server (port %port).',
            array('%server' => $host, '%port' => $port));
        }
      }

      // If memcache is unable to connect to all servers it means that
      // we have no connections at all, and could not start memcached connection.
      if (sizeof($failed_connections) == sizeof($cluster_servers)) {
        return FALSE;
      }

      // Provided compressThreshold support for PECL Memcached library.
      if ($extension == 'Memcache') {

        // For more information see http://www.php.net/manual/en/memcache.setcompressthreshold.php.
        $compress_threshold = variable_get('memcache_storage_compress_threshold', array('threshold' => 20000, 'min_savings' => 0.2));
        if (isset($compress_threshold['threshold']) && isset($compress_threshold['min_savings'])) {
          $memcache->setCompressThreshold($compress_threshold['threshold'], $compress_threshold['min_savings']);
        }
      }
      elseif ($extension == 'Memcached') {

        $default_options = array(
          Memcached::OPT_COMPRESSION => FALSE,
          Memcached::OPT_DISTRIBUTION => Memcached::DISTRIBUTION_CONSISTENT,
        );

        // For more info about memcached contants see http://www.php.net/manual/en/memcached.constants.php.
        $memcached_options = variable_get('memcache_options', array());
        $memcached_options += $default_options;

        // Set memcached options.
        // See http://www.php.net/manual/en/memcached.setoption.php.
        foreach ($memcached_options as $key => $value) {
          $memcache->setOption($key, $value);
        }
      }

      // Store memcache object as a static object, to avoid duplicate connections to the same
      // memcache cluster, but for differens cache bins.
      self::$connections[$bin_cluster] = $memcache;
    }

    return self::$connections[$bin_cluster];
  }

  /**
   * Get single cache value from memcached.
   */
  public static function get($cache_id, $cache_bin = '', $preprocess_keys = TRUE) {
    $cache = self::getMultiple(array($cache_id), $cache_bin, $preprocess_keys);
    return isset($cache[$cache_id]) ? $cache[$cache_id] : FALSE;
  }

  /**
   * Get values from memcache storage.
   * Provide debug logging.
   *
   * @see http://www.php.net/manual/en/memcache.get.php
   */
  public static function getMultiple($cache_ids, $cache_bin = '', $preprocess_keys = TRUE) {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // If cache ids is a string, convert it to array anyway.
    if (!is_array($cache_ids)) {
      $cache_ids = array($cache_ids);
    }

    // Preprocess cache keys.
    $cids = array();
    $cid_matches = array();
    foreach ($cache_ids as $cache_id) {
      $cid = $preprocess_keys ? self::buildCacheKey($cache_id, $cache_bin) : $cache_id;
      $cids[] = $cid;
      $cid_matches[$cid] = $cache_id;
    }

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Get data from memcache storage.
    $cache = array();
    if ($memcache instanceof Memcache) {
      $cache = $memcache->get($cids);
    }
    elseif ($memcache instanceof Memcached) {
      $cache = $memcache->getMulti($cids);
    }

    // Return cache with correct keys.
    $output = array();
    if (!empty($cache)) {
      foreach ($cache as $cid => $data) {
        $cache_id = $cid_matches[$cid];
        $output[$cache_id] = $data;
      }
    }

    // Run final debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::finalDebugActions('get', $cache_bin, $cache_ids, $cid_matches, $output);
    }

    return $output;
  }

  /**
   * Set data to memcache pool.
   * Provide debug logging.
   *
   * @see http://www.php.net/manual/en/memcache.set.php
   */
  public static function set($cache_id, $data, $expire, $cache_bin = '', $preprocess_keys = TRUE) {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Build unique cache id.
    $cid = $preprocess_keys ? self::buildCacheKey($cache_id, $cache_bin) : $cache_id;

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Set data to memcached pool.
    $result = FALSE;
    if ($memcache instanceof Memcache) {
      // Get compression mode.
      $compressed = variable_get('memcache_storage_compress_data', 0);
      $result = $memcache->set($cid, $data, $compressed, $expire);
    }
    elseif ($memcache instanceof Memcached) {
      $result = $memcache->set($cid, $data, $expire);
    }

    // Run final debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::finalDebugActions('set', $cache_bin, $cache_id, $cid, $result);
    }

    return $result;
  }

  /**
   * Replace existing data in memcache pool.
   * Provide debug logging.
   *
   * @see http://www.php.net/manual/en/memcache.replace.php
   */
  public static function replace($cache_id, $data, $expire, $cache_bin = '', $preprocess_keys = TRUE) {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Build unique cache id.
    $cid = $preprocess_keys ? self::buildCacheKey($cache_id, $cache_bin) : $cache_id;

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Replace data if exists.
    $result = FALSE;
    if ($memcache instanceof Memcache) {
      // Get compression mode.
      $compressed = variable_get('memcache_storage_compress_data', 0);
      $result = $memcache->replace($cid, $data, $compressed, $expire);
    }
    elseif ($memcache instanceof Memcached) {
      $result = $memcache->replace($cid, $data, $expire);
    }

    // Run final debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::finalDebugActions('replace', $cache_bin, $cache_id, $cid, $result);
    }

    return $result;
  }

  /**
   * Delete value from memcache pool.
   * Provide debug logging.
   *
   * @see http://www.php.net/manual/en/memcache.delete.php
   */
  public static function delete($cache_id, $cache_bin = '', $preprocess_keys = TRUE) {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Build unique cache id.
    $cid = $preprocess_keys ? self::buildCacheKey($cache_id, $cache_bin) : $cache_id;

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Delete cached data from memcached.
    $result = $memcache->delete($cid);

    // Run final debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::finalDebugActions('delete', $cache_bin, $cache_id, $cid, $result);
    }

    return $result;
  }

  /**
   * Immediately invalidates all existing items.
   */
  static public function flushClusters() {

    $indexes = &drupal_static('memcache_storage_bin_indexes');

    $cache = self::get('memcache_storage_bin_indexes', '', FALSE);
    if (!empty($cache)) {
      $indexes = $cache;
    }

    // Simply increase index for each bin.
    // This index is a part of memcache key, so cache will request for data with a new keys.
    foreach ($indexes as $cache_bin => &$bin_index) {
      ++$bin_index;
    }

    return self::set('memcache_storage_bin_indexes', $indexes, 0, '', FALSE);
  }

  /**
   * Generates unique cache key.
   *
   * @param $cid
   *   Cache ID.
   *
   * @param $cache_bin
   *   Cache bin name.
   *
   * @return string
   *   Unique cache key.
   */
  protected static function buildCacheKey($cid, $cache_bin) {

    // Unique index of bin storage.
    // To flush cache for single storage we simply need to change this value.
    $bin_index = self::getBinIndex($cache_bin);

    // Load key prefix from settings.php.
    $key_prefix = variable_get('memcache_storage_key_prefix', '');

    // Build unique cache key.
    $key_base = $cache_bin . '_' . $bin_index;

    // Add urlencode to avoid problems with different protocols.
    $full_key = urlencode($key_base . '-' . $key_prefix . '-' . $cid);

    // Memcache only supports key length up to 250 bytes. If we have generated
    // a longer key, hash it with md5 which will shrink the key down to 32 bytes
    // while still keeping it unique.
    if (strlen($full_key) > 250) {
      $full_key = urlencode($key_base . '-' . md5($key_prefix . '-' . $cid));
    }

    return $full_key;
  }

  /**
   * Increase cache bin index.
   * This operation changes all memcache keys in selected cache bin so we simulate cache flush for it.
   */
  public static function increaseBinIndex($cache_bin) {

    $currentIndex = self::getBinIndex($cache_bin);

    $indexes = &drupal_static('memcache_storage_bin_indexes');
    $indexes[$cache_bin] = ++$currentIndex;

    self::set('memcache_storage_bin_indexes', $indexes, 0, '', FALSE);
  }

  /**
   * Load cache bin index.
   * This index is part of memcache key and changes if cache bin should be cleared.
   */
  public static function getBinIndex($cache_bin) {

    // Prevent from making unique indexes for locking mechanism and user sessions.
    if (in_array($cache_bin, array('semaphore', 'users', 'sessions', 'sessions_map'))) {
      return 0;
    }

    $indexes = &drupal_static('memcache_storage_bin_indexes');

    if (empty($indexes)) {
      $indexes = array();

      // Try to get bin indexes from cache.
      $cache = self::get('memcache_storage_bin_indexes', '', FALSE);
      if (!empty($cache)) {
        $indexes = $cache;
      }
    }

    if (empty($indexes[$cache_bin])) {
      $indexes[$cache_bin] = 1; // Initial index value.
      self::set('memcache_storage_bin_indexes', $indexes, 0, '', FALSE);
    }

    return $indexes[$cache_bin];
  }

  /**
   * Get name of cluster where cache bin should be stored.
   * Config loads from settings.php.
   *
   * @param $bin
   *   Cache bin name. i.e. 'cache' or 'cache_bootstrap'.
   *
   * @return string
   *   Cluster name.
   */
  static protected function getCacheBinCluster($bin) {

    // Example:
    // $conf['memcache_bins'] = array(
    //   'cache' => 'default',
    //   'cache_page' => 'pages',
    // );
    $cluster_bins = variable_get('memcache_bins', array());

    // Get server name for current cache bin.
    $cluster = 'default';
    if (!empty($cluster_bins[$bin])) {
      $cluster = $cluster_bins[$bin];
    }

    return $cluster;
  }

  /**
   * Trigger error if something goes wrong.
   *
   * @param $message
   * @param array $variables
   */
  static protected function logError($message, $variables = array()) {

    // We can't use watchdog because this happens in a bootstrap phase
    // where watchdog is non-functional. Register a shutdown handler
    // instead so it gets recorded at the end of page load.
    register_shutdown_function('watchdog', 'memcache_storage', $message, $variables, WATCHDOG_ERROR);
  }

  /**
   * First step of debug logging.
   * Start timer and get usage of memory before memcache action.
   */
  protected static function initialDebugActions() {
    $mem_usage = &drupal_static('memcache_storage_debug_mem_usage');

    // Start count time spent on setting data to memcache.
    timer_start(self::$debug_key);

    // Get memory usage before set new value into cache.
    $mem_usage[self::$debug_key] = memory_get_usage();
  }

  /**
   * Last step of debug logging.
   *
   * @param $method
   *   Memcache action name. For example, 'set'.
   *
   * @param $cache_bin
   *   Cache bin name where action performs.
   *
   * @param $cache_id
   *   Unprocessed Cache ID.
   *
   * @param $memcache_id
   *   Processed Cache ID right before memcache action.
   *
   * @param $result
   *   Results of action execution.
   */
  protected static function finalDebugActions($method, $cache_bin, $cache_id, $memcache_id, $result) {

    // Stop count timer.
    timer_stop(self::$debug_key);

    // Calculate memory usage.
    $mem_usage = &drupal_static('memcache_storage_debug_mem_usage');
    $used_memory = memory_get_usage() - $mem_usage[self::$debug_key];

    // Get array with debug data.
    $memcache_storage_debug_output = &drupal_static('memcache_storage_debug_output');

    // Log entries about memcache action.
    if (is_array($cache_id)) {
      foreach ($cache_id as $cid) {

        $unique_class = str_replace(array(' ','_', '/', '[', ']', ':'), '-', $cache_bin . '-' . $cid);
        $clear_link = array(
          '#theme' => 'link',
          '#text' => 'Delete',
          '#path' =>  'memcache_storage/delete/nojs/' . $cache_bin . '/' . $cid,
          '#options' => array(
            'attributes' => array(
              'class' => array('use-ajax', $unique_class),
            ),
            'html' => FALSE,
          ),
        );

        $memcache_storage_debug_output[] = array(
          'action' => count($cache_id) > 1 ? $method . 'Multiple' : $method,
          'timer' => timer_read(self::$debug_key),
          'memory' => $used_memory,
          'result' => isset($result[$cid]) ? 'HIT' : 'MISS',
          'bin' => $cache_bin,
          'key' => $cid,
          'clear_link' => $clear_link,
          'mem_key' => array_search($cid, $memcache_id),
        );
      }
    }
    else {

      $unique_class = str_replace(array(' ','_', '/', '[', ']', ':'), '-', $cache_bin . '-' . $cache_id);
      $clear_link = array(
        '#theme' => 'link',
        '#text' => 'Delete',
        '#path' =>  'memcache_storage/delete/nojs/' . $cache_bin . '/' . $cache_id,
        '#options' => array(
          'attributes' => array(
            'class' => array('use-ajax', $unique_class),
          ),
          'html' => FALSE,
        ),
      );

      $memcache_storage_debug_output[] = array(
        'action' => $method,
        'timer' => timer_read(self::$debug_key),
        'memory' => $used_memory,
        'result' => $result ? 'HIT' : 'MISS',
        'bin' => $cache_bin,
        'key' => $cache_id,
        'clear_link' => $clear_link,
        'mem_key' => $memcache_id,
      );
    }

    // Increase timer to get new time results.
    self::$debug_key++;
  }

}
