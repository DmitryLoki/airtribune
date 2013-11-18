<?php



$plugin = array(
  'field_type' => 'number_integer',
  'widget_type' => 'number',
  'preprocessor' => 'feaval_preprocessor__number_integer__number',
  'after_build' => 'feaval_preprocessor__number_integer__number_after_build',
  'selector' => 'feaval_preprocessor__number_integer__number__selector',
  //~ 'validator' => 'at_validation_validator__number_integer__number',
);

function feaval_preprocessor__number_integer__number(&$element, &$form_state, $context) {
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


function feaval_preprocessor__number_integer__number_after_build($element, &$form_state) {
  //~ dsm('number_integer test after build2');
  return $element;
}

function feaval_preprocessor__number_integer__number__selector($element, $triggering_element) {
  // TODO: Get delta
  $delta = 0;
  $selector = '#' . $element['#id'] . "-$delta-value";
  return $selector;
}

//~ function at_validation_validator__number_integer__number_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }
