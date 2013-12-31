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
  'edit form' => 'airtribune_pilots_statistics_content_type_form',
);

/**
 * Event statistics plugin form
 */
function airtribune_pilots_statistics_content_type_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['total'] = array(
    '#title' => t('Show total pilots'),
    '#type' => 'select',
    '#options' => array(
      0 => t('No'),
      1 => t('Yes')
    ),
    '#default_value' => $conf['total'],
  );
  $form['confirmed'] = array(
    '#title' => t('Show confirmed pilots'),
    '#type' => 'select',
    '#options' => array(
      0 => t('No'),
      1 => t('Yes')
    ),
    '#default_value' => $conf['confirmed'],
  );
  $form['allowed'] = array(
    '#title' => t('Show allowed pilots'),
    '#type' => 'select',
    '#options' => array(
      0 => t('No'),
      1 => t('Yes')
    ),
    '#default_value' => $conf['allowed'],
  );
  return $form;
}

/**
 * Submit function for the access plugins settings.
 *
 * We cast all settings to numbers to ensure they can be safely handled.
 */
function airtribune_pilots_statistics_content_type_form_submit($form, $form_state) {
  foreach (array('total', 'confirmed', 'allowed') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Render event statisics pane.
 */
function airtribune_pilots_statistics_content_type_render($subtype, $conf, $panel_args, $context) {

  if (empty($context) || empty($context->data) || $context->data->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }

  // Event node.
  $node = $context->data;
  
  if ($conf['total']) {
    $result = airtribune_count_pilots($node->nid);
  
    
    $content['pilots_total'] = array(
      '#theme_wrappers' => array('container'),
      '#attributes' => array('class' => array('pilots-total')),
    );
    $content['pilots_total']['result'] = array(
      '#theme' => 'container',
      '#markup' => $result,
      '#attributes' => array('class' => array('pilots-result')),
    );
    $content['pilots_total']['text'] = array(
      '#theme' => 'container',
      '#markup' => t('Total registered'),
      '#attributes' => array('class' => array('pilots-text')),
    );
  }

  if ($conf['confirmed']) {
    $result = airtribune_count_pilots($node->nid, AIRTRIBUNE_PG_CONTESTANT_CONFIRMED);
  
    $content['pilots_confirmed'] = array(
      '#theme_wrappers' => array('container'),
      '#attributes' => array('class' => array('pilots-confirmed')),
      '#weight' => -1,
    );
    $content['pilots_confirmed']['result'] = array(
      '#theme' => 'container',
      '#markup' => $result,
      '#attributes' => array('class' => array('pilots-result')),
    );
    $content['pilots_confirmed']['text'] = array(
      '#theme' => 'container',
      '#markup' => str_replace($result, '', format_plural($result, 'Confirmed pilot', '@count Confirmed pilots')),
      '#attributes' => array('class' => array('pilots-text')),
    );
  }

  if ($conf['allowed']) {
    $pilots_allowed_items = field_get_items('node', $node, 'field_max_number_contestants');
    if (isset($pilots_allowed_items[0]['value'])) {
      $pilots_allowed = $pilots_allowed_items[0]['value'];
      $content['pilots_allowed'] = array(
        '#theme_wrappers' => array('container'),
        '#attributes' => array('class' => array('pilots-allowed')),
        '#weight' => 10,
      );
      $content['pilots_allowed']['result'] = array(
        '#theme' => 'container',
        '#markup' => $pilots_allowed,
        '#attributes' => array('class' => array('pilots-result')),
      );
      $content['pilots_allowed']['text'] = array(
        '#theme' => 'container',
        '#markup' => str_replace($pilots_allowed, '', format_plural($pilots_allowed, 'Pilot allowed', '@count Allowed pilots')),
        '#attributes' => array('class' => array('pilots-text')),
      );
    }
  }

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );

}
