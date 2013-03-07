<?php

$plugin = array(
  'field_type' => 'text',
  'widget_type' => 'autocomplete_widgets_flddata',
  'validator' => 'at_validation_validator__text__autocomplete_widgets_flddata',
  'selector' => 'at_validation_validator__text__autocomplete_widgets_flddata_id',
);

function at_validation_validator__text__autocomplete_widgets_flddata(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = at_validation_ajax_defaults();
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
}

function at_validation_validator__text__autocomplete_widgets_flddata_id($element, $triggering_element, &$errors) {
  $selector = '#' . $element['#id'] . '-value';
  return $selector;
}
