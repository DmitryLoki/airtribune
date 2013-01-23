<?php

/**
 * @file
 * Airtribune event links pane plugin.
 *
 * @see #2423.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune event links'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune event links pane.
 */
function airtribune_airtribune_event_links_content_type_render($subtype, $conf, $panel_args, $context) {
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_links';

  // Event node.
  $node = $context->data;

  $links[] = array(
    'href' => 'event/' . $node->nid . '/details',
    'title' => t('Selection and entry fee'),
    'fragment' => 'selection',
  );
  $links[] = array(
    'href' => 'event/' . $node->nid . '/details',
    'title' => t('General schedule'),
    'fragment' => 'general-schedule',
  );
  $links[] = array(
    'href' => 'event/' . $node->nid . '/details',
    'title' => t('Daily schedule'),
    'fragment' => 'daily-schedule',
  );
  $links[] = array(
    'href' => 'event/' . $node->nid . '/details',
    'title' => t('Rules'),
    'fragment' => 'rules',
  );

  $open_class_items = field_get_items('node', $node, AIRTRIBUNE_OPENCLASS_FIELD);
  // Open class actually is not a link.
  if (empty($open_class_items[0]['value'])) {
    $links[] = array(
      'title' => t('Open class prohibited'),
      'attributes' => array('class' => 'open-class-prohibited'),
    );
  }
  else {
    $links[] = array(
      'title' => t('Open class allowed'),
      'attributes' => array('class' => 'open-class-allowed'),
    );
  }

  $content['links'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#attributes' => array('id' => 'airtribune-event-links'),
    '#attached' => array('css' => array($plugin_path . '/airtribune_event_links.css')),
  );

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}
