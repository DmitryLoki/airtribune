<?php

class geofield_proximity_handler_field extends geofield_handler_field {

  function query() {
    // Get the referenced filter.
    $filter = $this->options['location'];
    // Get the referenced filter hanlder.
    $handler = $this->view->display_handler->get_handler('filter', $filter);

    // If the filter is exposed, get the real values:
    if (!empty($this->view->exposed_raw_input)) {
      $location = $this->view->exposed_raw_input[$filter]['origin'];
    }
    // Otherwise, get the filter hanlder's default values...
    else {
      $location = $handler->options['value']['origin'];
    }

    // Geolocate based on this value.
      // @TODO don't geolcoate the same string more than once.  Cache?  Relationship?
    $geocoded = geocoder($handler->options['geocoder'], $location);
    if ($geocoded) {
      $lat = $geocoded->getY();
      $long = $geocoded->getX();

      // Get the real geofield.
      $geofield = $this->view->field[$this->real_field];

      $this->ensure_my_table();
      $radius_of_earth = $handler->options['value']['unit'];
      $haversine = geofield_haversine($lat, $long, $geofield->definition['field_name'] . '_lat', $geofield->definition['field_name'] . '_lon', $radius_of_earth);
      $this->field_alias = $this->query->add_field(NULL, $haversine, $this->field);
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['location'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    
    if ($handlers = $this->view->display_handler->get_handlers('filter')) {
      $options = array();
      foreach ($handlers as $name => $handler) {
        if ($handler->definition['handler'] == 'geofield_proximity_handler_filter') {
          $options[$name] = $handler->definition['group'] . ': ' . $handler->definition['title'];
        }
      }
      $form['location'] = array(
        '#title' => t('Distance from'),
        '#type' => 'select',
        '#options' => $options,
        '#description' => t('Select location from which to measure distance.'),
      );
    }
    parent::options_form($form, $form_state);
    
    // Remove lat and lon distance from options form.
    unset($form['dist_lat']);
    unset($form['dist_lon']);

  }
  
  function get_value($values, $field = NULL) {
    if (isset($values->{$this->field})) {
      return $values->{$this->field};
    }
  }

}
