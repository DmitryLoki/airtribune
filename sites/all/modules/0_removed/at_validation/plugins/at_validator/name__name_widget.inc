<?php

$plugin = array(
  'field_type' => 'name',
  'widget_type' => 'name_widget',
  'validator' => 'at_validation_validator__name__name_widget',
  'selector' => 'at_validation_validator__name__name_widget_id',
  'after_build' => 'at_validation_validator__name__name_widget_after_build',
);

function at_validation_validator__name__name_widget(&$element, &$form_state, $context) {
  $element['#after_build'][] = 'at_validation_field_widget_form_after_build';
}


function at_validation_validator__name__name_widget_after_build($element, &$form_state) {
  foreach ($element['#components'] as $component => $data) {
    if (!empty($data['exclude'])) {
      continue;
    }
    $element[$component]['#ajax'] = at_validation_ajax_defaults();
    $element[$component]['#ajax'] += array(
      'event' => 'focusout',
    );
    unset($element[$component]['#ajax_processed']);
    $element[$component] = ajax_process_form($element[$component], $form_state);
  }

  return $element;
}

function at_validation_validator__name__name_widget_id($element, $triggering_element, &$errors) {
  $component = end($triggering_element['#array_parents']);


  $field_label = $element['#title'];
  $triggering_title = $triggering_element['#title'];

  // Check all messages and show only those that correspond to the triggering element, if any,
  // or link message to another id.

  // TODO:
  // 

  $patterns = array();


  $blank = t('%name also requires the following parts: %components.', array(
    '%name' => t($field_label),
    '%components' => '_blank_'
  ));
  $blank = explode('_blank_', $blank);
  $patterns['components_blank'] = $blank[0];
  $patterns['components_check'] = t('%name also requires the following parts: %components.', array(
    '%name' => $field_label,
    '%components' => $triggering_title
  ));
  $patterns['field_required'] = t('%name is required.', array('%name' => $field_label));

  if (!empty($errors)) {
    foreach ($errors as $k => $error) {
      // If message relates to only one element and this element doesn't correspond
      // to the triggering one, then skip it.

      // Else if this element corresponds to the triggering one, return this message.

      // Else if message is common for a number of elements, choose the most appropriate element
      // and return the message.
      if (strpos($error, $patterns['components_blank']) !== FALSE) {
        unset($errors[$k]);
        break;
        /*
        if ($error != $patterns['components_check']) {
          //$component = ($component == 'given') ? 'family' : 'given';
          unset($errors[$k]);
          break;
        }
        */
      }
      // Else if 'Name is required' message.
      elseif ($error == $patterns['field_required']) {
        //$component = 'given';
        unset($errors[$k]);
        break;
      }
      // Else if neither case found, return the message and link to the triggering element.
    }
  }

  $selector = '#' . $element['#id'] . '-' . $component;
  return $selector;
}
