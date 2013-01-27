<?php

/**
 * @file
 * Airtribune event twitter pane plugin.
 *
 * @see #2578.
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

  if (empty($node->field_social_links)) {
    return;
  }

  foreach ($node->field_social_links['und'] as $link) {
    if (strpos($link['url'], 'twitter.com')) {
      $twitter_url = $link['url'];
    }
  }

  if (empty($twitter_url)) {
    return;
  }

  // remove trailing slash
  $twitter_url = rtrim($twitter_url, '/');
  // get username from url
  $twitter_user = substr($twitter_url, strrpos($twitter_url, '/') + 1);

  $widget_html = "<script src='http://widgets.twimg.com/j/2/widget.js'></script>
<script>
new TWTR.Widget({
    version: 2,
    type: 'profile',
    rpp: 10,
    interval: 5000,
    width: 220,
    height: 300,
    theme: {
        shell: {
            background: '#eceff2',
            color: '#333a40'
        },
        tweets: {
            background: '#ffffff',
            color: '#333a40',
            links: '#00acee'
        }
    },
    features: {
        scrollbar: false,
        loop: true,
        live: true,
        hashtags: true,
        timestamp: true,
        avatars: false,
        behavior: 'default'
    }
}).render().setUser('@$twitter_user').start();
</script>";

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
>>>>>>> 56603e5c11abb0f28f831132016ae79800e1470b
