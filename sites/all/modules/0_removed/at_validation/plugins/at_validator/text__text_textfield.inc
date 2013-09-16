<?php

$plugin = array(
  'field_type' => 'text',
  'widget_type' => 'text_textfield',
  'validator' => 'at_validation_validator__text__text_textfield',
  'selector' => 'at_validation_validator__text__text_textfield_id',
);

function at_validation_validator__text__text_textfield(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = at_validation_ajax_defaults();
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
}

function at_validation_validator__text__text_textfield_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-value';
  return $selector;
}
