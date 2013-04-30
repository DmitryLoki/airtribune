<?php

/**
 * @file
 * Airtribune player pane plugin.
 * 
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see #3068.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune player'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Race'), 'ent_race'),
);

/**
 * Render airtribune player pane.
 */
function airtribune_airtribune_player_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_RACE_TYPE) {
    return;
  }

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_player';

  // Race entity.
  $race = $context->data;
  $raceId = $race->field_core_id[0][LANGUAGE_NONE]['value'];
  
  // Get groups
  $groups = og_get_entity_groups($race->entityType(), $race);

  $contest = node_load($groups['node']);
  $contestId = $contest->field_core_id[0][LANGUAGE_NONE]['value'];

  $content['widget']['#markup'] = '';
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-player'));
  $content['#theme_wrappers'] = array('container');

  // Url for visualisation
  $baseUrl = AIRTRIBUNE_VIS_URL;
  
  // Chekh 2nd argunent. Get widget type.
  $mapWidget = !empty($panel_args[1]) ? $panel_args[1] : "2d";
  
  // Chekh 3th argunent. Get online status.
  $isOnline = (!empty($panel_args[2]) && $panel_args[2] == 'online') ? 'true' : 'false';

  $widget_html = "<script data-main=\"{$baseUrl}/js/init\" src=\"{$baseUrl}/js/require.js\"></script>
    <div>
    <!-- ko widget: { data: page, imgRootUrl: \"{$baseUrl}/img/\", raceId: \"{$raceId}\", contestId: \"{$contestId}\", isOnline: {$isOnline}, mapWidget: \"{$mapWidget}\" } --><!-- /ko -->
    </div>";

  $content['widget']['#markup'] = $widget_html;

  $content['#attached']['css'] = array($plugin_path . '/airtribune_player.css');
  $content['#attached']['css'][] = $baseUrl . "/css/airvis.css";
  $content['#attached']['css'][] = $baseUrl . "/css/checkbox.css";
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-player'));
  $content['#theme_wrappers'] = array('container');

  return (object)array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_player_content_type_edit_form($form, &$form_state) {
  return $form;
}

