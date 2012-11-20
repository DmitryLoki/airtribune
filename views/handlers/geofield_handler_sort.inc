<?php

/**
 * @file
 * Distance sort implementation.
 */

class geofield_handler_sort extends views_handler_sort {
  function query() {
    $this->ensure_my_table();
    $lat_alias = $this->table_alias . '.' . $this->definition['field_name'] . '_lat';
    $lon_alias = $this->table_alias . '.' . $this->definition['field_name'] . '_lon';

    $proximityPlugin = geofield_proximity_load_plugin($this->options['source']);
    $options = $proximityPlugin->query($this);

    if ($options != FALSE) {
      $haversine_options = array(
        'origin_latitude' => $lat_alias,
        'origin_longitude' => $lon_alias,
        'destination_latitude' => $options['destination_latitude'],
        'destination_longitude' => $options['destination_longitude'],
        'earth_radius' => GEOFIELD_KILOMETERS,
      );

      $this->query->add_orderby(NULL, geofield_haversine($haversine_options), $this->options['order'], $this->table_alias . '_geofield_distance');
    }    
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    
    $proximityHandlers = geofield_proximity_views_handlers();
    foreach ($proximityHandlers as $key => $handler) {
      $proximityPlugin = new $handler['class']();
      $proximityPlugin->option_definition($options, $this);
    } 
    
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['source'] = array(
      '#type' => 'select',
      '#title' => t('Source of Origin Point'),
      '#description' => t('How do you want to enter your origin point?'),
      '#options' => array(),
      '#default_value' => $this->options['source'],
    );

    $proximityHandlers = geofield_proximity_views_handlers();
    foreach ($proximityHandlers as $key => $handler) {
      $form['source']['#options'][$key] = $handler['name'];

      $proximityPlugin = new $handler['class']();
      $proximityPlugin->options_form($form, $form_state, $this);
    }
  }
}
