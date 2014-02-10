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
    // Render a Views form item placeholder.
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  /**
   * Add to and alter the form.
   */
  function views_form(&$form, &$form_state) {
    // Create a container for our replacements
    $form[$this->options['id']] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );

    $user_is_org = !is_user_team_leader($this->view->team);
    $form['#attributes'] = $user_is_org ? array('class' => 'teamcard-for-organizer-form') : array('class' => 'teamcard-for-teamlead-form');

    // Iterate over the result and add our replacement fields to the form.
    foreach ($this->view->result as $row_index => $row) {
      $uid = $row->_field_data['profile_users_pid']['entity']->uid;
      $checked = isset($row->_field_data['field_team_member_users_id']['entity']);
      // Add a text field to the form.  This array convention
      // corresponds to the placeholder HTML comment syntax.
      $form[$this->options['id']][$row_index] = array(
        '#type' => 'checkbox',
        '#value' => $checked,
        '#default_value' => $uid,
        '#disabled' => $user_is_org,
        '#required' => TRUE,
      );
    }

    // Submit to the current page if not a page display.
    if ($this->view->display_handler->plugin_name != 'page') {
      $form['#action'] = '/' . current_path();
    }
  }

  /**
   * Form submit method.
   */
  function views_form_submit($form, &$form_state) {
    $team = $this->view->team;

    if (!is_user_team_leader($team)) {
      return;
    }

    // Determine which pilots was checked.
    $selected_pilots = array();
    foreach ($this->view->result as $row_index => $row) {
      if ($form_state['input'][$this->options['id']][$row_index]) {
        $selected_pilots[] = $row->uid;
      }
    }

    $wrapper = entity_metadata_wrapper($team->entityType(), $team);
    $wrapper->field_team_member->set($selected_pilots);
    $wrapper->save();

    $contest = node_load($this->view->args[0]);
    $country = get_country_name($this->view->args[1]);
    $organizer = user_load($contest->uid);
    $teamleader = user_load($team->uid);

    at_messages_send_mail_change_team(array(
      'replacements' => array(
        '@teamleader_fullname' => at_user_get_full_name($teamleader),
        '@organizer_fullname' => at_user_get_full_name($organizer),
        '@event_name' => $contest->title,
        '@event_manage_team_link' => $GLOBALS['base_url'] . $form['#action'],
        '@country' => $country,
      ),
      'user' => $organizer,
    ));

    drupal_set_message(t('Team of @country changed.',array('@country' => $country)));
  }

}