<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */

$plugin = array(
  'title'    => t('Airtribune two column brick'),
  'category' => 'Airtribune',
  'icon'     => 'event-brick.png',
  'theme'    => 'event_brick',
  'admin css' => 'event-brick.admin.css',
  'theme arguments' => array('id', 'content'),
  'regions' => array(
    'event_brick_top'         => t('Top'),
    'event_brick_left_above'  => t('Left above'),
    'event_brick_right_above' => t('Right above'),
    'event_brick_middle'      => t('Middle'),
    'event_brick_left_below'  => t('Left below'),
    'event_brick_right_below' => t('Right below'),
    'event_brick_bottom'      => t('Bottom'),
  ),
  'type' => 'two',
  'options' => array(
    'event-brick' => 'default',
    'event-brick-stack' => 'stack',
  ),
  'styles' => array(
    'event-brick' => array(
      'css' => array(
        'fn' => array('.event-brick > .panel-row' => 'float:none'),
        '50' => array('.event-brick > .panel-row > .region' => 'width:50%'),
      ),
    ),
    'event-brick-stack' => array(
      'css' => array(
        'fdw' => array('.event-brick > .panel-row > .region' => 'float:none;display:block;width:100%;clear:both'),
      ),
    ),
  ),
);


/**
 * Preprocess variables for event-brick.tpl.php
 */
function template_preprocess_event_brick(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
