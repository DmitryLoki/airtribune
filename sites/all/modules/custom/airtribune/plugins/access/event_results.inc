<?php

/**
 * @file
 * Plugin to provide access control based upon event results.
 */

// Plugin defenition.
$plugin = array(
  'title' => t('Event results'),
  'description' => t('Check whether event results is ready.'),
  'callback' => 'airtribune_event_results_access_check',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Check for access.
 */
function airtribune_event_results_access_check($conf, $context) {

  // There should always be a context at this point, but this is safe.
  if (empty($context) || empty($context->data) || !($context->data->type == AIRTRIBUNE_PG_CONTEST_TYPE )) {
    return;
  }

  // Event node.
  $node = $context->data;
  
  $dates_items = field_get_items('node', $node, 'field_dates');
  $results_items = field_get_items('node', $node, 'field_results_summary');

  if (empty($dates_items) || empty($results_items)) {
    return FALSE;
  }

  return strtotime($dates_items[0]['value2']) < REQUEST_TIME;
}
