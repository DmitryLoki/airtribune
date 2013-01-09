<?php

/**
 * @file
 * Airtribune event title pane plugin.
 *
 * @see #2496.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune event title'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune event title pane.
 */
function airtribune_airtribune_event_title_content_type_render($subtype, $conf, $panel_args, $context) {
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_title';

  // Event node.
  $node = $context->data;

  $content['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h1',
    '#value' => check_plain($node->title),
  );

  $content['description'] = array(
   '#type' => 'container',
   '#attributes' => array('id' => 'event-description', 'class' => array('container-inline')),
  );

  foreach (array(AIRTRIBUNE_COUNTRY_FIELD, AIRTRIBUNE_CITY_FIELD, AIRTRIBUNE_DATES_FIELD) as $weight => $field) {
    $content['description'][$field] = field_view_field('node', $node, $field, 'full');
    $content['description'][$field]['#weight'] = $weight;
  }

  $tmz_items = field_get_items('node', $node, AIRTRIBUNE_TIMEZONE_FIELD);
  if (!empty($tmz_items[0]['value'])) {
    $date = new DateTime();
    $date->setTimezone(new DateTimeZone($tmz_items[0]['value']));
    $content['description']['time'] = array(
      '#type' => 'item',
      '#markup' => t('Local time &#151; !time', array('!time' => $date->format('H:i'))),
      '#weight' => 5,
    );
  }

  $content['#attached']['css'] = array($plugin_path . '/airtribune_event_title.css');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-event-title'));
  $content['#theme_wrappers'] = array('container');

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels needs this empty form.
 */
function airtribune_airtribune_event_title_content_type_edit_form($form, &$form_state) {
  return $form;
}
