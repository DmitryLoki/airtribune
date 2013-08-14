<?php

/**
 * @file
 * Provide class that processes memcached operations.
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

    // Get name of cluster for the selected cache bin storage.
    $cluster_name = self::getCacheBinCluster($bin);

    // Connect to the cluster and get memcached object.
    if (!isset(self::$connections[$cluster_name])) {

      // Store memcached object as a static object, to avoid duplicate connections to the same
      // memcached cluster but for differens cache bins.
      self::$connections[$cluster_name] = self::connectToCluster($cluster_name);
    }

    return self::$connections[$cluster_name];
  }

  /**
   * Connect to memcached cluster and return memcached object.
   *
   * @param $cluster_name
   *   Name of memcached cluster.
   *
   * @return object
   *   Connected memcached object or FALSE if no connection.
   */
  protected static function connectToCluster($cluster_name) {

    // Load available servers and its cluster names from settings.php.
    $server_list = variable_get('memcache_servers', array('127.0.0.1:11211' => 'default'));

    // Search for all servers matching bin cluster.
    $cluster_servers = array();
    foreach ($server_list as $server => $name) {
      if ($name == $cluster_name) {
        $cluster_servers[] = $server;
      }
    }

    // No servers found for this cache bin.
    if (empty($cluster_servers)) {

      // Log error.
      self::logError('Could not find server(s) for cluster %cluster. Check your settings.php configuration.',
        array('%cluster' => $cluster_name));

      // Return not initialized value.
      return FALSE;
    }

    $preferred = variable_get('memcache_extension');
    if (!empty($preferred) && class_exists($preferred)) {
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

    // Create new memcached connection.
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

      // Adding new server for memcached connection.
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

    return $memcache;
  }

  /**
   * Get single cache value from memcached pool.
   */
  public static function get($cache_id, $cache_bin = '') {
    $cache = self::getMultiple(array($cache_id), $cache_bin);
    return isset($cache[$cache_id]) ? $cache[$cache_id] : FALSE;
  }

  /**
   * Get values from memcache storage.
   * Provide debug logging.
   *
   * @see http://www.php.net/manual/en/memcache.get.php
   */
  public static function getMultiple($cache_ids, $cache_bin = '') {

    // Get memcached object.
    $memcache = self::openConnection($cache_bin);

    // No memcached connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Preprocess cache keys.
    $cids = array();
    foreach ($cache_ids as $cache_id) {
      $safe_key = self::preprocessCacheKey($cache_id, $cache_bin);
      $cids[$safe_key] = $cache_id;
    }

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Fetch data from memcached pool.
    $cache = array();
    if ($memcache instanceof Memcache) {
      $cache = @$memcache->get(array_keys($cids));
    }
    elseif ($memcache instanceof Memcached) {
      $cache = @$memcache->getMulti(array_keys($cids));
    }

    // Return cache with correct keys.
    $output = array();
    if (!empty($cache)) {
      $cache_keys = array_keys($cache);
      foreach ($cache_keys as $cache_key) {
        $output[$cids[$cache_key]] = $cache[$cache_key];
      }
    }

    // Run final debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::finalDebugActions('get', $cache_bin, array_values($cids), $cids, $output);
    }

    return $output;
  }

  /**
   * Save data into memcached pool.
   * Provide debug logging.
   *
   * @see http://www.php.net/manual/en/memcache.set.php
   */
  public static function set($cache_id, $data, $expire, $cache_bin = '') {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Build unique cache id.
    $cid = self::preprocessCacheKey($cache_id, $cache_bin);

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Set data to memcached pool.
    $result = FALSE;
    if ($memcache instanceof Memcache) {
      // Get compression mode.
      $compressed = variable_get('memcache_storage_compress_data', 0);
      $result = @$memcache->set($cid, $data, $compressed, $expire);
    }
    elseif ($memcache instanceof Memcached) {
      $result = @$memcache->set($cid, $data, $expire);
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
  public static function replace($cache_id, $data, $expire, $cache_bin = '') {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Build unique cache id.
    $cid = self::preprocessCacheKey($cache_id, $cache_bin);

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Replace data if exists.
    $result = FALSE;
    if ($memcache instanceof Memcache) {
      // Get compression mode.
      $compressed = variable_get('memcache_storage_compress_data', 0);
      $result = @$memcache->replace($cid, $data, $compressed, $expire);
    }
    elseif ($memcache instanceof Memcached) {
      $result = @$memcache->replace($cid, $data, $expire);
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
  public static function delete($cache_id, $cache_bin = '') {

    // Get memcache object.
    $memcache = self::openConnection($cache_bin);

    // No memcache connection.
    if (empty($memcache)) {
      return FALSE;
    }

    // Build unique cache id.
    $cid = self::preprocessCacheKey($cache_id, $cache_bin);

    // Run initial debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::initialDebugActions();
    }

    // Delete cached data from memcached.
    $result = @$memcache->delete($cid);

    // Run final debug actions.
    if (variable_get('memcache_storage_debug', FALSE)) {
      self::finalDebugActions('delete', $cache_bin, $cache_id, $cid, $result);
    }

    return $result;
  }

  /**
   * Immediately invalidates all existing items in a selected memcached cluster.
   *
   * @param $cluster_name
   *   Name of memcached cluster.
   *
   * @return bool
   *   Status of operation.
   */
  public static function flushCluster($cluster_name) {
    $memcache = self::connectToCluster($cluster_name);
    if (!$memcache) {
      return FALSE;
    }
    return @$memcache->flush();
  }

  /**
   * Immediately invalidates all existing items in all memcached clusters.
   */
  static public function flushClusters() {

    $servers = variable_get('memcache_servers', array('127.0.0.1:11211' => 'default'));
    $clusters = array();
    foreach ($servers as $cluster_name) {
      if (!in_array($cluster_name, $clusters)) {
        $clusters[] = $cluster_name;
      }
    }

    foreach ($clusters as $cluster_name) {
      self::flushCluster($cluster_name);
    }
  }

  /**
   * Adds memcached key prefix and ensures that key is safe.
   *
   * @param $cache_id
   *   Cache ID.
   *
   * @param $cache_bin
   *   Name of cache bin.
   *
   * @return string
   *   Unique cache key.
   */
  protected static function preprocessCacheKey($cache_id, $cache_bin) {

    // Get key prefix from settings.php.
    $key_prefix = variable_get('memcache_storage_key_prefix', '');

    // Build unique cache key.
    $cache_key  = $key_prefix ? $key_prefix . '-' : '';
    $cache_key .= $cache_bin ? $cache_bin . '-' : '';
    $cache_key .= $cache_id;

    // Add urlencode to avoid problems with different protocols.
    // If cache bin is 'cache_page' it means that we use external page cache.
    // Otherwise cache bin name is 'cache_page_[INDEX]'. We don't need to
    // encode url for external page cache because external servers may not be able
    // to urldecode this.
    $safe_key = $cache_bin == 'cache_page' ? $cache_key : urlencode($cache_key);

    // Memcache only supports key length up to 250 bytes. If we have generated
    // a longer key, hash it with md5 which will shrink the key down to 32 bytes
    // while still keeping it unique.
    if (strlen($safe_key) > 250) {
      $safe_key = md5($safe_key);
    }

    return $safe_key;
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
    //   'cache_bootstrap' => 'default',
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
    $mem_usage = &drupal_static('memcache_storage_debug_mem_usage', array());

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
    $mem_usage = &drupal_static('memcache_storage_debug_mem_usage', array());
    $used_memory = memory_get_usage() - $mem_usage[self::$debug_key];

    // Preprocess cache bin name (remove suffix _[INDEX] if exists).
    // A little bit creepy, but this is a debug output, and we can do it here.
    $cache_bin_suffix = substr($cache_bin, strrpos($cache_bin, '_') + 1);
    $cache_bin_original = $cache_bin;
    if (ctype_digit($cache_bin_suffix)) {
      $cache_bin_original = substr($cache_bin, 0, strrpos($cache_bin, '_'));
    }

    // Get array with debug data.
    $memcache_storage_debug_output = &drupal_static('memcache_storage_debug_output');

    if (is_string($cache_id)) {
      $cache_id = array($cache_id);
    }

    // Log entries about memcache action.
    foreach ($cache_id as $cid) {

      $unique_class = str_replace(array(' ','_', '/', '[', ']', ':'), '-', $cache_bin . '-' . $cid);
      $clear_link = array(
        '#theme' => 'link',
        '#text' => 'Delete',
        '#path' =>  'memcache_storage/delete/nojs/' . $cache_bin . '/' . $cid,
        '#options' => array(
          'attributes' => array('class' => array('use-ajax', $unique_class)),
          'html' => FALSE,
        ),
      );

      // Get result string (HIT or MISS).
      if (is_array($result)) {
        $result_string = isset($result[$cid]) ? 'HIT' : 'MISS';
      }
      else {
        $result_string = $result ? 'HIT' : 'MISS';
      }

      $memcache_storage_debug_output[] = array(
        'action' => count($cache_id) > 1 ? $method . 'Multiple' : $method,
        'timer' => timer_read(self::$debug_key),
        'memory' => $used_memory,
        'result' => $result_string,
        'bin' => $cache_bin_original,
        'cid' => $cid,
        'mem_key' => is_array($memcache_id) ? array_search($cid, $memcache_id) : $memcache_id,
        'clear_link' => $cid != 'memcache_storage_bin_indexes' ? $clear_link : '',
        'token' => $cache_bin . '-' . $cid,
      );
    }

    // Increase timer to get new time results.
    self::$debug_key++;
  }

}
