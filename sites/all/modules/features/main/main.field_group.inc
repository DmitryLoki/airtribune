<?php
/**
 * @file
 * main.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function main_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_all|profile2|main|default';
  $field_group->group_name = 'group_all';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'All',
    'weight' => '0',
    'children' => array(
      0 => 'field_birthdate',
      1 => 'field_gender',
      2 => 'field_full_name',
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
  $export['group_all|profile2|main|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_all|profile2|main|form';
  $field_group->group_name = 'group_all';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '0',
    'children' => array(
      0 => 'field_gender',
      1 => 'field_full_name',
      2 => 'field_birthdate',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Personal',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_all|profile2|main|form'] = $field_group;

  return $export;
}
