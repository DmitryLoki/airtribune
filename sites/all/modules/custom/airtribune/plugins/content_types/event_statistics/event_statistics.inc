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

    $view = views_get_view('paragliding_pilots_list');
    $view->set_arguments(array($node->nid));
    $view->execute();
    $content['pilots_waiting'] = count($view->result);

    $view = views_get_view('paragliding_pilots_list');
    $view->set_arguments(array($node->nid));
    $view->display['default']->display_options['filters'][AIRTRIBUNE_PG_CONTESTANT_STATUS_FIELD . '_value']['value'] = array(AIRTRIBUNE_PG_CONTESTANT_CONFIRMED);
    $view->execute();
    $content['pilots_confirmed'] = count($view->result);

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
 */
function template_preprocess_airtribune_event_statistics_pane(&$vars) {
  foreach (element_children($vars['elements']) as $key) {
    $vars[$key] = render($vars['elements'][$key]);
  }

  $vars['pilots_url'] = 'event/' . $vars['elements']['#event_id'] . '/pilots';
  $vars['map_url'] = 'event/' . $vars['elements']['#event_id'] . '/map';

  $vars['pilots_confirmed_link'] = l(str_replace($vars['pilots_confirmed'], '', format_plural($vars['pilots_confirmed'], 'Pilot', '@count Pilots')), $vars['pilots_url']);
  $vars['pilots_waiting_link'] = l(str_replace($vars['pilots_waiting'], '', format_plural($vars['pilots_waiting'], 'Pilot', '@count Pilots')), $vars['pilots_url']);

}
