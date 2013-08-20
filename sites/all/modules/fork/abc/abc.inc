<?php

// TODO:
function abc_init_form() {
  $form = element_info('form');
  return $form;
}

function abc_init_settings(&$settings) {
  foreach ($settings['#subforms'] as $k => $subform) {
    $settings['#subforms'][$k] += array(
      'args' => array(),
      '#before_execute' => array(),
      '#after_execute' => array(),
    );
  }
}

// TODO: Replace $subform_id with index in order to support same forms in multiform.
function abc_delayed_submit_prepare(&$multiform, $form, $form_state, $form_id, $unprocessed_form) {
  // TODO: Check if form was submitted and related issues
  
  // Store data for further processing
  $multiform['#subforms'][$form_id] = array(
    'form' => $form,
    'form_state' => $form_state,
    'unprocessed_form' => $unprocessed_form,
  );
}

// TODO:
function abc_delayed_submit_execute(&$multiform, &$form, &$form_state, $form_id) {
  $form = $multiform['#subforms'][$form_id]['form'];
  $form_state = $multiform['#subforms'][$form_id]['form_state'];
  $unprocessed_form = $multiform['#subforms'][$form_id]['unprocessed_form'];
  
  abc_drupal_process_form_finish($form_id, $form, $form_state, $unprocessed_form);
  
  // Store data (submit results) for #before_execute and #after_execute hooks.
  // Data can be used/changed in #before_execute and #after_execute hooks.
  // Usually only $form_state is changed in submit handlers.
  // Also there is no trouble if form wasn't submitted. Data isn't used anywhere else except those hooks.
  // Actually, these are needed only if multiform was submitted and validation passed correctly.
  $multiform['#subforms'][$form_id]['form'] = $form;
  $multiform['#subforms'][$form_id]['form_state'] = $form_state;
  
  
  // Invoke #after_execute functions for each form after it is submitted.
  // Invoke only in case form was submitted and there are no validation errors (see abc_drupal_process_form_finish()).
  $subform_settings = $multiform['#subforms'][$form_id]['#subform_settings'];
  if ($form_state['executed'] == TRUE) {
    foreach ($subform_settings['#after_execute'] as $function) {
      $function($multiform, $form_id);
    }
  }
  
}

// TODO:
// #1
// If a form contains a single textfield, and the ENTER key is pressed
// within it, Internet Explorer submits the form with no POST data...
// https://api.drupal.org/api/drupal/includes%21form.inc/function/form_builder/7
// I.e. we should thing about first button for a subform
