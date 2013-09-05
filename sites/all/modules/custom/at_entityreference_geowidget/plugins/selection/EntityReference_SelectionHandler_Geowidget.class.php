<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of EntityReference_SelectionClass_Geowidget
 *
 * @author gease
 */
class EntityReference_SelectionHandler_Geowidget extends EntityReference_SelectionHandler_Views implements EntityReference_SelectionHandler {
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new EntityReference_SelectionHandler_Geowidget($field, $instance);
  }

  protected function __construct($field, $instance) {
    $this->field = $field;
    $this->instance = $instance;
  }

  public static function settingsForm($field, $instance) {
    $maps = openlayers_maps();
    $default = !empty($field['settings']['handler_settings']['map']) ? $field['settings']['handler_settings']['map'] : NULL;
    $options = array();
    foreach ($maps as $key => $map) {
      $options[$key] = $map->title;
    }
    $form['map'] = array(
      '#type' => 'select',
      '#title' => t('Map'),
      '#options' => $options,
      '#default_value' => $default
    );
    //following is rewrite of views_get_applicable_views()
    //inspired by EntityReference_SelectionHandler_Views::settingsForm
    $views = views_get_all_views();
    $options = array();
    foreach ($views as $view) {
      // Skip disabled views.
      if (!empty($view->disabled)) {
        continue;
      }

      if (empty($view->display)) {
        // Skip this view as it is broken.
        vsm(t("Skipping broken view @view", array('@view' => $view->name)));
        continue;
      }

      // Loop on array keys because something seems to muck with $view->display
      // a bit in PHP4.
      foreach (array_keys($view->display) as $id) {
        $plugin = views_fetch_plugin_data('display', $view->display[$id]->display_plugin);
        if ($plugin['handler'] == 'openlayers_views_plugin_display_openlayers') {
          $v = $view->clone_view();
          if ($v->set_display($id) && $v->display_handler->get_option('enabled')) {
            $options[$v->name . ':' . $id] = $v->name . ' - ' . $v->display[$id]->display_title;
          }
        }
      }
    }
    //$entity_info = entity_get_info($field['settings']['target_type']);
    if ($options) {
      $default = !empty($view_settings['view_name']) ? $view_settings['view_name'] . ':' . $view_settings['display_name'] : NULL;
      $form['view']['view_and_display'] = array(
        '#type' => 'select',
        '#title' => t('View used to select the entities'),
        '#required' => TRUE,
        '#options' => $options,
        '#default_value' => $default,
        '#description' => '<p>' . t('Choose the view and display that select the entities that can be referenced.<br />Only views with a display of type "Entity Reference" are eligible.') . '</p>',
      );

      $default = !empty($view_settings['args']) ? implode(', ', $view_settings['args']) : '';
      $form['view']['args'] = array(
        '#type' => 'textfield',
        '#title' => t('View arguments'),
        '#default_value' => $default,
        '#required' => FALSE,
        '#description' => t('Provide a comma separated list of arguments to pass to the view.'),
      );
    }
    else {
      $form['view']['no_view_help'] = array(
        '#markup' => '<p>' . t('No eligible views were found. <a href="@create">Create a view</a> with an <em>Entity Reference</em> display, or add such a display to an <a href="@existing">existing view</a>.', array(
          '@create' => url('admin/structure/views/add'),
          '@existing' => url('admin/structure/views'),
        )) . '</p>',
      );
    }
    $form['view']['#element_validate'] = array('entityreference_view_settings_validate');
    return $form;
  }

  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    return NULL;
  }

  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS') {
    return NULL;
  }

  public function validateAutocompleteInput($input, &$element, &$form_state, $form) {
    return NULL;
  }

  public function validateReferencableEntities(array $ids) {
    return $ids;
  }

  public function getLabel($entity) {
    return NULL;
  }

  public function entityFieldQueryAlter(SelectQueryInterface $query) {
    return NULL;
  }
}

?>
