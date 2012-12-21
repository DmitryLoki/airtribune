<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function airtribune2_fourcoltworow_panels_layouts() {
  $items['fourcoltworow'] = array(
    'title'    => t('Four column two row'),
    'category' => t('AT Responsive Panels - 4,5,6 column'),
    'icon'     => 'fourcoltworow.png',
    'theme'    => 'fourcoltworow',
    'admin css' => 'fourcoltworow.admin.css',
    'css' => 'fourcoltworow.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'four_first'  => t('Column 1'),
      'four_second' => t('Column 2'),
      'four_third'  => t('Column 3'),
      'four_fourth' => t('Column 4'),
      'four_five' => t('Row 2'),
    ),
    // AT Core
    'type' => 'four',
    'options' => array(
      'fourcoltworow' => 'default',
      'fourcoltworow-right-stack' => 'stack right',
      'fourcoltworow-2x2-grid' => '2x2 grid',
      'fourcoltworow-stack' => 'stack',
    ),
    'styles' => array(
      'fourcoltworow' => array(
        'css' => array(
          '50fl' => array('.fourcoltworow > .panel-row-100 > .panel-row > .region,.fourcoltworow > .panel-row-100 > .panel-row' => 'width:50%;float:left'),
        ),
      ),
      'fourcoltworow-right-stack' => array(
        'css' => array(
          '50fl' => array('.fourcoltworow > .panel-row-100 > .panel-row,.fourcoltworow > .panel-row-100 > .row-2 > .region' => 'width:50%;float:left'),
          'fdw' => array('.fourcoltworow > .panel-row-100 > .row-1 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'fourcoltworow-2x2-grid' => array(
        'css' => array(
          '50' => array('.fourcoltworow > .panel-row-100 > .panel-row > .region' => 'width:50%'),
          'fdw' => array('.fourcoltworow > .panel-row-100 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'fourcoltworow-stack' => array(
        'css' => array(
          'fdw' => array('.fourcoltworow > .panel-row-100 > .panel-row > .region,.fourcoltworow > .panel-row-100 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for fourcoltworow.tpl.php
 */
function airtribune2_preprocess_fourcoltworow(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
