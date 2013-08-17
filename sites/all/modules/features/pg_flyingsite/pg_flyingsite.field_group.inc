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
  $field_group->identifier = 'group_flying_site_description|node|pg_flyingsite|form';
  $field_group->group_name = 'group_flying_site_description';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pg_flyingsite';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Description',
    'weight' => '3',
    'children' => array(
      0 => 'field_geographic_position',
      1 => 'field_meteo_info',
      2 => 'field_events_held_there',
      3 => 'field_seasonality',
      4 => 'field_historic_info',
      5 => 'field_records_made_there',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Description',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-flying-site-description field-group-fieldset ',
        'description' => 'Please, fill in the forms below in a free manner. 
After saving all these separate forms will become an single text.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_flying_site_description|node|pg_flyingsite|form'] = $field_group;

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
      0 => 'field_gt_general',
      1 => 'field_gt_bus',
      2 => 'field_gt_car',
      3 => 'field_gt_train',
      4 => 'field_gt_plane',
      5 => 'field_gt_taxi',
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
