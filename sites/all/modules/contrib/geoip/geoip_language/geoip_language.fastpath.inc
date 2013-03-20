<?php

/**
 * @file
 * description
 */

/**
 * Some sort of caching.
 */
function page_cache_fastpath() {
  $file = variable_get('file_directory_path', conf_path() . '/files') . '/geoip_language.txt';
  if (file_exists($file)) {
    $data = unserialize(file_get_contents($file));
    $mapping = isset($data['geoip']) ? $data['geoip'] : NULL;
  }
  else {
    return FALSE;
  }

  $args = explode('/', $_GET['q']);
  $prefix = $args[0];
  if (!in_array($prefix, $mapping)) {
    global $base_path;

    // no language prefix; geoip detect, then redirect.
    include_once dirname(dirname(__FILE__)) . '/geoip.module';
    $country = geoip_country_code();
    $prefix = ($country && isset($mapping[$country])) ? $mapping[$country] : $data['default'];
    header('Location: ' . $base_path . $prefix . '/' . $_GET['q']);
    exit();
  }

  return FALSE;
}
