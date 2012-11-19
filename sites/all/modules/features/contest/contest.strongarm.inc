<?php
/**
 * @file
 * contest.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function contest_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__contest';
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
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'language' => array(
          'weight' => '3',
        ),
        'path' => array(
          'weight' => '22',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_contest';
  $strongarm->value = '4';
  $export['language_content_type_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_contest';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_contest';
  $strongarm->value = '1';
  $export['node_preview_contest'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_contest';
  $strongarm->value = 0;
  $export['node_submitted_contest'] = $strongarm;

  return $export;
}
