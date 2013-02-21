<?php

// TODO:
// Selector is not correctly defined.
// Ajax on select fires only once.

$plugin = array(
  'field_type' => 'list_text',
  'widget_type' => 'options_select',
  'validator' => 'at_validation_validator__list_text__options_select',
  'selector' => 'at_validation_validator__list_text__options_select_id',
);

function at_validation_validator__list_text__options_select(&$element, &$form_state, $context) {
  $element['#ajax'] = array(
    'path' => 'at-validation/ajax',
    'event' => 'change',
  );
}

function at_validation_validator__list_text__options_select_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'];
  //$selector = '#edit-profile-pilot-field-blood-type-und';
  return $selector;
}
