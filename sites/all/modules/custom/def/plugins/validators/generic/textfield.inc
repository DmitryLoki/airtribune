<?php

$plugin = array(
  'element_type' => 'textfield',
  'preprocessor' => 'def_preprocessor__input__textfield',
  //~ 'selector' => 'at_validation_validator__input__textfield_id',
);

function def_preprocessor__input__textfield(&$element, &$form_state) {
  $element['#ajax'] = def_ajax_defaults($form_state);
  $element['#ajax'] += array(
    'event' => 'focusout',
  );
  //~ dsm($element);
}

//~ function at_validation_validator__input__textfield_id($element, $triggering_element) {
  //~ $selector = '#' . $element['#id'];
  //~ return $selector;
//~ }
