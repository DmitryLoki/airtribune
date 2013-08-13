<?php

/**
 * @file
 * Event statisitics pane plugin.
 *
 * @see #2544.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Event statistics'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render event statisics pane.
 */
function airtribune_event_statistics_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }


  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/event_statistics';

  // Event node.
  $node = $context->data;

  $content = array(
    '#theme' => 'airtribune_event_statistics_pane',
    '#attached' => array('css' => array($plugin_path . '/event_statistics.css')),
  );

  try {
    $content['pilots_waiting'] = airtribune_count_pilots($node->nid);
    $content['pilots_confirmed'] = airtribune_count_pilots($node->nid, AIRTRIBUNE_PG_CONTESTANT_CONFIRMED);
    $wrapper = entity_metadata_wrapper('node', $node);
    $location = $wrapper->{AIRTRIBUNE_HQ_LOCATION_FIELD}->value();
    if ($location) {
      // TODO: Do not count unpublished nodes.
      $location_table = 'field_data_' . AIRTRIBUNE_LOCATION_FIELD;
      $sql = "SELECT COUNT(*) FROM $location_table location WHERE bundle = :bundle AND
      ST_Distance(ST_Point(location.field_location_lon, field_location_lat)::geography, ST_Point(:lon, :lat)::geography) < :distance";

      // Count contest accomodation.
      $result = db_query($sql, array(
        ':bundle' => 'accommodation',
        ':lat' => $location['lat'],
        ':lon' => $location['lon'],
        ':distance' => 30000,
      ));
      $content['accommodation'] = $result->fetchField();

      // Count contest activities.
      $result = db_query($sql, array(
        ':bundle' => 'activity',
        ':lat' => $location['lat'],
        ':lon' => $location['lon'],
        ':distance' => 100000,
      ));
      $content['activities']  = $result->fetchField();
    }
    else {
      throw new Exception(t('Cannot load HQ location field.'));
    }
  }
  catch (Exception $e) {
    watchdog('airtribune', 'Event statistics failed: %message', array('%message' => $e->getMessage()), WATCHDOG_ERROR);
    return;
  }

  $content['#event_id'] = $node->nid;

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_event_statistics_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Process variables for airtribune-event-statistics-pane.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see airtribune-event-statistics-pane.tpl.php
 * @see theme_airtribune_event_statistics()
 */
function template_preprocess_airtribune_event_statistics_pane(&$vars) {
  $elements = $vars['elements'];

  $vars['pilots_url'] = 'event/' . $elements['#event_id'] . '/pilots';
  $vars['places_url'] = 'event/' . $elements['#event_id'] . '/map';

  $pilots_confirmed = array(
    '#theme' => 'airtribune_event_statistics',
    '#count' => $elements['pilots_confirmed'],
    '#text_1' => str_replace($elements['pilots_confirmed'], '', format_plural($elements['pilots_confirmed'], 'Pilot', '@count Pilots')),
    '#text_2' => t('Confirmed'),
    '#attributes' => array('class' => 'es-pilots-confirmed'),
    '#url' => $vars['pilots_url'],
  );
  $vars['pilots_confirmed'] = render($pilots_confirmed);

  $pilots_waiting = array(
    '#theme' => 'airtribune_event_statistics',
    '#count' => $elements['pilots_waiting'],
    '#text_1' => str_replace($elements['pilots_waiting'], '', format_plural($elements['pilots_waiting'], 'Pilot', '@count Pilots')),
    '#text_2' => t('total registered'),
    '#attributes' => array('class' => 'es-pilots-waiting'),
    '#url' => $vars['pilots_url'],
  );
  $vars['pilots_waiting'] = render($pilots_waiting);

  $accommodation = array(
    '#theme' => 'airtribune_event_statistics',
    '#count' => $elements['accommodation'],
    '#text_1' => t('Accommodation', array(), array('context' => 'event-statistics')),
    '#text_2' => t('places'),
    '#attributes' => array('class' => 'es-accommodation'),
    '#url' => $vars['places_url'],
  );
  $vars['accommodation'] = render($accommodation);

  $activities = array(
    '#theme' => 'airtribune_event_statistics',
    '#count' => $elements['activities'],
    '#text_1' => t('Activities', array(), array('context' => 'event-statistics')),
    '#text_2' => t('places'),
    '#attributes' => array('class' => 'es-activities'),
    '#url' => $vars['places_url'] . '/activities',
  );

  $vars['activities'] = render($activities);

}
