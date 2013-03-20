<?php

/**
 * @file
 * Admin functions for geoip module.
 */

/**
 * Menu callback and form builder for admin/settings/geoip.
 */
function geoip_admin_settings() {
  $form['geoip_data_file'] = array(
    '#type' => 'textfield',
    '#title' => t('GeoIP data file location'),
    '#description' => t("The path to the GeoIP database file. If you're using the city database you'll need to provide the correct filename."),
    '#default_value' => variable_get('geoip_data_file', 'sites/all/libraries/geoip/GeoIP.dat'),
    '#after_build' => array('geoip_data_file_validate'),
  );
  $form['geoip_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('GeoIP debug mode'),
    '#description' => t('With this setting enabled, an IP may be passed in through the query string using the <kbd>geoip_debug</kbd> parameter. This should not be used on production sites.'),
    '#default_value' => variable_get('geoip_debug', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Validate that the geoip_data_file exists.
 */
function geoip_data_file_validate($form_element) {
  $file = $form_element['#value'];

  if (!file_exists($file)) {
    form_error($form_element, t('The GeoIP data file could not be located at the specified location.'));
  }
  else {
    $mtime = filemtime($file);
    if ($mtime < strtotime('1 months ago')) {
      drupal_set_message(t('The GeoIP database file is more than a month old. Download the latest <a href="@country-url">country</a> or <a href="@city-url">city</a> databases from <a href="http://maxmind.com">MaxMind.com</a>.', array('@country-url' => 'http://geolite.maxmind.com/download/geoip/database/GeoLiteCountry/GeoIP.dat.gz', '@city-url' => 'http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz', '@home-url' => 'http://www.maxmind.com/app/ip-location')), 'warning');
    }
  }

  return $form_element;
}
