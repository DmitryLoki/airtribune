<?php
/**
 * @file
 * device.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function device_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Unique value';
  $rule->name = 'unique_value';
  $rule->field_name = 'field_device_id';
  $rule->col = 'value';
  $rule->entity_type = 'ent_tracker';
  $rule->bundle = 'device';
  $rule->validator = 'field_validation_unique_validator';
  $rule->settings = array(
    'data' => 'entity',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      3 => 0,
      6 => 0,
      5 => 0,
      7 => 0,
    ),
    'errors' => 1,
  );
  $rule->error_message = '[field-name] must have a unique value.';
  $export['unique_value'] = $rule;

  return $export;
}
