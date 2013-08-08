<?php

/**
 * @file
 * Definition of views_handler_field_airtribune_count_pilots.
 */

/**
 * Field handler to count registred pilots.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_airtribune_count_pilots extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['status'] = 1;
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['status'] = array(
      '#type' => 'radios',
      '#title' => t('Pilots status'),
      '#options' => array(
        AIRTRIBUNE_PG_CONTESTANT_WAITING_LIST => t('In waiting list'),
        AIRTRIBUNE_PG_CONTESTANT_CONFIRMED => t('Confirmed'),
      ),
      '#default_value' => $this->options['status'] ? $this->options['status'] : 1,
    );
    parent::options_form($form, $form_state);
  }

  function render($values) {
   
    if (($node = $this->get_value($values)) && $node->type == AIRTRIBUNE_PG_CONTEST_TYPE) {
      airtribune_count_pilots($node->nid, 4);
      return 555;
    }
  }


}
