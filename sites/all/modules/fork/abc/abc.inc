<?php

// TODO:
function abc_init_form() {
  $form = element_info('form');
  return $form;
}

// TODO: Include abc_submits_form() only if submits map is declared.
function abc_init_settings(&$settings) {
  
  $settings += array(
    '#multiform_id' => DEFAULT_MULTIFORM_ID,
  );
  
  $submits_form = array(
    'form_id' => 'abc_submits_form',
    'args' => array($settings),
  );
  
  // Add submits_form to subforms array.
  //~ array_unshift($settings['#subforms'], $submits_form);
  // TODO: Add to the end of subforms list.
  array_push($settings['#subforms'], $submits_form);
  //~ dsm($settings);
  
  foreach ($settings['#subforms'] as $k => $subform) {
    $settings['#subforms'][$k] += array(
      'args' => array(),
      '#before_execute' => array(),
      '#after_execute' => array(),
      '#preprocess_form_state' => array(),
    );
  }
}

// TODO:
function abc_submits_form($form, $form_state, $settings) {
  $form = array();
  if (!empty($settings['#submit_map']['#submits'])) {
    foreach ($settings['#submit_map']['#submits'] as $k => $info) {
      $form[$k] = $info;
    }
  }
  
  return $form;
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

function abc_preprocess_form_state(&$form_state, $subform) {
  foreach ($subform['#preprocess_form_state'] as $function) {
    $function($form_state);
  }
}

// TODO:
// We don't want to execute submits subform's submits
// so exclude posted data (if any) before building subforms.
// Cached settings could be use instead of $settings.
function abc_preprocess_post(&$post, $settings) {
  if (isset($post['multiform']['abc_submits_form'])) {
    // TODO: Why name is 'op'?
    if (!empty($post['multiform']['abc_submits_form']['op'])) {
      
      // TODO: Security issue. Check that key exists.
      if (empty($post['multiform_seettings_build_id'])) {
        return;
      }
      
      $multiform_seettings_build_id = $post['multiform_seettings_build_id'];
      $cache = cache_get($multiform_seettings_build_id, 'cache');
      
      if (empty($cache)) {
        return;
      }
      
      $cached_settings = $cache->data;
      
      
      // #name of auxiliary submit.
      $name = $post['multiform']['abc_submits_form']['op'];
      
      // Identify array key of the triggering submit, if any.
      foreach ($settings['#submit_map']['#submits'] as $k => $data) {
        if ($name == $data['#value']) {
          $key = $k;
          break;
        }
      }
      
      if (!empty($key)) {
        foreach ($settings['#subforms'] as $k => $data) {
          if (!empty($data['#map'])) {
            $form_id = $data['form_id'];
            foreach ($data['#map'] as $m => $map) {
              if (in_array($key, $map['#triggering_submit'])) {
                $parents = $map['#parents'];
                if (!empty($cached_settings['#subforms'][$k]['#map'][$m]['#element'])) {
                  $element = $cached_settings['#subforms'][$k]['#map'][$m]['#element'];
                  
                  // Set mapped submit's value.
                  $post['multiform'][$form_id][$element['#name']] = $element['#value'];
                }
              }
            }
          }
        }
      }
      

    }
  
    // TODO: Always unset this subform.
    unset($post['multiform']['abc_submits_form']);
  }
}

// TODO:
// Cache only if submits map is not empty.
// Hide mapped submits.
function abc_cache_prepare($build_id_hash, $settings, &$multiform_form) {
  // TODO:
  $cache = array();
  
  // Actually we don't need to cache settings itself.
  $cache['settings'] = array($settings);
  
  
  
  // Prepare cache only in case submits map is set.
  
  $form_keys = array();
  // TODO: Skip submits_map subform
  foreach ($multiform_form['multiform'] as $k => $subform) {
    $form_id = $subform['#form_id'];
    if ($form_id != 'abc_submits_form') {
      $form_keys[$form_id] = $k;
    }
  }
  
  foreach ($settings['#subforms'] as $k => $subform) {
    if (!empty($subform['#map']) && isset($form_keys[$subform['form_id']])) {
      $form_key = $form_keys[$subform['form_id']];
      foreach ($subform['#map'] as $m => $map) {
        $key_exists = FALSE;
        $form_key = $form_keys[$subform['form_id']];
        $element = drupal_array_get_nested_value($multiform_form['multiform'][$form_key], $map['#parents'], $key_exists);
        if ($key_exists) {
          // TODO:
          // Remove multiform #name prefix.
          //~ $element['#name'] = str_replace("multiform[{$subform['form_id']}]", $subform['form_id'], $element['#name']);
          $element['#name'] = 'op';
          $settings['#subforms'][$k]['#map'][$m]['#element'] = $element;
          
          // Hide mapped submit.
          drupal_array_set_nested_value($multiform_form['multiform'][$form_key], array_merge($map['#parents'], array('#printed')), TRUE, TRUE);
        }
      }
    }
  }
  
  // TODO: Check if cache is already set.
  // Set cache.
  cache_set('multiform_settings-' . $build_id_hash, $settings, 'cache', CACHE_TEMPORARY);
}

// TODO:
function abc_cache_get($id) {
  // TODO:
}

// TODO:
// #1
// If a form contains a single textfield, and the ENTER key is pressed
// within it, Internet Explorer submits the form with no POST data...
// https://api.drupal.org/api/drupal/includes%21form.inc/function/form_builder/7
// I.e. we should thing about first button for a subform
