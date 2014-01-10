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
    new ctools_context_required(t('Race'), AIRTRIBUNE_RACE_ENTITY_TYPE),
    new ctools_context_required(t('Scoring category'), 'node'),
  ),
);

/**
 * Render airtribune player pane.
 */
function airtribune_airtribune_task_results_content_type_render($subtype, $conf, $panel_args, $context) {
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

  $wrapper_race = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $context_race->data);

  switch ($conf['results_type']) {
    case 'day':
      $results = $wrapper_race->field_day_results->value();
      break;
    case 'competition':
      $results = $wrapper_race->field_competition_results->value();
      break;
  }

  foreach ($results as $key => $category) {
    if ($category->field_scoring_category_ref[LANGUAGE_NONE][0]['target_id'] == $context_category->data->nid) {
      $wrapper_category = entity_metadata_wrapper($category->entityType(), $category);
      $file_entity = $wrapper_category->field_results_file->value();
      if (isset($file_entity['uri'])) {
        $output = file_get_contents(drupal_realpath($file_entity['uri']));
      }
    }
  }
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
function airtribune_airtribune_task_results_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $types = array('day' => 'Day', 'competition' => 'Competition');

  $form['results_type'] = array(
    '#type' => 'radios',
    '#title' => t('Results type'),
    '#options' => $types,
    '#default_value' => !empty($conf['widget_type']) ? $conf['widget_type'] : '2d',
  );

  return $form;
}


/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_task_results_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['results_type'] = $form_state['values']['results_type'];
  return $form;
}
