<?php
/**
 * @file   twocol_70_30_stacked.inc
 * @author António P. P. Almeida <appa@perusio.net>
 * @date   Sun Jul 24 20:43:02 2011
 *
 * @brief  The two column 70/30 stacked layout.
 *
 *
 */

// Plugin definition.
$plugin = array(
  'title' => t('Full event layout'),
  'category' => t('Columns: 3'),
  'icon' => 'twocolfourrow.png',
  'theme' => 'event-brick-full',
  'css' => 'event-brick-full.css',
  'admin css' => 'event-brick.admin.css',
  'regions' => array(
    'featured_header_title' => t('Featured header title'),
    'featured_header_padding' => t('Featured header padding'),
    'top' => t('Top'),
    'left' => t('Left'),
    'right' => t('Right'),
    'event_brick_top'         => t('Top'),
    'event_brick_left_above'  => t('Left above'),
    'event_brick_right_above' => t('Right above'),
    'event_brick_middle'      => t('Middle'),
    'event_brick_left_below'  => t('Left below'),
    'event_brick_right_below' => t('Right below'),
    'event_brick_left_bottom'  => t('Left bottom'),
    'event_brick_right_bottom' => t('Right bottom'),
  ),
);

