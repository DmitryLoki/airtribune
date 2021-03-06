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
  $rule->rulename = 'Address1_alphanumeric';
  $rule->name = 'address1_alphanumeric';
  $rule->field_name = 'field_address';
  $rule->col = 'thoroughfare';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[\\x20-\\x7F]+$',
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
  $rule->error_message = 'This field may contain only English letters.';
  $export['address1_alphanumeric'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Address2_alphanumeric';
  $rule->name = 'address2_alphanumeric';
  $rule->field_name = 'field_address';
  $rule->col = 'premise';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[\\x20-\\x7F]+$',
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
  $rule->error_message = 'This field may contain only English letters.';
  $export['address2_alphanumeric'] = $rule;

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
    'data' => '^[a-zA-Z0-9\\-\\.,)(/\\\\\\\\&\' ]*$',
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
  $rule->error_message = 'This field may contain only English letters and digits.';
  $export['alphanumeric'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'City Latin';
  $rule->name = 'city_latin';
  $rule->field_name = 'field_address';
  $rule->col = 'locality';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[\\x20-\\x7F]+$',
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
  $rule->error_message = 'This field may contain only English letters.';
  $export['city_latin'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Insurance_alphanumeric';
  $rule->name = 'insurance_alphanumeric';
  $rule->field_name = 'field_insurance_company';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[\\x20-\\x7F]+$',
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
  $rule->error_message = 'This field may contain only English letters and digits.';
  $export['insurance_alphanumeric'] = $rule;

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
    'data' => '^[a-zA-Z0-9\\-\\.,)(/\\\\\\\\&\' ]*$',
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
  $rule->error_message = 'This field may contain only English letters and digits.';
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
    'data' => '^[\\x20-\\x7F]+$',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      3 => 0,
      6 => 0,
      5 => 0,
      4 => 0,
      7 => 0,
    ),
    'errors' => 1,
  );
  $rule->error_message = 'This field may contain only English letters.';
  $export['name'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'og_paraglider_color';
  $rule->name = 'og_paraglider_color';
  $rule->field_name = 'field_paraglider_color';
  $rule->col = 'value';
  $rule->entity_type = 'og_membership';
  $rule->bundle = 'pg_contestant';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[\\x20-\\x7F]+$',
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
  $rule->error_message = 'This field may contain only English letters.';
  $export['og_paraglider_color'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'og_paraglider_manufacturer';
  $rule->name = 'og_paraglider_manufacturer';
  $rule->field_name = 'field_paraglider_manufacturer';
  $rule->col = 'value';
  $rule->entity_type = 'og_membership';
  $rule->bundle = 'pg_contestant';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z0-9\\-\\.,)(/\\\\\\\\&\' ]*$',
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
  $rule->error_message = 'This field may contain only English letters.';
  $export['og_paraglider_manufacturer'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'og_paraglider_model';
  $rule->name = 'og_paraglider_model';
  $rule->field_name = 'field_paraglider_model';
  $rule->col = 'value';
  $rule->entity_type = 'og_membership';
  $rule->bundle = 'pg_contestant';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[a-zA-Z0-9\\-\\.,)(/\\\\\\\\&\' ]*$',
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
  $rule->error_message = 'This field may contain only English letters.';
  $export['og_paraglider_model'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'OG Phone required length';
  $rule->name = 'og_phone_required_length';
  $rule->field_name = 'field_phone';
  $rule->col = 'number';
  $rule->entity_type = 'og_membership';
  $rule->bundle = 'pg_contestant';
  $rule->validator = 'field_validation_length_validator';
  $rule->settings = array(
    'min' => '2',
    'max' => '',
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
  $rule->error_message = 'This field is required.';
  $export['og_phone_required_length'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'paraglider_color_latin';
  $rule->name = 'paraglider_color_latin';
  $rule->field_name = 'field_paraglider_color';
  $rule->col = 'value';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^[\\x20-\\x7F]+$',
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
  $rule->error_message = 'This field may contain only English letters and digits.';
  $export['paraglider_color_latin'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'person_phone_digits';
  $rule->name = 'person_phone_digits';
  $rule->field_name = 'field_person_phone';
  $rule->col = 'full_number';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^\\+[0-9]*$',
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
  $rule->error_message = 'This field may contain only digits.';
  $export['person_phone_digits'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Person phone required length';
  $rule->name = 'person_phone_required_length';
  $rule->field_name = 'field_person_phone';
  $rule->col = 'number';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_length_validator';
  $rule->settings = array(
    'min' => '2',
    'max' => '',
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
  $rule->error_message = 'This field is required.';
  $export['person_phone_required_length'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'phone_digits';
  $rule->name = 'phone_digits';
  $rule->field_name = 'field_phone';
  $rule->col = 'full_number';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_regex_validator';
  $rule->settings = array(
    'data' => '^\\+[0-9]*$',
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
  $rule->error_message = 'This field may contain only digits.';
  $export['phone_digits'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Phone required length';
  $rule->name = 'phone_required_length';
  $rule->field_name = 'field_phone';
  $rule->col = 'number';
  $rule->entity_type = 'profile2';
  $rule->bundle = 'pilot';
  $rule->validator = 'field_validation_length_validator';
  $rule->settings = array(
    'min' => '2',
    'max' => '',
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
  $rule->error_message = 'This field is required.';
  $export['phone_required_length'] = $rule;

  return $export;
}
