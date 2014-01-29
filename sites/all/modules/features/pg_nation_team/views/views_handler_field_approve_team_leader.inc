<?php

/**
 * @file
 * Approve team leader field handler.
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see $4339
 * @todo this is handler only for teams_applications view
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
    $options = array(
      'team_country' => $this->view->result[$this->view->row_index]->field_field_country[0]['raw']['value'],
      'row_index' => $this->view->row_index,
      'value' => $this->tokenize_value($this->options['team_leader'], $this->view->row_index),
      'team_entity' => $this->entities[$this->view->row_index],
    );
    return  drupal_get_form('pg_nation_team_approve_team_leader_form', $options);
  }
}
