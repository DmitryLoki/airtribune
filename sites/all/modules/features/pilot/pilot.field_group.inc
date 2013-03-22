<?php
/**
 * @file
 * pilot.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pilot_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_all|profile2|pilot|default';
  $field_group->group_name = 'group_all';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'All',
    'weight' => '0',
    'children' => array(
      0 => 'group_emergency',
      1 => 'group_paraglider',
      2 => 'group_personal',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_all|profile2|pilot|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_all|profile2|pilot|form';
  $field_group->group_name = 'group_all';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'All',
    'weight' => '0',
    'children' => array(
      0 => 'group_emergency',
      1 => 'group_paraglider',
      2 => 'group_personal',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_all|profile2|pilot|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact_person|profile2|pilot|default';
  $field_group->group_name = 'group_contact_person';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_emergency';
  $field_group->data = array(
    'label' => 'Person to contact in case of emergency',
    'weight' => '6',
    'children' => array(
      0 => 'field_person_phone',
      1 => 'field_person_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_contact_person|profile2|pilot|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact_person|profile2|pilot|form';
  $field_group->group_name = 'group_contact_person';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_emergency';
  $field_group->data = array(
    'label' => 'Person to contact in case of emergency',
    'weight' => '5',
    'children' => array(
      0 => 'field_person_phone',
      1 => 'field_person_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_contact_person|profile2|pilot|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_emergency|profile2|pilot|default';
  $field_group->group_name = 'group_emergency';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_all';
  $field_group->data = array(
    'label' => 'in case of emergency',
    'weight' => '7',
    'children' => array(
      0 => 'field_insurance_policy_number',
      1 => 'field_blood_type',
      2 => 'field_insurance_company',
      3 => 'group_contact_person',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_emergency|profile2|pilot|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_emergency|profile2|pilot|form';
  $field_group->group_name = 'group_emergency';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_all';
  $field_group->data = array(
    'label' => 'in case of emergency',
    'weight' => '3',
    'children' => array(
      0 => 'field_insurance_policy_number',
      1 => 'field_blood_type',
      2 => 'field_insurance_company',
      3 => 'group_contact_person',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_emergency|profile2|pilot|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_paraglider|profile2|pilot|default';
  $field_group->group_name = 'group_paraglider';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_all';
  $field_group->data = array(
    'label' => 'Paraglider',
    'weight' => '2',
    'children' => array(
      0 => 'field_paraglider_color',
      1 => 'field_paraglider_manufacturer',
      2 => 'field_paraglider_model',
      3 => 'field_sponsors',
      4 => 'field_fai_license_number',
      5 => 'field_civl_id',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_paraglider|profile2|pilot|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_paraglider|profile2|pilot|form';
  $field_group->group_name = 'group_paraglider';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_all';
  $field_group->data = array(
    'label' => 'Paraglider',
    'weight' => '2',
    'children' => array(
      0 => 'field_paraglider_color',
      1 => 'field_paraglider_manufacturer',
      2 => 'field_paraglider_model',
      3 => 'field_sponsors',
      4 => 'field_fai_license_number',
      5 => 'field_civl_id',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_paraglider|profile2|pilot|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal|profile2|pilot|default';
  $field_group->group_name = 'group_personal';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_all';
  $field_group->data = array(
    'label' => 'Personal info',
    'weight' => '1',
    'children' => array(
      0 => 'field_t_shirt_size',
      1 => 'field_name_in_national_alphabet',
      2 => 'field_address',
      3 => 'field_phone',
      4 => 'field_pilot_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_personal|profile2|pilot|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal|profile2|pilot|form';
  $field_group->group_name = 'group_personal';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'pilot';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_all';
  $field_group->data = array(
    'label' => 'Personal info',
    'weight' => '1',
    'children' => array(
      0 => 'field_t_shirt_size',
      1 => 'field_name_in_national_alphabet',
      2 => 'field_address',
      3 => 'field_phone',
      4 => 'field_pilot_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_personal|profile2|pilot|form'] = $field_group;

  return $export;
}
