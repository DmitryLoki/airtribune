<?php

// @todo: move this plugin into pg_race.module

$plugin = array(
  'title' => t('Frontpage Live event footer'),
  'renderer' => 'at_helper__frontpage_live_event_footer__renderer',
  'required_tokens' => 'at_helper__frontpage_live_event_footer__required_keys',
);

function at_helper__frontpage_live_event_footer__renderer(array $components, array $tokens) {
  $values = array();
  foreach ($components as $k => $token) {
    $values[$k] = $tokens[$token];
  }

  //~ dsm($components); dsm($tokens);
  dsm($values);

  $watch_timer = $values['watch_timer'];
  $watch_status = $values['watch_status'];
  $task_title = $values['task_title'];
  $day_blog = $values['dayblog_last_entry'];
  $event_nid = $values['event_nid'];
  $day_status_value = $values['day_status_value'];
  $day_status_name = $values['day_status_name'];
  $day_number = $values['day_number'];

  // Prepare output for "nothing_extended" handler.


  switch ($watch_status) {
    case PG_RACE_WATCH_STATUS_IS_LIVE :
      $timer_label = t('Race is on:');
      break;
    case PG_RACE_WATCH_STATUS_FINISHED :
      break;
    case PG_RACE_WATCH_STATUS_AWAITING :
      $timer_label = t('Race starts in:');
      break;
    case PG_RACE_WATCH_STATUS_EMPTY :
    default :
      break;
  }




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


  if (!empty($timer_label) && !empty($watch_timer)) {
    $timer_output = "<span class='help-text'>{$timer_label}</span><span class='time'>{$watch_timer}</span>";
  }

  $title = !empty($task_title) ? $task_title : $day_title;
  //~ $output = $day_title . $timer_output . $task_title . $day_blog;

  if (!empty($timer_output)) {
    $day_blog = '';  // Hide dayblog if there is task watch info.
  }


  $class = !empty($day_blog) ? 'day-blog' : 'day-blog no-blog';
  $output = !empty($day_blog) ? "<span class='title'>{$title}</span>{$day_blog}" : "<span class='title'>{$title}</span>";
  $output .= !empty($timer_output) ? "<span class='task-timer race-online'>{$timer_output}</span>" : "";

  $output = "<span class='{$class}'>{$output}</span>";
  $url = url("event/{$event_nid}/blog") . "#!day_{$day_number}";

  // Wrap output into url tag.
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
