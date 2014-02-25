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
  //dpm($items);
  foreach ($items as $delta => $item) {
    $element[$delta]['#markup'] = $item['safe_value'];
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
  $value = isset($items[$delta]['value']) ? $items[$delta]['value'] : 'none';
  if ($instance['widget']['type'] == 'at_tracker') {
    $field_name = $field['field_name'];
    $settings = $field['settings'];
    $entity = $form['#entity'];
    //$d = $form['#parents'][1];
    $d = $delta;
    // TODO: get default value from Core

    $element = array(
      '#type' => 'select',
      '#title' => t('Tracker'),
      '#options' => _at_tracker_trackers_options(),
      '#empty_option' => t('-- None selected --'),
      '#empty_value' => 'none',
      '#default_value' => $value,
      '#prefix' => "<div id='at_tracker-wrapper-{$d }'>", 
      '#suffix' => '</div>',
      '#attached' => array('js' => array(drupal_get_path('module', 'at_tracker') . '/js/at_tracker.js')),
      '#ajax' => array(
        'callback' => '_ajax_at_tracker_widget_callback',
        'wrapper' => 'at_tracker-wrapper-' . $d,
        'method' => 'replace',
        'event' => 'mousedown',
      ),
    );
    $form_state['at'] = array('tracker_field' => $field['field_name'], 'field_delta' => $d);

  }

  return array('value' => $element);;
}

/**
 * Returns the tracker element filtered by continent via AJAX.
 */
function _ajax_at_tracker_widget_callback($form, $form_state) {
  $field_name = $form_state['at']['tracker_field'];
  $delta = $form_state['at']['field_delta'];
  $form[$field_name][LANGUAGE_NONE][0]['#options'] = array('none' => t('-- None selected --')) + _at_tracker_trackers_options();
  $form[$field_name][LANGUAGE_NONE][0]['#default_value'] = $form_state['values'][$field_name][LANGUAGE_NONE][0];
  $commands[] = ajax_command_insert('#at_tracker-wrapper-' . $delta, drupal_render($form[$field_name]));
  $commands[] = ajax_command_invoke(NULL,'changeBindTrackerField',array($field_name));
  $commands[] = ajax_command_invoke('#at_tracker-wrapper-' . $delta . ' select','attr',array('size', 5));
  return array('#type' => 'ajax', '#commands' => $commands);
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
  $trackers = _at_tracker_trackers_options();
  foreach ($entities as $id => $entity) {
    foreach ($items[$id] as $delta => $item) {
      $tracker_id = $items[$id][$delta]['value'];
      $items[$id][$delta]['value'] = $trackers[$tracker_id];
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
  $result = at_core_sync_entity_sync($entity_type, $entity, 'patch', array('tracker' => $field['field_name']));
}

/**
 * Implements hook_field_update().
 */
function at_tracker_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {
  $result = at_core_sync_entity_sync($entity_type, $entity, 'patch', array('tracker' => $field['field_name']));
}

/**
 * 
 * @return $options array - trackers from core storage. Key is tracker id, value - tracker name.
 */
function _at_tracker_trackers_options() {
  $options = array();
  // Request only hardvare trackers
  $response = ATSync::requestToCore('tracker?device_type=tr203&device_type=telt_gh3000', array(), 'GET');
  foreach($response as $key => $tracker) {
    $options[$tracker->id] = $tracker->name;
  }
  
  asort($options);
  
  return $options;
}
