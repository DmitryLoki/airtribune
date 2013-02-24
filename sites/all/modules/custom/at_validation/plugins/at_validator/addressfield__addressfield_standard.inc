<?php

$plugin = array(
  'field_type' => 'addressfield',
  'widget_type' => 'addressfield_standard',
  'validator' => 'at_validation_validator__addressfield__addressfield_standard',
  'selector' => 'at_validation_validator__addressfield__addressfield_standard_id',
  'after_build' => 'at_validation_validator__addressfield__addressfield_standard_after_build',
);

function at_validation_validator__addressfield__addressfield_standard(&$element, &$form_state, $context) {
  $element['#after_build'][] = 'at_validation_validator__addressfield__addressfield_standard_after_build';
}

function at_validation_validator__addressfield__addressfield_standard_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-number';
  return $selector;
}

/**
 * #after_build callback.
 */
function at_validation_validator__addressfield__addressfield_standard_after_build($element, &$form_state) {
  $defaults = at_validation_ajax_defaults();
  
  // TODO: Actually commented part should replace the checks below.
  // But by some reason drupal_array_set_nested_value() doesn't find locality and postal_code
  /*
  $components = array(
    'thoroughfare' => array('street_block', 'thoroughfare'), // Address 1
    'premise' => array('street_block', 'premise'),
    'locality' => array('locality_block ', 'locality'), // City
    'postal_code' => array('locality_block ', 'postal_code'), // Zip code
  );
  //if (isset($element['locality_block']['locality'])) drupal_set_message('test');
  
  foreach ($components as $parents) {
    $key_exists = NULL;
    $component = drupal_array_get_nested_value($element, $parents, $key_exists);
    if (!empty($key_exists)) {
      $component['#ajax'] = $defaults;
      $component['#ajax'] += array(
        'event' => 'focusout',
      );
      unset($component['#ajax_processed']);
      ajax_process_form($component, $form_state);
      drupal_array_set_nested_value($element, $parents, $component, TRUE);
      
    }
  }
  */
  
  
  // Address 1
  if (isset($element['street_block']['thoroughfare'])) {
    $element['street_block']['thoroughfare']['#ajax'] = $defaults;
    $element['street_block']['thoroughfare']['#ajax'] += array(
      'event' => 'focusout',
    );
    unset($element['street_block']['thoroughfare']['#ajax_processed']);
    $element['street_block']['thoroughfare'] = ajax_process_form($element['street_block']['thoroughfare'], $form_state);
  }
  
  // City
  if (isset($element['locality_block']['locality'])) {
    $element['locality_block']['locality']['#ajax'] = $defaults;
    $element['locality_block']['locality']['#ajax'] += array(
      'event' => 'focusout',
    );
    unset($element['locality_block']['locality']['#ajax_processed']);
    $element['locality_block']['locality'] = ajax_process_form($element['locality_block']['locality'], $form_state);
  }
  
  // Zip code
  if (isset($element['locality_block']['postal_code'])) {
    $element['locality_block']['postal_code']['#ajax'] = $defaults;
    $element['locality_block']['postal_code']['#ajax'] += array(
      'event' => 'focusout',
    );
    unset($element['locality_block']['postal_code']['#ajax_processed']);
    $element['locality_block']['postal_code'] = ajax_process_form($element['locality_block']['postal_code'], $form_state);
  }
  
  return $element;
}
