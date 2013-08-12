<?php

/**
 * @file
 * Airtribune event twitter pane plugin.
 *
 * @see #2578 #3362
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune event twitter'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune event twitter pane.
 */
function airtribune_airtribune_event_twitter_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_event_twitter';

  // Event node.
  $node = $context->data;
  $twitter_widget_code = field_get_items('node', $node, AIRTRIBUNE_TWITTER_WIDGET_CODE_FIELD);

  if (empty($twitter_widget_code[0]['value'])) {
    return;
  }

  // Load username & widget id from html code by regex
  if (preg_match('!(href="https://twitter.com/)([[:alnum:]]+)!si', $twitter_widget_code[0]['value'], $matches)) {
    $twitter_user = $matches[2];
  }
  if (preg_match('!(data-widget-id=")([0-9]+)!si', $twitter_widget_code[0]['value'], $matches)) {
    $twitter_widget_id = $matches[2];
  }

  if (empty($twitter_user) || empty($twitter_widget_id)) {
    return;
  }

  $widget_html = '<a class="twitter-timeline" data-dnt="true" href="https://twitter.com/' . $twitter_user . '" data-widget-id="' . $twitter_widget_id . '">' . t('Tweets by @twitter_user', array('@twitter_user' => $twitter_user)) . '</a>
<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?\'http\':\'https\';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+"://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");</script>';

  $content['widget']['#markup'] = $widget_html;
  $content['#attached']['css'] = array($plugin_path . '/airtribune_event_twitter.css');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-event-twitter'));
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
function airtribune_airtribune_event_twitter_content_type_edit_form($form, &$form_state) {
  return $form;
}
