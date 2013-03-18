<?php

$plugin = array(
  'field_type' => 'list_text 0',  // We don't need this plugin
  'widget_type' => 'options_select 0',
  'validator' => 'at_validation_validator__list_text__options_select',
  'selector' => 'at_validation_validator__list_text__options_select_id',
);

function at_validation_validator__list_text__options_select(&$element, &$form_state, $context) {
  $element['#ajax'] = at_validation_ajax_defaults();
  $element['#ajax'] += array(
    'event' => 'change',
  );
}

function at_validation_validator__list_text__options_select_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'];
  return $selector;
}
