<?php

$plugin = array(
  'field_type' => 'text',
  'widget_type' => 'text_textfield',
  'preprocessor' => 'feaval_preprocessor__text__text_textfield',
  'selector' => 'feaval_preprocessor__text__text_textfield__selector',
  //~ 'validator' => 'at_validation_validator__text__text_textfield',
);

function feaval_preprocessor__text__text_textfield(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = feaval_ajax_defaults($form_state);
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
}

function feaval_preprocessor__text__text_textfield__selector($element, $triggering_element) {
  // TODO: Get delta
  $delta = 0;
  $selector = '#' . $element['#id'] . "-$delta-value";
  return $selector;
}

//~ function at_validation_validator__text__text_textfield_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }
