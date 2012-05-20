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
      case 'manual':
        $lat_origin = $this->value['origin']['lat'];
        $lon_origin = $this->value['origin']['lon'];
        break;
      case 'geocode':
        if (!empty($this->value['origin'])) {
          if ($origin_geo = geocoder($this->options['geocoder'], $this->value['origin'])) {
            $lat_origin = $origin_geo->getY();
            $lon_origin = $origin_geo->getX();
          }
        }
        break;
      case 'other_geofield':
        if (!empty($this->value['origin'])) {
          $other_geofield = $this->view->display_handler->get_handler('field', $this->value['origin']);
          $this->query->add_field($other_geofield->table, $other_geofield->definition['field_name'] . '_lat');
          $this->query->add_field($other_geofield->table, $other_geofield->definition['field_name'] . '_lon');
          $lat_origin = $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lat';
          $lon_origin = $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lon';
        }
        break;
    }
    $lat_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lat');
    $lon_alias = $this->query->add_field($this->table_alias, $this->definition['field_name'] . '_lon');
    $this->ensure_my_table();

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $haversine_options = array(
        'origin_latitude' => $lat_origin,
        'origin_longitude' => $lon_origin,
        'destination_latitude' => $this->table_alias . '.' . $lat_alias,
        'destination_longitude' => $this->table_alias . '.' . $lon_alias,
        'earth_radius' => $this->value['unit'],
      );
      $this->{$info[$this->operator]['method']}($haversine_options);
    }
  }

  function op_between($options) {
    $this->query->add_where_expression($this->options['group'], geofield_haversine($options) . ' ' . strtoupper($this->operator) . ' ' . $this->value['distance'] . ' AND ' . $this->value['distance2']);
  }

  function op_simple($options) {
    $this->query->add_where_expression($this->options['group'], geofield_haversine($options) . ' ' . $this->operator . ' ' . $this->value['distance']);
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    $options['value'] = array(
      'default' => array(
        'distance' => 100,
        'distance2' => 200,
        'unit' => GEOFIELD_KILOMETERS,
        'origin' => array(),
      ),
    );
    if (module_exists('geocoder')) {
      $options['geocoder'] = array('default' => 'google');
    }
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

      $geocoders_raw = geocoder_handler_info('text');
      $geocoder_options = array();
      foreach ($geocoders_raw as $key => $geocoder) {
        $geocoder_options[$key] = $geocoder['title'];
      }
      $form['geocoder'] = array(
        '#type' => 'select',
        '#title' => t('Geocoding Service'),
        '#options' => $geocoder_options,
        '#default_value' => $this->options['geocoder'],
        '#dependency' => array(
          'edit-options-source' => array('geocode'),
        ),
      );
    }
  }

  function value_form(&$form, &$form_state) {
    //kpr($this);

    $form['value'] = array(
      '#type' => 'geofield_proximity',
      '#title' => t('Proximity Search'),
      '#default_value' => array(
        'distance' => $this->value['distance'],
        'unit' => $this->value['unit'],
        'origin' => $this->value['origin'],
      ),
    );

    switch ($this->options['source']) {
      case 'manual':
        $form['value']['#origin_element'] = 'geofield_latlon';
        break;
      case 'geocode':

        break;
      case 'other_geofield':
        $handlers = $this->view->display_handler->get_handlers('field');
        $other_geofield_options = array();

        foreach ($handlers as $handle) {
          if (!empty($handle->field_info['type']) && $handle->field_info['type'] == 'geofield') {
            $other_geofield_options[$handle->options['id']] = (!empty($handle->options['label'])) ? $handle->options['label'] : $handle->options['id'];
          }
        }

        $form['value']['#origin_element'] = 'select';
        $form['value']['#origin_options'] = array(
          '#options' => $other_geofield_options,
        );
        break;
    }

    if (in_array($this->operator, array('between', 'not between'))) {
      $form['value']['#geofield_range'] = TRUE;
      $form['value']['#default_value']['distance2'] = $this->value['distance2'];
    }
  }

  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    $options = $this->operator_options('short');
    $output = check_plain($options[$this->operator]);
    if (in_array($this->operator, $this->operator_values(2))) {
      $output .= ' ' . t('@min and @max', array('@min' => $this->value['distance'], '@max' => $this->value['distance2']));
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