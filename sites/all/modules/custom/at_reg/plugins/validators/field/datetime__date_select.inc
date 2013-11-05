<?php

// TODO: Inherit plugin properties from parent plugin.

$plugin = array(
  'field_type' => 'datetime',
  'widget_type' => 'date_select',
  'preprocessor' => 'at_reg_preprocessor__datetime__date_select',
  'selector' => 'at_reg_preprocessor__datetime__date_select__selector',
  //~ 'validator' => 'at_validation_validator__datetime__date_select',
  //~ 'selector' => 'at_validation_validator__datetime__date_select_id',
  'after_build' => 'at_reg_preprocessor__datetime__date_select__after_build',
);

function at_reg_preprocessor__datetime__date_select(&$element, &$form_state, $context) {
    //~ dsm($element);
    $element['#ajax'] = feaval_ajax_defaults($form_state);
    $element['#ajax'] += array(
      'event' => 'change',
    );
}


function at_reg_preprocessor__datetime__date_select__selector($element) {
  // TODO: Get delta (maybe from triggering_element)
  $delta = 0;
  //~ $selector = "#" . $element['#id'] . "-$delta-value";
  $selector = "#" . $element['#id'] . "-$delta-value-year";
  return $selector;
}


function at_reg_preprocessor__datetime__date_select__after_build($element, &$form_state) {
  if (isset($form_state['#feaval_ajax_validation'])) {
    // Check that Name + Date of birth are unique.
    $element['#element_validate'][] = 'at_reg_name_dateofbirth_element_validate';
  }
  return $element;
}



//~ function at_validation_validator__datetime__date_select_id($element, $triggering_element, $errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }
