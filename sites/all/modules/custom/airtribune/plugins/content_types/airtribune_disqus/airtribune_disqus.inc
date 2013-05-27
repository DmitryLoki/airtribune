<?php

/**
 * @file
 * Airtribune disqus pane plugin.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune disqus comments'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render airtribune disqus pane.
 */
function airtribune_airtribune_disqus_content_type_render($subtype, $conf, $panel_args, $context) {
  global $base_url;

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_disqus';

  $disqus_shortname = 'airtribune';
  if (strpos($base_url, "dev.")) {
    $disqus_shortname = 'devtribune';
  }

  $node = $context->data;
  // if we have two args - event nid & accommodation/activity/newsblog nid,
  // like event/[nid]/map/[nid] or event/[nid]/blog/[nid]
  // load second arg node, override $node from $context
  if (count($panel_args) == 2 && $panel_args[1] != 'details') {
    $node = node_load($panel_args[1]);
  }

  if ($node->type == AIRTRIBUNE_ACCOMMODATION_TYPE ||
      $node->type == AIRTRIBUNE_ACTIVITY_TYPE ||
      $node->type == AIRTRIBUNE_NEWSBLOG_TYPE) {
    $alias = drupal_get_path_alias('node/' . $node->nid);
  } else {
    // don't show disqus comment for other node types and don't render pane
    return;
  }

  $node_url = $base_url . '/' . $alias;

  $content['widget']['#markup'] = '';
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-disqus'));
  $content['#theme_wrappers'] = array('container');

  $widget_html = "
<div id='disqus_thread'></div>
<script type='text/javascript'>
    var disqus_shortname = '{$disqus_shortname}';
    var disqus_url = '{$node_url}';
    (function() {
        var dsq = document.createElement('script'); dsq.type = 'text/javascript'; dsq.async = true;
        dsq.src = '//' + disqus_shortname + '.disqus.com/embed.js';
        (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(dsq);
    })();
</script>
<noscript>Please enable JavaScript to view the <a href='http://disqus.com/?ref_noscript'>comments powered by Disqus.</a></noscript>
<a href='http://disqus.com' class='dsq-brlink'>blog comments powered by <span class='logo-disqus'>Disqus</span></a>";

  $content['widget']['#markup'] = $widget_html;
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-disqus'));
  $content['#theme_wrappers'] = array('container');

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

function airtribune_airtribune_disqus_content_type_edit_form($form, &$form_state) {
  return $form;
}