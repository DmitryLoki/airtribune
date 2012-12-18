<?php

/**
 * Initialize $multiform array.
 */
function multiform_init_multiform_settings($all_args) {
  $multiform = array();
  $count = count($all_args);
  // Check for multiform_settings.
  if ($count > 0 && is_array($all_args[$count-1])) {
    $multiform_candidate = $all_args[$count-1];
    foreach ($multiform_candidate as $key => $value) {
      // Check for settings keys. Settings keys start with # sign.
      if (strpos($key, '#') === 0) {
        // Remove multiform settings.
        $multiform = array_pop($all_args);
        break;
      }
    }
    unset($key);
  }
  if (!isset($multiform['#subforms'])) {
    $multiform['#subforms'] = array();
  }
  // Move all subforms into $multiform
  $subforms = array();
  $max_key = 0;
  foreach ($all_args as $key => $args) {
    $form_id = array_shift($args);
    $subforms[$form_id . '_' . $key] = array(
      'key' => $key,
      'form_id' => $form_id,
      'args' => $args,
      '#weight' => $key,
    );
  }
  $next_key = isset($key) ? $key+1 : 0;
  // Check for additional subforms in $multiform.
  if (!empty($multiform['#subforms'])) {
    foreach ($multiform['#subforms'] as $subform) {
      $index = $subform['form_id'] . '_' . $next_key;
      $subform['key'] = $next_key;
      $subform['#weight'] = $next_key;
      $subform['args'] = !empty($subform['args']) ? $subform['args'] : array();
      $subforms[$index] = $subform;
      $next_key++;
    }
  }
  $multiform['#subforms'] = $subforms;
  
  // Set settings' defaults.
  // TODO: work out redirection functionality.
  $defaults = array(
    '#redirect' => FALSE,  // For internal use only
    '#redirect_array' => array(),  // For internal use only (by now)
    '#multiform_id' => DEFAULT_MULTIFORM_ID,
    '#submitted' => FALSE,
  );
  foreach ($defaults as $key => $value) {
    if (!isset($multiform[$key])) $multiform[$key] = $value;
  }
  
  return $multiform;
}

/**
 * Change and Restore some $form_state values in order to avoid submit and other operations
 * that follow validation in drupal_process_form(). This allows to perform all subforms validation
 * before any submit is fired. Afterwards, restore form_state to pass into further workflow.
 * 
 * $op = {'modify', 'restore'}
 */
// TODO: Check over $new_values array().
function multiform_process_form_state($op, &$form_state) {
  switch($op) {
    // Used in auxilary validation to prevent submit handlers execution.
    case 'modify' :
      $changed = array();
      // Force caching after validation
      // since we need $unprocessed_form for _multiform_execute_delayed_submit().
      // But prevent other operations' execution.
      $new_values = array(
        'submitted' => FALSE,
        'executed' => TRUE,
        'rebuild' => FALSE,
        'cache' => TRUE,
        'no_cache' => 'unset',
      );
      foreach($new_values as $key => $value) {
        $changed[$key] = isset($form_state[$key]) ? $form_state[$key] : 'unset';
        if($value !== 'unset') {
          $form_state[$key] = $value;
        } else {
          unset($form_state[$key]);
        }
      }
      // Changed values will be restored after validation.
      $form_state['#restore_values'] = $changed;
      break;
    case 'restore' :
      if(isset($form_state['#restore_values'])) {
        foreach($form_state['#restore_values'] as $key => $value) {
          if($value !== 'unset') {
            $form_state[$key] = $value;
          } else {
            unset($form_state[$key]);
          }
        }
        // Keep $form_state clean as possible.
        unset($form_state['#restore_values']);
      }
      break;
  }
}

/**
 * Restore actual $form_state data
 * and cache $form and $form_state for further delayed submit execution.
 * 
 */
