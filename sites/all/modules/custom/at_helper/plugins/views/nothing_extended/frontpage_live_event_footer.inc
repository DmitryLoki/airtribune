<?php

// @todo: move this plugin into pg_race.module

$plugin = array(
  'title' => t('Frontpage Live event footer'),
  'renderer' => 'at_helper__frontpage_live_event_footer__renderer',
  'required_tokens' => 'at_helper__frontpage_live_event_footer__required_keys',
);

function at_helper__frontpage_live_event_footer__renderer(array $components, array $tokens) {
  drupal_add_css(drupal_get_path('module', 'pg_race') .'/css/pg_race.watch.css', 'file');

  $values = array();
  foreach ($components as $k => $token) {
    $values[$k] = $tokens[$token];
  }

  //~ dsm($components); dsm($tokens);
  //~ dsm($values);

  $watch_timer = $values['watch_timer'];
  $watch_status = $values['watch_status'];
  $task_title = $values['task_title'];
  $day_blog = $values['dayblog_last_entry'];
  $event_nid = $values['event_nid'];
  $day_status_value = $values['day_status_value'];
  $day_status_name = $values['day_status_name'];
  $day_number = $values['day_number'];
  $race_id = $values['race_id'];




  // Prepare output for "nothing_extended" handler.

  if (!empty($task_title))  {
    $title = $task_title;
  }
  else {
    // @todo: Use globals.
    $day_title = '';
    switch ($day_status_value) {
      case 0 :  // Ok
        $day_title = t('Day') . " {$day_number}";
        break;
      case 1 :  // Stopped
      case 2 :  // Cancelled
      case 3 :  // Rest day
        $day_title = t('Day') . " {$day_number} ({$day_status_name})";
        break;
      case 4 :  // Registration day
      case 5 :  // Training day
        $day_title =  $day_status_name;
        break;
    }
    $title = $day_title;
  }





  $output = "<span class='title'>{$title}</span>";
  if (!empty($watch_timer)) {
    $output .= "<span class='task-timer'>{$watch_timer}</span>";
  }
  //~ elseif (!empty($day_blog)) {
  if (!empty($day_blog)) {
    //~ $output .= !empty($watch_timer) ? "<span class='day-blog-wrapper' style='display:none;'>{$day_blog}</span>" : "<span class='day-blog-wrapper'>{$day_blog}</span>";
    $output .= !empty($watch_timer) ? "<span class='day-blog-wrapper dayblog-hidden' style='display:none;'>{$day_blog}</span>" : "<span class='day-blog-wrapper'>{$day_blog}</span>";
  }

  // dayblog is not rendered if there is task watch info
  $class = !empty($day_blog) && empty($watch_timer) ? 'day-blog' : 'day-blog no-blog';
  if (!empty($race_id)) {
    $class .= " day-blog-race-id-{$race_id}";
  }
  // Add status class
  $css_status = array(PG_RACE_WATCH_STATUS_AWAITING => 'awaiting', PG_RACE_WATCH_STATUS_STARTING => 'starting', PG_RACE_WATCH_STATUS_IS_LIVE => 'is_live', PG_RACE_WATCH_STATUS_FINISHED => 'finished');
  if (!empty($watch_status) && isset($css_status[$watch_status])) {
    $class .= " {$css_status[$watch_status]}";
  }

  $output = "<span class='{$class}'>{$output}</span>";

  // Wrap output into url tag.
  $url = url("event/{$event_nid}/blog") . "#!day_{$day_number}";
  $output = "<a href='{$url}'>{$output}</a>";

  return $output;
}

// @todo
/**
 * Required token keys.
 */
function at_helper__frontpage_live_event_footer__required_keys() {
  return array(
    'day_nid',  // day nid
    'day_number', // day number
  );
}
