<?php



$plugin = array(
  'field_type' => 'number_integer',
  'widget_type' => 'number',
  'preprocessor' => 'at_reg_preprocessor__number_integer__number',
  //~ 'validator' => 'at_validation_validator__number_integer__number',
  //~ 'selector' => 'at_validation_validator__number_integer__number_id',
  'after_build' => 'at_reg_preprocessor__number_integer__number_after_build',
);

function at_reg_preprocessor__number_integer__number(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = feaval_ajax_defaults($form_state);
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
  //~ global $plugin;
  //~ dsm($plugin);
  //~ dsm($element);
  //~ $element['#after_build'][] = 'feaval_field_element_after_build';
  //~ $element['#feaval_after_build_plugin']['module'] = 'feaval';
  //~ $element['#feaval_after_build_plugin']['type'] = 'field';
  //~ $element['#feaval_after_build_plugin']['id'] = 'number_integer__number';
}

//~ function at_validation_validator__number_integer__number_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }

function at_reg_preprocessor__number_integer__number_after_build($element, &$form_state) {
  // Check that Pilot's number is unique.
  $element['#element_validate'][] = 'at_reg_pilot_number_element_validate';
  return $element;
}
