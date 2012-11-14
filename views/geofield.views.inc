<?php

/**
 * @file
 * Hooks for Views integration.
 */

/**
 * Implements hook_field_views_data().
 *
 * Views integration for geofields.
 *
 */
function geofield_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'];

  foreach ($data as $table_name => $table_data) {
    if (isset($table_data[$field_name])) {
      $group_name = $table_data[$field_name]['group'];
      $data[$table_name]['field_geofield_distance'] = array(
        'group' => $group_name,
        'title'       => $table_data[$field_name]['title'] . ' - proximity',
        'title short' => $table_data[$field_name]['title'] . ' - proximity',
        'help' => $table_data[$field_name]['help'],
        'sort' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_sort',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
        ),
        'field' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_field',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
          'float' => TRUE,
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_filter',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
        ),
      );
    }
  }
  return $data;
}

/**
 * Mini-plugins for geofield proximity views plugins.
 */

function geofield_proximity_views_handlers() {
  return array(
    'manual' => array(
      'name' => t('Manually Enter Point'),
      'class' => 'geofieldProximityManual',
    ),
    // @TODO: Check for geocoder module first. :-/
    'geocoder' => array(
      'name' => t('Geocoded Location'),
      'class' => 'geofieldProximityGeocoder',
    ),
  );
}

function geofield_proximity_load_plugin($plugin) {
  $handlers = geofield_proximity_views_handlers();
  if (class_exists($handlers[$plugin]['class'])) {
    return new $handlers[$plugin]['class'];
  }
  else {
    return FALSE;
  }
}

interface geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin);
  public function options_form(&$form, &$form_state, $views_plugin);
  public function options_validate(&$form, &$form_state, $views_plugin);
  public function value_form(&$form, &$form_state, $views_plugin);
  public function value_validate(&$form, &$form_state, $views_plugin);
  public function query($views_plugin);
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

  public function query($views_plugin) {
    return array(
      'destination_latitude' => 0,
      'destination_longitude' => 0,
    );
  }
}

class geofieldProximityManual extends geofieldProximityBase implements geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin) {
    $options['geofield_proximity_manual'] = array(
      'default' => array(
        'lat' => 0,
        'lon' => 0,
      )
    );
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    $form['geofield_proximity_manual'] = array(
      '#type' => 'geofield_latlon',
      '#title' => t('Source'),
      '#default_value' => $views_plugin->options['geofield_proximity_manual'],
      '#states' => array(
        'visible' => array(
          ':input[name="options[source]"]' => array('value' => 'manual'),
        ),
      ),
      '#proximity_plugin_value_element' => TRUE,
    );
  }

  public function value_form(&$form, &$form_state, $views_plugin) {
    $form['value']['#origin_element'] = 'geofield_latlon';
  }

  public function query($views_plugin) {
    return array(
      'destination_latitude' => (isset($views_plugin->value)) ? $views_plugin->value['origin']['lat'] : $views_plugin->options['geofield_proximity_manual']['lat'],
      'destination_longitude' => (isset($views_plugin->value)) ? $views_plugin->value['origin']['lon'] : $views_plugin->options['geofield_proximity_manual']['lon'],
    );
  }
}

class geofieldProximityGeocoder extends geofieldProximityBase implements geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin) {
    $options['geofield_proximity_geocoder'] = array('default' => '');
    $options['geofield_proximity_geocoder_engine'] = array('default' => 'google');
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    $form['geofield_proximity_geocoder'] = array(
      '#type' => 'textfield',
      '#title' => t('Source'),
      '#default_value' => $views_plugin->options['geofield_proximity_geocoder'],
      '#dependency' => array(
        'edit-options-source' => array('geocoder'),
      ),
      '#proximity_plugin_value_element' => TRUE,
    );

    $geocoders_raw = geocoder_handler_info('text');
    $geocoder_options = array();
    foreach ($geocoders_raw as $key => $geocoder) {
      $geocoder_options[$key] = $geocoder['title'];
    }

    $form['geofield_proximity_geocoder_engine'] = array(
      '#type' => 'select',
      '#title' => t('Geocoding Service'),
      '#options' => $geocoder_options,
      '#default_value' => $this->options['geofield_proximity_geocoder_engine'],
      '#dependency' => array(
        'edit-options-source' => array('geocoder'),
      ),
    );
  }

  public function query($views_plugin) {
    $geocoder_engine = $views_plugin->options['geofield_proximity_geocoder_engine'];
    $location = (isset($views_plugin->value)) ? $views_plugin->value['origin'] : $views_plugin->options['geofield_proximity_geocoder'];

    $geocoded_data_raw = geocoder($geocoder_engine, $location);
    if ($geocoded_data_raw) {
      return array(
        'destination_latitude' => $geocoded_data_raw->getX(),
        'destination_longitude' => $geocoded_data_raw->getY(),
      );
    } else {
      // @TODO: Tmp, should return false.
      return array(
        'destination_latitude' => 0,
        'destination_longitude' => 0,
      );
    }
  }
}
