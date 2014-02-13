<?php

/**
 * Implements hook_views_data().
 */
function pg_race_views_data() {
  $data = array();
  $data['eck_ent_race']['watch_task'] = array(
    'title' => t('Watch task'),
    'help' => t('Watch live or Preview task link.'),
    'field' => array(
      'handler' => 'pg_race_handler_watch_task',
    ),
  );
  $data['eck_ent_race']['watch_task_time'] = array(
    'title' => t('Watch task time'),
    'help' => t('Watch live or Preview task start time or countdown.'),
    'field' => array(
      'handler' => 'pg_race_handler_watch_task_time',
    ),
  );
  return $data;
}
