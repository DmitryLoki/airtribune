<?php

/**
 * @file
 * Contains geofieldProximityEntityURL.
 */

/**
 * Description of geofieldProximityArgument
 *
 * @author gease
 */
class geofieldProximityArgument extends geofieldProximityBase implements geofieldProximityPluginInterface{
  
  public function option_definition(&$options, $views_plugin) {
    $options['geofield_proximity_argument_entity_type'] = array(
      'default' => 'node',
    );
    $options['geofield_proximity_argument_field'] = array(
      'default' => '',
    );
    $options['geofield_proximity_argument_delta'] = array(
      'default' => 0,
    );
    $options['geofield_proximity_argument_number'] = array(
      'default' => 0,
    );
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    $form['geofield_proximity_argument_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Argument position'),
      '#default_value' => $views_plugin->options['geofield_proximity_argument_number'],
      '#dependency' => array(
        'edit-options-source' => array('entity_from_argument'),
      ),
    );
    if (module_exists('elements')) {
      $form['geofield_proximity_argument_number']['#type'] = 'numberfield';
      $form['geofield_proximity_argument_number']['#attributes'] = array(
        'step' => 1,
        'min' => 0,
        'max' => 10
      );
    }
    
    $entities = entity_get_info();
    $entity_options = array();
    foreach ($entities as $key => $entity) {
      $entity_options[$key] = $entity['label'];
    }

    $form['geofield_proximity_argument_entity_type'] = array(
      '#type' => 'select',
      '#title' => t('Entity Type'),
      '#default_value' => $views_plugin->options['geofield_proximity_argument_entity_type'],
      '#options' => $entity_options,
      '#dependency' => array(
        'edit-options-source' => array('entity_from_argument'),
      ),
    );

    $geofields = _geofield_get_geofield_fields();
    $field_options = array();
    foreach ($geofields as $key => $field) {
      $field_options[$key] = $key;
    }

    $form['geofield_proximity_argument_field'] = array(
      '#type' => 'select',
      '#title' => t('Source Field'),
      '#default_value' => $views_plugin->options['geofield_proximity_argument_field'],
      '#options' => $field_options,
      '#dependency' => array(
        'edit-options-source' => array('entity_from_argument'),
      ),
    );
  }

  public function getSourceValue($views_plugin) {
    $entity_type = $views_plugin->options['geofield_proximity_argument_entity_type'];
    $geofield_name = $views_plugin->options['geofield_proximity_argument_field'];
    $delta = $views_plugin->options['geofield_proximity_argument_delta'];
    $argument = $views_plugin->view->args[$views_plugin->options['geofield_proximity_argument_number']];
    $entity = entity_metadata_wrapper($views_plugin->options['geofield_proximity_argument_entity_type'], $argument);
    $options = array();
    if (isset($entity->{$views_plugin->options['geofield_proximity_argument_field']})) {
      $options = $entity->{$views_plugin->options['geofield_proximity_argument_field']}->value();
      if ($options) {
        return array(
          'latitude' => $options['lat'],
          'longitude' => $options['lon'],
        );
      }
    }
    return FALSE;
  }
}