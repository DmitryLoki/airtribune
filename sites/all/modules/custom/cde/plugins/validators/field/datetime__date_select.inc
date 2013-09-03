<?php

$plugin = array(
  'field_type' => 'datetime',
  'widget_type' => 'date_select',
  'preprocessor' => 'cde_preprocessor__datetime__date_select',
  //~ 'validator' => 'at_validation_validator__datetime__date_select',
  //~ 'selector' => 'at_validation_validator__datetime__date_select_id',
  'after_build' => 'cde_preprocessor__datetime__date_select__after_build',
);

function cde_preprocessor__datetime__date_select(&$element, &$form_state, $context) {
    //~ dsm($element);
    $element['#ajax'] = def_ajax_defaults();
    $element['#ajax'] += array(
      'event' => 'change',
    );
}

function cde_preprocessor__datetime__date_select__after_build($element, &$form_state) {
  if (isset($form_state['#def_ajax_validation'])) {
    // Check that Name + Date of birth are unique.
    $element['#element_validate'][] = 'cde_name_dateofbirth_element_validate';
  }
  return $element;
}

//~ function at_validation_validator__datetime__date_select_id($element, $triggering_element, $errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }
