<?php

/*
 * @file
 * Contains validator plugin for geofield
 * Modelled after views_plugin_argument_validate_node 
 * @author Vadim Valuev<gease@mail.ru>
 */

class geofield_plugin_argument_validate_entity extends views_plugin_argument_validate{
  
  function option_definition() {
    $options = parent::option_definition();
    $options['entity'] = array('default' => '');
    $options['geofield'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $types = entity_get_info();
    $options = array();
    foreach ($types as $type => $info) {
      $options[$type] = check_plain(t($info['label']));
    }
    $form['entity'] = array(
      '#type' => 'select',
      '#title' => t('Entity type'),
      '#options' => $options,
      '#default_value' => $this->options['entity'],
      '#description' => t('Choose entity type to validate with.'),
    );
    
    $fields = _geofield_get_geofield_fields();
    $options = array();
    foreach ($fields as $field => $info) {
      $options[$field] = check_plain(t($info['field_name']));
    }

    $form['geofield'] = array(
      '#type' => 'select',
      '#title' => t('Geofield name'),
      '#options' => $options,
      '#default_value' => $this->options['geofield'],
    );
  }

  function options_submit(&$form, &$form_state, &$options = array()) {
    // filter trash out of the options so we don't store giant unnecessary arrays
    //$options['entity'] = array_filter($options['entity']);
  }
  
  function validate_argument($argument) {
    $entity = $this->options['entity'];
    $field = $this->options['geofield'];
    $wrapper = entity_metadata_wrapper($entity, $argument);
    if (isset($wrapper) && isset($wrapper->{$field}) && $wrapper->{$field}->value() != NULL){
      return TRUE;
    }
    return FALSE;
  }
}
