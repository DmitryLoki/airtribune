<?php
/**
 * @file
 * validation.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function validation_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Alphanumeric';
  $rule->name = 'alphanumeric';
  $rule->field_name = 'field_paraglider_model';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z0-9]*$',
    'errors' => 0,
  );
  $rule->error_message = 'Disallowed symbols in paraglider model';
  $export['alphanumeric'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Alphanumeric 2';
  $rule->name = 'alphanumeric_2';
  $rule->field_name = 'field_insurance_policy_number';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z0-9]*$',
    'errors' => 1,
  );
  $rule->error_message = 'Disallowed symbols in insurance policy number';
  $export['alphanumeric_2'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Alphanumeric';
  $rule->name = 'alphanumeric_sponsors';
  $rule->field_name = 'field_sponsors';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z0-9-,.]*$',
    'errors' => 0,
  );
  $rule->error_message = 'Disallowed symbols in sponsors';
  $export['alphanumeric_sponsors'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'FAI license number';
  $rule->name = 'fai_license_number';
  $rule->field_name = 'field_fai_license_number';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z0-9-,.]*$',
    'errors' => 0,
  );
  $rule->error_message = 'Disallowed symbols in FAI license number';
  $export['fai_license_number'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Latin';
  $rule->name = 'latin';
  $rule->field_name = 'field_paraglider_manufacturer';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z]*$',
    'errors' => 1,
  );
  $rule->error_message = 'Non-latin symbols in paraglider manufacturer';
  $export['latin'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Name';
  $rule->name = 'name';
  $rule->field_name = 'field_person_name';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z-\' ]*$',
    'errors' => 1,
  );
  $rule->error_message = 'Illegal symbols in contact person\'s name';
  $export['name'] = $rule;

  return $export;
}
