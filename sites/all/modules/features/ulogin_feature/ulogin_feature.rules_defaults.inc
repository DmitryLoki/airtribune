<?php
/**
 * @file
 * ulogin_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ulogin_feature_default_rules_configuration() {
  $items = array();
  $items['rules_on_empty_profile'] = entity_import('rules_config', '{ "rules_on_empty_profile" : {
      "LABEL" : "Redirect to main profile if name not filled",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_login" ],
      "IF" : [
        { "data_is_empty" : { "data" : [ "account:profile-main:field-full-name" ] } }
      ],
      "DO" : [
        { "drupal_message" : { "message" : "Please enter your first, last name and birthday." } },
        { "redirect" : { "url" : "profile-main\\/[account:uid]\\/edit" } }
      ]
    }
  }');
  return $items;
}
