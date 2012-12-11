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
  'title' => t('Two column 70/30 stacked'),
  'category' => t('Columns: 2'),
  'icon' => 'twocol_70_30_stacked.png',
  'theme' => 'twocol_70_30_stacked',
  'css' => 'twocol_70_30_stacked.css',
  'regions' => array(
    'header' => t('Header'),
    'top' => t('Top'),
    'left' => t('Left'),
    'right' => t('Right'),
    'footer' => t('Footer'),
  ),
);
