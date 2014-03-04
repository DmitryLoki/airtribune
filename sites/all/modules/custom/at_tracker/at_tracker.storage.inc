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
      $cid = _at_tracker_get_cid($entity_type, $entity);
      $item = NULL;
      $tracker = NULL;
      list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
      if ($cached = cache_get($cid, 'cache')) {
        $item = $cached->data;
      } else {
        cache_clear_all("field:$entity_type:$id", 'cache_field');
        $sync = _get_class_by_entity($entity_type, $entity);
        $result = $sync->getFromCore();
        if (!empty($result->tracker)) {
          $tracker = ATSync::requestToCore('tracker/'. $result->tracker, array(), 'GET');
        }
        $item = array();
        $item['value'] = $tracker->id;
        $item['name'] = $tracker->name;
        cache_set($cid, $item, 'cache', 60*60); //1 hour
      }
      if (!empty($tracker)) {
        if (!isset($delta_count[$entity->id][LANGUAGE_NONE])) {
          $delta_count[$entity->id][LANGUAGE_NONE] = 0;
        }

        if ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED || $delta_count[$entity->id][LANGUAGE_NONE] < $field['cardinality']) {
          // Add the item to the field values for the entity.
          $entities[$entity->id]->{$field_name}[LANGUAGE_NONE][] = $item;
          $delta_count[$entity->id][LANGUAGE_NONE]++;
        }
      }
    }
  }
}

/**
 * Implements hook_field_storage_write().
 */
function at_tracker_field_storage_write($entity_type, $entity, $op, $fields, $entity_write = FALSE) {
  foreach ($fields as $field_id) {
    $field = field_info_field_by_id($field_id);
    $field_name = $field['field_name'];
    $result = at_core_sync_entity_sync($entity_type, $entity, 'patch', array('tracker' => $field_name));
    dpm($result);
    cache_clear_all(_at_tracker_get_cid($entity_type, $entity), 'cache');
    cache_clear_all('at_tracker:trackers_options', 'cache');
    list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    cache_clear_all("field:$entity_type:$id", 'cache_field');
  }
}

function _at_tracker_get_cid($entity_type, $entity) {
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
  return "at_tracker:{$bundle}:{$id}";
}

/**
 * Implement hook_field_storage_delete().
 */
function at_tracker_field_storage_delete($entity_type, $entity, $fields) {

}
