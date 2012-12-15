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
  
  dsm($_POST);
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
    dsm($element);
  }
  
  return $element;
}

/*
// Remove
function multiform_ajax_preprocess(&$form) {
  // TODO: must be executed before pre_render called (see ajax_pre_render_element).
  // Possibly could be done in #after_build.
  
  $form['multiform']['user_register_form_1']['profile_pilot']['field_address']['und'][0]['country']['#ajax']['path'] = 'multiform/ajax';
  unset($form['multiform']['user_register_form_1']['profile_pilot']['field_address']['und'][0]['country']['#ajax']);
  dsm($form);
}
*/

// TODO:
function multiform_ajax_pre_render_element($element) {
  
}
