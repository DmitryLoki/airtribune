<?php

$plugin = array(
  'field_type' => 'name',
  'widget_type' => 'name_widget',
  'validator' => 'at_validation_validator__name__name_widget',
  'selector' => 'at_validation_validator__name__name_widget_id',
  'after_build' => 'at_validation_validator__name__name_widget_after_build',
);

function at_validation_validator__name__name_widget(&$element, &$form_state, $context) {
  
  foreach ($element['#components'] as $k => $component) {
    if (empty($component['exclude'])) {
      $element['#components'][$k]['#ajax'] = array(
        'path' => 'at-validation/ajax',
        'event' => 'focusout',
      );
    }
  }
  $element['#after_build'][] = 'at_validation_field_widget_form_after_build';
}


function at_validation_validator__name__name_widget_after_build($element, &$form_state) {
  foreach ($element['#components'] as $component => $data) {
    if (!empty($data['exclude'])) {
      continue;
    }
    $element[$component]['#ajax'] = array(
      'path' => 'at-validation/ajax',
      'event' => 'focusout',
    );
    unset($element[$component]['#ajax_processed']);
    $element[$component] = ajax_process_form($element[$component], $form_state);
  }
  
  return $element;
}

function at_validation_validator__name__name_widget_id($element, $triggering_element) {
  $component = end($triggering_element['#array_parents']);
  $selector = '#' . $element['#id'] . '-' . $component;
  return $selector;
}
