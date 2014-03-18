<?php

// @todo: move this plugin into pg_race.module

$plugin = array(
  'title' => t('Frontpage Live event link'),
  'renderer' => 'at_helper__frontpage_live_event_link__renderer',
  'required_tokens' => 'at_helper__frontpage_live_event_link__required_keys',
);

function at_helper__frontpage_live_event_link__renderer(array $components, array $tokens) {
  $values = array();
  foreach ($components as $k => $token) {
    $values[$k] = $tokens[$token];
  }

  $day_blog = $values['dayblog_last_entry'];
  $event_nid = $values['event_nid'];
  return !empty($day_blog) ? "event/{$event_nid}/blog" : "event/{$event_nid}/info";
}

/**
 * Required token keys.
 */
function at_helper__frontpage_live_event_link__required_keys() {
  return array(
    'dayblog_last_entry',  // day blog
    'event_nid',  // event nid
  );
}
