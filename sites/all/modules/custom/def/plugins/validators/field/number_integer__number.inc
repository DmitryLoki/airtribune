<?php



$plugin = array(
  'field_type' => 'number_integer',
  'widget_type' => 'number',
  'preprocessor' => 'def_preprocessor__number_integer__number',
  //~ 'validator' => 'at_validation_validator__number_integer__number',
  //~ 'selector' => 'at_validation_validator__number_integer__number_id',
  'after_build' => 'def_preprocessor__number_integer__number_after_build',
);

function def_preprocessor__number_integer__number(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = def_ajax_defaults($form_state);
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
  //~ global $plugin;
  //~ dsm($plugin);
  //~ dsm($element);
  //~ $element['#after_build'][] = 'def_field_element_after_build';
  //~ $element['#def_after_build_plugin']['module'] = 'def';
  //~ $element['#def_after_build_plugin']['type'] = 'field';
  //~ $element['#def_after_build_plugin']['id'] = 'number_integer__number';
}

//~ function at_validation_validator__number_integer__number_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }

function def_preprocessor__number_integer__number_after_build($element, &$form_state) {
  //~ dsm('number_integer test after build2');
  return $element;
}
