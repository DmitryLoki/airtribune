<?php
/**
 * @file
 * pg_race.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pg_race_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__pg_race';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'path' => array(
          'weight' => '6',
        ),
        'language' => array(
          'weight' => '4',
        ),
        'title' => array(
          'weight' => '-5',
        ),
        'metatags' => array(
          'weight' => '10',
        ),
        'xmlsitemap' => array(
          'weight' => '5',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__pg_race'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_pg_race';
  $strongarm->value = '4';
  $export['language_content_type_pg_race'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_pg_race';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_pg_race'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_pg_race';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_pg_race'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_pg_race';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_pg_race'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_pg_race';
  $strongarm->value = '1';
  $export['node_preview_pg_race'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_pg_race';
  $strongarm->value = 0;
  $export['node_submitted_pg_race'] = $strongarm;

  return $export;
}
