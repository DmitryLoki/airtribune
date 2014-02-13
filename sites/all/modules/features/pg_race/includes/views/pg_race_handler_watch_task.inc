<?php

/**
 * Description of what my handler does.
 */
class pg_race_handler_watch_task extends views_handler_field_entity {

  /**
   * Default options form.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );

    //~ // The path is set by render_link function so don't allow to set it.
    //~ $form['alter']['path'] = array('#access' => FALSE);
    //~ $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    module_load_include('inc', 'pg_race', 'includes/pg_race.watch');


    //~ dsm($values);
    if ($entity = $this->get_value($values)) {
      //~ dsm($entity);

      $raceWatch = new RaceWatch($entity);
      dsm($raceWatch->raceStatus());
    }
    return 'watch live';
  }
}
