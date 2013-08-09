<?php

/**
 * @file
 *  Airtribune module drush integration.
 * 
 * @author Chivse
 */

/**
 * Implements hook_drush_command().
 */
function airtribune_drush_command() {
  $items['airtribune-set-environment'] = array(
    'description' => 'Set airtribuntate',
    'aliases' => array('ase'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function airtribune_drush_help($section) {
  switch ($section) {
    case 'drush:airtribune-set-environment':
      return dt('TODO Add help text here.');
  }
}

/**
 * Command callback: Set airtribune deployment state.
 */
function drush_airtribune_set_environment($site_state = FALSE) {

  if ($site_state && $site_state != 'production' && $site_state != 'development') {
    drush_set_error('Invalid site state value!');
    $site_state = FALSE;
  }

  if (!$site_state) {
    $site_state = drush_choice(
      array('production' => 'Production', 'development' => 'Development'),
      'Select site state:'
    );
    // Canceled.
    if (!$site_state) {
      return;
    }
  }

  // These operations take up a lot of memory.
  //ini_set('memory_limit', '256M');

  $previous_state = $site_state == 'production' ? 'development' : 'production';
  drush_print("Now we will put airtribune to $site_state state...");
  sleep(1);

  drush_include_engine('drupal', 'environment');
  // Needed because _drupal_install_module().
  require_once DRUSH_DRUPAL_CORE . '/includes/install.inc';
  $step = 0;

  $step++;
  drush_print("\n$step. Disable $previous_state modules...");
  sleep(1);
  call_user_func_array('drush_pm_disable', airtribune_get_modules($previous_state));

  $step++;
  drush_print("\n$step. Enable $site_state modules...");
  sleep(1);
  drush_set_context('PM_ENABLE_MODULES', airtribune_get_modules($site_state));
  drush_pm_enable();

  $step++;
  drush_print("\n$step. Set drupal variables to $site_state state...");
  sleep(1);
  foreach (airtribune_get_variables($site_state) as $variable_name => $variable_value) {
    drush_print("   $variable_name = $variable_value");
    variable_set($variable_name, $variable_value);
  }

  //$step++;
  //drush_print("\n$step. Change logo in garland theme...");
  //sleep(1);
  //$garland_settings = variable_get('theme_garland_settings', FALSE);
  //if (isset($garland_settings['logo_path'])) {
  //  $garland_settings['logo_path'] = drupal_get_path('module', 'airtribune') . "/logo-$site_state.png";
  //  variable_set('theme_garland_settings', $garland_settings);
  //};

  //$step++;
  //drush_print("\n$step. Clear dblog messages...");
  //sleep(1);
  //db_query('DELETE FROM {watchdog}');

  $step++;
  drush_print("\n$step. Invoke \"hook_airtribune_set_environment\"...");
  sleep(1);
  module_invoke_all('airtribune_set_environment', $site_state);

  $step++;
  drush_print("\n$step. Run all cron hooks...");
  sleep(1);
  drush_core_cron();

  $step++;
  drush_print("\n$step. Flush all caches...");
  sleep(1);
  drupal_flush_all_caches();

  if ($site_state == 'development') {
    $step++;
    drush_print("\n$step. Reset admin password...");
    sleep(1);
    db_update('users')
      ->fields(array('pass' => "\$S\$D.PGNZ40LDzKdblKp2E3j/rXtarzEgcKG7FdQ4mkaZIX5DVSjuK2"))
      ->condition('uid', 1)
      ->execute();
  }

  // Finish.
  echo "\n";
  watchdog('airtribune', "Site moved to $site_state state", array(), WATCHDOG_NOTICE, l('View status report', 'admin/reports/status'));
}

/**
 * List of modules which should be enabled or disabled.
 */
function airtribune_get_modules($site_state) {
  $modules = array(
    'production' => array(
      //'googleanalytics',
      'syslog',
      'xmlsitemap',
      'xmlsitemap_engines',
      'xmlsitemap_node',
      'xmlsitemap_user',
      'xmlsitemap_custom',
    ),
    'development' => array(
      'coder',
      'devel',
      'devel_generate',
      'devel_node_access',
      'location_generate',
      'dblog',
      'update',
      'rules_ui',
      'views_ui',
      'field_validation_ui',
    ),
  );
  return $modules[$site_state];
}

/**
 * List of processed variables.
 */
function airtribune_get_variables($site_state) {
  $variables =  array(
    'production' => array (
      'cache' => CACHE_NORMAL,
      'preprocess_js' => 1,
      'preprocess_css' => 1,
      'error_level' => 0,
      //'smtp_library' => drupal_get_filename('module', 'mimemail'),
      'at_core_sync_address' => 'http://api.airtribune.com',
      'at_core_sync_version' => 'v0.2',
      'file_temporary_path' => '/home/airtribune/data/mod-tmp'
    ),
    'development' => array (
      'cache' => CACHE_DISABLED,
      'preprocess_js' => 0,
      'preprocess_css' =>  0,
      'error_level' => 1,
      //'smtp_library' => drupal_get_filename('module', 'devel'),
      'at_core_sync_address' => 'http://apidev.airtribune.com',
      'at_core_sync_version' => 'v0.1.4',
      'file_temporary_path' => '/home/devtribune/data/mod-tmp',
    ),
  );
  return $variables[$site_state];
}
