<?php

/**
 * @file
 * Set tracker.
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see $4422
 */

class views_handler_at_tracker_widget extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($values) {
    $output = 'n/a';
    $row_index = $this->view->row_index;

    $entity = $this->entities[$this->view->row_index];
    //$output = drupal_get_form('at_tracker_field_widget_form');
    //$field, $instance, $langcode, $items, $delta, $element
    //$entity = entity_load($values->id);
    $entity_type = $entity->entityType();
    $instances = field_info_instances($entity_type, $entity->type);
    foreach ($instances as $field_name => $instance) {
      if ($instance['widget']['type'] == 'at_tracker') {
        $item = $entity->{$field_name}[LANGUAGE_NONE][0];
        //$output = field_view_value($entity_type, $entity, $field_name, $item);
        $field = field_info_field($field_name);
        $output = drupal_get_form('at_tracker_editable_widget_form', $entity_type, $entity, $field, $instance, LANGUAGE_NONE, 0, $row_index);
      }
    }
    return $output;
  }
}
