<?php

/**
 * @file
 * Airtribune event twitter pane plugin.
 *
 * @see #2578 #3362 #2834
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune event twitter / facebook'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'airtribune_event_tw_fb_content_type_edit_form',
  'render callback' => 'airtribune_event_tw_fb_content_type_render',
);

/**
 * Render airtribune event twitter pane.
 */
function airtribune_event_tw_fb_content_type_render(&$subtype, $conf, $panel_args, $context) {

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

  // Load facebook page from html code by regex, cut to first question mark.
  if (preg_match('!(facebook.com/)(.*\?|.*)!si', $twitter_widget_code[0]['value'], $matches)) {
    $facebook_page_url = $matches[2];
  }

  if (!empty($twitter_user) && !empty($twitter_widget_id)) {
    $widget_html = '<a class="twitter-timeline" data-dnt="true" href="https://twitter.com/' . $twitter_user . '" data-widget-id="' . $twitter_widget_id . '">' . t('Tweets by @twitter_user', array('@twitter_user' => $twitter_user)) . '</a>
  <script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?\'http\':\'https\';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+"://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");</script>';
    $content['#attributes'] = array('id' => drupal_html_id('airtribune-event-twitter'));
    $title = 'Twitter';
  }
  elseif (!empty($facebook_page_url)) {
    $widget_html = '<iframe src="//www.facebook.com/plugins/likebox.php?href=' . urlencode("https://facebook.com/$facebook_page_url") . '&amp;width&amp;height=258&amp;colorscheme=light&amp;show_faces=true&amp;header=false&amp;stream=false&amp;show_border=false" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width: 232px; height: 204px;" allowTransparency="true"></iframe>';
    $content['#attributes'] = array('id' => drupal_html_id('airtribune-event-facebook'));
    $title = 'Facebook';
    // TODO remove this after renaming plugin.
    // Subtype don't must be passed by reference and changed, workaround for css.
    $subtype = 'airtribune_event_facebook';
  }
  else {
    return;
  }
  
  $content['widget']['#markup'] = $widget_html;
  $content['#attached']['css'] = array($plugin_path . '/airtribune_event_twitter.css');
  $content['#theme_wrappers'] = array('container');

  return (object) array(
    'title' => $title,
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_event_tw_fb_content_type_edit_form($form, &$form_state) {
  return $form;
}
