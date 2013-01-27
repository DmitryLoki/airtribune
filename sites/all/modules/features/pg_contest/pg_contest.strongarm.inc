<?php
/**
 * @file
 * pg_contest.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pg_contest_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__pg_contest';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'language' => array(
          'weight' => '4',
        ),
        'path' => array(
          'weight' => '30',
        ),
        'metatags' => array(
          'weight' => '32',
        ),
        'xmlsitemap' => array(
          'weight' => '31',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__pg_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_pg_contest';
  $strongarm->value = '4';
  $export['language_content_type_pg_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_pg_contest';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_pg_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_pg_contest';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_pg_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_pg_contest';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_pg_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_pg_contest';
  $strongarm->value = '1';
  $export['node_preview_pg_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_pg_contest';
  $strongarm->value = 0;
  $export['node_submitted_pg_contest'] = $strongarm;

  return $export;
}
