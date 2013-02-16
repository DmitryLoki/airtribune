<?php

// TODO:
// This plugin needs to implement an #after_build callback to process ajax.
// See name__name_widget.inc for an example.
// Also selector callback should be defined.

$plugin = array(
  'field_type' => 'list_text',
  'widget_type' => 'options_buttons',
  'validator' => 'at_validation_validator__list_text__options_buttons',
);

function at_validation_validator__list_text__options_buttons(&$element, &$form_state, $context) {
  $element['#ajax'] = array(
    'path' => 'at-validation/ajax',
    'event' => 'change',
  );
}
