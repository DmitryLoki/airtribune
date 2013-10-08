<?php

/**
 * @file
 * Airtribune points widget plugin.
 * Designed after airtribune_player
 * @author Vadim Valuev <gease@mail.ru>
 * @see airtribune_player.inc
 * @see #2276
 * @see #3659
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune points widget'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'render callback' => 'airtribune_airtribune_points_widget_render',
  'edit form' => 'airtribune_airtribune_points_widget_edit_form',
  'required context' => new ctools_context_required(t('Contest'), 'node'),
);

/**
 * Render airtribune player pane.
 */
function airtribune_airtribune_points_widget_render($subtype, $conf, $panel_args, $context) {
  global $base_url;
 

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_points_widget';

  // Contest node.
  $contest = $context->data;

  // Options for widget
  $options = array(
    'eventId' => $contest->nid,
    'mapWidget' => $conf['widget_type'],
    'widgetHeight' => $conf['widget_height'],
    'widgetWidth' => $conf['widget_width']
  );

  $widget_html = _airtribune_points_widget_get_widget($contest->nid, $options);

  $content['widget']['#markup'] = $widget_html;
  //$content['#attached']['css'] = array($plugin_path . '/airtribune_player.css');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-points-widget'));
  $content['#theme_wrappers'] = array('container');

  return (object) array(
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
 *    apiDomain - domain of CoreAPI
 *    apiVersion - version of CoreAPI
 *    mode - widget mode (retrieve)
 *    titleUrl - URL for title link
 * @return string HTML-code widget.
 */
function _airtribune_points_widget_get_widget($eventId, $options = array()) {
  // Initialization
  $mapWidget = isset($options['mapWidget']) ? ', mapWidget: "' . $options['mapWidget'] . '"' : '';
  $baseUrl = isset($options['baseUrl']) ? $options['baseUrl'] : AIRTRIBUNE_VIS_URL;
  $widgetWidth = isset($options['widgetWidth']) ? $options['widgetWidth'] : '100%';
  $widgetHeight = isset($options['widgetHeight']) ? $options['widgetHeight'] : '100%';
  
  $output = '<script data-main="' . $baseUrl . '/wp/js/init" src="' . $baseUrl . '/wp/js/require.js"></script><link rel="stylesheet" href="' . $baseUrl . '/wp/css/reset.css" />
<link rel="stylesheet" href="' . $baseUrl . '/wp/css/WayPointerEditor.css" />';
    
    $output .= '<dv><!-- ko widget: { data: page, imgRootUrl: "' . $baseUrl . '/wp/img/", eventPointsUrl: "/points/get", createFileUrl: "/points/upload", eventId: ' . $eventId . ', width:"' . $widgetWidth . '", height:"' . $widgetHeight . '"' . $mapWidget . ' } --><!-- /ko --></div>';
  return $output;
}

/**
 * 'Edit form' callback for the content type.
 */
function airtribune_airtribune_points_widget_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $types = array('2d' => '2D', '3d' => '3D');

  $form['widget_type'] = array(
    '#type' => 'radios',
    '#title' => t('Widget type'),
    '#options' => $types,
    '#default_value' => !empty($conf['widget_type']) ? $conf['widget_type'] : '2d',
  );
  $form['widget_height'] = array(
    '#type' => 'numberfield',
    '#title' => t('Widget height'),
    '#min' => 200,
    '#max' => 1200,
    '#step' => 5,
    '#field_suffix' => 'px',
    '#default_value' => !empty($conf['widget_height']) ? $conf['widget_height'] : 600,
  );
  $form['widget_width'] = array(
    '#type' => 'numberfield',
    '#title' => t('Widget width'),
    '#min' => 400,
    '#max' => 1800,
    '#step' => 5,
    '#field_suffix' => 'px',
    '#default_value' => !empty($conf['widget_width']) ? $conf['widget_width'] : 900,
  );
  return $form;
}


/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_points_widget_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['widget_type'] = $form_state['values']['widget_type'];
  $form_state['conf']['widget_height'] = $form_state['values']['widget_height'];
  $form_state['conf']['widget_width'] = $form_state['values']['widget_width'];
  return $form;
}
