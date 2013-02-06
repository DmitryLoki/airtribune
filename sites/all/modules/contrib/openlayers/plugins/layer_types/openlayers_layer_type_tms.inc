<?php
/**
 * @file
 * TMS Layer Type
 */

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_tms_openlayers_layer_types() {
  return array(
    'title' => t('TMS'),
    'description' => t('<a href="!url">Tile Map Service</a>',
      array('!url' => 'http://en.wikipedia.org/wiki/Tile_Map_Service')),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_tms.inc',
      'class' => 'openlayers_layer_type_tms',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * OpenLayers TMS Layer Type class
 */
class openlayers_layer_type_tms extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_handler' => 'tms',
      'type' => 'png',
      'wrapDateLine' => false,
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
          $this->data['base_url'] : '',
        '#description' => t('This is the base URL of the TMS service.  For example, if this was your tile scheme URL: http://example.com/tms/1.0.0/layer_name/{z}/{y}/{x}.png, then <em>http://example.com/tms/</em> would be the Base URL.'),
      ),
      'layername' => array(
        '#type' => 'textfield',
        '#title' => t('Layer Name'),
        '#default_value' => isset($this->data['layername']) ?
          $this->data['layername'] : '',
        '#description' => t('This is the base URL of the TMS service.  For example, if this was your tile scheme URL: http://example.com/tms/1.0.0/layer_name/{z}/{y}/{x}.png, then <em>layer_name</em> would be the Layer Name.'),
      ),
      'type' => array(
        '#type' => 'select',
        '#title' => t('File Format'),
        '#options' => array(
          'png' => 'png',
          'jpg' => 'jpg'),
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
          array_map('strval', openlayers_get_resolutions('900913')),
        '#description' => t('The available zoom levels for the tiles.'),
      ),
      'wrapDateLine' => array(
        '#type' => 'checkbox',
        '#title' => t('Wrap Dateline'),
        '#default_value' => isset($this->data['type']) ?
          $this->data['type'] : False,
        '#description' => t('Wrapping the dateline will cause the map to appear to repeat itself when going east or west.  This may not be supported by all tilesets.'),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .
      '/plugins/layer_types/openlayers_layer_type_tms.js');
  }
}