function multiform_delayed_submit_prepare(&$multiform, $current_form, &$form_state, $index) {
  $index = $form_state['multiform_index'];
  // IF #restore_values isn't set, it means that there is no delayed validation
  // or validation hasn't worked out, i.e. form is built for rendering.
  if (isset($form_state['#restore_values'])) {
    // form_state values of any of the forms could only be modified if form was submitted.
    $multiform['#submitted'] = TRUE;
    // Restore $form_state['submitted'] (and possibly other values) from form_state['#restore_values'].
    // See multiform_delay_form_submitting_validate().
    multiform_process_form_state('restore', $form_state);
    $multiform['#subforms'][$index]['form'] = $current_form;
    $multiform['#subforms'][$index]['form_state'] = $form_state;
  }
}

// TODO: Add capability to alter redirect behavior via hook_multiform_alter().

/**
 * Invoke hook_multiform_alter() implementations and execute forms' handlers.
 * 
 */
function multiform_delayed_submit_execute(&$multiform) {
  // Only execute when form was submitted.
  if ($multiform['#submitted']) {
    // Invoke hook_multiform_alter(&$multiform).
    // It can be used to change exectution order or to pass results of one form processing
    // into another form via changing $multiform['#subforms'][$index]['form_state'].
    foreach (module_implements('multiform_alter') as $module) {
      $function = $module . '_multiform_alter';
      $function($multiform);
    }
    
    // Sort by #weight to change forms' execution order.
    uasort($multiform['#subforms'], 'element_sort');
    
    // Perform form submitting. This is central place where processing takes place.
    $subforms = $multiform['#subforms'];
    foreach ($subforms as $index => $data) {
      $hooks = array(
        '#before_execute' => isset($multiform['#subforms'][$index]['#before_execute'])
                              ? $multiform['#subforms'][$index]['#before_execute']
                              : array(),
        '#after_execute' => isset($multiform['#subforms'][$index]['#after_execute'])
                              ? $multiform['#subforms'][$index]['#after_execute']
                              : array(),
      );
      // Invoke #before_execute functions for each form before it is submitted.
      // We apply hooks to initial multiform_settings array, so changes could be used further.
      foreach ($hooks['#before_execute'] as $function) {
        $function($multiform, $index);
      }
      
      // We use here multiform_settings['#subforms'][$index] instead of $data
      // because it could be changed in hooks (in case hooks use it by reference).
      $subform_data = $multiform['#subforms'][$index];
      $form = $subform_data['form'];
      $form_state = $subform_data['form_state'];
      $form_id = $subform_data['form_id'];
      
      // Execute submit handlers.
      _multiform_delayed_submit_execute($form, $form_state, $form_id, $multiform);
      // Store submit results in order to use them in #after_execute hooks.
      // Usually only $form_state is changed in submit handelers.
      $multiform['#subforms'][$index]['form'] = $form;
      $multiform['#subforms'][$index]['form_state'] = $form_state;
      
      // Invoke #after_execute functions for each form before it is submitted.
      if($form_state['executed'] == TRUE) {
        foreach ($hooks['#after_execute'] as $function) {
          $function($multiform, $index);
        }
      }
    }
  }
}

// TODO: Remove cached form if needed (see validation).

/**
 * This is a copy of part of the code from drupal_process_form(),
 * needed to execute delayed submit.
 */
