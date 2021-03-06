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
  $items['hg_contestant'] = entity_import('og_membership_type', '{
    "name" : "hg_contestant",
    "description" : "Hang Gliding Contestant",
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
  $items['pg_winddummy'] = entity_import('og_membership_type', '{
    "name" : "pg_winddummy",
    "description" : "Paragliding Wind Dummy",
    "language" : "",
    "rdf_mapping" : []
  }');
  $items['tracked_object'] = entity_import('og_membership_type', '{
    "name" : "tracked_object",
    "description" : "Tracked object",
    "language" : "",
    "rdf_mapping" : []
  }');
  return $items;
}
