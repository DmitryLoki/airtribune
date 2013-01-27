<?php
/**
 * @file
 * ent_featured_header.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_featured_header_eck_entity_type_info() {
$items = array(
       'ent_featured_header' => array(
  'name' => 'ent_featured_header',
  'label' => 'Featured header',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
