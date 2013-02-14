<?php

/**
 * @file
 * Distance field implementation.
 */

class geofield_handler_argument extends views_handler_argument {
  
  var $operator = NULL;
  
  function option_definition() {
    $options = parent::option_definition();
    $proximityPlugin = new geofieldProximityEntityURL();
    $proximityPlugin->option_definition($options, $this);
    $options['distance'] = array(
      'default' => 100
    );
    $options['unit'] = array(
      'default' => GEOFIELD_KILOMETERS
    );
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state); 
    $proximityPlugin = new geofieldProximityEntityURL();
    $proximityPlugin->options_form($form, $form_state, $this);
    $form['distance'] = array(
      '#type' => 'textfield',
      '#title' => t('Distance'),
      '#default_value' => !empty($this->options['distance']) ? $this->options['distance'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
    );
    $form['unit'] = array(
      '#type' => 'select',
      '#options' => geofield_radius_options(),
      '#title' => t('Unit'),
      '#default_value' => !empty($this->options['unit']) ? $this->options['unit'] : GEOFIELD_KILOMETERS,
      '#title_display' => 'invisible',
    );
  }
  
/**
  * Set the input for this argument
  *
  * @return TRUE if it successfully validates; FALSE if it does not.
  */
function set_argument($arg) {
  if (!$this->validate_arg($arg)) {
    return FALSE;
  }
  $this->argument = $arg;
  return TRUE;
}
  
  function query($group_by = FALSE) {
  }
}
