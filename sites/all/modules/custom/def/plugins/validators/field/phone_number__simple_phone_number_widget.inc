<?php

$plugin = array(
  'field_type' => 'phone_number',
  'widget_type' => 'simple_phone_number_widget',
  'preprocessor' => 'def_preprocessor__phone_number__simple_phone_number_widget',
  //~ 'validator' => 'at_validation_validator__phone_number__simple_phone_number_widget',
  //~ 'selector' => 'at_validation_validator__phone_number__simple_phone_number_widget_id',
);

function def_preprocessor__phone_number__simple_phone_number_widget(&$element, &$form_state, $context) {
  $element['full_number']['#ajax'] = def_ajax_defaults($form_state);
  $element['full_number']['#ajax'] += array(
    'event' => 'focusout',
  );
}

//~ function at_validation_validator__phone_number__simple_phone_number_widget_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-full-number';
  //~ return $selector;
//~ }
