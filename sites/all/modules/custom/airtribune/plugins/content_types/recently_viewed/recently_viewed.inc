<?php

/**
 * @file
 * Airtribune recently viewed pane plugin.
 *
 * @see #3544.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Recently viewed'),
  'single' => TRUE,
  'category' => array('Airtribune'),
);

/**
 * Render event title pane.
 */
function airtribune_recently_viewed_content_type_render($subtype, $conf, $panel_args) {

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/recently_viewed';

  $content['#attached']['js'] = array($plugin_path . '/recently_viewed.js');
  $content['#attributes'] = array('id' => drupal_html_id('recently-viewed'));
  $content['#theme_wrappers'] = array('container');

  return (object) array(
    'module' => 'airtribune',

    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_recently_viewed_content_type_edit_form($form, &$form_state) {
  return $form;
}
