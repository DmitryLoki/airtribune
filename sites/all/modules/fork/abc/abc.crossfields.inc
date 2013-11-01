<?php

// TODO:
// Store $multiform in cache to attach to form_state when ajax used. Use multiform form_build_id
// Attach $multiform to form_state in multiform_get_form when ajax is not used
// So there will be no difference among ajax and non-ajax forms
// We can't attach it to $form because of drupal_rebuild_form().

// TODO: This currently doesn't work with ajax forms.
// TODO: store tag in $form_state for ajax forms.

// TODO:
/**
 * Collects crossfields data for a given multiform.
 * 
 */
function abc_crossfields_info($multiform) {
  static $stored_info = array();
  
  
  if (!isset($stored_info[$multiform['#multiform_id']])) {
    $stored_info[$multiform['#multiform_id']] = array();
    
    // Invoke hook_multiform_crossfields()
    // Modules should return only items for a given multiform_id
    $items = module_invoke_all('multiform_crossfields', $multiform);
    //~ return $items;
    foreach ($items as $item) {
      // TODO:
      //~ $base_index = multiform_get_index_by_tag($multiform, $item['#base']['#tag']);
      $base_index = $item['#base']['#tag'];
      //~ $dependent_index = multiform_get_index_by_tag($multiform, $item['#dependent']['#tag']);
      $dependent_index = $item['#dependent']['#tag'];
      if($base_index && $dependent_index) {
        $item['#base']['#index'] = $base_index;
        $item['#dependent']['#index'] = $dependent_index;
        $stored_info[$multiform['#multiform_id']][] = $item;
      }
    }
    //multiform_crossfields_check($stored_info);
    
  }
  
  return $stored_info;
}

// TODO:
/**
 * Set values for crossfields based on $_POST array.
 */
function abc_crossfields_set_post_values($multiform, $crossfields_info) {
  if (!empty($_POST) && isset($multiform['#multiform_id']) && isset($crossfields_info[$multiform['#multiform_id']])) {
    //~ print_r($_POST);
    $multiform_id = $multiform['#multiform_id'];
    foreach ($crossfields_info[$multiform_id] as $item) {
      // Get array path to the element in $_POST.
      $parents_base = $item['#base']['#parents'];
      array_unshift($parents_base, 'multiform', $item['#base']['#index']);
      //~ print_r($parents_base);
      // Get base value
      $key_exists = NULL;
      $value = drupal_array_get_nested_value($_POST, $parents_base, $key_exists);
      // If base key exist in $_POST array, set dependent value.
      if ($key_exists) {
        $parents_dependent = $item['#dependent']['#parents'];
        array_unshift($parents_dependent, 'multiform', $item['#dependent']['#index']);
        drupal_array_set_nested_value($_POST, $parents_dependent, $value, TRUE);
      }
    }
  }
}

// TODO: Check ajax forms
// Remove validation error messages for hidden fields
function abc_crossfields_hide_elements($multiform, $crossfields_info, &$form, $form_state) {
  if (isset($form_state['#subform_index'])) {
    $multiform_id = $multiform['#multiform_id'];
    $subform_index = $form_state['#subform_index'];
    if (isset($crossfields_info[$multiform_id])) {
      foreach ($crossfields_info[$multiform_id] as $item) {
        if ($item['#dependent']['#index'] == $subform_index) {
          $array_parents_dependent = $item['#dependent']['#array_parents'];
          if (drupal_array_nested_key_exists($form, $array_parents_dependent)) {
            array_push($array_parents_dependent, '#pre_render');
            $pre_render = drupal_array_get_nested_value($form, $array_parents_dependent);
            if (is_array($pre_render)) {
              $pre_render[] = 'multiform_crossfields_pre_render';
            }
            else {
              $pre_render = array('multiform_crossfields_pre_render');
            }
            drupal_array_set_nested_value($form, $array_parents_dependent, $pre_render, TRUE);
          }
        }
      }
    }
  }
  
  //$form['#after_build'][] = 'at_reg_hide_intersections_after_build';
  // for ajax requests store multiform_data in cache
  // pass into form_state
}

// TODO:
function multiform_crossfields_pre_render($element) {
  $element['#printed'] = TRUE;
  return $element;
}
/*




// TODO:
function multiform_crossfields_check($stored_info) {
  
}


// Hook implementation example.
// hook_multiform_crossfields($multiform_id)
function hook_multiform_crossfields($multiform_id) {
  
  $items = array();
  if ($multiform_id == 'my_custom_multiform_id') {
    // Crossfields are supposed to be different instances of the same field.
    $items['base_entity_1']['dependent_entity_1']['field_name'] = array(
      // Subforms must be different.
      'base_subform_index' => 'index1',
      'dependent_subform_index' => 'index2',
    );
    
    'base_subform_index' => array(
      'base_field_1' => array(
      
      ),
    ),
  }
  return $items;
  
  $lang
}

*/
