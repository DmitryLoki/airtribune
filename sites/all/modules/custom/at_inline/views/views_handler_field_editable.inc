<?php

/**
 * @file
 * Single editable field handler.
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see #4359
 */

class views_handler_field_editable extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['editable_field'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $fields = field_info_fields();
    foreach ($fields as $field_name => $field) {
      $fields_list[$field_name] = $field_name;
    }
    $form['editable_field'] = array(
      '#title' => t('Field'),
      '#type' => 'select',
      '#options' => $fields_list,
      '#default_value' => $this->options['editable_field'],
    );
  }

  function render($values) {
    $view = $this->view;
    $entity_type = $this->entity_type;
    $entity = $this->entities[$view->row_index];
    $field_name = $this->options['editable_field'];

    $display = array(
      'type' => 'editable',
      'label' => 'hidden',
      );
    return field_view_field($entity_type, $entity, $this->options['editable_field'], $display);
  }
}
