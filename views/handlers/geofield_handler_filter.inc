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
    switch ($this->options['source']) {
      case 'geocode':
        if (!empty($this->value['origin'])) {
          if ($origin_geo = geocoder('google', $this->value['origin'])) {
            $lat_origin = $origin_geo->getY();
            $lon_origin = $origin_geo->getX();
          }
        }
        break;
    }
    $lat_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lat');
    $lon_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lon');
    $this->ensure_my_table();

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}(geofield_haversine($lat_origin, $lon_origin, $this->table_alias . '.' . $lat_alias, $this->table_alias . '.' . $lon_alias, $this->value['unit']));
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
    $this->query->add_where_expression($this->options['group'], $field . ' ' . $this->operator . ' ' . $this->value['distance']);
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    $options['value'] = array(
      'default' => array(
        'distance' => 100,
        'unit' => GEOFIELD_KILOMETERS,
        'origin' => array(),
      ),
    );
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
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'geofield_proximity',
      '#title' => t('Proximity Search'),
      '#default_value' => array(
        'distance' => $this->value['distance'],
        'unit' => $this->value['unit'],
        'origin' => $this->value['origin'],
      ),
    );
  }

  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    $options = $this->operator_options('short');
    $output = check_plain($options[$this->operator]);
    if (in_array($this->operator, $this->operator_values(2))) {
      $output .= ' ' . t('@min and @max', array('@min' => $this->value['min'], '@max' => $this->value['max']));
    }
    elseif (in_array($this->operator, $this->operator_values(1))) {
      $output .= ' ' . check_plain($this->value['distance']);
    }
    return $output;
  }

  /**
   * Check to see if input from the exposed filters should change
   * the behavior of this filter.
   *   - @TODO: This could be more polished.
   */
  function accept_exposed_input($input) {
    if ($input['field_geofield_distance']['distance'] === '' || $input['field_geofield_distance']['origin'] === '') {
      return FALSE;
    }

    $this->value['distance'] = $input['field_geofield_distance']['distance'];
    $this->value['unit'] = $input['field_geofield_distance']['unit'];
    $this->value['origin'] = $input['field_geofield_distance']['origin'];
    return TRUE;
  }
}