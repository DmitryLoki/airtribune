<?php

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Map Form Values Behavior
 */
class openlayers_behavior_geofield extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    //TODO: use the field name and the delta in naming these items so we don't get conflicts
    return array(
        'wkt' => '#wkt',
        'type' => '#type',
        'lat' => '#lat',
        'lon' => '#lon',
        'left' => '#left',
        'bottom' => '#bottom',
        'right' => '#right',
        'top' => '#top',
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'geofield') .'/includes/behaviors/js/openlayers_behavior_geofield.js');
    return $this->options;
  }
}
