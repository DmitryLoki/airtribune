<?php

/**
 * @file
 * Airtribune event statisitics pane plugin.
 *
 * @see #2544.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune event statistics'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune event title pane.
 */
function airtribune_airtribune_event_statistics_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_statistics';

  // Event node.
  $node = $context->data;

  $content = array(
    '#theme' => 'airtribune_event_statistics_pane',
    '#attached' => array('css' => array($plugin_path . '/airtribune_event_statistics.css')),
  );

  try {
    // Count contest pilots.
    $query = db_select('users', 'u');
    $query->join('og_membership', 'ogm', 'u.uid = ogm.etid');
    $query->join('field_data_' . AIRTRIBUNE_PG_CONTESTANT_STATUS_FIELD, 'pc_status', 'pc_status.entity_id = ogm.id');
    $query
      ->condition('u.status', 0, '<>')
      ->condition('ogm.gid', $node->nid);
    $total_pilots = $query->countQuery()->execute()->fetchField();
    $query->condition('pc_status.' . AIRTRIBUNE_PG_CONTESTANT_STATUS_FIELD . '_value', AIRTRIBUNE_PG_CONTESTANT_CONFIRMED);

    $content['pilots_confirmed'] = $query->countQuery()->execute()->fetchField();
    $content['pilots_waiting'] = $total_pilots - $content['pilots_confirmed'];

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
        ':distance' => 100000,
      ));
      $content['accommodation'] = $result->fetchField();

      // Count contest activities.
      $result = db_query($sql, array(
        ':bundle' => 'activity',
        ':lat' => $location['lat'],
        ':lon' => $location['lon'],
        ':distance' => 30000,
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

  $content['pilots_list_link'] = l(t('View pilot list'), 'event/' . $node->nid . '/pilots');
  $content['event_map_link'] = l(t('View event map'), 'event/' . $node->nid . '/map');

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_event_statistics_content_type_edit_form($form, &$form_state) {
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
}
