<?php

/**
 * @file
 * Select pilot for nation team.
 * @author Vasily Kraev
 * @see $4335
 */

class views_handler_field_pilot_selection extends views_handler_field_entity {

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
    // Return form for pilot select
    $options = array(
      'contest_nid' => $this->view->args[0],
      'user_country' => $this->view->args[1],
      //'user_country' => $this->view->result[$this->view->row_index]->field_field_address[0]['raw']['country'],
      'row_index' => $this->view->row_index,
      'uid' => $values->uid,
      'ent_team' => $values->_field_data['field_team_member_users_id']['entity'],
    );
    return drupal_get_form('pg_nation_team_pilot_selection_form', $options);
  }
}
