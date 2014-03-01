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
    $options['output_type'] = array('default' => 'links');

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

    $form['output_type'] = array(
      '#type' => 'select',
      '#title' => t('Task info output type'),
      '#options' => array('links' => t('Watch links'), 'timer' => t('Task timer'), 'status' => t('Status value'),),
      '#default_value' => $this->options['output_type'],
      '#required' => TRUE,
    );
    //~ // The path is set by render_link function so don't allow to set it.
    //~ $form['alter']['path'] = array('#access' => FALSE);
    //~ $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    module_load_include('inc', 'pg_race', 'includes/pg_race.watch');


    //~ if ($this->options['output_type'] == 'links') return "<span class='watch-links'>some links</span>";

    $output = '';

    //~ dsm($values);
    if ($entity = $this->get_value($values)) {

      // Define chosen output type option.
      $output_type = $this->options['output_type'];

      $raceWatch = new RaceWatch($entity);
      $raceStatus = $raceWatch->raceStatus();

      switch ($output_type) {
        case 'links' :
          drupal_add_js(drupal_get_path('module', 'pg_race') .'/js/pg_race.watch.js', 'file');
          drupal_add_css(drupal_get_path('module', 'pg_race') .'/css/pg_race.watch.css', 'file');

          $race_id = $entity->id;
          $linksInfo = $raceWatch->raceLinksInfo();
          //~ dsm_once($linksInfo, 'handler links');
          $output = theme('live_event_watch_links', array('links_info' => $linksInfo, 'race_status' => $raceStatus));


          $css_status = array(PG_RACE_WATCH_STATUS_AWAITING => 'awaiting', PG_RACE_WATCH_STATUS_STARTING => 'starting', PG_RACE_WATCH_STATUS_IS_LIVE => 'is_live', PG_RACE_WATCH_STATUS_FINISHED => 'finished');
          $classes = "watch-links watch-links-race-id-{$race_id}";
          $classes = isset($css_status[$raceStatus]) ? "{$classes} {$css_status[$raceStatus]}" : $classes;

          $output = !empty($output) ? "<span class='{$classes}'>{$output}</span>" : "";


          // Add js settings for links
          $settings = array();
          $js_status = array(PG_RACE_WATCH_STATUS_AWAITING => 'awaiting', PG_RACE_WATCH_STATUS_STARTING => 'starting', PG_RACE_WATCH_STATUS_IS_LIVE => 'is_live', PG_RACE_WATCH_STATUS_FINISHED => 'finished');
          switch ($raceStatus) {
            case PG_RACE_WATCH_STATUS_AWAITING :
            case PG_RACE_WATCH_STATUS_STARTING :
            case PG_RACE_WATCH_STATUS_IS_LIVE :
            case PG_RACE_WATCH_STATUS_FINISHED :
              $timeInfo = $raceWatch->getTimeInfo();
              $coreRequestIds = $raceWatch->getCoreRequestIds();

              $settings[$race_id] = array(
                'status' => $js_status[$raceStatus],
                'race_id' => $race_id,
                'open' => $timeInfo['open'],
                'close' => $timeInfo['close'],
                'start' => $timeInfo['start'],
                'end' => $timeInfo['end'],
                'now_local' => $timeInfo['now_local'],
                'now_utc' => $timeInfo['now_utc'],
                'offset' => $timeInfo['offset'],
                'function_name' => 'pg_race_frontpage_live_events_links',  // js function name to process this item

                'contest_cid' => $coreRequestIds['contest_cid'],
                'race_cid' => $coreRequestIds['race_cid'],
                'core_api_address' => at_core_sync_get_api_url(),  // @todo: maybe this option should be also set in getCoreRequestIds()
              );
              break;
          }
          if (!empty($settings)) {
            drupal_add_js(array('pg_race' => array('task_watch' => array('frontpage_live_events_links' => $settings))), 'setting');
            //~ drupal_add_js('var pageLoadStart = new Date();', 'inline');
          }

          break;
        case 'status' :
          $output = $raceStatus;
          break;
        case 'timer' :
          drupal_add_js(drupal_get_path('module', 'pg_race') .'/js/pg_race.watch.js', 'file');
          drupal_add_css(drupal_get_path('module', 'pg_race') .'/css/pg_race.watch.css', 'file');


          //~ $timerInfo = $raceWatch->raceTimerInfo();
          //~ $timerInfo = $raceWatch->getTimeInfo();
          $race_id = $entity->id;
          $timerInfo = array('timer' => $raceWatch->raceTimer(), 'race_id' => $race_id);


          $output = theme('live_event_watch_timer', array('timer_info' => $timerInfo, 'race_status' => $raceStatus));
          break;
      }
    }
    return $output;
  }
}
