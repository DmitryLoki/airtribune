<?php


/**
 * Implements hook_field_formatter_info().
 *
 */
function geofield_field_formatter_info() {
  return array(
    'default' => array(
      'label' => t('Default geo field'),
      'field types' => array('geofield'),
    ),
  );
}