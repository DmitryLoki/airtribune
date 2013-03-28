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
  'title' => t('Onecolumn barebone default'),
  'category' => t('Columns: 1'),
  'icon' => 'twocolfourrow.png',
  'theme' => 'onecol',
  'css' => 'onecol.css',
  'regions' => array(
    'header' => t('Header'),
    //'featured_header_title' => t('Featured header title'),
    //'featured_header_padding' => t('Featured header padding'),
    'middle' => t('Middle'),
    'footer' => t('Footer'),
  ),
);
