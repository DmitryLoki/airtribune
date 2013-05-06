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

  // Chekh 3th argunent. Get online status.
  $isOnline = (!empty($panel_args[2]) && $panel_args[2] == 'online') ? 'true' : 'false';

  // Options for widget
  $options = array(
    'isOnline' => $isOnline,
    'mapWidget' => $panel_args[1],
    'widgetHeight' => $conf['widgetHeight'],
    'widgetWidth' => $conf['widgetWidth'],
  );
  
  // Set finction for output widget.
  $function = $conf['widget_is_preview'] ? '_airtribune_airtribune_player_get_race_preview' : '_airtribune_airtribune_player_get_race_widget';
  
  $widget_html = $function($contestId, $raceId, $options);

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
 * @return string HTML-code widget.
 */
function _airtribune_airtribune_player_get_race_widget ($contestId, $raceId, $options = array()) {
  // Initialization
  $mapWidget = isset($options['mapWidget']) ? $options['mapWidget'] : '2d';
  $isOnline = isset($options['isOnline']) ? $options['isOnline'] : 'false';
  $baseUrl = isset($options['baseUrl']) ? $options['baseUrl'] : AIRTRIBUNE_VIS_URL;

  $output = "<link rel=\"stylesheet\" href=\"{$baseUrl}/css/airvis.css\"/>
    <link rel=\"stylesheet\" href=\"{$baseUrl}/css/checkbox.css\"/>  
    <script data-main=\"{$baseUrl}/js/init\" src=\"{$baseUrl}/js/require.js\"></script>
    <div>
    <!-- ko widget: { data: page, imgRootUrl: \"{$baseUrl}/img/\", raceId: \"{$raceId}\", contestId: \"{$contestId}\", isOnline: {$isOnline}, mapWidget: \"{$mapWidget}\" } --><!-- /ko -->
    </div>";
  return $output;
}

/**
 * Returns an HTML-code to insert a race preview.
 * @contestId string
 * @raceId string
 * @options array Widget settings.
 *    widgetWidth
 *    widgetHeight
 *    baseUrl - url hosting visualisation
 * @return string HTML-code widget.
 */
function _airtribune_airtribune_player_get_race_preview ($contestId, $raceId, $options = array()) {
  // Initialization
  $widgetWidth = isset($options['widgetWidth']) ? $options['widgetWidth'] : '100%';
  $widgetHeight = isset($options['widgetHeight']) ? $options['widgetHeight'] : '100%';
  $baseUrl = isset($options['baseUrl']) ? $options['baseUrl'] : AIRTRIBUNE_VIS_URL;
  
  $output = "<script data-main=\"{$baseUrl}/js/initSimple\" src=\"{$baseUrl}/js/require.js\"></script>
    <div>
    <!-- ko widget: { data: page, contestId: \"{$contestId}\", raceId: \"{$raceId}\", width: \"{$widgetWidth}\", height: \"{$widgetHeight}\" } --><!-- /ko -->
    </div>";
  return $output;
}

/**
* 'Edit form' callback for the content type.
*/
function airtribune_airtribune_player_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['widget_is_preview'] = array(
    '#type' => 'checkbox',
    '#title' => t('View as preview'),
    '#default_value' => !empty($conf['widget_is_preview']) ? $conf['widget_is_preview'] : false,
  );
  $form['widgetWidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Preview Width'),
    '#size' => 4,
    '#default_value' => !empty($conf['widgetWidth']) ? $conf['widgetWidth'] : '100%',
  );
  $form['widgetHeight'] = array(
    '#type' => 'textfield',
    '#title' => t('Preview Height'),
    '#size' => 4,
    '#default_value' => !empty($conf['widgetHeight']) ? $conf['widgetHeight'] : '100%',
  );
  return $form;
}

/**
* Submit function, note anything in the formstate[conf] automatically gets saved
*/
function airtribune_airtribune_player_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['widget_is_preview'] = $form_state['values']['widget_is_preview'];
  $form_state['conf']['widgetWidth'] = $form_state['values']['widgetWidth'];
  $form_state['conf']['widgetHeight'] = $form_state['values']['widgetHeight'];
}
