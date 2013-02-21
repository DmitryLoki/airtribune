<?php

$plugin = array(
  'field_type' => 'text',
  'widget_type' => 'autocomplete_widgets_flddata',
  'validator' => 'at_validation_validator__text__autocomplete_widgets_flddata',
  'selector' => 'at_validation_validator__text__autocomplete_widgets_flddata_id',
);

function at_validation_validator__text__autocomplete_widgets_flddata(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = array(
    'path' => 'at-validation/ajax',
    'event' => 'focusout',
  );
}

function at_validation_validator__text__autocomplete_widgets_flddata_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-value';
  return $selector;
}
