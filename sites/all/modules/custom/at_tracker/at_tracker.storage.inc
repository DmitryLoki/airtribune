<?php

/**
 * Implements hook_field_storage_info().
 */
function at_tracker_field_storage_info() {
  return array(
    'at_tracker_field_storage' => array(
      'label' => t('AT Tracker field storage'),
      'description' => t('Stores fields in a Core.'),
    ),
  );
}

/**
 * Implements hook_field_storage_load().
 */
function at_tracker_field_storage_load($entity_type, $entities, $age, $fields, $options) {
  $load_current = $age == FIELD_LOAD_CURRENT;
  foreach ($fields as $field_id => $ids) {
    $field = field_info_field_by_id($field_id);
    $field_name = $field['field_name'];
    $delta_count = array();
    foreach ($entities as $entity) {
      $sync = _get_class_by_entity($entity_type, $entity);
      $result = $sync->getFromCore();

      if (!isset($delta_count[$entity->id][LANGUAGE_NONE])) {
        $delta_count[$entity->id][LANGUAGE_NONE] = 0;
      }

      if ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED || $delta_count[$entity->id][LANGUAGE_NONE] < $field['cardinality']) {
        $item = array();
        $column_name = 'value';
        $item[$column_name] = $result->tracker;

        // Add the item to the field values for the entity.
        $entities[$entity->id]->{$field_name}[LANGUAGE_NONE][] = $item;
        $delta_count[$entity->id][LANGUAGE_NONE]++;
      }
    }
  }
}