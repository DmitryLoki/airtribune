<?php
/**
 * @file
 * seo.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function seo_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "path_breadcrumbs" && $api == "path_breadcrumbs") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
