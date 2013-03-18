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
  $items['rules_create_not_og_blog_alias'] = entity_import('rules_config', '{ "rules_create_not_og_blog_alias" : {
      "LABEL" : "Create Not OG blog alias",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og", "path" ],
      "ON" : [ "node_insert", "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "newsblog" : "newsblog" } }
          }
        },
        { "og_entity_is_group_content" : { "entity" : [ "node" ] } },
        { "data_is_empty" : { "data" : [ "node:og-group-ref" ] } }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "node:og-group-ref:0:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
          }
        },
        { "path_alias" : { "source" : "node\\/[node:nid]" } },
        { "path_alias" : { "source" : "node\\/[node:nid]", "alias" : "activity\\/[node:title]" } }
      ]
    }
  }');
  $items['rules_create_og_blog_alias'] = entity_import('rules_config', '{ "rules_create_og_blog_alias" : {
      "LABEL" : "Create OG blog alias",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og", "path" ],
      "ON" : [ "node_insert", "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "newsblog" : "newsblog" } }
          }
        },
        { "og_entity_is_group_content" : { "entity" : [ "node" ] } },
        { "NOT data_is_empty" : { "data" : [ "node:og-group-ref" ] } }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "node:og-group-ref:0:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
          }
        },
        { "path_alias" : { "source" : "node\\/[node:nid]" } },
        { "path_alias" : {
            "source" : "node\\/[node:nid]",
            "alias" : "[entity-fetched:title]\\/blog\\/[node:title]"
          }
        }
      ]
    }
  }');
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
  $items['rules_on_empty_profile'] = entity_import('rules_config', '{ "rules_on_empty_profile" : {
      "LABEL" : "Redirect to main profile if name not filled",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "hybridauth" ],
      "ON" : [ "user_login" ],
      "IF" : [
        { "data_is_empty" : { "data" : [ "account:profile-main:field-full-name" ] } },
        { "hybridauth_user_created_hybridauth" : { "account" : [ "account" ] } }
      ],
      "DO" : [
        { "drupal_message" : { "message" : "Your account has been created with Facebook login. Please, fill the form below." } },
        { "redirect" : { "url" : "[account:edit-url]" } }
      ]
    }
  }');
  $items['rules_pg_contestant_active'] = entity_import('rules_config', '{ "rules_pg_contestant_active" : {
      "LABEL" : "OG membership pg_contestant active",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
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
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_membership_presave" ],
      "IF" : [
        { "entity_has_field" : { "entity" : [ "og-membership" ], "field" : "field_pg_contestant_status" } },
        { "data_is" : { "data" : [ "og-membership:field-pg-contestant-status" ], "value" : "1" } }
      ],
      "DO" : [ { "data_set" : { "data" : [ "og-membership:state" ], "value" : "2" } } ]
    }
  }');
  $items['rules_redirect_to_user_edit'] = entity_import('rules_config', '{ "rules_redirect_to_user_edit" : {
      "LABEL" : "Redirect from user\\/view to user\\/edit",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_view" ],
      "IF" : [
        { "data_is" : { "data" : [ "account:uid" ], "value" : [ "site:current-user:uid" ] } }
      ],
      "DO" : [ { "redirect" : { "url" : "[account:edit-url]" } } ]
    }
  }');
  $items['rules_rules_redirect_to_pilot_edit'] = entity_import('rules_config', '{ "rules_rules_redirect_to_pilot_edit" : {
      "LABEL" : "Redirect from profile-pilot\\/view to profile-pilot\\/edit",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "profile2" ],
      "ON" : [ "profile2_view" ],
      "IF" : [
        { "data_is" : { "data" : [ "profile2:type:type" ], "value" : "pilot" } }
      ],
      "DO" : [ { "redirect" : { "url" : "user\\/[profile2:user:uid]\\/pilot" } } ]
    }
  }');
  return $items;
}
