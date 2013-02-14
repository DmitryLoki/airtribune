<?php

/**
 * @file
 * Airtribune HQ distance pane plugin.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune HQ distance'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune HQ distance pane.
 */
function airtribune_hq_distance_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE || !is_numeric($panel_args[1])) {
    return;
  }

  $wrapper = entity_metadata_wrapper('node', $context->data);
  if ($wrapper->value() ) {
    $hq_location = $wrapper->field_hq_location->value();
    if ($hq_location) {
      $hq_location_latlon = array($hq_location['lon'], $hq_location['lat']);
    }
  }

  $wrapper = entity_metadata_wrapper('node', $panel_args[1]);
  $location_types = array(AIRTRIBUNE_ACCOMMODATION_TYPE, AIRTRIBUNE_ACTIVITY_TYPE);
  if ($wrapper->value() && in_array($wrapper->getBundle(), $location_types)) {
    $location = $wrapper->field_location->value();
    if ($location) {
      $location_latlon = array($location['lon'], $location['lat']);
    }
  }

  if (isset($hq_location_latlon, $location_latlon)) {
    $distance = airtribune_calculate_distance($hq_location_latlon, $location_latlon);
    $content = t('HQ Distance !distance km', array('!distance' => '<span class="hq-distance">' . round($distance/1000, 2) . '</span>'));

    return (object) array(
      'module' => 'airtribune',
      'content' => $content,
      'delta' => 1,
    );
  }
  else {
    // TODO Add watchdog message here.
  }

}

/**
 * Panels module needs this empty form.
 */
function airtribune_hq_distance_content_type_edit_form($form, &$form_state) {
  return $form;
}
