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
  $items['og_transport'] = entity_import('og_membership_type', '{
    "name" : "og_transport",
    "description" : "Transport",
    "language" : "",
    "rdf_mapping" : []
  }');
  $items['pg_contestant'] = entity_import('og_membership_type', '{
    "name" : "pg_contestant",
    "description" : "Paragliding Contestant",
    "language" : "",
    "rdf_mapping" : []
  }');
  $items['pg_organizer'] = entity_import('og_membership_type', '{
    "name" : "pg_organizer",
    "description" : "Paragliding Organizer",
    "language" : "",
    "rdf_mapping" : []
  }');
  return $items;
}
