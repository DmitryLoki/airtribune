<?php

/**
 * @file
 * Airtribune race preview pane plugin.
 * 
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see #3115.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune race preview'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_optional(t('Race'), 'ent_race'),
);

/**
 * Render airtribune player pane.
 */
function airtribune_airtribune_race_preview_content_type_render($subtype, $conf, $panel_args, $context) {
  $contestId = '';
  $raceId = '';
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_race_preview';

  if (!empty($context) && !empty($context->data) && $context->data->type == AIRTRIBUNE_PG_RACE_TYPE) {
    // Race entity.
    $race = $context->data;
    $raceId = $race->field_core_id[0][LANGUAGE_NONE]['value'];

    // Get groups
    $groups = og_get_entity_groups($race->entityType(), $race);

    $contest = node_load($groups['node']);
    $contestId = $contest->field_core_id[0][LANGUAGE_NONE]['value'];
  }

  // Options for widget
  $options = array(
    'isOnline' => 'false',
    'mapWidget' => '2d',
    'widgetHeight' => $conf['widgetHeight'],
    'widgetWidth' => $conf['widgetWidth'],
    'apiVersion' => at_core_sync_get_api_version(),
  );
  
  $widget_html = _airtribune_airtribune_race_preview_get_race_preview($contestId, $raceId, $options);

  $content['widget']['#markup'] = $widget_html;
  $content['#attached']['js'] = array(drupal_get_path('module', 'airtribune') . '/js/day-blog-airvis-controller.js');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-player'));
  $content['#theme_wrappers'] = array('container');

  return (object)array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Returns an HTML-code to insert a race preview.
 * @contestId string
 * @raceId string
 * @options array Widget settings.
 *    widgetWidth
 *    widgetHeight
 *    baseUrl - url hosting visualisation
 *    apiDomain - domain of CoreAPI
 *    apiVersion - version of CoreAPI
 * @return string HTML-code widget.
 */
function _airtribune_airtribune_race_preview_get_race_preview ($contestId, $raceId, $options = array()) {
  // Initialization
  $widgetWidth = isset($options['widgetWidth']) ? $options['widgetWidth'] : '100%';
  $widgetHeight = isset($options['widgetHeight']) ? $options['widgetHeight'] : '100%';
  $baseUrl = isset($options['baseUrl']) ? $options['baseUrl'] : AIRTRIBUNE_VIS_URL;
  $apiDomain = isset($options['apiDomain']) ? $ $options['apiDomain'] : variable_get('at_core_sync_address', 'http://api.airtribune.com');
  $apiVersion = isset($options['apiVersion']) ? $options['apiVersion'] : at_core_sync_get_api_version();
  
  $output = "<script  data-main=\"{$baseUrl}/js/init\" src=\"{$baseUrl}/js/lib/require.js\"></script>
    <div role=\"main\" class=\"airvis-container\">
      <div class=\"airvis-loading-container\">
        <div class=\"airvis-loading\">&nbsp;</div>
      </div>
      <!-- ko widget: { data: page, imgRootUrl: \"{$baseUrl}/img/\", contestId: \"{$contestId}\", raceId: \"{$raceId}\", width: \"{$widgetWidth}\", height: \"{$widgetHeight}\", callback: window.airvisPageLoadedCallback, mode: \"simple\", apiDomain: \"{$apiDomain}\", apiVersion: \"{$apiVersion}\", mapOptions: {panControl:false,streetViewControl:false,scrollwheel:false,zoomControl:true,mapTypeControl:false,zoomControlOptions:{style:google.maps.ZoomControlStyle.LARGE} } } --><!-- /ko -->
    </div>";
  return $output;
}

/**
* 'Edit form' callback for the content type.
*/
function airtribune_airtribune_race_preview_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
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
function airtribune_airtribune_race_preview_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['widgetWidth'] = $form_state['values']['widgetWidth'];
  $form_state['conf']['widgetHeight'] = $form_state['values']['widgetHeight'];
}
