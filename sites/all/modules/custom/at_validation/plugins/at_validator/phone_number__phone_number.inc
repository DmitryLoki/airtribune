<?php

$plugin = array(
  'field_type' => 'phone_number',
  'widget_type' => 'phone_number',
  'validator' => 'at_validation_validator__phone_number__phone_number',
  'selector' => 'at_validation_validator__phone_number__phone_number_id',
  'after_build' => 'at_validation_validator__phone_number__phone_number_after_build',
);

function at_validation_validator__phone_number__phone_number(&$element, &$form_state, $context) {
  $element['#after_build'][] = 'at_validation_field_widget_form_after_build';
}

function at_validation_validator__phone_number__phone_number_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-number';
  return $selector;
}

/**
 * #after_build callback.
 * Process ajax here since there are no components at form_alter stage.
 */
function at_validation_validator__phone_number__phone_number_after_build($element, &$form_state) {
  $defaults = at_validation_ajax_defaults();
  // 'number' component
  $element['number']['#ajax'] = $defaults;
  $element['number']['#ajax'] += array(
    'event' => 'focusout',
  );
  unset($element['number']['#ajax_processed']);
  $element['number'] = ajax_process_form($element['number'], $form_state);
  /*
  // /country_codes' component
  $element['country_codes']['#ajax'] = $defaults;
  $element['country_codes']['#ajax'] += array(
    'event' => 'change',
  );
  unset($element['country_codes']['#ajax_processed']);
  $element['country_codes'] = ajax_process_form($element['country_codes'], $form_state);
  */
  return $element;
}
