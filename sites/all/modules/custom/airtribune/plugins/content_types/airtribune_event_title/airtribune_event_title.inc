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

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_title';

  // Event node.
  $node = $context->data;

  $content['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h1',
    '#value' => l(check_plain($node->title), 'event/' . $node->nid),
  );

  $content['description'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'event-description', 'class' => array('container-inline')),
  );

  $fields = array(
    AIRTRIBUNE_COUNTRY_FIELD,
    AIRTRIBUNE_CITY_FIELD,
    AIRTRIBUNE_DATES_FIELD,
    AIRTRIBUNE_TIMEZONE_FIELD,
  );
  foreach ($fields as $weight => $field) {
    $content['description'][$field] = field_view_field('node', $node, $field, 'full');
    $content['description'][$field]['#weight'] = $weight;
  }
  $content['description'][$field]['#prefix'] = '<div class="field local_time">' . t('Local time — ');
  $content['description'][$field]['#suffix'] = '</div>';

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
 * Panels module needs this empty form.
 */
function airtribune_airtribune_event_title_content_type_edit_form($form, &$form_state) {
  return $form;
}
