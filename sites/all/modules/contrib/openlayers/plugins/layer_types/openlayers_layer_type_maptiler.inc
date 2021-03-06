<?php
/**
 * @file
 * TileWarper Layer Type
 */

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_maptiler_openlayers_layer_types() {
  return array(
    'title' => t('MapTiler'),
    'description' => t('<a href="!url">MapTiler</a> or GDAL2Tiles',
      array('!url' => 'http://www.maptiler.org/')),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_maptiler.inc',
      'class' => 'openlayers_layer_type_maptiler',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * OpenLayers MapTiler Layer Type class
 */
class openlayers_layer_type_maptiler extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'type' => 'png',
      'layer_handler' => 'maptiler',
    ) + parent::options_init();
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
      'base_url' => array(
        '#type' => 'textfield',
        '#title' => t('Base URL'),
        '#default_value' => isset($this->data['base_url']) ?
          $this->data['base_url'] : ''
      ),
      'type' => array(
        '#type' => 'select',
        '#options' => array(
          'jpg' => 'JPG',
          'png' => 'PNG'
        ),
        '#default_value' => isset($this->data['type']) ?
          $this->data['type'] : 'png'
      ),
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(
          array_map('strval', openlayers_get_resolutions('900913')),
          range(0, 21)
        ),
        '#title' => t('Zoom Level Range'),
        '#default_value' => isset($this->data['resolutions']) ?
          $this->data['resolutions'] :
          array_map('strval', openlayers_get_resolutions('900913'))
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .
      '/plugins/layer_types/openlayers_layer_type_maptiler.js');
  }
}
