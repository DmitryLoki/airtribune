<?php
/**
 * @file
 * pg_flyingsite.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pg_flyingsite_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_how_to_get_here|node|pg_flyingsite|default';
  $field_group->group_name = 'group_how_to_get_here';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pg_flyingsite';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'How to get here',
    'weight' => '35',
    'children' => array(
      0 => 'field_gt_plane',
      1 => 'field_gt_train',
      2 => 'field_gt_car',
      3 => 'field_gt_bus',
      4 => 'field_gt_taxi',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'How to get here',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_how_to_get_here|node|pg_flyingsite|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_how_to_get_here|node|pg_flyingsite|form';
  $field_group->group_name = 'group_how_to_get_here';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pg_flyingsite';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'How to get here',
    'weight' => '5',
    'children' => array(
      0 => 'field_gt_plane',
      1 => 'field_gt_train',
      2 => 'field_gt_car',
      3 => 'field_gt_bus',
      4 => 'field_gt_taxi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-how-to-get-here field-group-fieldset ',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_how_to_get_here|node|pg_flyingsite|form'] = $field_group;

  return $export;
}
