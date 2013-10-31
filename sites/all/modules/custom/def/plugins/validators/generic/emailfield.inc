<?php

// This is a copy of textfield plugin.
// See note in def_form_alter about html5_tools_form_user_register_form_alter().

$plugin = array(
  'element_type' => 'emailfield',
  'preprocessor' => 'def_preprocessor__input__emailfield',
  'selector' => 'def_preprocessor__input__emailfield__selector',
);

function def_preprocessor__input__emailfield(&$element, &$form_state) {
  $element['#ajax'] = def_ajax_defaults($form_state);
  $element['#ajax'] += array(
    'event' => 'focusout',
  );
  //~ dsm($element);
}


function def_preprocessor__input__emailfield__selector($element, $triggering_element) {
  // TODO: Remove index added in form_builder(?). E.g. "edit-mail--2"
  $selector = '#' . $element['#id'];
  $elems = explode('--', $selector);
  array_pop($elems);
  $selector = implode('--', $elems);
  return $selector;
}

//~ function at_validation_validator__input__textfield_id($element, $triggering_element) {
  //~ $selector = '#' . $element['#id'];
  //~ return $selector;
//~ }
