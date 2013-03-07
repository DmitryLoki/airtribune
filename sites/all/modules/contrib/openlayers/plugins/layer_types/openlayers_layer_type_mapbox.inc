<?php

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_mapbox_openlayers_layer_types() {
  return array(
    'title' => t('MapBox'),
    'description' => t('<a href="!url">MapBox</a> Custom Map',
      array('!url' => 'http://mapbox.com/')),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_mapbox.inc',
      'class' => 'openlayers_layer_type_mapbox',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * @file MapBox layer type definition for OpenLayers
 */
class openlayers_layer_type_mapbox extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'url' => array(
        'http://a.tiles.mapbox.com/mapbox/',
        'http://b.tiles.mapbox.com/mapbox/',
        'http://c.tiles.mapbox.com/mapbox/',
        'http://d.tiles.mapbox.com/mapbox/',
      ),
      'osm' => FALSE,
      'layername' => '',
      'layer_handler' => 'MapBox',
      'type' => 'png',
    ) + parent::options_init();
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textarea',
        '#title' => t('Base URLs'),
        '#description' => t('The list of base URLs specified on !tiles (with trailing "/"). For details, visit the !support site.', array(
          '!tiles' => l(t('TileStream'), 'http://tiles.mapbox.com/'),
          '!support' => l(t('MapBox Support'), 'http://support.mapbox.com/kb/tilestream/using-tilestream-with-drupal'),
        )),
        '#default_value' => !empty($this->data['url']) ? implode("\n", $this->data['url']) : '',
      ),
      'layername' => array(
        '#type' => 'textfield',
        '#title' => t('MapBox Layer Name'),
        '#description' => t('The layer name specified on !tiles.', array(
          '!tiles' => l(t('TileStream'), 'http://tiles.mapbox.com/'),
        )),
        '#default_value' => $this->data['layername']
      ),
      'osm' => array(
        '#type' => 'checkbox',
        '#default_value' => $this->data['osm'],
        '#title' => t('OSM Attribution'),
        '#description' => t('Required if OpenStreetMap data is used.'),
      ),
      'type' => array(
        '#title' => t('File extension'),
        '#type' => 'select',
        '#default_value' => $this->data['type'],
        '#options' => drupal_map_assoc(array('png', 'jpg')),
      ),
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(array_map('strval', openlayers_get_resolutions('900913')), range(0, 21)),
        '#title' => t('Zoom Level Range'),
        '#default_value' => isset($this->data['resolutions']) ? array_map('strval', $this->data['resolutions']) : array(),
      ),
    );
  }

  function options_form_validate($form, &$form_state) {
    $form_state['data']['url'] = explode("\n", $form_state['data']['url']);
    $form_state['data']['resolutions'] = array_map('floatval', array_values($form_state['data']['resolutions']));
    $form_state['data']['projection'] = array_values($form_state['data']['projection']);
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') . '/plugins/layer_types/openlayers_layer_type_mapbox.js');
  }
}
