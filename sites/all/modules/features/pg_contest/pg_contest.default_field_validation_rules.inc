<?php
/**
 * @file
 * pg_contest.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function pg_contest_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Unique prize category';
  $rule->name = 'unique_prize_category';
  $rule->field_name = 'field_awards_photos';
  $rule->col = 'title';
  $rule->entity_type = 'node';
  $rule->bundle = 'pg_contest';
  $rule->validator = 'airtribune_unique_values_validator';
  $rule->settings = array(
    'data' => 'airtribune',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      3 => 0,
      6 => 0,
      5 => 0,
      4 => 0,
      7 => 0,
    ),
    'errors' => 0,
  );
  $rule->error_message = 'You can add only one picture per prize category. [value] has already got a picture.';
  $export['unique_prize_category'] = $rule;

  return $export;
}
