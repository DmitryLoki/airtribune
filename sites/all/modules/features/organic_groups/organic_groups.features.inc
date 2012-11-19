<?php
/**
 * @file
 * organic_groups.features.inc
 */

/**
 * Implements hook_default_og_membership_type().
 */
function organic_groups_default_og_membership_type() {
  $items = array();
  $items['competitor'] = entity_import('og_membership_type', '{
    "name" : "competitor",
    "description" : "Competitor",
    "language" : "",
    "rdf_mapping" : []
  }');
  return $items;
}
