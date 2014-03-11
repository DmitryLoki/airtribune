<?php

/**
 * Implements hook_views_data().
 */
function pg_race_views_data() {
  $data = array();
  $data['eck_ent_race']['watch_task'] = array(
    'title' => t('Watch task'),
    'help' => t('Watch live or Preview task link, time or status.'),
    'field' => array(
      'handler' => 'pg_race_handler_watch_task',
    ),
  );

  return $data;
}
