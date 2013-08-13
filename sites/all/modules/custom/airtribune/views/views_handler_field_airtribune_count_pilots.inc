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
      $result = airtribune_count_pilots($node->nid, $this->options['status']);

      switch ($this->options['status']) {
        case AIRTRIBUNE_PG_CONTESTANT_WAITING_LIST:
          $text_1 = str_replace($result, '', format_plural($result, 'Pilot in waitng list', '@count Pilots'));
          $text_2 = t('in waiting list');
          break;

        case AIRTRIBUNE_PG_CONTESTANT_CONFIRMED:
          $text_1 = str_replace($result, '', format_plural($result, 'Confirmed pilot', '@count Pilots'));
          $text_2 = t('confirmed');
          break;
      }

      $pilots = array(
        '#theme' => 'airtribune_event_statistics',
        '#count' => $result,
        '#text_1' => $text_1,
        '#text_2' => $text_2,
        '#attributes' => array('class' => 'es-pilots'),
      );
      return render($pilots);
    }
  }


}
