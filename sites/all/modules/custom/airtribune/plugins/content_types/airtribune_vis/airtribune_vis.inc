<?php

/**
 * @file
 * Airtribune visualisation pane plugin.
 *
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see #3068, #3960.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune visualisation'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => array(
    new ctools_context_required(t('Contest'), 'node'),
    new ctools_context_optional(t('Race'), 'ent_race'),
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

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_vis';

  $widget_type = isset($conf['widget_type']) ? $conf['widget_type'] : NULL;
  if (isset($widget_type) && $widget_type == '_none') {
    $widget_type = isset($panel_args[1]) ? $panel_args[1] : '2d';
  }

  $data = array(
    'contest' => $context_contest->data,
    'race' => $context_race->data,
    'widget_type' => $widget_type,
    'widget_width' => $conf['widget_width'],
    'widget_height' => $conf['widget_height'],
    'node' => $context_contest->data,
  );

  $widget_html = check_markup(token_replace($conf['widget_code']['value'], $data), $conf['widget_code']['format']);

  $content['widget']['#markup'] = $widget_html;
  $content['#attached']['css'] = array($plugin_path . '/airtribune_vis.css');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-vis'));
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
  $types = array('_none' => 'From argument', '2d' => '2D', 'ge' => '3D (Google Earth)');

  $form['widget_code'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#format' => 'full_html',
    '#title' => t('Widget code'),
    '#default_value' => !empty($conf['widget_code']['value']) ? $conf['widget_code']['value'] : '',
    '#cols' => 40,
    '#rows' => 6,
    '#resizable' => TRUE,
  );

  // Add to form
  // Display the list of available placeholders if token module is installed.
  if(module_exists("token")) { 
    $form['token_help']['content'] = array(
      '#type' => 'markup',
      '#token_types' => array('node'),
      '#theme' => 'token_tree');
  }

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
    '#default_value' => !empty($conf['widget_height']) ? $conf['widget_height'] : 380,
  );

  $form['widget_width'] = array(
    '#type' => 'numberfield',
    '#title' => t('Widget width'),
    '#min' => 400,
    '#max' => 1800,
    '#step' => 5,
    '#field_suffix' => 'px',
    '#default_value' => !empty($conf['widget_width']) ? $conf['widget_width'] : 940,
  );
  return $form;
}


/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_vis_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['widget_code'] = $form_state['values']['widget_code'];
  $form_state['conf']['widget_type'] = $form_state['values']['widget_type'];
  $form_state['conf']['widget_height'] = $form_state['values']['widget_height'];
  $form_state['conf']['widget_width'] = $form_state['values']['widget_width'];
  return $form;
}
