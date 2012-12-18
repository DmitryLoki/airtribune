<?php

// TODO:
// multiform issue http://drupal.org/node/1785184
/**
 * Menu callback; handles Ajax requests for the #ajax Form API property.
 */
function multiform_ajax_form_callback() {
  // require includes/form.inc (see system_menu() $items['system/ajax'])
  // require_once './includes/form.inc';
  
  module_load_include('inc', 'multiform');
  
  $multiform = array(
    'multiform' => $_POST['multiform'],
    'form_id' => $_POST['form_id'],
    'form_build_id' => $_POST['form_build_id'],
  );
  foreach($multiform as $key => $value) {
    unset($_POST[$key]);
  }
  $_POST += $multiform['multiform']['user_register_form_1'];
  
  
  
  // This part is based on ajax_form_callback().
  list($form, $form_state) = ajax_get_form();
  
  drupal_process_form($form['#form_id'], $form, $form_state);
  $multiform = array();  // custom
  multiform_process_form_state('restore', $form_state);  // custom
  _multiform_delayed_submit_execute($form, $form_state, $form['#form_id'], $multiform);  // custom
  if (!empty($form_state['triggering_element'])) {
    $callback = $form_state['triggering_element']['#ajax']['callback'];
  }
  if (!empty($callback) && function_exists($callback)) {
    return $callback($form, $form_state);
  }
}

// TODO:
function multiform_ajax_process_form($element, &$form_state) {
  $element = ajax_process_form($element, $form_state);
  if (isset($element['#attached']['js'])) {
    // TODO: check multiform_id and complete_form if used
    //$multiform_id = $form_state['multiform_id'];
    //$multiform_index = $form_state['multiform_index'];
    //$form = $form_state['complete_form'];
    
    //dsm($form_state);
    // maybe change $settings['submit']['_triggering_element_value']
    
    // Replace ajax url with multiform specific.
    foreach ($element['#attached']['js'] as $key => $setting) {
      if (isset($setting['data']['ajax'][$element['#id']]['url'])) {
        $element['#attached']['js'][$key]['data']['ajax'][$element['#id']]['url'] = '/multiform/ajax';
      }
    }
    //dsm($element);
  }
  
  return $element;
}

/*
// TODO:
function multiform_ajax_pre_render_element($element) {
  
}
*/
