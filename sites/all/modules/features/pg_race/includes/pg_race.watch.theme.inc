<?php

function theme_live_event_watch_links($variables) {
  $race_status = $variables['race_status'];
  $linksInfo = $variables['links_info'];
  $output = '';

  switch ($race_status) {
    case PG_RACE_WATCH_STATUS_AWAITING :
      break;
    case PG_RACE_WATCH_STATUS_STARTING :
      // @
      break;
    case PG_RACE_WATCH_STATUS_IS_LIVE :
      if (!empty($linksInfo['links']['live']['2d']) || !empty($linksInfo['links']['live']['3d'])) {
        $label = t('Watch live'); $label = "<a href='#'>{$label}</a>";

        $link_2d = !empty($linksInfo['links']['live']['2d']) ? l(t('2D'), $path_2d = $linksInfo['links']['live']['2d']['path'], array('attributes' => array('target' => '_blank'))) : '';
        $link_2d = !empty($link_2d) ? "<li>{$link_2d}</li>" : "";
        $link_3d = !empty($linksInfo['links']['live']['3d']) ? l(t('3D Google Earch'), $path_3d = $linksInfo['links']['live']['3d']['path'], array('attributes' => array('target' => '_blank'))) : '';
        $link_3d = !empty($link_3d) ? "<li>{$link_3d}</li>" : "";

        $_output = "<span class='links-label'>{$label}</span>";
        $_output .= "<div class='links-content'><ul>{$link_2d}{$link_3d}</ul></div>";
        $_output = "<span class='task-live'>{$_output}</span>";

        $output .= $_output;
      }
      break;
    case PG_RACE_WATCH_STATUS_FINISHED :
      if (!empty($linksInfo['links']['results']['day']) || !empty($linksInfo['links']['results']['competition'])) {
        $label = t('Results'); $label = "<a href='#'>{$label}</a>";
        $results_day = _pg_race_watch_links_results($linksInfo['links']['results']['day'], 'day');
        $results_competition = _pg_race_watch_links_results($linksInfo['links']['results']['competition'], 'competition');
        $output = "<span class='links-label'>{$label}</span>";
        $output .= "<div class='links-content'>{$results_day}{$results_competition}</div>";
        $output = "<span class='task-results'>{$output}</span>";
      }
      elseif (!empty($linksInfo['links']['leader_board'])) {
        $path = $linksInfo['links']['leader_board']['path'];
        $link = l(t('Leader Board'), $path, array('attributes' => array('target' => '_blank')));
        $output = "<span class='leaderboard-label'>{$link}</span>";
        $output = "<span class='task-leaderboard'>{$output}</span>";
      }

      if (!empty($linksInfo['links']['replay']['2d']) || !empty($linksInfo['links']['replay']['3d'])) {
        $label = t('Replay'); $label = "<a href='#'>{$label}</a>";

        $link_2d = !empty($linksInfo['links']['replay']['2d']) ? l(t('2D'), $path_2d = $linksInfo['links']['replay']['2d']['path']) : '';
        $link_2d = !empty($link_2d) ? "<li>{$link_2d}</li>" : "";
        $link_3d = !empty($linksInfo['links']['replay']['3d']) ? l(t('3D Google Earch'), $path_3d = $linksInfo['links']['replay']['3d']['path']) : '';
        $link_3d = !empty($link_3d) ? "<li>{$link_3d}</li>" : "";

        $_output = "<span class='links-label'>{$label}</span>";
        $_output .= "<div class='links-content'><ul>{$link_2d}{$link_3d}</ul></div>";
        $_output = "<span class='task-replay'>{$_output}</span>";

        $output .= $_output;
      }
      break;
  }

  return $output;
}

function _pg_race_watch_links_results($items, $type) {
  $output = '';
  if (!empty($items)) {
    $label = '';
    switch ($type) {
      case 'day' :
        $label = t('Task results');
        break;
      case 'competition' :
        $label = t('Competition results');
        break;
    }

    $label = !empty($label) ? "<span class='label'>{$label}</span>" : "";

    $links = '';
    foreach ($items as $item) {
      $l = l($item['category'], $item['path'], array('attributes' => array('target' => '_blank')));
      $links .= "<li>{$l}</li>";
    }
    $output = "<span class='task-result'>{$label}<ul>{$links}</ul></span>";
  }

  return $output;
}




function theme_live_event_watch_timer($variables) {
  $race_status = $variables['race_status'];
  $timerInfo = $variables['timer_info'];
  $output = '';

  switch ($race_status) {
    case PG_RACE_WATCH_STATUS_AWAITING :
      $timer_label = t('Race starts in:');
      $timer_time = date('H:i:s', $timerInfo['timer']);
      break;
    case PG_RACE_WATCH_STATUS_STARTING :
      $timer_label = t('Race starts in:');
      $timer_time = date('H:i:s', $timerInfo['timer']);
      break;
    case PG_RACE_WATCH_STATUS_IS_LIVE :
      $timer_label = t('Race is on:');
      $timer_time = date('H:i:s', $timerInfo['timer']);
      break;
  }

  if (!empty($timer_label) && !empty($timer_time)) {
    $timer_output = "<span class='help-text'>{$timer_label}</span><span class='time'>{$timer_time}</span>";
  }

  $output = !empty($timer_output) ? "<span class='race-online'>{$timer_output}</span>" : "";

  return $output;
}
