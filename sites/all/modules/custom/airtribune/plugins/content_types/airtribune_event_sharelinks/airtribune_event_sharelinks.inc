<?php

/**
 * @file
 * Airtribune event share links pane plugin.
 *
 * @see #3036 #3141
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune share links'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune sharelinks pane.
 */
function airtribune_airtribune_event_sharelinks_content_type_render($subtype, $conf, $panel_args, $context) {
//  dpm($context,'context');
//  dpm($panel_args,'panels_args');
//  dpm($conf,'conf');

  // don't render share links pane on user profile pages
  // @see #3257
  if (arg(0) == 'user' || arg(0) == 'account' || strpos(arg(0), "profile-") !== FALSE) {
    return;
  }
  if (empty($context) || empty($context->data)) {
    // if pane loaded on <front>
    $alias = "";
  } else {
    // event node
    $node = $context->data;

    // if we have two args - event nid & accommodation/activity/newsblog nid,
    // like event/[nid]/map/[nid] or event/[nid]/blog/[nid]
    // load second arg node, override $node from $context
    if (count($panel_args) == 2 && $panel_args[1] != 'details') {
      $node = node_load($panel_args[1]);
    }
    // event/nid/* - sharelinks change by event tab
    // @see #3141
    if ($node->type == 'pg_contest') {
      // get inner path, like event/1234/pilots
      $path = isset($_GET['q']) ? $_GET['q'] : '<front>';
      $end = "/";
      if (strpos($path, "blog")) $end .= "blog";
      if (strpos($path, "map")) $end .= "map";
      if (strpos($path, "pilots")) $end .= "pilots";
      if (strpos($path, "results")) $end .= "results";
      if (strpos($path, "info") || strpos($path, "info/details") || strpos($path, "register"))  $end .= "info";
      $alias = drupal_get_path_alias('event/' . $node->nid . $end);
    }
    // node/nid
    else {
      $alias = drupal_get_path_alias('node/' . $node->nid);
    }
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

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_sharelinks';
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
