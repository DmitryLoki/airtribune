<?php
/**
 * @file
 * featured_header.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function featured_header_eck_bundle_info() {
  $items = array(
  'ent_featured_header_ent_featured_header' => array(
  'machine_name' => 'ent_featured_header_ent_featured_header',
  'entity_type' => 'ent_featured_header',
  'name' => 'ent_featured_header',
  'label' => 'Featured header',
),
  );
  return $items;
}
