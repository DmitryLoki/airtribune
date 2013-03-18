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
  'title' => t('Two column four row'),
  'category' => t('Columns: 2'),
  'icon' => 'twocolfourrow.png',
  'theme' => 'twocolfourrow',
  'css' => 'twocolfourrow.css',
  'regions' => array(
    'header' => t('Header'),
    'featured_header_title' => t('Featured header title'),
    'featured_header_padding' => t('Featured header padding'),
    'top' => t('Top'),
    'left' => t('Left'),
    'right' => t('Right'),
    'footer' => t('Footer'),
  ),
);
