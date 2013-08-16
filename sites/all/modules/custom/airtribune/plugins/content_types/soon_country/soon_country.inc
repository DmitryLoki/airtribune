<?php

/**
 * @file
 * Airtribune 'Soon in country' pane plugin.
 *
 * @see #3543.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Soon in country'),
  'single' => TRUE,
  'category' => array('Airtribune'),

);

/**
 * Render event title pane.
 */
function airtribune_soon_country_content_type_render($subtype, $conf, $panel_args, $context) {

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/soon_country';
  drupal_add_library('system', 'drupal.ajax');

  $content = '<div id="soon-county-wrapper"></div>';
  $title = t('Soon in country');

  $links[] = array(
    'href'  => 'soon_country/de/',
    'title' => t('Germany'),
    'attributes' =>array('class' => array('use-ajax')),
  );
  $links[] = array(
    'href'  =>  'soon_country/ru/',
    'title' => t('Russia'),
    'attributes' =>array('class' => array('use-ajax')),
  );
  $links[] = array(
    'href'  =>  'soon_country/ua/',
    'title' => t('Ukraine'),
    'attributes' =>array('class' => array('use-ajax')),
  );
  $links[] = array(
    'href'  =>  'soon_country/tr/',
    'title' => t('Turkey'),
    'attributes' =>array('class' => array('use-ajax')),
  );

  $location = array(
    '#theme' => 'links',
    '#attributes' => array('id' => 'countries-wrapper'),
    '#heading' => t('Change location'),
    '#links' => $links,
  );

  return (object) array(
    'module' => 'airtribune',
    'title' => $title . render($location),
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_soon_country_content_type_edit_form($form, &$form_state) {
  return $form;
}


function airtribune_soon_country($country_code) {

  $view = views_get_view('frontpage_events');
  $view->set_arguments(array(strtoupper($country_code)));

  $output = $view->preview('soon_in_country_pane');
  // See ajax_example_advanced.inc for more details on the available commands
  // and how to use them.
  $commands[] = ajax_command_html('#soon-county-wrapper', $output);
  $page = array('#type' => 'ajax', '#commands' => $commands);
  ajax_deliver($page);
}
