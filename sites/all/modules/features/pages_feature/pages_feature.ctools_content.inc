<?php
/**
 * @file
 * pages_feature.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function pages_feature_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'coming_soon';
  $content->admin_title = 'Coming soon';
  $content->admin_description = 'Coming soon';
  $content->category = '';
  $content->settings = array(
    'admin_title' => 'Coming soon',
    'title' => '',
    'body' => 'Coming soon',
    'format' => 'filtered_html',
    'substitute' => 1,
  );
  $export['coming_soon'] = $content;

  return $export;
}
