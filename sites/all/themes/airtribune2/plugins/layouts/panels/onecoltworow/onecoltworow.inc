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
  'title' => t('One column two row'),
  'category' => t('Columns: 1'),
  'icon' => 'onecoltworow.png',
  'theme' => 'onecoltworow',
  'css' => 'onecoltworow.css',
  'regions' => array(
    'featured_header_title' => t('Featured header title'),
    'featured_header_padding' => t('Featured header padding'),
    'top' => t('Top'),
    'left' => t('Left'),
  ),
);
