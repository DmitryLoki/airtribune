<?php

/**
 * @file
 * Distance field implementation.
 */

class geofield_handler_field extends views_handler_field_numeric {
  function query() {
    /**
     * @TODO: Not sure if this is the best way to handle this, but attempting to set this on the object
     * seems to break things.
     */

    $table_alias = $this->table;
    if (!empty($this->relationship)) {
      $table_alias = $this->relationship . '__' . $this->table;
    }

    $this->query->add_field($table_alias, $this->definition['field_name'] . '_lat');
    $this->query->add_field($table_alias, $this->definition['field_name'] . '_lon');

    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field(NULL, geofield_haversine($this->options['dist_lat'], $this->options['dist_lon'], $this->definition['field_name'] . '_lat', $this->definition['field_name'] . '_lon', $this->options['radius_of_earth']), $this->table_alias . '_' . $this->field);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['dist_lat'] = array('default' => 0);
    $options['dist_lon'] = array('default' => 0);
    $options['radius_of_earth'] = array('default' => '6371');
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
  
  function get_value($values, $field = NULL) {
    if (isset($values->{$this->field_alias})) {
      return $values->{$this->field_alias};
    }
  }
}
