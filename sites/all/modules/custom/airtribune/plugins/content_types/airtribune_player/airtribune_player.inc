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
  $items = field_get_items('ent_race', $race, AIRTRIBUNE_CORE_ID_FIELD);

  $raceId = $items[0]['value'];
  
  // Get groups
  $groups = og_get_entity_groups($race->entityType(), $race);

  $contest = node_load(array_shift(array_values($groups['node'])));
  $items = field_get_items('node', $contest, AIRTRIBUNE_CORE_ID_FIELD);
  $contestId = $items[0]['value'];

  // Chekh 3th argunent. Get online status.
  $isOnline = (!empty($panel_args[2]) && $panel_args[2] == 'online') ? 'true' : 'false';

  // Options for widget
  $options = array(
    'isOnline' => $isOnline,
    'mapWidget' => $panel_args[1],
    'apiVersion' => at_core_sync_get_api_version(),
  );
  
  $widget_html = _airtribune_airtribune_player_get_race_widget($contestId, $raceId, $options);

  $content['widget']['#markup'] = $widget_html;
  $content['#attached']['css'] = array($plugin_path . '/airtribune_player.css');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-player'));
  $content['#theme_wrappers'] = array('container');

  return (object)array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Returns an HTML-code to insert a widget.
 * @contestId string
 * @raceId string
 * @options array Widget settings.
 *    mapWidget - type of widget (2d, 3d and etc.)
 *    isOnline - online mode
 *    baseUrl - url hosting visualisation
 *    apiVersion - version of CoreAPI
 * @return string HTML-code widget.
 */
function _airtribune_airtribune_player_get_race_widget ($contestId, $raceId, $options = array()) {
  // Initialization
  $mapWidget = isset($options['mapWidget']) ? $options['mapWidget'] : '2d';
  $isOnline = isset($options['isOnline']) ? $options['isOnline'] : 'false';
  $baseUrl = isset($options['baseUrl']) ? $options['baseUrl'] : AIRTRIBUNE_VIS_URL;
  $apiVersion = isset($options['apiVersion']) ? $options['apiVersion'] : at_core_sync_get_api_version();

  $output = "<link rel=\"stylesheet\" href=\"{$baseUrl}/css/airvis.css\"/>
    <link rel=\"stylesheet\" href=\"{$baseUrl}/css/checkbox.css\"/>  
    <link rel=\"stylesheet\" href=\"{$baseUrl}/css/shiny-sprite.css\">
    <script data-main=\"{$baseUrl}/js/init\" src=\"{$baseUrl}/js/lib/require.js\"></script>
    <div>
    <!-- ko widget: { data: page, imgRootUrl: \"{$baseUrl}/img/\", raceId: \"{$raceId}\", contestId: \"{$contestId}\", isOnline: {$isOnline}, mapWidget: \"{$mapWidget}\", apiVersion: \"{$apiVersion}\"  } --><!-- /ko -->
    </div>";
  return $output;
}

/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_player_content_type_edit_form_submit(&$form, &$form_state) {
  return $form;
}
