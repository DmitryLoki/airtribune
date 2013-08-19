<?php

// Based on 7.23 version form.inc

// This is a copy of drupal_build_form() with minor difference:
// abc_drupal_process_form() is called instead of drupal_process_form()
// and $unprocessed_form is passed into arguments.
function abc_drupal_build_subform($form_id, &$form_state, &$unprocessed_form) {
  // Ensure some defaults; if already set they will not be overridden.
  $form_state += form_state_defaults();

  if (!isset($form_state['input'])) {
    $form_state['input'] = $form_state['method'] == 'get' ? $_GET : $_POST;
  }

  if (isset($_SESSION['batch_form_state'])) {
    // We've been redirected here after a batch processing. The form has
    // already been processed, but needs to be rebuilt. See _batch_finished().
    $form_state = $_SESSION['batch_form_state'];
    unset($_SESSION['batch_form_state']);
    return drupal_rebuild_form($form_id, $form_state);
  }

  // If the incoming input contains a form_build_id, we'll check the cache for a
  // copy of the form in question. If it's there, we don't have to rebuild the
  // form to proceed. In addition, if there is stored form_state data from a
  // previous step, we'll retrieve it so it can be passed on to the form
  // processing code.
  $check_cache = isset($form_state['input']['form_id']) && $form_state['input']['form_id'] == $form_id && !empty($form_state['input']['form_build_id']);
  if ($check_cache) {
    $form = form_get_cache($form_state['input']['form_build_id'], $form_state);
  }

  // If the previous bit of code didn't result in a populated $form object, we
  // are hitting the form for the first time and we need to build it from
  // scratch.
  if (!isset($form)) {
    // If we attempted to serve the form from cache, uncacheable $form_state
    // keys need to be removed after retrieving and preparing the form, except
    // any that were already set prior to retrieving the form.
    if ($check_cache) {
      $form_state_before_retrieval = $form_state;
    }

    $form = drupal_retrieve_form($form_id, $form_state);
    drupal_prepare_form($form_id, $form, $form_state);

    // form_set_cache() removes uncacheable $form_state keys defined in
    // form_state_keys_no_cache() in order for multi-step forms to work
    // properly. This means that form processing logic for single-step forms
    // using $form_state['cache'] may depend on data stored in those keys
    // during drupal_retrieve_form()/drupal_prepare_form(), but form
    // processing should not depend on whether the form is cached or not, so
    // $form_state is adjusted to match what it would be after a
    // form_set_cache()/form_get_cache() sequence. These exceptions are
    // allowed to survive here:
    // - always_process: Does not make sense in conjunction with form caching
    //   in the first place, since passing form_build_id as a GET parameter is
    //   not desired.
    // - temporary: Any assigned data is expected to survives within the same
    //   page request.
    if ($check_cache) {
      $uncacheable_keys = array_flip(array_diff(form_state_keys_no_cache(), array('always_process', 'temporary')));
      $form_state = array_diff_key($form_state, $uncacheable_keys);
      $form_state += $form_state_before_retrieval;
    }
  }

  // Now that we have a constructed form, process it. This is where:
  // - Element #process functions get called to further refine $form.
  // - User input, if any, gets incorporated in the #value property of the
  //   corresponding elements and into $form_state['values'].
  // - Validation and submission handlers are called.
  // - If this submission is part of a multistep workflow, the form is rebuilt
  //   to contain the information of the next step.
  // - If necessary, the form and form state are cached or re-cached, so that
  //   appropriate information persists to the next page request.
  // All of the handlers in the pipeline receive $form_state by reference and
  // can use it to know or update information about the state of the form.
  $unprocessed_form = abc_drupal_process_form_start($form_id, $form, $form_state);

  // If this was a successful submission of a single-step form or the last step
  // of a multi-step form, then drupal_process_form() issued a redirect to
  // another page, or back to this page, but as a new request. Therefore, if
  // we're here, it means that this is either a form being viewed initially
  // before any user input, or there was a validation error requiring the form
  // to be re-displayed, or we're in a multi-step workflow and need to display
  // the form's next step. In any case, we have what we need in $form, and can
  // return it for rendering.
  return $form;
}



// Modified copy of drupal_process_form() devided into two parts,
// abc_drupal_process_form_start() and abc_drupal_process_form_finish().
function abc_drupal_process_form_start($form_id, &$form, &$form_state) {
  $form_state['values'] = array();

  // With $_GET, these forms are always submitted if requested.
  if ($form_state['method'] == 'get' && !empty($form_state['always_process'])) {
    if (!isset($form_state['input']['form_build_id'])) {
      $form_state['input']['form_build_id'] = $form['#build_id'];
    }
    if (!isset($form_state['input']['form_id'])) {
      $form_state['input']['form_id'] = $form_id;
    }
    if (!isset($form_state['input']['form_token']) && isset($form['#token'])) {
      $form_state['input']['form_token'] = drupal_get_token($form['#token']);
    }
  }

  // form_builder() finishes building the form by calling element #process
  // functions and mapping user input, if any, to #value properties, and also
  // storing the values in $form_state['values']. We need to retain the
  // unprocessed $form in case it needs to be cached.
  $unprocessed_form = $form;
  $form = form_builder($form_id, $form, $form_state);

  // Only process the input if we have a correct form submission.
  if ($form_state['process_input']) {
    drupal_validate_form($form_id, $form, $form_state);
  }
  
  return $unprocessed_form;
}

function abc_drupal_process_form_finish($form_id, &$form, &$form_state, $unprocessed_form) {
  // Only process the input if we have a correct form submission.
  if ($form_state['process_input']) {
    // Form was validated in abc_drupal_process_form_start()
    // drupal_validate_form($form_id, $form, $form_state);

    // drupal_html_id() maintains a cache of element IDs it has seen,
    // so it can prevent duplicates. We want to be sure we reset that
    // cache when a form is processed, so scenarios that result in
    // the form being built behind the scenes and again for the
    // browser don't increment all the element IDs needlessly.
    if (!form_get_errors()) {
      // In case of errors, do not break HTML IDs of other forms.
      drupal_static_reset('drupal_html_id');
    }

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
      if ($batch =& batch_get() && !isset($batch['current_set'])) {
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
      drupal_redirect_form($form_state);
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
