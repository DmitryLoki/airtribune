<?php

/**
 * @file
 */

class geofieldProximityManual extends geofieldProximityBase implements geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin) {
    $options['geofield_proximity_manual'] = array(
      'default' => array(
        'lat' => 0,
        'lon' => 0,
      )
    );
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    $form['geofield_proximity_manual'] = array(
      '#type' => 'geofield_latlon',
      '#title' => t('Source'),
      '#default_value' => $views_plugin->options['geofield_proximity_manual'],
      '#states' => array(
        'visible' => array(
          ':input[name="options[source]"]' => array('value' => 'manual'),
        ),
      ),
      '#proximity_plugin_value_element' => TRUE,
    );
  }

  public function value_form(&$form, &$form_state, $views_plugin) {
    $form['value']['#origin_element'] = 'geofield_latlon';
  }

  public function query($views_plugin) {
    return array(
      'destination_latitude' => (isset($views_plugin->value)) ? $views_plugin->value['origin']['lat'] : $views_plugin->options['geofield_proximity_manual']['lat'],
      'destination_longitude' => (isset($views_plugin->value)) ? $views_plugin->value['origin']['lon'] : $views_plugin->options['geofield_proximity_manual']['lon'],
    );
  }
}