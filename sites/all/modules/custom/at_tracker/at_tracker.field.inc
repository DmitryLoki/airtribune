<?php

/**
 * Implements hook_field_info().
 */
function at_tracker_field_info() {
  return array(
    'at_tracker' => array(
      'label' => t('Tracker'),
      'description' => t('This field stores the tracker value.'),
      'settings' => array(
      ),
      'instance_settings' => array(
      ),
      'storage' => array('type' => 'at_tracker_field_storage'),
      'default_widget' => 'at_tracker',
      'default_formatter' => 'at_tracker_default',
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function at_tracker_field_formatter_info() {
  $formatters = array(
    'at_tracker_default' => array(
      'label' => t('Default'),
      'field types' => array('at_tracker'),
    ),
  );
  return $formatters;
}

/**
 * Implements hook_field_formatter_view().
 */
function at_tracker_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    $element[$delta]['#markup'] = $item['name'];
  }
  return $element;
}

/**
 * Implements hook_field_widget_info().
 */
function at_tracker_field_widget_info() {
  return array(
    'at_tracker' => array(
      'label' => t('Tracker'),
      'field types' => array('at_tracker'),
      'settings' => array(),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function at_tracker_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // suppose what fields is single value
  $value = isset($items[$delta]['value']) ? $items[$delta]['value'] : 'none';
  if ($instance['widget']['type'] == 'at_tracker') {
    $field_name = $field['field_name'];
    $settings = $field['settings'];
    $entity = $form['#entity'];
    $d = $delta;
    if (isset($form['#row_index'])) {
      $d = $form['#row_index'];
    }

    $entity_type = $entity->entityType();
    list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    $contest = get_contest_for_entity($entity_type, $entity);
    $contest_core_id = get_core_id_from_entity('node', $contest);

    $element = array(
      '#attributes' => array(
        'class' => array('form-select-at_tracker'),
        'data-contestid' => array($contest_core_id),
      ),
      '#entity' => $entity,
      '#field_name' => $field['field_name'],
      '#element_id' => $id,
      '#row_index' => $d,
      '#type' => 'select',
      '#title' => t('Tracker'),
      '#options' => _at_tracker_trackers_options($entity, $field),
      '#empty_option' => t('-- None selected --'),
      '#empty_value' => 'none',
      '#default_value' => $value,
      '#prefix' => "<div id='at_tracker-wrapper-{$id}'>",
      '#suffix' => '</div>',
      '#attached' => array('js' => array(drupal_get_path('module', 'at_tracker') . '/js/at_tracker.js')),
      '#ajax' => array(
        'callback' => '_ajax_at_tracker_widget_callback',
        'wrapper' => 'at_tracker-wrapper-' . $id,
        'method' => 'replace',
        'event' => 'change',
      ),
    );
  }

  return array('value' => $element);
}

/**
 * Save selected value of tracker.
 */
function _ajax_at_tracker_widget_callback($form, $form_state) {
  $field_name = $form_state['triggering_element']['#field_name'];
  $entity = $form_state['triggering_element']['#entity'];
  $entity_type = $entity->entityType();
  $entity->{$field_name}[LANGUAGE_NONE][0]['value'] = $form_state['triggering_element']['#value'];

  // Get the numeric id of your field by passing field name
  $info = field_info_field($field_name);
  $fields = array($info['id']);

  // Execute the storage function
  at_tracker_field_storage_write($entity_type, $entity, 'update', $fields);
}

/**
 * Implements hook_field_is_empty().
 */
function at_tracker_field_is_empty($item, $field) {
  if (empty($item['value']) && (string) $item['value'] !== '0') {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_field_prepare_view().
 */
function at_tracker_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items) {
  foreach ($entities as $id => $entity) {
    foreach ($items[$id] as $delta => $item) {
      $tracker_id = $items[$id][$delta]['value'];
      $items[$id][$delta]['value'] = $items[$id][$delta]['name'];
      $items[$id][$delta]['safe_value'] = $trackers[$tracker_id];
      $items[$id][$delta]['safe'] = $items[$id][$delta]['safe_value'];
    }
  }
}

/**
 * Implements hook_field_load().
 */
function at_tracker_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {

}

/**
 * Implements hook_field_insert().
 */
function at_tracker_field_insert($entity_type, $entity, $field, $instance, $langcode, &$items) {

}

/**
 * Implements hook_field_update().
 */
function at_tracker_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {

}

/**
 * 
 * @return $options array - trackers from core storage. Key is tracker id, value - tracker name.
 */
function _at_tracker_trackers_options($entity = NULL, $field = NULL) {
  $contest_core_id = NULL;
  cache_clear_all(NULL,'cache');
  if (!empty($entity)) {
    $entity_type = $entity->entityType();
    $contest_core_id = get_core_id_from_entity('node', get_contest_for_entity($entity_type, $entity));
  }
  $cid_part = !empty($contest_core_id) ? ':' . $contest_core_id : '';
  if ($cached = cache_get('at_tracker:trackers_options:' . $cid_part, 'cache'))  {
    $options = $cached->data;
  } else {


    $options = array();
    if (!empty($contest_core_id)) {
      $url_part = '&not_registered_at=' . $contest_core_id;
    }
    // Request only hardvare trackers
    $response = ATSync::requestToCore('tracker?device_type=tr203&device_type=telt_gh3000'. $url_part, array(), 'GET');
    foreach($response as $key => $tracker) {
      $options[$tracker->id] = $tracker->name;
    }

    cache_set('at_tracker:trackers_options:' . $cid_part, $options, 'cache', 5); //5 seconds
  }
  if (isset($field) && !empty($entity->{$field['field_name']}[LANGUAGE_NONE][0]['value'])) {
    $options[$entity->{$field['field_name']}[LANGUAGE_NONE][0]['value']] = $entity->{$field['field_name']}[LANGUAGE_NONE][0]['name'];
  }
  asort($options);
  
  return $options;
}
