<?php

/**
 * @file
 * Event statisitics pane plugin.
 *
 * @see #2973.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Pilots statistics'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render event statisics pane.
 */
function airtribune_pilots_statistics_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }

  // Event node.
  $node = $context->data;

  $view = views_get_view('paragliding_pilots_list');
  $view->set_arguments(array($node->nid));
  unset($view->display['default']->display_options['filters'][AIRTRIBUNE_PG_CONTESTANT_STATUS_FIELD . '_value']);
  $view->execute();
  $pilots_total = count($view->result);
  $content['pilots_total'] = array(
    '#theme_wrappers' => array('container'),
    '#attributes' => array('class' => array('pilots-total')),
  );
  $content['pilots_total']['result'] = array(
    '#theme' => 'container',
    '#markup' => $pilots_total,
    '#attributes' => array('class' => array('pilots-result')),
  );
  $content['pilots_total']['text'] = array(
    '#theme' => 'container',
    '#markup' => t('Total registred'),
    '#attributes' => array('class' => array('pilots-text')),
  );

  $view = views_get_view('paragliding_pilots_list');
  $view->set_arguments(array($node->nid));
  $view->execute();
  $pilots_confirmed = count($view->result);
  $content['pilots_confirmed'] = array(
    '#theme_wrappers' => array('container'),
    '#attributes' => array('class' => array('pilots-confirmed')),
    '#weight' => -1,
  );
  $content['pilots_confirmed']['result'] = array(
    '#theme' => 'container',
    '#markup' => $pilots_confirmed,
    '#attributes' => array('class' => array('pilots-result')),
  );
  $content['pilots_confirmed']['text'] = array(
    '#theme' => 'container',
    '#markup' => str_replace($pilots_confirmed, '', format_plural($pilots_confirmed, 'Confirmed pilot', '@count Confirmed pilots')),
    '#attributes' => array('class' => array('pilots-text')),
  );

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}