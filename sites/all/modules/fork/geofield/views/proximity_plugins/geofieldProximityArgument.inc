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
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
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

    //$entity = menu_get_object($entity_type);
    if (isset($entity) && !empty($geofield_name)) {
      $field_data = field_get_items($entity_type, $entity, $geofield_name);

      if ($field_data != FALSE) {
        return array(
          'latitude' => $field_data[$delta]['lat'],
          'longitude' => $field_data[$delta]['lon'],
        );
      }
    }

    return FALSE;
  }
}