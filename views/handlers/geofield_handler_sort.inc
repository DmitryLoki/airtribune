<?php

/**
 * @file
 * Distance sort implementation.
 */

class geofield_handler_sort extends views_handler_sort {
  function query() {
    $this->ensure_my_table();

    switch ($this->options['source']) {
      case 'manual':
        break;
      case 'geocode':
        if (!empty($this->options['geocoder_location'])) {
          if ($origin_geo = geocoder($this->options['geocoder'], $this->options['geocoder_location'])) {
            $this->options['source_lat'] = $origin_geo->getY();
            $this->options['source_lon'] = $origin_geo->getX();
          }
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
      case 'exposed_filter':
        $exposed_filter = $this->view->display_handler->get_handler('filter', 'field_geofield_distance');
        if (!empty($exposed_filter)) {
          $geocoded_data_raw = $exposed_filter->get_calculated_geospatial();
          if ($geocoded_data_raw) {
            $this->options['source_lon'] = $geocoded_data_raw['lon'];
            $this->options['source_lat'] = $geocoded_data_raw['lat'];
          }
        }
        break;
      default:
        break;
    }

    $haversine_options = array(
      'origin_latitude' => $this->table_alias . '.' . $this->definition['field_name'] . '_lat',
      'origin_longitude' => $this->table_alias . '.' . $this->definition['field_name'] . '_lon',
      'destination_latitude' => $this->options['source_lat'],
      'destination_longitude' => $this->options['source_lon'],
      'earth_radius' => GEOFIELD_KILOMETERS,
    );
    $this->query->add_orderby(NULL, geofield_haversine($haversine_options), $this->options['order'], $this->table_alias . '_geofield_distance');
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
        'exposed_filter' => t('Exposed Filter'),
      ),
      '#default_value' => $this->options['source'],
    );

    if (module_exists('geocoder')) {
      $form['source']['#options']['geocode'] = t('Geocode');
    }

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
  }
}
