<?php
/**
 * @file   onecolthreerow.inc
 * @author Vyacheslav Malchik <info@vkey.biz>
 *
 */

// Plugin definition.
$plugin = array(
  'title' => t('Onecolumn barebone default'),
  'category' => t('Columns: 1'),
  'icon' => 'onecolthreerow.png',
  'theme' => 'onecolthreerow',
  'css' => 'onecolthreerow.css',
  'regions' => array(
    'header' => t('Header'),
    'middle' => t('Middle'),
    'footer' => t('Footer'),
  ),
);
