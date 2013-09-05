==================
## REQUIREMENTS ##
==================

- Availability of a memcached daemon: http://memcached.org/
- PECL memcache package: http://pecl.php.net/package/memcache (version 2.2.1 or greater).
  OR PECL memcached package: http://pecl.php.net/package/memcached (version 2.0.1 or greater).


==================
## INSTALLATION ##
==================

These are the broad steps you need to take in order to use this software. ORDER IS IMPORTANT!

 1. Install the memcached binaries on your server and start the memcached
    service. See for instance: http://www.lullabot.com/articles/how_install_memcache_debian_etch

 2. Install your chosen PECL memcache extension -- this is the memcache client
    library which will be used by the Drupal memcache module to interact with
    the memcached server(s). Generally PECL memcached (2.0.1+) is recommended,
    but PECL memcache (2.2.1+) also works well for some people. Use of older
    versions may cause problems.

 3. Start at least one instance of memcached on your server.

 4. Download and extract Memcache Storage module into sites/all/modules directory.

 5. Install the Memcache Storage module as usual.

 6. Put your site into offline mode.

 7. Edit settings.php to configure Memcache Storage module (see ## CONFIGURATIONS ## section).

 8. Go to Status report page (/admin/reports/status) to check Memcache Storage status.

 9. Bring your site back online.


====================
## CONFIGURATIONS ##
====================

Note: all module settings should be changed only in settings.php.


1. QUICK CONFIGURATION

To add memcached support for your site you should simply add following settings at the bottom of settings.php:

..
$conf['cache_backends'][] = 'sites/all/modules/memcache_storage/memcache_storage.inc';
$conf['cache_default_class'] = 'MemcacheStorage';
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
..


2. ADVANCED CONFIGURATION

Memcache Storage module provides some additional settings for advanced users.


2.1. DEBUG MODE.

To enable the debug mode you can by setting 'memcache_storage_debug' to TRUE:

..
$conf['memcache_storage_debug'] = TRUE;
..

Default: FALSE

At the bottom of each page will be displayed all stats about memcached operations.


2.2. KEY PREFIX.

Add custom prefix to every memcache key.
You may need this if you are using one memcached instance for different sites.

..
$conf['memcache_storage_key_prefix'] = 'some_key';
..

Default: ''

Note that after changing this setting all cache stored in memcached pool will be flushed.


2.3. COMPRESSION MODE (ONLY FOR MEMCACHE EXTENSION)

You may set compress mode for all data stored in memcached pool.

..
$conf['memcache_storage_compress_data'] = 0;
..

Default: 0
Available values: 0 or 2 (MEMCACHE_COMPRESSED)
See: http://www.php.net/manual/en/memcache.set.php

Enabling compress might slightly decrease performance but reduce amount of used by memcache memory.


2.4. COMPRESSION FOR BIG VALUES (ONLY FOR MEMCACHE EXTENSION)

Compress Threshold enables automatic compression of large values.

..
$conf['memcache_storage_compress_threshold'] = array(
  'threshold' => 20000,
  'min_savings' => 0.2,
);
..

Default: array('threshold' => 20000, 'min_savings' => 0.2)
See: http://www.php.net/manual/en/memcache.setcompressthreshold.php


2.5. WILDCARDS INVALIDATION.

Memcache is not allowed to flush data using wildcards so we have to store all wildcards and its creation time in variables.
This value allows to flush wildcards after some time when they might be expired to avoid collecting big wildcards arrays.

..
$conf['memcache_storage_wildcard_invalidate'] = 60 * 60 * 24 * 30;  // 30 days.
..

Default: 60 * 60 * 24 * 30 // 30 days.


2.6. MULTIPLE SERVERS SUPPORT.

The available memcached servers are specified in $conf in settings.php. If
you do not specify any servers, memcache.inc assumes that you have a
memcached instance running on localhost:11211. If this is true, and it is
the only memcached instance you wish to use, no further configuration is
required.

If you have more than one memcached instance running, you need to add two
arrays to $conf: memcache_servers and memcache_bins. The arrays follow this
pattern:

..
$conf['memcache_servers'] => array(
  'host1:port1' => 'default',
  'host2:port2' => 'cluster_name2',
  'host3:port3' => 'cluster_name3',
);

$conf['memcache_bins'] = array(
  'cache'           => 'default',
  'cache_page'      => 'cluster_name2',
  'cache_bootstrap' => 'cluster_name3',
);
..

The bin/cluster/server model can be described as follows:

- Servers are memcached instances identified by host:port.

- Bins are groups of data that get cached together and map 1:1 to the $table
  parameter of cache_set(). Examples from Drupal core are cache_filter,
  cache_menu. The default is 'cache'.

- Clusters are groups of servers that act as a memory pool.

- Many bins can be assigned to a cluster.

- The default cluster is 'default'.

Here is a simple setup that has two memcached instances, both running on
localhost. The 11212 instance belongs to the 'pages' cluster and the table
cache_page is mapped to the 'pages' cluster. Thus everything that gets cached,
with the exception of the page cache (cache_page), will be put into 'default',
or the 11211 instance. The page cache will be stored in 123.1.3.4:11212.

..
$conf['memcache_servers'] => array(
  '127.0.0.1:11211' => 'default',
  '127.0.0.1:12211' => 'default',
  '123.1.3.4:11211' => 'pages',
);

$conf['memcache_bins'] = array(
  'cache'      => 'default',
  'cache_page' => 'pages',
);
..

Also you may use unix sockets as a host. See example:

..
$conf['memcache_servers'] = array(
  'unix:///path/to/memcached.socket1' => 'default',
  'unix:///path/to/memcached.socket2' => 'bootstrap',
  'unix:///path/to/memcached.socket3' => 'field',
  'unix:///path/to/memcached.socket4' => 'menu',
  'unix:///path/to/memcached.socket5' => 'page',
  'unix:///path/to/memcached.socket6' => 'path',
);

$conf['memcache_bins'] = array(
  'cache'            => 'default',
  'cache_bootstrap'  => 'bootstrap',
  'cache_field'      => 'field',
  'cache_menu'       => 'menu',
  'cache_page'       => 'page',
  'cache_path'       => 'path',
);
..

See: http://drupal.org/node/1181968

All cache bins not matched in the $conf['memcache_bins'] will use 'default' server.


2.7. CUSTOM PAGE CACHE EXPIRATION

If you want to configure expiration of cached pages separately from other cache bins, you may use following settings:

..
$conf['memcache_storage_page_cache_custom_expiration'] = TRUE;
$conf['memcache_storage_page_cache_expire'] = 60 * 60 * 24;  // 1 day.
..

In this case page cache won't be flushed automatically. It will expire only after one day.

Here you may use cool trick that will greatly reduce server load. See next config:

..
$conf['memcache_storage_page_cache_custom_expiration'] = TRUE;
$conf['memcache_storage_page_cache_expire'] = 0;  // NEVER EXPIRE.
..

In this case page cache will NEVER expire (until memcached daemon is rebooted, or cache was rewriten because of lack of the memory).
But you have to expire cached pages anyway. What could you do? Answer is simple: enable Memcache Storage Page Cache module!
This module allows you to configure custom actions for page cache expiration.
The idea of this module is simple: No need to expire cached page, if it was not updated.
You may configure custom actions that will expire page cache only for pages where content is REALLY UPDATED!


2.8. LOCKING

The memcache-lock.inc file included with this module can be used as a drop-in
replacement for the database-mediated locking mechanism provided by Drupal
core. To enable, define the following in your settings.php:

..
$conf['lock_inc'] = 'sites/all/modules/memcache_storage/includes/lock.inc';
..

Locks are written in the 'semaphore' table, which will map to the 'default'
memcache cluster unless you explicitly configure a 'semaphore' cluster.

Read more about locking mechanism here http://api.drupal.org/api/drupal/includes!lock.inc/group/lock/7.


2.9. PREFERRED EXTENSION

As Memcache Storage supports both PECL memcache and PECL memcached extensions,
you may choose which extension to use. But this requires only when both extenstions are enabled on a server.

..
$conf['memcache_extension'] = 'Memcached';
..

default: 'Memcache';


2.10. CONFIGURE PECL MEMCACHED EXTENSION

NOTE: It is important to realize that the memcached php.ini options do not impact
the memcached extension, this new extension doesn't read in options that way.
Instead, it takes options directly from Drupal. Because of this, you must
configure memcached in settings.php. Please look here for possible options:

http://www.php.net/manual/en/memcached.constants.php

An example configuration block is below, this block also illustrates our
default options. These will be set unless overridden in settings.php.

..
$conf['memcache_options'] = array(
  Memcached::OPT_COMPRESSION => FALSE,
  Memcached::OPT_DISTRIBUTION => Memcached::DISTRIBUTION_CONSISTENT,
);
..

These are as follows:

 * Turn off compression, as this takes more CPU cycles than its worth for most users
 * Turn on consistent distribution, which allows you to add/remove servers easily

If you are using memcached 1.4 or above, you could enable the binary protocol,
which is more advanced and faster, by adding the following to settings.php:

..
$conf['memcache_options'] = array(
  Memcached::OPT_BINARY_PROTOCOL => TRUE,
);
..

If you experience slower performance when using the binary protocol, consider
enabling tcp no-delay mode as well:

..
$conf['memcache_options'] = array(
  Memcached::OPT_TCP_NODELAY => TRUE,
  Memcached::OPT_BINARY_PROTOCOL => TRUE,
);
..


2.11. PERSISTENT CONNECTION

PHP may open persistent connection to memcached daemon.

..
$conf['memcache_storage_persistent_connection'] = TRUE;
..

Default: FALSE


2.12. SESSIONS SUPPORT

Memcache Storage allows you to store all session data in memory.
It helps database to reduce amount of queries.

..
$conf['session_inc'] = 'sites/all/modules/memcache_storage/includes/session.inc';
..

Read more about sessions here http://api.drupal.org/api/drupal/includes!session.inc/7

2.13. INTEGRATION WITH NGINX

Since 7.x-1.1 Memcache Storage supports integration with servers that may read cached pages
directly from memcached pool. It stores a plain HTML text instead of object. This allows
server to read this HTML and serve it to user, without passing request to the backend.
It is very cool performance improvement because it may handle a REALLY LOT of anonymous
reqests per second.

To enable this feature you have to add this lines to your settings.php file:

..
# Advanced usage of Drupal page cache.
$conf['cache_backends'][] = 'sites/all/modules/memcache_storage/memcache_storage.page_cache.inc';
$conf['cache_class_cache_page'] = 'MemcacheStoragePageCache';

# Enable storing of plain HTML text instead of Drupal usual cache object.
$conf['memcache_storage_external_page_cache'] = TRUE;
..

Part of Nginx config that you will need to implement:

..
  # Set content type for the rest requests.
  default_type text/html;

  # Trying to find page cache in memcached pool.
  add_header X-Nginx-Page-Cache HIT;
  set $memcached_key "[PREFIX]-cache_page-$scheme://$server_name$uri$is_args$args";
  memcached_pass unix:/var/run/memcached/memcached.socket0;

  proxy_intercept_errors on;
  error_page 404 502 = @drupal;
..

If you didn't define $conf['memcache_storage_key_prefix'] $memcache_key will look like that:

..
  set $memcached_key "cache_page-$scheme://$server_name$uri$is_args$args";
..

I promise that later I will create an article with full example of Nginx configuration.
But now I can show you only main part of it. All the rest you have to do yourself.
You may find useful this article: http://nginx.org/en/docs/http/ngx_http_memcached_module.html


====================================
## DRUSH SUPPORT ##
====================================

1. To flush ALL DATA stored in memcached print one of the following drush command:

..
drush memcache-storage-flush
drush ms-flush
..

2. To remove cache object from bin use next commands:

drush memcache-storage-clear-cache CACHE_ID CACHE_BIN

Examples:

drush memcache-storage-clear-cache panels:223  // Removes cache with ID 'panels:223' from bin 'cache'.
drush ms-cc module_implements cache_bootstrap  // Removes cache with ID 'module_implements' from bin 'cache_bootstrap'.

3. To invalidate all cache objects in some cache bin, use this command:

drush memcache-storage-flush-bin CACHE_BIN

Examples:

drush memcache-storage-flush-bin  // Flushes cache bin 'cache'.
drush ms-fb cache_bootstrap  // Flushes cache bin 'cache_bootstrap'.


====================================
## ADVANCED CONFIGARATION EXAMPLE ##
====================================

# Move all cached data (except form cache) to memcache storage.
$conf['cache_backends'][] = 'sites/all/modules/memcache_storage/memcache_storage.inc';
$conf['cache_default_class'] = 'MemcacheStorage';
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';

# Advanced usage of Drupal page cache.
$conf['cache_backends'][] = 'sites/all/modules/memcache_storage/memcache_storage.page_cache.inc';
$conf['cache_class_cache_page'] = 'MemcacheStoragePageCache';

# Do not connect to the database when serving cached page for anonymous users.
$conf['page_cache_invoke_hooks'] = FALSE;
$conf['page_cache_without_database'] = TRUE;

# Open persistent memcached connection.
$conf['memcache_storage_persistent_connection'] = TRUE;

# Configure Memcache Storage module.
$conf['memcache_storage_debug'] = TRUE;
$conf['memcache_storage_key_prefix'] = 'build-1';
$conf['memcache_storage_wildcard_invalidate'] = 60 * 60 * 24 * 5; // 5 days.

# Add multiple memcached instances.
$conf['memcache_servers'] = array(
  'unix:///var/run/memcached/memcached.socket0' => 'default',
  'unix:///var/run/memcached/memcached.socket1' => 'bootstrap',
  'unix:///var/run/memcached/memcached.socket2' => 'field',
  'unix:///var/run/memcached/memcached.socket3' => 'page',
);

# Set reference between cache bins and memcache server names.
# All other bins will be refered to the 'default' server.
$conf['memcache_bins'] = array(
  'cache_bootstrap'  => 'bootstrap',
  'cache_field'      => 'field',
  'cache_page'       => 'page',
);

# Set custom expiration for cached pages.
$conf['memcache_storage_page_cache_custom_expiration'] = TRUE;
$conf['memcache_storage_page_cache_expire'] = 60 * 60 * 24;  // 1 day.

# Set current extension.
$conf['memcache_extension'] = 'Memcached';

# Configure memcached extenstion.
$conf['memcache_options'] = array(
  Memcached::OPT_TCP_NODELAY => TRUE,
  Memcached::OPT_BINARY_PROTOCOL => TRUE,
);

# Move storage for lock system into memcached.
$conf['lock_inc'] = 'sites/all/modules/memcache_storage/includes/lock.inc';

# Move storage for sessions into memcached.
$conf['session_inc'] = 'sites/all/modules/memcache_storage/includes/session.inc';

=============
## CREDITS ##
=============

Module was designed and developed by Maslouski Yauheni (http://drupalace.ru).
Module development was not sponsored by anyone. It was created for the love of Drupal.
