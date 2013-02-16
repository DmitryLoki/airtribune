<?php

$plugin = array(
  'field_type' => 'datetime',
  'widget_type' => 'date_select',
  'validator' => 'at_validation_validator__datetime__date_select',
  'selector' => 'at_validation_validator__datetime__date_select_id',
);

function at_validation_validator__datetime__date_select(&$element, &$form_state, $context) {
  $element['#ajax'] = array(
    'path' => 'at-validation/ajax',
    'event' => 'change',
  );
}

function at_validation_validator__datetime__date_select_id($element, $triggering_element) {
  $selector = '#' . $element['#id'] . '-value';
  return $selector;
}
