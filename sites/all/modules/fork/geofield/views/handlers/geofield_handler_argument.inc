<?php

/**
 * @file
 * Distance field implementation.
 */

class geofield_handler_argument extends views_handler_argument {
  
  var $operator = NULL;
  
  function init(&$view, &$options){
    parent::init($view, $options);
    $this->operator = '<';
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $proximityPlugin = new geofieldProximityEntityURL();
    $proximityPlugin->option_definition($options, $this);
    $options['distance'] = array(
      'default' => 100
    );
    $options['unit'] = array(
      'default' => GEOFIELD_KILOMETERS
    );
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state); 
    $proximityPlugin = new geofieldProximityEntityURL();
    $proximityPlugin->options_form($form, $form_state, $this);
    $form['distance'] = array(
      '#type' => 'textfield',
      '#title' => t('Distance'),
      '#default_value' => !empty($this->options['distance']) ? $this->options['distance'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
    );
    $form['unit'] = array(
      '#type' => 'select',
      '#options' => geofield_radius_options(),
      '#title' => t('Unit'),
      '#default_value' => !empty($this->options['unit']) ? $this->options['unit'] : GEOFIELD_KILOMETERS,
      '#title_display' => 'invisible',
    );
  }
  
  function query($group_by = FALSE) {
    $entity = entity_metadata_wrapper($this->options['geofield_proximity_entity_url_entity_type'], $this->argument);
    $options = array();
    if (isset($entity->{$this->options['geofield_proximity_entity_url_field']})) {
      $options = $entity->{$this->options['geofield_proximity_entity_url_field']}->value();
    }
    if ($options) {
      $lat_alias = $this->definition['field_name'] . '_lat';
      $lon_alias = $this->definition['field_name'] . '_lon';
      $this->ensure_my_table();
      $haversine_options = array(
        'origin_latitude' => $options['lat'],
        'origin_longitude' => $options['lon'],
        'destination_latitude' => $this->table_alias . '.' . $lat_alias,
        'destination_longitude' => $this->table_alias . '.' . $lon_alias,
        'earth_radius' => $this->options['unit'],
      );
      $this->query->add_where_expression(0, geofield_haversine($haversine_options) . ' ' .$this->operator . ' ' . $this->options['distance']);     
    }
  }
}
