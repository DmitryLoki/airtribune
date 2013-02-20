<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Ctools plugin definition.
 */
function olfp_openlayers_behavior_fp_openlayers_behaviors() {
  return array(
    'title' => t('OL Feature Popups'),
    'description' => t('OL Feature Popups: Provide an easy way to manage popups.'),
    'type' => 'layer',
    'behavior' => array(
      'file' => 'openlayers_behavior_fp.inc',
      'class' => 'openlayers_behavior_fp',
      'parent' => 'openlayers_behavior',
    ),
    'group' => 'Info boxes'
  );
}

/**
 * Attribution Behavior
 */
class openlayers_behavior_fp extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layers' => array(),
    );
  }

  /**
   * Form defintion for per map customizations.
   */
  function options_form($defaults = array()) {
    $form = parent::options_form(array());

    // Only prompt for vector layers.
    $vector_layers = array();
    foreach ($this->map['layers'] as $id => $name) {
      $layer = openlayers_layer_load($id);
      if (isset($layer->data['vector']) && $layer->data['vector'] == TRUE) {
        $vector_layers[$id] = $name;
      }
    }



    ksort($vector_layers);

    foreach ($vector_layers as $id => $name) {
      $form['#tree'] = true;
      $form['layers'][$id] = array(
        '#type' => 'fieldset',
        '#title' => t('Options for layer @layer', array('@layer' => $name)),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form['layers'][$id]['layer'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable the behavior on this layer ?'),
        '#default_value' => !empty($defaults['layers'][$id]['layer']) ? 1 : FALSE,
      );
      $form['layers'][$id]['popup'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable the popup on click ?'),
        '#description' => t(''),
        '#default_value' => !empty($defaults['layers'][$id]['popup']) ? 1 : FALSE,
      );
      $form['layers'][$id]['tooltip'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable the tooltip on hover ?'),
        '#description' => t(''),
        '#default_value' => !empty($defaults['layers'][$id]['tooltip']) ? 1 : FALSE,
      );
      $form['layers'][$id]['templates'] = array(
        '#type' => 'fieldset',
        '#title' => t('Template customizations'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE
      );
      $form['layers'][$id]['templates']['item'] = array(
        '#type' => 'textarea',
        '#title' => t('Single item template'),
        '#description' => t('This item template is used when displaying a list of item in a popup, like in cluster.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<li><a href="#" ${showPopup()}>${.name}</a></li>')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['item']) ?
          $defaults['layers'][$id]['templates']['item'] : '',
      );
      $form['layers'][$id]['templates']['list'] = array(
        '#type' => 'textarea',
        '#title' => t('List template'),
        '#description' => t('This list template is used when displaying a list of features in a popup, like in cluster.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<h2>${layer.name} - ${count}</h2><ul>${html}</ul>')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['list']) ?
          $defaults['layers'][$id]['templates']['list'] : '',
      );
      $form['layers'][$id]['templates']['single']['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Single popup title template'),
        '#description' => t('This is the template of the title in a single popup.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<div class="openlayers-fp openlayers-tooltip-name">${.name}</div>')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['single']['title']) ?
          $defaults['layers'][$id]['templates']['single']['title'] : '',
      );
      $form['layers'][$id]['templates']['single']['content'] = array(
        '#type' => 'textarea',
        '#title' => t('Single popup content template'),
        '#description' => t('This is the template of the content in a single popup.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<div class="openlayers-fp openlayers-tooltip-description">${.description}</div>')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['single']['content']) ?
          $defaults['layers'][$id]['templates']['single']['content'] : '',
      );
      $form['layers'][$id]['templates']['hover'] = array(
        '#type' => 'textfield',
        '#title' => t('Hover item template'),
        '#description' => t('This is the template when hovering a feature.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<li>${.name}</li>')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['hover']) ?
          $defaults['layers'][$id]['templates']['hover'] : '',
      );
      $form['layers'][$id]['templates']['hoverlist'] = array(
        '#type' => 'textarea',
        '#title' => t('Hover list template'),
        '#description' => t('This is the template when hovering a clustered feature.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<b>${count} ${i18n("features")}:</b><br>${html}')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['hoverlist']) ?
          $defaults['layers'][$id]['templates']['hoverlist'] : '',
      );
      $form['layers'][$id]['templates']['hoveritem'] = array(
        '#type' => 'textarea',
        '#title' => t('Hover item template in hoverlist'),
        '#description' => t('This is the template of an item when hovering a clustered feature.<br/>Default is: <code>@default</code>.<br>You can use the ${.name} variables and all the other one from your field\'s view, just be aware that you need to add a dot in front of the name of the variable.', array('@default' => '<li>${.name}</li>')),
        '#default_value' => !empty($defaults['layers'][$id]['templates']['hoveritem']) ?
          $defaults['layers'][$id]['templates']['hoveritem'] : '',
      );
    }

    return $form;
  }

  /**
   * Render.
   */
  function render(&$map) {
    // Put weight on JS so that we know navigation is included already as this
    // will affect touch devices.
    // Add the OL Feature Popups extension.
    if ($path = _olfp_get_path()) {
      drupal_add_js($path . '/lib/patches_OL-popup-autosize.js');
      drupal_add_js($path . '/lib/FeaturePopups.js');
    }

    drupal_add_css(drupal_get_path('module', 'olfp') . '/olfp.css', array('weight' => 12));

    drupal_add_js(drupal_get_path('module', 'olfp') .
      '/openlayers_plugins/behaviors/openlayers_behavior_fp.js', array('weight' => 12));

    return $this->options;
  }
}
