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
  $items['rules_pg_contestant_active'] = entity_import('rules_config', '{ "rules_pg_contestant_active" : {
      "LABEL" : "OG membership pg_contestant active",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_membership_presave" ],
      "IF" : [
        { "entity_has_field" : { "entity" : [ "og-membership" ], "field" : "field_pg_contestant_status" } },
        { "OR" : [
            { "data_is" : { "data" : [ "og-membership:field-pg-contestant-status" ], "value" : "2" } },
            { "data_is" : { "data" : [ "og-membership:field-pg-contestant-status" ], "value" : "3" } },
            { "data_is" : { "data" : [ "og-membership:field-pg-contestant-status" ], "value" : "4" } }
          ]
        }
      ],
      "DO" : [ { "data_set" : { "data" : [ "og-membership:state" ], "value" : "1" } } ]
    }
  }');
  $items['rules_pg_contestant_pending'] = entity_import('rules_config', '{ "rules_pg_contestant_pending" : {
      "LABEL" : "OG membership pg_contestant pending",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_membership_presave" ],
      "IF" : [
        { "entity_has_field" : { "entity" : [ "og-membership" ], "field" : "field_pg_contestant_status" } },
        { "data_is" : { "data" : [ "og-membership:field-pg-contestant-status" ], "value" : "1" } }
      ],
      "DO" : [ { "data_set" : { "data" : [ "og-membership:state" ], "value" : "2" } } ]
    }
  }');
  return $items;
}
