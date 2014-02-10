<?php

/**
 * @file
 * Plugin to provide a user context from team entity.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User from team entity'),
  'keyword' => 'teamuser',
  'context name' => 'teamuser',
  'single' => TRUE,
  'category' => array('Airtribune'),
  'context' => 'user_team_context',
  'edit form' => 'user_team_settings_form',
);

function user_team_context($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context(array('entity:user', 'entity', 'user'));
  $context->plugin = 'user';

  if ($empty) {
    return $context;
  }

  // event/%contest/pilots/manage/teams/%team
  if (is_numeric(arg(5))) {
    $team = entity_load_single(AIRTRIBUNE_TEAM_TYPE, arg(5));
    $data = user_load($team->uid);
  }

  if (!empty($data)) {
    $context->data     = $data;
    $context->title    = isset($data->name) ? $data->name : t('Anonymous');
    $context->argument = $data->uid;
    return $context;
  }
}

function user_team_settings_form($form, &$form_state) {
  return $form;
}