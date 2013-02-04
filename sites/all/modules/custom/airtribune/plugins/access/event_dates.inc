<?php

/**
 * @file
 * Plugin to provide access control based upon event dates.
 */

// Plugin defenition.
$plugin = array(
  'title' => t('Event dates'),
  'description' => t('Control access by node dates.'),
  'callback' => 'airtribune_event_dates_access_check',
  'default' => array(),
  'settings form' => 'airtribune_event_dates_access_settings',
  'summary' => 'airtribune_event_dates_access_check_access_summary',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Settings form for the event dates access plugin.
 */
function airtribune_event_dates_access_settings($form, &$form_state, $conf) {
  $form['settings']['status'] = array(
    '#title' => t('Event status'),
    '#type' => 'radios',
    '#options' => array(
      'past' => t('Past event'),
      'current' => t('Current event'),
      'next' => t('Next event'),
    ),
    '#default_value' => $conf['status'],
  );
  return $form;
}

/**
 * Check for access.
 */
function airtribune_event_dates_access_check($conf, $context) {
  // There should always be a context at this point, but this is safe.
  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }

  // Event node.
  $node = $context->data;

  $dates_items = field_get_items('node', $node, AIRTRIBUNE_DATES_FIELD);
  if (isset($dates_items[0]['value'], $dates_items[0]['value2'])) {
    $value_1 = strtotime($dates_items[0]['value']);
    $value_2 = strtotime($dates_items[0]['value2']);
    $status = $value_2 < REQUEST_TIME ? 'past' : ($value_1 > REQUEST_TIME ? 'next' : 'current');
    $access = $status == $conf['status'];
  }
  else {
    // Event node without dates?
    $access = FALSE;
  }

  return $access;
}

/**
 * Provide a summary description based upon the checked event status.
 */
function airtribune_event_dates_access_check_access_summary($conf, $context) {
  return t('@identifier is a @status event', array('@identifier' => $context->identifier, '@status' => $conf['status']));
}