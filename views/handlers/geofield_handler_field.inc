<?php

class geofield_handler_field extends views_handler_field {
  function query() {
    $geofield = $this->view->field[$this->real_field];
    $this->query->add_field($geofield->table, $geofield->definition['field_name'] . '_lat');
    $this->query->add_field($geofield->table, $geofield->definition['field_name'] . '_lon');

    $this->ensure_my_table();
    $this->query->add_field(NULL, '( 3959 * acos( cos( radians(' . $this->options['dist_lat'] . ') ) * cos( radians( ' . $geofield->definition['field_name'] . '_lat ) ) * cos( radians( ' . $geofield->definition['field_name'] . '_lon ) - radians( ' . $this->options['dist_lon'] . ') ) + sin( radians( ' . $this->options['dist_lat'] . ') ) * sin( radians( ' . $geofield->definition['field_name'] . '_lat ) ) ) )', $this->field);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['dist_lat'] = array('default' => 0);
    $options['dist_lon'] = array('default' => 0);
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
  }
  
  function get_value($values, $field = NULL) {
    if (isset($values->{$this->field})) {
      return $values->{$this->field};
    }
  }
}
