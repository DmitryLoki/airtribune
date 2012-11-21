<?php

/**
 * @file
 */

interface geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin);
  public function options_form(&$form, &$form_state, $views_plugin);
  public function options_validate(&$form, &$form_state, $views_plugin);
  public function value_form(&$form, &$form_state, $views_plugin);
  public function value_validate(&$form, &$form_state, $views_plugin);
  public function getSourceValue($views_plugin);
}

class geofieldProximityBase implements geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin) {
    
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    
  }

  public function options_validate(&$form, &$form_state, $views_plugin) {

  }

  public function value_form(&$form, &$form_state, $views_plugin) {
  }

  public function value_validate(&$form, &$form_state, $views_plugin) {
    
  }

  public function getSourceValue($views_plugin) {
    return array(
      'latitude' => 0,
      'longitude' => 0,
    );
  }
}
