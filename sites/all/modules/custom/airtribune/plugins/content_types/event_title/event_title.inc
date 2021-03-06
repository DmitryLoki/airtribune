<?php

/**
 * @file
 * Airtribune event title pane plugin.
 *
 * @see #2496.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Eevent title'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render event title pane.
 */
function airtribune_event_title_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || !in_array($context->data->type, array(AIRTRIBUNE_PG_CONTEST_TYPE, AIRTRIBUNE_HG_CONTEST_TYPE))) {
    return;
  }

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/event_title';

  // Event node.
  $node = $context->data;

  $content['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h1',
    '#value' => l($node->title, 'event/' . $node->nid),
  );

  $content['description'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'event-description', 'class' => array('container-inline')),
  );

  switch ($conf['title_type']) {
    case 'default':
      $fields[] = AIRTRIBUNE_COUNTRY_FIELD;
      $fields[] = AIRTRIBUNE_CITY_FIELD;
      $fields[] = AIRTRIBUNE_DATES_FIELD;
      // Do not display "None" FAI category value. See #2632.
      $fai_items = field_get_items('node', $node, AIRTRIBUNE_FAI_CATEGORY_FIELD);
      if (!empty($fai_items[0]['value'])) {
        $fields[] = AIRTRIBUNE_FAI_CATEGORY_FIELD;
      }
      $fields[] = AIRTRIBUNE_TIMEZONE_FIELD;


      foreach ($fields as $weight => $field) {
        $content['description'][$field] = field_view_field('node', $node, $field, 'full');
        $content['description'][$field]['#weight'] = $weight;
      }
      $content['description'][AIRTRIBUNE_TIMEZONE_FIELD]['#prefix'] = '<div class="field local_time">' . t('Local time — ');
      $content['description'][AIRTRIBUNE_TIMEZONE_FIELD]['#suffix'] = '</div>';
      // Add event timezone offset to drupal settins. See #3460.
      if ($event_date = airtribune_extract_time_from_contest($node)) {
        $content['#attached']['js'][] = array(
          'data' => array('airtribune_event_offset' => $event_date['offset']),
          'type' => 'setting',
        );
        $content['#attached']['js'][] = $plugin_path . '/event_title.js';
      }
      break;
    case 'task_results':
      $content['description']['promo_link'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => l(t('Competition news, Live races, Results, Media and much more!'),''),
  );
      break;
  }
  $content['#attached']['css'] = array($plugin_path . '/event_title.css');
  $content['#attributes'] = array('id' => drupal_html_id('event-title'));
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
function airtribune_event_title_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $types = array('default'=> 'Default', 'task_results' => 'Task results');

  $form['title_type'] = array(
    '#type' => 'radios',
    '#title' => t('Title type'),
    '#options' => $types,
    '#default_value' => !empty($conf['title_type']) ? $conf['title_type'] : 'default',
  );
  return $form;
}

/**
 * Panels module needs this empty form.
 */
function airtribune_event_title_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['title_type'] = $form_state['values']['title_type'];
  return $form;
}
