<?php

 

$plugin = array(
  'field_type' => 'number_integer',
  'widget_type' => 'number',
  'validator' => 'at_validation_validator__number_integer__number',
  'selector' => 'at_validation_validator__number_integer__number_id',
);

function at_validation_validator__number_integer__number(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = at_validation_ajax_defaults();
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
}

function at_validation_validator__number_integer__number_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-value';dsm($selector);
  return $selector;
}
