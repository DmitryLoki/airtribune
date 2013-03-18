<?php
/**
 * @file
 * pg_contest.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pg_contest_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contacs|node|pg_contest|form';
  $field_group->group_name = 'group_contacs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pg_contest';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contacts',
    'weight' => '33',
    'children' => array(
      0 => 'field_contacts_email',
      1 => 'field_contacts_name',
      2 => 'field_contacts_phone',
      3 => 'field_position',
    ),
    'format_type' => 'field_group_multiple_table',
    'format_settings' => array(
      'label' => 'Contacts',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-contacs field-group-field_group_multiple_table ',
        'description' => '',
        'parent_format_type' => 'fieldset',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'row_titles' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_contacs|node|pg_contest|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contacts|node|pg_contest|default';
  $field_group->group_name = 'group_contacts';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pg_contest';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contacts',
    'weight' => '46',
    'children' => array(
      0 => 'field_contacts_email',
      1 => 'field_contacts_name',
      2 => 'field_position',
      3 => 'field_contacts_phone',
    ),
    'format_type' => 'field_group_multiple_container',
    'format_settings' => array(
      'label' => 'Contacts',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'parent_format_type' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_contacts|node|pg_contest|default'] = $field_group;

  return $export;
}
