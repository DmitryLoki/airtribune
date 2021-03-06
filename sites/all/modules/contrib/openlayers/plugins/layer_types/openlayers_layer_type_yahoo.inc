<?php
/**
 * @file
 * Yahoo Layer Type
 */

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_yahoo_openlayers_layer_types() {
  return array(
    'title' => t('Yahoo'),
    'description' => t('Yahoo Maps API Map'),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_yahoo.inc',
      'class' => 'openlayers_layer_type_yahoo',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * OpenLayers Yahoo Layer Type class
 */
class openlayers_layer_type_yahoo extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_handler' => 'yahoo',
    ) + parent::options_init();
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    $warning = (!variable_get('openlayers_layers_yahoo_api', FALSE)) ?
      array('#value' => t('WARNING: Your Yahoo API key is not set.
        Map including Yahoo layers will break until it is set correctly.')
      ) : NULL;

    $yahoo_layer_types = array(
      'hybrid' => 'Hybrid',
      'street' => 'Street',
      'satellite' => 'Satellite',
    );

    return array(
      'type' => array(
        '#title' => t('Yahoo Layer Type'),
        '#type' => 'select',
        '#default_value' => isset($this->data['type']) ?
          $this->data['type'] : 'normal',
        '#options' => $yahoo_layer_types
      ),
      $warning
    );
  }

  function settings_form() {
    return array(
      'openlayers_layers_yahoo_api' => array(
        '#type' => 'textfield',
        '#title' => t('Yahoo API Key'),
        '#default_value' => variable_get('openlayers_layers_yahoo_api', ''),
      )
    );
  }


  /**
   * Render.
   */
  function render(&$map) {
    static $yahoo_maps_included;

    if (!isset($yahoo_maps_included)) {
      drupal_add_js("//api.maps.yahoo.com/ajaxymap?v=3.0&appid=" .
          variable_get('openlayers_layers_yahoo_api', ''),
        'external');
      drupal_add_js(drupal_get_path('module', 'openlayers') .
        '/plugins/layer_types/openlayers_layer_type_yahoo.js');
      $yahoo_maps_included = TRUE;
    }
  }
}
