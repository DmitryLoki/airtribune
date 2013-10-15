<?php

$plugin = array(
  'field_type' => 'datetime',
  'widget_type' => 'date_select',
  'preprocessor' => 'def_preprocessor__datetime__date_select',
  'selector' => 'def_preprocessor__datetime__date_select__selector',
  //~ 'validator' => 'at_validation_validator__datetime__date_select',
  //~ 'selector' => 'at_validation_validator__datetime__date_select_id',
);

function def_preprocessor__datetime__date_select(&$element, &$form_state, $context) {
    //~ dsm($element);
    $element['#ajax'] = def_ajax_defaults($form_state);
    $element['#ajax'] += array(
      'event' => 'change',
    );
}

function def_preprocessor__datetime__date_select__selector($element, $triggering_element) {
  // TODO: Get delta (maybe from triggering_element)
  $delta = 0;
  //~ $selector = "#" . $element['#id'] . "-$delta-value";
  $selector = "#" . $element['#id'] . "-$delta-value-year";
  return $selector;
}

//~ function at_validation_validator__datetime__date_select_id($element, $triggering_element, $errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }
