<?php

$plugin = array(
  'field_type' => 'phone_number',
  'widget_type' => 'simple_phone_number_widget',
  'preprocessor' => 'def_preprocessor__phone_number__simple_phone_number_widget',
  'selector' => 'def_preprocessor__phone_number__simple_phone_number_widget__selector',
  //~ 'validator' => 'at_validation_validator__phone_number__simple_phone_number_widget',
);

function def_preprocessor__phone_number__simple_phone_number_widget(&$element, &$form_state, $context) {
  $element['full_number']['#ajax'] = def_ajax_defaults($form_state);
  $element['full_number']['#ajax'] += array(
    'event' => 'focusout',
  );
}


function def_preprocessor__phone_number__simple_phone_number_widget__selector($element, $triggering_element) {
  // TODO: Get delta
  $delta = 0;
  $selector = '#' . $element['#id'] . "-$delta-full-number";
  return $selector;
}

//~ function at_validation_validator__phone_number__simple_phone_number_widget_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-full-number';
  //~ return $selector;
//~ }
