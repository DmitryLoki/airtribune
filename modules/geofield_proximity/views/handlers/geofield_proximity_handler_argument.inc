<?php

/**
 * @file
 * Geofield proximity search argument / contextual filter
 */

class geofield_proximity_handler_argument extends views_handler_argument {
  function init(&$view, &$options) {
    parent::init($view, $options);
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['radius'] = array(
      'dist'            => array('default' => 100),
      'radius_of_earth' => array('default' => 6371),
    );
    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, &$form_state);

    $form['radius'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Radius'),
      '#description' => t('Radius will be used when an argument is provided and geocoded. Nodes within the radius around the geocoded orgin will be shown in the results.'),
      '#tree'        => TRUE,
      '#attributes'  => array(
        'class'      => array('exposed-proximity-radius'),
      ),
    );

    $form['radius']['dist'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Distance'),
      '#default_value' => (!empty($this->options['radius']['dist'])) ? $this->options['radius']['dist'] : 100,
      '#size'          => 4,
      '#title_display' => 'invisible',
    );

    $form['radius']['radius_of_earth'] = array(
      '#type'          => 'select',
      '#title'         => t('Unit of Measurement'),
      '#options'       => geofield_radius_options(),
      '#default_value' => (!empty($this->options['radius']['radius_of_earth'])) ? $this->options['radius']['radius_of_earth'] : '6371',
      '#title_display' => 'invisible',
    );
  }

  function query() {

    if (!empty($this->argument)) {
      $geocoded = geocoder('yahoo', $this->argument);
      if ($geocoded) {
        $lat  = $geocoded->coords[1];
        $long = $geocoded->coords[0];

        $lat_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lat');
        $lon_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lon');

        $this->ensure_my_table();

        $field  = "$this->table_alias.$this->real_field";
        $radius = $this->options['radius']['radius_of_earth'];
        $dist   = $this->options['radius']['dist'];

        $haversine = geofield_haversine($lat, $long, $this->table_alias . '.' . $lat_alias, $this->table_alias . '.' . $lon_alias, $radius);

        $this->query->add_where_expression(0, $haversine . ' <= ' . $dist);
      }
    }
  }
}
