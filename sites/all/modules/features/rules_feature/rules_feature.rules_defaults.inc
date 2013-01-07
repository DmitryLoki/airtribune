<?php
/**
 * @file
 * rules_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rules_feature_default_rules_configuration() {
  $items = array();
  $items['rules_og_pilot_subscribe'] = entity_import('rules_config', '{ "rules_og_pilot_subscribe" : {
      "LABEL" : "OG pilot subscribe",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_insert" ],
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:type" ], "value" : "pg_contestant" } },
        { "user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "2" : "2" } } } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } }
      ]
    }
  }');
  return $items;
}
