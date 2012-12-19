<?php

/**
 * @file
 * Ajax helper, which provides multiform module specific process functions
 * for ajax-enabled elements.
 *
 */

/**
 * Menu callback; handles Ajax requests for the #ajax Form API property.
 */
function multiform_ajax_form_callback() {
  
  module_load_include('inc', 'multiform');
  
  $multiform = array(
    'multiform' => $_POST['multiform'],
    'form_id' => $_POST['form_id'],
    'form_build_id' => $_POST['form_build_id'],
  );
  foreach ($multiform as $key => $value) {
    unset($_POST[$key]);
  }
  // Define triggering element's subform index.
  $multiform_index = isset($_POST['_multiform_index']) ? $_POST['_multiform_index'] : FALSE;
  if (!$multiform_index) {
    return;
  }
  $_POST += $multiform['multiform'][$multiform_index];
  
  // This part is based on ajax_form_callback().
  list($form, $form_state) = ajax_get_form();
  drupal_process_form($form['#form_id'], $form, $form_state);
  
  $multiform = array();
  multiform_process_form_state('restore', $form_state);
  _multiform_delayed_submit_execute($form, $form_state, $form['#form_id'], $multiform);
  
  if (!empty($form_state['triggering_element'])) {
    $callback = $form_state['triggering_element']['#ajax']['callback'];
  }
  if (!empty($callback) && function_exists($callback)) {
    return $callback($form, $form_state);
  }
}

/**
 * Override element's ajax settings to add multiform support.
 */
function multiform_ajax_process_form($element, &$form_state) {
  // Get standard settings.
  $element = ajax_process_form($element, $form_state);
  // Override alax callback path and add _multiform_index.
  if (isset($element['#attached']['js'])) {
    // Replace ajax url with multiform specific.
    foreach ($element['#attached']['js'] as $key => $setting) {
      // Invoke hook_multiform_ajax_alter() implementations.
      foreach (module_implements('multiform_ajax_alter') as $module) {
        $function = $module . '_multiform_ajax_alter';
        $function($element, $key, $form_state);
      }
    }
  }
  return $element;
}

/**
 * Implements hook_multiform_ajax_alter().
 */
function multiform_multiform_ajax_alter(&$element, $key, $form_state) {
      $setting = $element['#attached']['js'][$key];
      if (isset($setting['data']['ajax'][$element['#id']]['url']) && $setting['data']['ajax'][$element['#id']]['url'] == '/system/ajax') {
        $element['#attached']['js'][$key]['data']['ajax'][$element['#id']]['url'] = '/multiform/ajax';
        // Add multiform_index in order to define triggering element's subform when triggered.
        if (isset($setting['data']['ajax'][$element['#id']]['submit']) && is_array($setting['data']['ajax'][$element['#id']]['submit'])) {
          $multiform_index = $form_state['multiform_index'];
          $element['#attached']['js'][$key]['data']['ajax'][$element['#id']]['submit']['_multiform_index'] = $multiform_index;
        }
      }  
}
