<?php

class geofield_handler_sort extends views_handler_sort {
  function query() {
    $geofield = $this->view->sort['field_geofield_distance'];
    $this->query->add_field($geofield->table, $geofield->definition['field_name'] . '_lat');
    $this->query->add_field($geofield->table, $geofield->definition['field_name'] . '_lon');

    $this->ensure_my_table();
    $this->query->add_orderby(NULL, geofield_haversine($this->options['dist_lat'], $this->options['dist_lon'], $geofield->definition['field_name'] . '_lat', $geofield->definition['field_name'] . '_lon', $this->options['radius_of_earth']), $this->options['order'], $this->field);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['dist_lat'] = array('default' => 0);
    $options['dist_lon'] = array('default' => 0);
    $options['radius_of_earth'] = array('default' => '6731');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
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
}
