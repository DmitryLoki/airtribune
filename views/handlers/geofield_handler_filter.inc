<?php

/**
 * @file
 * Distance filter implementation.
 */

class geofield_handler_filter extends views_handler_filter_numeric {

    function operators() {
    $operators = array(
      '<' => array(
        'title' => t('Is less than'),
        'method' => 'op_simple',
        'short' => t('<'),
        'values' => 1,
      ),
      '<=' => array(
        'title' => t('Is less than or equal to'),
        'method' => 'op_simple',
        'short' => t('<='),
        'values' => 1,
      ),
      '=' => array(
        'title' => t('Is equal to'),
        'method' => 'op_simple',
        'short' => t('='),
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'method' => 'op_simple',
        'short' => t('!='),
        'values' => 1,
      ),
      '>=' => array(
        'title' => t('Is greater than or equal to'),
        'method' => 'op_simple',
        'short' => t('>='),
        'values' => 1,
      ),
      '>' => array(
        'title' => t('Is greater than'),
        'method' => 'op_simple',
        'short' => t('>'),
        'values' => 1,
      ),
      'between' => array(
        'title' => t('Is between'),
        'method' => 'op_between',
        'short' => t('between'),
        'values' => 2,
      ),
      'not between' => array(
        'title' => t('Is not between'),
        'method' => 'op_between',
        'short' => t('not between'),
        'values' => 2,
      ),
    );

    return $operators;
  }

  function query() {
    $lat_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lat');
    $lon_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lon');
    $this->ensure_my_table();

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}(geofield_haversine($this->options['dist_lat'], $this->options['dist_lon'], $this->table_alias . '.' . $lat_alias, $this->table_alias . '.' . $lon_alias, $this->options['radius_of_earth']));
    }
  }

  function op_between($field) {
    if ($this->operator == 'between') {
      $this->query->add_where_expression($this->options['group'], $field, array($this->value['min'], $this->value['max']), 'BETWEEN');
    }
    else {
      // @TODO: Figure out how to do this with add_where_expression.
      //$this->query->add_where($this->options['group'], db_or()->condition($field, $this->value['min'], '<=')->condition($field, $this->value['max'], '>='));
    }
  }

  function op_simple($field) {
    $this->query->add_where_expression($this->options['group'], $field . ' ' . $this->operator . ' ' . $this->value['value']);
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    // Geocoder options
    if (module_exists('geocoder')) {
      $options['geocoder'] = array('default' => 'google'); // @TODO: load from geocoder list of available plugins, pull first.
      $options['geocoder_location'] = array(
        'contains' => array(
          'origin' => array('default' => ''),
          'distance' => array('default' => 100),
          'unit' => array('default' => 6371),
        ),
        'default' => array(),
      );
    }
    // Other geofield
    $options['other_geofield'] = array('default' => '');
    // Raw origin point values.
    $options['source_lat'] = array('default' => 0);
    $options['source_lon'] = array('default' => 0);
    $options['radius_of_earth'] = array('default' => '6371');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['source'] = array(
      '#type' => 'select',
      '#title' => t('Source of Origin Point'),
      '#description' => t('How do you want to enter your origin point?'),
      '#options' => array(
        'manual' => t('Manually Enter Point'),
        'other_geofield' => t('Other Geofield'),
      ),
      '#default_value' => $this->options['source'],
    );

    if (module_exists('geocoder')) {
      $form['source']['#options']['geocode'] = t('Geocode');
    }

    $form['dist_lat'] = array(
      '#type' => 'textfield',
      '#title' => t('Latitude of origin point.'),
      '#description' => t(''),
      '#default_value' => $this->options['dist_lat'],
    );
    $form['dist_lon'] = array(
      '#type' => 'textfield',
      '#title' => t('Longitude of origin point.'),
      '#description' => t(''),
      '#default_value' => $this->options['dist_lon'],
    );

    $form['radius_of_earth'] = array(
      '#type' => 'select',
      '#title' => t('Unit of Measure'),
      '#description' => '',
      '#options' => geofield_radius_options(),
      '#default_value' => $this->options['radius_of_earth'],
    );
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
}
