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
    '#type' => 'fieldset',
    '#title' => t('Cache actions'),
  );

  // Flush all cache.
  $form['cache']['basic'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Flush all caches'),
  );

  $form['cache']['basic']['warning'] = array(
    '#type' => 'item',
    '#markup' => '<span style="color:red;">' . t('All data stored in memcache will be cleared.') . '</span>',
  );

  $form['cache']['basic']['flush_all_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Flush all memcache data'),
    '#submit' => array('memcache_storage_flush_all_cache'),
  );

  // Flush cache in a selected bins.
  $form['cache']['advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Flush selected bins'),
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

  $form['cache']['advanced']['bins'] = array(
    '#type' => 'checkboxes',
    '#multiple' => TRUE,
    '#title' => t('Select cache bins'),
    '#description' => t('Cache will be flushed only from selected bins.'),
    '#options' => $available_bins,
  );

  $form['cache']['advanced']['flush_selected_bins'] = array(
    '#type' => 'submit',
    '#value' => t('Flush selected'),
    '#submit' => array('memcache_storage_admin_flush_selected_bins'),
  );

  return $form;
}

/**
 * Flush cached data from selected bins.
 */
function memcache_storage_admin_flush_selected_bins($form, &$form_state) {
  $selected_bins = array_filter($form_state['values']['bins']);

  if (empty($selected_bins)) {
    drupal_set_message(t('No bins were selected.'), 'warning');
  }

  foreach ($selected_bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
    drupal_set_message(t('Bin %bin was successfully cleared.', array('%bin' => check_plain($bin))));
  }
}
