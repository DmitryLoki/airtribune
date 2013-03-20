<?php

/**
 * @file
 * Admin page callbacks for the GeoIP Language module.
 */

/**
 * Create the overview table of the already existing mappgins
 *
 * @param array $languages
 * @return string
 *  HTML Table
 */
function geoip_language_settings_overview() {
  if (variable_get('language_negotiation', LANGUAGE_NEGOTIATION_NONE) != GEOIP_LANGUAGE_NEGOTIATION_PATH) {
    drupal_set_message(t('The GeoIP settings will have no effect until <em>Language Negotiation</em> is set to <em>Path prefix with GeoIP detection fallback</em> on the <a href="@language-configure">Language configuration page</a>.', array('@language-configure' => url('admin/settings/language/configure'))), 'warning');
  }

  $countries = geoip_country_values();
  $languages = locale_language_list('name', TRUE);
  $mapping = geoip_language_mappings();

  $rows = array();
  foreach ($mapping as $country => $info) {
    $rows[] = array(
      $country,
      $countries[$country],
      $info->language,
      $languages[$info->language],
      l(t('Delete'), 'admin/settings/language/geoip/delete/'. $country, array('query' => drupal_get_destination())),
    );
  }
  if (count($rows)) {
    $header = array(
      array('data' => t('Country'), 'colspan' => 2),
      array('data' => t('Language'), 'colspan' => 2),
      t('Operations'),
    );
    $output .= theme('table', $header, $rows);
  }
  else {
    drupal_set_message(t('No GeoIP language mappings defined.'));
  }

  $output .= drupal_get_form('geoip_language_settings_form');
  return $output;
}

/**
 * FAPI callback for creating a new country-language mapping.
 *
 * @return array
 */
function geoip_language_settings_form() {
  $countries = geoip_country_values();
  $mapping = geoip_language_mappings();
  $options = array();
  foreach ($countries as $key => $value) {
    if (!$mapping[$key]) {
      $options[$key] = "$key - $value";
    }
  }

  $form['new'] = array(
    '#type' => 'fieldset',
    '#title' => t('New mapping'),
    '#tree' => 0,
  );
  $form['new']['country'] = array(
    '#type' => 'select',
    '#title' => t('Detected country'),
    '#options' => $options,
  );
  $form['new']['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => locale_language_list('name', TRUE),
  );

  $form['new']['buttons'] = array();
  $form['new']['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add mapping'),
  );

  return $form;
}

/**
 * FAPI submit handler.
 */
function geoip_language_settings_form_submit($form, &$form_state) {
  geoip_language_mapping_create($form_state['values']['country'], $form_state['values']['language']);

  $countries = geoip_country_values();
  drupal_set_message(t('GeoIP mapping created for %country.', array('%country' => $countries[$form_state['values']['country']])));

  $form_state['redirect'] = 'admin/settings/language/geoip';
}

/**
 * Create the confirmmation form for deleting a mapping item.
 */
function geoip_admin_delete_mapping(&$form_state, $country) {
  $form['country'] = array(
    '#type' => 'value',
    '#value' => $country,
  );

  return confirm_form($form,
    t('Are you sure you want to delete this mapping?'),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/language/geoip',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Process a confirmed delete request of a mapping item.
 */
function geoip_admin_delete_mapping_submit($form, &$form_state) {
  geoip_language_mapping_delete($form_state['values']['country']);

  $countries = geoip_country_values();
  drupal_set_message(t('GeoIP mapping deleted for %country.', array('%country' => $countries[$form_state['values']['country']])));

  $form_state['redirect'] = 'admin/settings/language/geoip';
}