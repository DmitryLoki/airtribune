<?php

/**
 * @file
 * Implementation of hook_panels_layouts().
 */

// Plugin defenition.
$plugin = array(
  'title'    => t('Airtribune featured header'),
  'category' => 'Airtribune',
  'icon'     => 'featured-header.png',
  'theme'    => 'featured_header',
  'admin css' => 'featured-header.admin.css',
  'css' => 'featured-header.css',
  'regions' => array(
    'title'   => t('Title'),
    'padding' => t('Padding'),
  ),
 );
