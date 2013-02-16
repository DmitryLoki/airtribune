<?php

$plugin = array(
  'input_type' => 'textfield',
  'validator' => 'at_validation_validator__input__textfield',
  'selector' => 'at_validation_validator__input__textfield_id',
);

function at_validation_validator__input__textfield(&$element, &$form_state) {
  $element['#ajax'] = array(
    'path' => 'at-validation/ajax',
    'event' => 'focusout',
  );
}

function at_validation_validator__input__textfield_id($element, $triggering_element) {
  $selector = '#' . $element['#id'];
  return $selector;
}
