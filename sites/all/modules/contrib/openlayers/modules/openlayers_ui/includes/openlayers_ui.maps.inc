<?php

/**
 * @file
 * This file holds the functions handling maps in the
 * Openlayers UI.
 *
 * @ingroup openlayers
 */

/**
 * Form submit for map add form, for the projection add ahah
 */
function openlayers_ui_maps_add_projection_submit($form, &$form_state) {
  unset($form_state['submit_handlers']);
  form_execute_handlers('submit', $form, $form_state);
  $form_state['rebuild'] = TRUE;
}


/**
 * OpenLayers AHAH
 *
 * Function to handle the AHAH request of the openlayers form
 */
function openlayers_ui_map_ahah() {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);

  // Get variables
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  // Reprocess form with new form state
  drupal_process_form($form_id, $form, $form_state);

  // Rebuild form and remove any submit handlers
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  // Unset wrapper and create output
  $output = theme('status_messages') . drupal_render($form['layerstyles']);

  // Final rendering callback.
  drupal_json(array('status' => TRUE, 'data' => $output));
}

/**
 * Process form submission into a map array.
 *
 * @param $values
 *   Array of values to process.
 * @return
 *   Map data array.
 */
function openlayers_ui_maps_form_process($values = array()) {
  // Valid keys that we will cherry-pick from the form values.
  $keys = array(
    'width',
    'height',
    'image_path',
    'css_path',
    'proxy_host',
    'hide_empty_map',
    'center',
    'behaviors',
    'layers',
    'layer_weight',
    'layer_styles',
    'layer_styles_select',
    'layer_activated',
    'layer_switcher',
    'projections',
    'styles'
  );

  // TODO: eliminate this process, too much disconnect between
  // forms and data
  $processed = array();
  foreach ($keys as $key) {
    switch ($key) {
      case 'behaviors':
        $processed['behaviors'] = array();
        foreach ($values['behaviors'] as $behavior => $settings) {
          if ($settings['enabled']) {
            $processed['behaviors'][$behavior] =
              isset($settings['options_set']['options']) ?
              $settings['options_set']['options'] : array();
          }
        }
        break;

      case 'projections':
        $processed['projection'] = $values['projections']['easy_projection'];
        $processed['displayProjection'] = $values['projections']['displayProjection'];
        break;

      case 'layers':
        // Put the default layer in the right place.
        // TODO: finish port here
        $processed['default_layer'] = $values['layers']['default_layer'];
        $baselayers = array_filter($values['layers']['baselayers']);
        $overlays = (isset($values['layers']['overlays'])) ?
          array_filter($values['layers']['overlays']) : array();
        // Sort overlay layers by weight, in case browser didn't
        // send them already sorted
        if (isset($values['layer_weight'])) {
          $overlays = array();
          asort($values['layer_weight']);
          foreach (array_keys($values['layer_weight']) as $layer_key) {
            if ($values['layers']['overlays'][$layer_key]) {
               $overlays[$layer_key] = $layer_key;
            }
          }
          // TODO: Above code is terrrrrrrrible. rewrite when I have the time
        }

        // Merge our different layer sections together
        $processed['layers'] = array_merge($baselayers, $overlays);
        break;

      default:
        // $processed[$key] = is_array($values[$key]) ?
        //   array_filter($values[$key]) : $values[$key];
        $processed[$key] = isset($values[$key]) ? $values[$key] : array();
        break;
    }
  }

  // Ensure these values are arrays
  $ensure_array = array('behaviors', 'layers', 'layer_weight', 'layer_styles', 'layer_styles_select', 'styles');
  foreach ($ensure_array as $key) {
    if (empty($processed[$key])) {
      $processed[$key] = array();
    }
  }

  return $processed;
}

/**
 * Get behavior options.
 */
function openlayers_ui_get_behavior_options($type, $defaults) {
  $form = array();
  $behaviors = openlayers_behaviors();
  uasort($behaviors, '_openlayers_ui_sort_behaviors');
  foreach ($behaviors as $key => $plugin) {
    // Get behavior class
    $class = ctools_plugin_load_class(
      'openlayers',
      'behaviors',
      $key,
      'behavior');
    if (!empty($class)) {
      $options = isset($defaults['behaviors'][$key]) ?
        $defaults['behaviors'][$key] : array();

      $behavior = new $class($options, $defaults);

      if (!isset($plugin['ui_visibility']) || $plugin['ui_visibility']) {
        // Create basic form structure for behavior
        $form[$key] = array(
          'enabled' => array(
            '#type' => 'checkbox',
            '#title' => $plugin['title'],
            '#description' => $plugin['description'],
            '#default_value' => isset($defaults['behaviors'][$key]),
            '#id' => $key . '-enabled',
          ),
          'dependencies' => openlayers_dependency_widget(
            $behavior->js_dependency()),
          'options' => array(),
        );

        // Create options items
        $options = $behavior->options_form($options);
        if (!empty($options)) {
          // HACK.  In order to use ctools form
          // dependencies, we have to use a hidden
          // field as it supports processing and IDs.
          $form[$key]['options_set'][$key . '-prefix'] = array(
            '#type' => 'hidden',
            '#id' => $key . '-options',
            '#prefix' => '<div><fieldset id="' . $key . '-options' .
              '" class="collapsible">',
            '#process' => array('ctools_dependent_process'),
            '#dependency' => array($key . '-enabled' => array(1)),
            '#weight' => -1000,
          );
          $form[$key]['options_set']['options'] = $options;
          $form[$key]['options_set'][$key . '-suffix'] = array(
            '#value' => '</fieldset></div>',
            '#weight' => 1000,
          );
        }
      }
    }
    else {
    }
  }
  return $form;
}

/**
 * Callback sorting behaviors alphabetically
 */
function _openlayers_ui_sort_behaviors($a, $b) {
  return strnatcmp($a['title'], $b['title']);
}

/**
 * Create Centering Map
 *
 * Create map for interactive default centering
 *
 * @param $defaults
 *   Array of defults to use for the map of centering and zooming
 * @return
 *   Themed map array
 */
function openlayers_ui_maps_form_center_map($defaults = array()) {
  // Pass variables etc. to javascript
  $pass_values = array(
    'openlayersForm' => array(
      'projectionLayers' => openlayers_ui_get_projection_options(),
    ),
  );
  drupal_add_js($pass_values, 'setting');

  // centerpoint & zoom of this map are overridden
  // by the mapformvalues behavior on page load.
  //
  // Note that navigation screws up the boxselect
  // behavior for getting extent.
  $centermap_def = array(
    'id' => 'openlayers-center-helpmap',
    'projection' => '900913',
    'displayProjection' => '900913',
    'default_layer' => 'mapquest_osm',
    'width' => '600px',
    'height' => '400px',
    'center' => array(
      'initial' => array(
        'centerpoint' => "0, 0",
        'zoom' => 2,
      ),
    ),
    'image_path' => drupal_get_path('module', 'openlayers') . '/themes/default_dark/img/',
    'layers' => array(
      'mapquest_osm',
    ),
    'behaviors' => array(
      //'openlayers_behavior_navigation' => array(),
      'openlayers_behavior_panzoombar' => array(),
      //'openlayers_behavior_dragpan' => array(),
      'openlayers_behavior_mapformvalues' => array(),
      'openlayers_behavior_boxselect' => array(),
      'openlayers_behavior_attribution' => array(),
    ),
  );
  return openlayers_render_map_data($centermap_def);
}
