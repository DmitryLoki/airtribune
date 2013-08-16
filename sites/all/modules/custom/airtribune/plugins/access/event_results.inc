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
  if (empty($context) || empty($context->data) || !($context->data->type == AIRTRIBUNE_PG_CONTEST_TYPE)) {
    return;
  }

  // Event node.
  $node = $context->data;

  $dates_items = field_get_items('node', $node, 'field_dates');
  $results_items = field_get_items('node', $node, 'field_results_summary');

  // 1) Сurrent time > date of event start.
  if (REQUEST_TIME > strtotime($dates_items[0]['value']) &&
    // 2) We have at least one competition day & one task
    $tasks = get_races_ids_for_contest($node)
  ) {
    foreach ($tasks as $task) {
      $current_task = array_pop(entity_load(AIRTRIBUNE_RACE_ENTITY_TYPE, array((string) $task), array(), TRUE));
      $track_item = field_get_items(AIRTRIBUNE_RACE_ENTITY_TYPE, $current_task, 'field_pg_race_tracks');
      $competition_results = field_get_items(AIRTRIBUNE_RACE_ENTITY_TYPE, $current_task, 'field_competition_results');
      // we have task/race with 3)uploaded tracks & 4)competition results
      // then show results tab
      if (count($track_item) && count($competition_results)) {
        return TRUE;
      }
    }
  }

  if (empty($dates_items) || empty($results_items)) {
    return FALSE;
  }

  return strtotime($dates_items[0]['value2']) - 86400 < REQUEST_TIME;
}
