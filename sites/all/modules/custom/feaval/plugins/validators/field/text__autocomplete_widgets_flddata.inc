<?php

$plugin = array(
  'field_type' => 'text',
  'widget_type' => 'autocomplete_widgets_flddata',
  'preprocessor' => 'feaval_preprocessor__text__autocomplete_widgets_flddata',
  'selector' => 'feaval_preprocessor__text__autocomplete_widgets_flddata__selector',
  //~ 'validator' => 'at_validation_validator__text__autocomplete_widgets_flddata',
);

function feaval_preprocessor__text__autocomplete_widgets_flddata(&$element, &$form_state, $context) {
  $element['value']['#ajax'] = feaval_ajax_defaults($form_state);
  $element['value']['#ajax'] += array(
    'event' => 'focusout',
  );
}


function feaval_preprocessor__text__autocomplete_widgets_flddata__selector($element, $triggering_element) {
  // TODO: Get delta
  $delta = 0;
  $selector = '#' . $element['#id'] . "-$delta-value";
  return $selector;
}
//~ function at_validation_validator__text__autocomplete_widgets_flddata_id($element, $triggering_element, &$errors) {
  //~ $selector = '#' . $element['#id'] . '-value';
  //~ return $selector;
//~ }
