<?php

/**
 * @file
 * Airtribune event share links pane plugin.
 *
 * @see #3036
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune event share links'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune event sharelinks pane.
 */
function airtribune_airtribune_event_sharelinks_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data)) {
    return;
  }

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_sharelinks';

  // Event node.
  $node = $context->data;

  $content['widget']['#markup'] = '';
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-event-sharelinks'));
  $content['#theme_wrappers'] = array('container');

  //  link to accommodation / activities
  if (
    (arg(2) == 'map' && arg(3)) || // without lang prefix, like event/nid/map/nid
    (arg(3) == 'map' && arg(4))    // with lang prefix, like /ru/event/nid/map/nid
  ) {
    $alias = drupal_get_path_alias('node/' . arg(3));
  }
  // event/nid/* - link to event
  elseif ($node->type == 'pg_contest') {
    $alias = drupal_get_path_alias('event/' . $node->nid);
  }
  // node/nid
  else {
    $alias = drupal_get_path_alias('node/' . $node->nid);
  }
  global $base_url;
  $sharelinks_url = $base_url . '/' . $alias;

  // set by default horizontal balloon style
  $balloon_type = 'h';
  if (!empty($conf['balloon_type'])) {
    $balloon_type = $conf['balloon_type'];
  }

  $widget_html = "
<script type='text/javascript'>var __st_loadLate=true;</script>
<script type='text/javascript'>var switchTo5x=false;</script>
<script type='text/javascript' src='http://w.sharethis.com/button/buttons.js'></script>
<script type='text/javascript'>stLight.options({publisher: '77e50a8c-2e6c-4d8c-883f-2ab1460a9f2c', nativeCount: true});</script>
<span class='st_facebook_{$balloon_type}count' st_url='{$sharelinks_url}' displayText='Facebook'></span><span class='st_twitter_{$balloon_type}count' st_url='{$sharelinks_url}' displayText='Tweet'></span><span class='st_googleplus_{$balloon_type}count' st_url='{$sharelinks_url}' displayText='Google+'></span></span><span class='st_sharethis_{$balloon_type}count' st_url='{$sharelinks_url}' displayText='Share'></span>";

  $content['widget']['#markup'] = $widget_html;

  $content['#attached']['css'] = array($plugin_path . '/airtribune_event_sharelinks.css');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-event-sharelinks'));
  $content['#theme_wrappers'] = array('container');

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

function airtribune_airtribune_event_sharelinks_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['balloon_type'] = array(
    '#type' => 'select',
    '#title' => t('Balloon type'),
    '#options' => array(
      'h' => t('Horizontal'),
      'v' => t('Vertical'),
    ),
    '#default_value' => 'h',
  );
  return $form;
}

function airtribune_airtribune_event_sharelinks_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('balloon_type') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}