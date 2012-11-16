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
    /*switch ($this->options['source']) {
      case 'manual':
        $lat_origin = $this->value['origin']['lat'];
        $lon_origin = $this->value['origin']['lon'];
        break;
      case 'geocode':
        $origin_value = trim($this->value['origin']);
        if (!empty($origin_value)) {
          if ($origin_geo = geocoder($this->options['geocoder'], $origin_value)) {
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
    }*/

    $proximityPlugin = geofield_proximity_load_plugin($this->options['source']);
    $options = $proximityPlugin->query($this);

    if ($options) {
      $lat_alias = $this->definition['field_name'] . '_lat';
      $lon_alias = $this->definition['field_name'] . '_lon';
      $this->ensure_my_table();

      $info = $this->operators();
      if (!empty($info[$this->operator]['method'])) {
        $haversine_options = array(
          'origin_latitude' => $this->table_alias . '.' . $lat_alias,
          'origin_longitude' => $this->table_alias . '.' . $lon_alias,
          'destination_latitude' => $options['destination_latitude'],
          'destination_longitude' => $options['destination_longitude'],
          'earth_radius' => $this->value['unit'],
        );
        $this->{$info[$this->operator]['method']}($haversine_options);
      }
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
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'geofield') . '/js/viewsProximityValue.js',
        ),
      ),
      '#default_value' => $this->options['source'],
    );

    $form['source_change'] = array(
      '#type' => 'submit',
      '#value' => 'Change Source Widget',
      '#submit' => array('geofield_views_ui_change_proximity_widget'),
    );

    $proximityHandlers = geofield_proximity_views_handlers();
    foreach ($proximityHandlers as $key => $handler) {
      $form['source']['#options'][$key] = $handler['name'];

      $proximityPlugin = new $handler['class']();
      $proximityPlugin->options_form($form, $form_state, $this);
    }

    // Look for any top-level item with a #proximity_plugin_value_element set. If found, it doesn't
    // belong in this particular field.
    foreach ($form as $key =>$form_item) {
      if (isset($form_item['#proximity_plugin_value_element']) && $form_item['#proximity_plugin_value_element'] == TRUE) {
        unset($form[$key]);
      }
    }

    /*if (module_exists('geocoder')) {
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
    }*/
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'geofield_proximity',
      '#title' => t('Proximity Search'),
      '#default_value' => array(
        'distance' => $this->value['distance'],
        'unit' => $this->value['unit'],
        'origin' => (is_string($this->value['origin'])) ? trim($this->value['origin']) : $this->value['origin'],
      ),
      '#origin_options' => array(
        '#attributes' => array(
          'class' => array('geofield-proximity-origin'),
        ),
      ),
    );

    $proximityPlugin = geofield_proximity_load_plugin($this->options['source']);
    $proximityPlugin->value_form($form, $form_state, $this);
    /*
    switch ($this->options['source']) {
      case 'manual':
        $form['value']['#origin_element'] = 'geofield_latlon';
        break;
      case 'geocode':
        break;
      case 'other_geofield':
        $form['value']['#origin_element'] = 'select';
        $form['value']['#origin_options'] += array(
          '#options' => $this->get_other_geofield_options(),
        );
        break;
    }*/

    if (in_array($this->operator, array('between', 'not between'))) {
      $form['value']['#geofield_range'] = TRUE;
      $form['value']['#default_value']['distance2'] = $this->value['distance2'];
    }
  }

  function value_validate($form, &$form_state) {
    if (isset($form_state['validate_handlers'][0])) {
      $form_state['validate_handlers'] = array();
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
    if (empty($input['field_geofield_distance']) || $input['field_geofield_distance']['distance'] === '' || $input['field_geofield_distance']['origin'] === '') {
      return FALSE;
    }

    $this->value['distance'] = $input['field_geofield_distance']['distance'];
    $this->value['unit'] = $input['field_geofield_distance']['unit'];
    $this->value['origin'] = $input['field_geofield_distance']['origin'];
    return TRUE;
  }

  /**
   * Helper function to retreive lat/lon points for other handlers who want to interact with this handler.
   *
   * @return
   *   An array with elements 'lat' and 'lon.' Either element can either be a float or a string (signifying a particular database field).
   */

  function get_calculated_geospatial() {
    $return = array();
    switch ($this->options['source']) {
      case 'manual':
        $return = array(
          'lat' => $this->value['origin']['lat'],
          'lon' => $this->value['origin']['lon'],
        );
        break;
      case 'geocode':
        $point = geocoder($this->options['geocoder'], $this->value['origin']);
        if (!empty($point)) {
          $return = array(
            'lat' => $point->getY(),
            'lon' => $point->getX(),
          );
        }
        else {
          $return = FALSE;
        }
        break;
      case 'other_geofield':
        $other_geofield = $this->view->display_handler->get_handler('field', $this->value['origin']);
        $return = array(
          'lat' => $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lat',
          'lon' => $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lon',
        );
        break;
      default:
        return FALSE;
    }

    return $return;
  }

  /**
   * Helper function to retreive other geofield options for 'Other Geofield' source.
   */

  function get_other_geofield_options() {
    $handlers = $this->view->display_handler->get_handlers('field');
    $other_geofield_options = array();

    foreach ($handlers as $handle) {
      if (!empty($handle->field_info['type']) && $handle->field_info['type'] == 'geofield') {
        $other_geofield_options[$handle->options['id']] = (!empty($handle->options['label'])) ? $handle->options['label'] : $handle->options['id'];
      }
    }

    return $other_geofield_options;
  }
}

function geofield_views_ui_change_proximity_widget($form, &$form_state) {
  $item = &$form_state['handler']->options;
  $changed = $item['source'] != $form_state['values']['options']['source'];
  $item['source'] = $form_state['values']['options']['source'];

  if ($changed) {
    if ($item['source'] == 'manual') {
      $item['value']['origin'] = array('lat' => '', 'lon' => '');
    }
    else {
      $item['value']['origin'] = '';
    }
  }

  $form_state['view']->set_item($form_state['display_id'], $form_state['type'], $form_state['id'], $item);

  views_ui_cache_set($form_state['view']);
  $form_state['rerender'] = TRUE;
  $form_state['rebuild'] = TRUE;
  $form_state['force_expose_options'] = TRUE;
}
