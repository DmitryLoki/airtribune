<?php

// TODO: Consider empty preprocessor option
// TODO: Unify function names. E.g. feaval__field_type__widget_type__function_key.

$plugin = array(
  'field_type' => 'name',
  'widget_type' => 'name_widget',
  'preprocessor' => 'feaval_preprocessor__name__name_widget',
  'after_build' => 'feaval_preprocessor__name__name_widget__after_build',
  'element_info_alter' => 'feaval_preprocessor__name__name_widget__element_info_alter',
  'selector' => 'feaval_preprocessor__name__name_widget__selector',
);

function feaval_preprocessor__name__name_widget(&$element, &$form_state, $context) {
  //~ $element['#after_build'][] = 'at_validation_field_widget_form_after_build';
  //~ dsm($element);
}

// Return info for hook_element_info_alter().
function feaval_preprocessor__name__name_widget__element_info_alter() {
  $data = array(
    'types' => array('name_element'),
    'process' => 'feaval_preprocessor__name__name_widget__process',
  );
  return $data;
}

function feaval_preprocessor__name__name_widget__process($element, &$form_state, $complete_form) {
  foreach ($element['#components'] as $component => $data) {
    if (!empty($data['exclude'])) {
      continue;
    }
    $element[$component]['#ajax'] = feaval_ajax_defaults($form_state);
    $element[$component]['#ajax'] += array(
      'event' => 'focusout',
    );
  }

  return $element;
}

function feaval_preprocessor__name__name_widget__selector($element, $triggering_element) {
  
  // TODO: Get delta
  $delta = 0;
  $triggering_component = array_pop($triggering_element['#parents']);
  $selector = '#' . $element['#id'] . "-$delta-$triggering_component";
  return $selector;
}


function feaval_preprocessor__name__name_widget__after_build($element, &$form_state) {
  
  if (isset($form_state['#feaval_ajax_validation'])) {
    
    // Remove name field original validation.
    $key = array_search('name_element_validate', $element['#element_validate']);
    if ($key !== FALSE) {
      unset($element['#element_validate'][$key]);
      //~ $element['#element_validate'] = array_values($element['#element_validate']);
    }
    
    // Add '#required' property to name components.
    $triggering_component = array_pop($form_state['triggering_element']['#array_parents']);
    foreach ($element['#components'] as $component => $data) {
      if (!empty($data['exclude'])) {
        continue;
      }
      $element[$component]['#required'] = TRUE;
      if ($component != $triggering_component) {
        // Disable validation for all components except triggering one.
        $element[$component]['#validated'] = TRUE;
      }
    }
  }
  
  return $element;
}

//~ function at_validation_validator__name__name_widget_id($element, $triggering_element, &$errors) {
  //~ $component = end($triggering_element['#array_parents']);
//~ 
//~ 
  //~ $field_label = $element['#title'];
  //~ $triggering_title = $triggering_element['#title'];
//~ 
  //~ // Check all messages and show only those that correspond to the triggering element, if any,
  //~ // or link message to another id.
//~ 
  //~ // TODO:
  //~ // 
//~ 
  //~ $patterns = array();
//~ 
//~ 
  //~ $blank = t('%name also requires the following parts: %components.', array(
    //~ '%name' => t($field_label),
    //~ '%components' => '_blank_'
  //~ ));
  //~ $blank = explode('_blank_', $blank);
  //~ $patterns['components_blank'] = $blank[0];
  //~ $patterns['components_check'] = t('%name also requires the following parts: %components.', array(
    //~ '%name' => $field_label,
    //~ '%components' => $triggering_title
  //~ ));
  //~ $patterns['field_required'] = t('%name is required.', array('%name' => $field_label));
//~ 
  //~ if (!empty($errors)) {
    //~ foreach ($errors as $k => $error) {
      //~ // If message relates to only one element and this element doesn't correspond
      //~ // to the triggering one, then skip it.
//~ 
      //~ // Else if this element corresponds to the triggering one, return this message.
//~ 
      //~ // Else if message is common for a number of elements, choose the most appropriate element
      //~ // and return the message.
      //~ if (strpos($error, $patterns['components_blank']) !== FALSE) {
        //~ unset($errors[$k]);
        //~ break;
        //~ /*
        //~ if ($error != $patterns['components_check']) {
          //~ //$component = ($component == 'given') ? 'family' : 'given';
          //~ unset($errors[$k]);
          //~ break;
        //~ }
        //~ */
      //~ }
      //~ // Else if 'Name is required' message.
      //~ elseif ($error == $patterns['field_required']) {
        //~ //$component = 'given';
        //~ unset($errors[$k]);
        //~ break;
      //~ }
      //~ // Else if neither case found, return the message and link to the triggering element.
    //~ }
  //~ }
//~ 
  //~ $selector = '#' . $element['#id'] . '-' . $component;
  //~ return $selector;
//~ }
