<?php

/**
 * @file
 * Administrative settings for Memcache Storage module.
 */

/**
 * Settings form.
 */
function memcache_storage_settings_form($form, &$form_state) {

  $form['cache'] = array(
    '#type' => 'vertical_tabs',
  );

  // Flush all cache.
  $form['cache']['all'] = array(
    '#type' => 'fieldset',
    '#title' => t('Clear all caches'),
  );

  $form['cache']['all']['warning'] = array(
    '#type' => 'item',
    '#markup' => '<span style="color:red;">' . t('All data stored in memcached pool will be flushed permanently.') . '</span>',
  );

  $form['cache']['all']['flush_all_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Clear all caches'),
    '#submit' => array('memcache_storage_flush_all_cache'),
  );

  // Flush selected clusters.
  $form['cache']['clusters_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flush selected clusters'),
    '#tree' => TRUE,
  );

  // Get list of cluster names.
  $clusters = array();
  $servers = variable_get('memcache_servers', array('127.0.0.1:11211' => 'default'));
  foreach ($servers as $server => $cluster_name) {
    $clusters[$cluster_name][] = $server;
  }

  $form['cache']['clusters_list']['title'] = array(
    '#type' => 'item',
    '#title' => t('Select memcached clusters'),
  );

  foreach ($clusters as $cluster_name => $cluster_servers) {
    $form['cache']['clusters_list'][$cluster_name] = array(
      '#type' => 'checkbox',
      '#title' => $cluster_name,
      '#description' => theme('item_list', array('items' => $cluster_servers)),
    );
  }

  if (empty($clusters)) {
    $form['cache']['clusters_list']['empty_text'] = array(
      '#type' => 'markup',
      '#markup' => t('No memcached clusters specified in settings.php'),
    );
  }
  else {
    $form['cache']['clusters_list']['flush_selected_clusters'] = array(
      '#type' => 'submit',
      '#value' => t('Flush selected clusters'),
      '#submit' => array('memcache_storage_admin_flush_selected_clusters'),
      '#limit_validation_errors' => array(array('clusters_list')),
    );
  }

  // Flush cache in a selected bins.
  $form['cache']['bins_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flush selected cache bins'),
  );

  // Load all cache bins available for flushing.
  $available_bins = array();
  $schema = drupal_get_complete_schema();
  foreach ($schema as $table_name => $table_data) {
    if (strpos($table_name, 'cache') === 0) {
      $available_bins[$table_name] = $table_name;
    }
  }
  ksort($available_bins);

  // We can't flush cached pages if enabled external page cache.
  // Otherwise it will change memcache key prefix and external server won't find cached pages.
  $external_page_cache = variable_get('memcache_storage_external_page_cache', FALSE);
  if ($external_page_cache) {
    unset($available_bins['cache_page']);
  }

  $form['cache']['bins_list']['bins'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select cache bins'),
    '#options' => $available_bins,
    '#description' => t('All selected cache bins will be flushed permanently.'),
  );

  $form['cache']['bins_list']['flush_selected_bins'] = array(
    '#type' => 'submit',
    '#value' => t('Flush selected cache bins'),
    '#submit' => array('memcache_storage_admin_flush_selected_bins'),
    '#limit_validation_errors' => array(array('bins')),
  );

  return $form;
}

/**
 * Flush cached data from selected bins.
 */
function memcache_storage_admin_flush_selected_bins($form, &$form_state) {
  $selected_bins = array_filter($form_state['values']['bins']);

  if (empty($selected_bins)) {
    drupal_set_message(t('No cache bins were selected.'), 'warning');
  }

  foreach ($selected_bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
    drupal_set_message(t('%bin bin was successfully flushed.', array('%bin' => check_plain($bin))));
  }
}

/**
 * Flush selected memcached clusters.
 */
function memcache_storage_admin_flush_selected_clusters($form, &$form_state) {
  $selected_clusters = array_filter($form_state['values']['clusters_list']);
  unset($selected_clusters['flush_selected_clusters']); // Remove button from clusters list.

  if (empty($selected_clusters)) {
    drupal_set_message(t('No memcached clusters were selected.'), 'warning');
  }

  foreach ($selected_clusters as $cluster_name => $value) {
    $flushed = MemcacheStorageAPI::flushCluster($cluster_name);
    if ($flushed) {
      drupal_set_message(t('%cluster cluster was successfully flushed.', array('%cluster' => $cluster_name)));
    }
    else {
      drupal_set_message(t('Could not flush %cluster cluster.', array('%cluster' => $cluster_name)), 'warning');
    }
  }
}
