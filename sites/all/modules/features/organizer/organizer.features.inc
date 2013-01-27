<?php
/**
 * @file
 * organizer.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function organizer_default_profile2_type() {
  $items = array();
  $items['organizer_profile'] = entity_import('profile2_type', '{
    "userCategory" : false,
    "userView" : false,
    "type" : "organizer_profile",
    "label" : "Organizer profile",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 1 },
    "rdf_mapping" : []
  }');
  return $items;
}
