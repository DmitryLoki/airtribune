<?php
/**
 * @file
 * accommodation.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function accommodation_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_price|node|accommodation|form';
  $field_group->group_name = 'group_price';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'accommodation';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Price',
    'weight' => '12',
    'children' => array(
      0 => 'field_price_single',
      1 => 'field_price_double',
      2 => 'field_price_currency',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-price field-group-fieldset ',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_price|node|accommodation|form'] = $field_group;

  return $export;
}