function _multiform_delayed_submit_execute(&$form, &$form_state, $form_id, &$multiform) {
    // Cache must exist since we forced it.
    $unprocessed_form = cache_get('form_' . $form['#build_id'], 'cache_form');
    $unprocessed_form = $unprocessed_form->data;
    // TODO: Maybe cache should be removed.
    /*
    cache_clear_all('form_' . $form['#build_id'], 'cache_form');
    cache_clear_all('form_state_' . $form['#build_id'], 'cache_form');
    */
    
    if ($form_state['submitted'] && !form_get_errors() && !$form_state['rebuild']) {
      // Execute form submit handlers.
      form_execute_handlers('submit', $form, $form_state);

      // We'll clear out the cached copies of the form and its stored data
      // here, as we've finished with them. The in-memory copies are still
      // here, though.
      if (!variable_get('cache', 0) && !empty($form_state['values']['form_build_id'])) {
        cache_clear_all('form_' . $form_state['values']['form_build_id'], 'cache_form');
        cache_clear_all('form_state_' . $form_state['values']['form_build_id'], 'cache_form');
      }

      // If batches were set in the submit handlers, we process them now,
      // possibly ending execution. We make sure we do not react to the batch
      // that is already being processed (if a batch operation performs a
      // drupal_form_submit).
      if ($batch = & batch_get() && !isset($batch['current_set'])) {
        // Store $form_state information in the batch definition.
        // We need the full $form_state when either:
        // - Some submit handlers were saved to be called during batch
        //   processing. See form_execute_handlers().
        // - The form is multistep.
        // In other cases, we only need the information expected by
        // drupal_redirect_form().
        if ($batch['has_form_submits'] || !empty($form_state['rebuild'])) {
          $batch['form_state'] = $form_state;
        }
        else {
          $batch['form_state'] = array_intersect_key($form_state, array_flip(array('programmed', 'rebuild', 'storage', 'no_redirect', 'redirect')));
        }

        $batch['progressive'] = !$form_state['programmed'];
        batch_process();

        // Execution continues only for programmatic forms.
        // For 'regular' forms, we get redirected to the batch processing
        // page. Form redirection will be handled in _batch_finished(),
        // after the batch is processed.
      }

      // Set a flag to indicate the the form has been processed and executed.
      $form_state['executed'] = TRUE;

      // Redirect the form based on values in $form_state.
      // drupal_redirect_form($form_state);
      $multiform['#redirect'] = TRUE;
    }

    // Don't rebuild or cache form submissions invoked via drupal_form_submit().
    if (!empty($form_state['programmed'])) {
      return;
    }

    // If $form_state['rebuild'] has been set and input has been processed
    // without validation errors, we are in a multi-step workflow that is not
    // yet complete. A new $form needs to be constructed based on the changes
    // made to $form_state during this request. Normally, a submit handler sets
    // $form_state['rebuild'] if a fully executed form requires another step.
    // However, for forms that have not been fully executed (e.g., Ajax
    // submissions triggered by non-buttons), there is no submit handler to set
    // $form_state['rebuild']. It would not make sense to redisplay the
    // identical form without an error for the user to correct, so we also
    // rebuild error-free non-executed forms, regardless of
    // $form_state['rebuild'].
    // @todo D8: Simplify this logic; considering Ajax and non-HTML front-ends,
//   along with element-level #submit properties, it makes no sense to have
//   divergent form execution based on whether the triggering element has
//   #executes_submit_callback set to TRUE.
    if (($form_state['rebuild'] || !$form_state['executed']) && !form_get_errors()) {
      // Form building functions (e.g., _form_builder_handle_input_element())
      // may use $form_state['rebuild'] to determine if they are running in the
      // context of a rebuild, so ensure it is set.
      $form_state['rebuild'] = TRUE;
      $form = drupal_rebuild_form($form_id, $form_state, $form);
    }
  

  // After processing the form, the form builder or a #process callback may
  // have set $form_state['cache'] to indicate that the form and form state
  // shall be cached. But the form may only be cached if the 'no_cache' property
  // is not set to TRUE. Only cache $form as it was prior to form_builder(),
  // because form_builder() must run for each request to accommodate new user
  // input. Rebuilt forms are not cached here, because drupal_rebuild_form()
  // already takes care of that.
  if (!$form_state['rebuild'] && $form_state['cache'] && empty($form_state['no_cache'])) {
    form_set_cache($form['#build_id'], $unprocessed_form, $form_state);
  }
}

/**
 * Return subform index by tag
 */
function multiform_get_index_by_tag($multiform, $tag, $multiple = FALSE) {
  $indices = array();
  foreach ($multiform['#subforms'] as $index => $subform) {
    if (isset($subform['#tag']) && $subform['#tag'] == $tag) {
      $indices[] = $index;
    }
  }
  if (empty($indices)) {
    return FALSE;  
  }
  else {
    return !$multiple ? $indices[0] : $indices;
  }
}
