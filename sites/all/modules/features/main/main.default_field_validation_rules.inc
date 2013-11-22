<?php
/**
 * @file
 * main.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function main_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'family_english';
  $rule->name = 'family_english';
  $rule->field_name = 'field_full_name';
  $rule->col = 'family';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'main';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z\' \'-]*$',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      3 => 0,
      6 => 0,
      5 => 0,
      7 => 0,
    ),
    'errors' => 0,
  );
  $rule->error_message = 'Last name: English text only';
  $export['family_english'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'given_english';
  $rule->name = 'given_english';
  $rule->field_name = 'field_full_name';
  $rule->col = 'given';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'main';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z\' \'-]*$',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      3 => 0,
      6 => 0,
      5 => 0,
      7 => 0,
    ),
    'errors' => 0,
  );
  $rule->error_message = 'First name: English text only';
  $export['given_english'] = $rule;

  return $export;
}
