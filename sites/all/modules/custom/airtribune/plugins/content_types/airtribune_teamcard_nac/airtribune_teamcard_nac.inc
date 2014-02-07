<?php

/**
 * @file
 * Airtribune team card NAC plugin
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune team card NAC'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => array(
    new ctools_context_required(t('Contest'), 'node'),
    new ctools_context_required(t('Team Entity'), 'ent_team'),
  ),
);

/**
 * Render airtribune team card header pane.
 */
function airtribune_airtribune_teamcard_nac_content_type_render(&$subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context[0]->data) || empty($context[1]->data)) {
    return;
  }

  $team = $context[1]->data;

  module_load_include('inc', 'eck', 'eck.entity');
  $form = eck__entity__edit(AIRTRIBUNE_TEAM_TYPE, AIRTRIBUNE_PG_NATION_TEAM_TYPE, $team->id);

  $form['title']['#access'] = FALSE;

  $form = drupal_render($form);

  $content['widget']['#markup'] = $form;

  $content['#theme_wrappers'] = array('container');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-teamcard-nac'));

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_teamcard_nac_content_type_edit_form_submit($form, &$form_state) {
  return $form;
}
