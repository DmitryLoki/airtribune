<?php
/**
 * @file
 * traker_type.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function traker_type_field_default_fields() {
  $fields = array();

  // Exported field: 'ent_traker_type-ent_traker_type-field_traker_ref'.
  $fields['ent_traker_type-ent_traker_type-field_traker_ref'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_traker_ref',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'direction' => 'ASC',
            'property' => 'id',
            'type' => 'property',
          ),
          'target_bundles' => array(
            'ent_traker_model' => 'ent_traker_model',
          ),
        ),
        'profile2_private' => FALSE,
        'target_type' => 'ent_traker_model',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'ent_traker_type',
      'default_value' => NULL,
      'default_value_function' => '',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'entityreference',
          'settings' => array(
            'link' => FALSE,
          ),
          'type' => 'entityreference_label',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ent_traker_type',
      'exclude_cv' => 0,
      'field_name' => 'field_traker_ref',
      'label' => 'Model',
      'required' => 1,
      'settings' => array(
        'behaviors' => array(
          'prepopulate' => array(
            'status' => 0,
          ),
        ),
        'entity_translation_sync' => FALSE,
        'exclude_cv' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_select',
        'weight' => '41',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Model');

  return $fields;
}
