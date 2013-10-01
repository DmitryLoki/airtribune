<?php
/**
 * @file
 * service_header.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function service_header_eck_bundle_info() {
  $items = array(
  'ent_featured_header_service_header' => array(
  'machine_name' => 'ent_featured_header_service_header',
  'entity_type' => 'ent_featured_header',
  'name' => 'service_header',
  'label' => 'Service header',
),
  );
  return $items;
}
