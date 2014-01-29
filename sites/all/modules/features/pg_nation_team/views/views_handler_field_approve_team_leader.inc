<?php

/**
 * @file
 * Approve team leader field handler.
 */

class views_handler_field_approve_team_leader extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['team_leader'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['team_leader'] = array(
      '#title' => t('Team leader'),
      '#type' => 'textfield',
      '#default_value' => $this->options['team_leader'],
    );
  }

  function render($values) {
    // Return form for approve current team leader
    $form['approve_team_leader'] = array(
      '#type' => 'checkbox',
      '#return_value' => $this->tokenize_value($this->options['team_leader'], $this->view->row_index), 
    );
    return drupal_render($form);
  }
}
