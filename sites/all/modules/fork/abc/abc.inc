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
}

// TODO:
// #1
// If a form contains a single textfield, and the ENTER key is pressed
// within it, Internet Explorer submits the form with no POST data...
// https://api.drupal.org/api/drupal/includes%21form.inc/function/form_builder/7
// I.e. we should thing about first button for a subform
