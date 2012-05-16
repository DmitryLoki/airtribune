<?php

/**
 * @file
 * Distance field implementation.
 */

class geofield_handler_field extends views_handler_field_numeric {
  function query() {
    $this->ensure_my_table();

    switch ($this->options['source']) {
      case 'geocode':
        $geocoded_data_raw = geocoder($this->options['geocoder'], $this->options['geocoder_location']);
        if ($geocoded_data_raw) {
          $this->options['source_lon'] = $geocoded_data_raw->getX();
          $this->options['source_lat'] = $geocoded_data_raw->getY();
        }
        break;
      case 'other_geofield':
        if (!empty($this->options['other_geofield'])) {
          $other_geofield = $this->view->display_handler->get_handler('field', $this->options['other_geofield']);
          $this->query->add_field($other_geofield->table, $other_geofield->definition['field_name'] . '_lat');
          $this->query->add_field($other_geofield->table, $other_geofield->definition['field_name'] . '_lon');
          $this->options['source_lat'] = $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lat';
          $this->options['source_lon'] = $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lon';
        }
        break;
      default:
        break;
    }

    $lat_alias = $this->table_alias . '.' . $this->definition['field_name'] . '_lat';
    $lon_alias = $this->table_alias . '.' . $this->definition['field_name'] . '_lon';

    $this->field_alias = $this->query->add_field(NULL, geofield_haversine($this->options['source_lat'], $this->options['source_lon'], $lat_alias, $lon_alias, $this->options['radius_of_earth']), $this->table_alias . '_' . $this->field);
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    // Geocoder options
    if (module_exists('geocoder')) {
      $options['geocoder'] = array('default' => 'google'); // @TODO: load from geocoder list of available plugins, pull first.
      $options['geocoder_location'] = array('default' => '');
    }
    // Other geofield
    $options['other_geofield'] = array('default' => '');
    // Raw origin point values.
    $options['source_lat'] = array('default' => 0);
    $options['source_lon'] = array('default' => 0);
    $options['radius_of_earth'] = array('default' => GEOFIELD_KILOMETERS);
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

    $form['source_lat'] = array(
      '#type' => 'textfield',
      '#title' => t('Latitude of origin point.'),
      '#description' => t(''),
      '#default_value' => $this->options['source_lat'],
      '#dependency' => array(
        'edit-options-source' => array('manual'),
      ),
    );
    $form['source_lon'] = array(
      '#type' => 'textfield',
      '#title' => t('Longitude of origin point.'),
      '#description' => t(''),
      '#default_value' => $this->options['source_lon'],
      '#dependency' => array(
        'edit-options-source' => array('manual'),
      ),
    );

    if (module_exists('geocoder')) {
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

      $form['geocoder_location'] = array(
        '#type' => 'textfield',
        '#title' => t('Geocoded Location'),
        '#default_value' => $this->options['geocoder_location'],
        '#dependency' => array(
          'edit-options-source' => array('geocode'),
        ),
      );
    }

    $handlers = $this->view->display_handler->get_handlers('field');
    $other_geofield_options = array(
      '' => '<none>',
    );

    foreach ($handlers as $handle) {
      if (!empty($handle->field_info['type']) && $handle->field_info['type'] == 'geofield') {
        $other_geofield_options[$handle->options['id']] = (!empty($handle->options['label'])) ? $handle->options['label'] : $handle->options['id'];
      }
    }

    $form['other_geofield'] = array(
      '#type' => 'select',
      '#title' => t('Other Geofield'),
      '#description' => t(''),
      '#default_value' => $this->options['other_geofield'],
      '#options' => $other_geofield_options,
      '#dependency' => array(
        'edit-options-source' => array('other_geofield'),
      ),
    );

    $form['radius_of_earth'] = array(
      '#type' => 'select',
      '#title' => t('Unit of Measure'),
      '#description' => '',
      '#options' => geofield_radius_options(),
      '#default_value' => $this->options['radius_of_earth'],
    );
  }

  function options_validate(&$form, &$form_state) {
    if ($form_state['values']['options']['source'] == 'geocode') {
      if (!geocoder($form_state['values']['options']['geocoder'], $form_state['values']['options']['geocoder_location'])) {
        form_set_error('options][geocoder_location', t('Geocoder cannot find this location. Check your connection or add a findable location.'));
      }
    }
    if ($form_state['values']['options']['source'] == 'other_geofield' && $form_state['values']['options']['other_geofield'] == '') {
      form_set_error('options][other_geofield', t('Please select a geofield.'));
    }
  }

  function get_value($values, $field = NULL) {
    if (isset($values->{$this->field_alias})) {
      return $values->{$this->field_alias};
    }
  }
}
