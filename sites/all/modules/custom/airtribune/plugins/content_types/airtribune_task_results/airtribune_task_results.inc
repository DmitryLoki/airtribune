<?php

/**
 * @file
 * Airtribune task results plugin.
 *
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see #4070.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Task results by cetegory'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => array(
    new ctools_context_required(t('Contest'), 'node'),
    new ctools_context_required(t('Race'), 'ent_race'),
    new ctools_context_required(t('Scoring category'), 'node'),
  ),
);

/**
 * Render airtribune player pane.
 */
function airtribune_airtribune_vis_content_type_render($subtype, $conf, $panel_args, $context) {
  if (!empty($context[0])) {
    $context_contest = $context[0];
  }
  if (!empty($context[1])) {
    $context_race = $context[1];
  }
  if (!empty($context[2])) {
    $context_category = $context[2];
  }
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_task_results';

  $output = '';

  $content['widget']['#markup'] = $output;
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-task-results'));
  $content['#theme_wrappers'] = array('container');

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * 'Edit form' callback for the content type.
 */
function airtribune_airtribune_vis_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  return $form;
}


/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_vis_content_type_edit_form_submit(&$form, &$form_state) {
  return $form;
}
