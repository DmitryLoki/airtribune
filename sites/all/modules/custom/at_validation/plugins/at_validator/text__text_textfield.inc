<?php

$plugin = array(
  'field_type' => 'text',
  'widget_type' => 'text_textfield',
  'validator' => 'at_validation_validator__text__text_textfield',
  'selector' => 'at_validation_validator__text__text_textfield_id',
);

function at_validation_validator__text__text_textfield(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = array(
    'path' => 'at-validation/ajax',
    'event' => 'focusout',
  );
}

function at_validation_validator__text__text_textfield_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-value';
  return $selector;
}
