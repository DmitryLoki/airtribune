<?php
/**
 * @file
 *  Adds features support when exporting contexts that use 
 *  the masquerade_context condition.
 */

/**
 * Implements hook_features_pipe_COMPONENT_alter().
 *
 * Alters the processing of a features component before it is exported.
 * This is useful for adding dependencies or updating exportable data.
 *
 * @see hook_features_pipe_COMPONENT_alter()
 * @see context_load()
 */
function masquerade_context_features_pipe_context_alter(&$pipe, $data, &$export) {
  // Scan over each selected context.
  foreach ($data as $machine_name) {
    // If other components in this feature already depend on masquerade_context,
    // just skip ahead. We don't need to scan over this multiple times.
    if (in_array('masquerade_context', $export['dependencies'])) {
      return;
    }

    // Try to load the context so we can see what components it is using.
    // If the "masquerade_is_masquerading" condition is in use, add
    // this module as a dependency.
    if ($context = context_load($machine_name)) {
      if (in_array('masquerade_context', array_keys($context->conditions))) {
        $export['dependencies'][] = 'masquerade_context';
      }
    }
  }
}
