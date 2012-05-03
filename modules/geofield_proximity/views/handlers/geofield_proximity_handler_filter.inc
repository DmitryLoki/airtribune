<?php

/**
 * @file
 * Geofield proximity search filter
 */

class geofield_proximity_handler_filter extends views_handler_filter {
  var $always_multiple = TRUE;
  var $no_operator = TRUE;

  function option_definition() {
    $options = parent::option_definition();

    $options['value'] = array(
      'contains' => array(
        'origin'   => array('default' => ''),
        'distance' => array('default' => 100),
        'unit'     => array('default' => 6371),
      ),
      'default' => array(),
    );

    $options['geocoder'] = array('default' =>'google');

    return $options;
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type'             => 'geofield_proximity_search',
      '#title'            => t('Proximity search'),
      '#default_value'    => $this->value['origin'],
      '#unit_default'     => $this->value['unit'],
      '#distance_default' => $this->value['distance'],
    );
  }

  function query() {
    if (!empty($this->value['origin'])) {
      $geocoded = geocoder($this->options['geocoder'], $this->value['origin']);
      if ($geocoded) {
        $lat = $geocoded->getY();
        $long = $geocoded->getX();

        $lat_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lat');
        $lon_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lon');
        $this->ensure_my_table();
        $field = "$this->table_alias.$this->real_field";

        $radius = $this->value['unit'];
        $dist = $this->value['distance'];

        $haversine = geofield_haversine($lat, $long, $this->table_alias . '.' . $lat_alias, $this->table_alias . '.' . $lon_alias, $radius);

        $this->query->add_where_expression($this->options['group'], $haversine . ' <= ' . $dist);
      }
    }
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $services = geocoder_handler_info('text');

    $options = array();
    foreach ($services as $service) {
      $options[$service['name']] = $service['title'];
    }

    //FIXME: Get the services and geocoder() call working together properly
    $form['geocoder'] = array(
      '#type'        => 'select',
      '#title'       => t('Geocoding service'),
      '#description' => t('Select which geocoding service should be used.'),
      '#options'     => $options,
      '#default_value' => $this->options['geocoder'],
    );
  }

  function accept_exposed_input($input) {
    if (empty($this->options['exposed'])) {
      return TRUE;
    }
    //rewrite input value
    if (!empty($this->options['expose']['identifier'])) {
      $value = &$input[$this->options['expose']['identifier']];
      if (!is_array($value)) {
        $value = array(
          'origin' => $value,
        );
      }
    }
    return parent::accept_exposed_input($input);
  }
  
  function filter_item_is_exposed($name) {
    return !empty($this->options['expose']['use_' . $name]) && !empty($this->options['expose'][$name]);
  }
}
