<?php

$plugin = array(
  'title' => t('My custom plugin'),
  'renderer' => 'at_helper__frontpage_live_event_footer__renderer',
  'required_tokens' => 'at_helper__frontpage_live_event_footer__required_keys',
);

function at_helper__frontpage_live_event_footer__renderer(array $components, array $tokens) {
  //~ dsm($components);
  //~ dsm($tokens);
  return 'some text';
}

// @todo
/**
 * Required token keys.
 */
function at_helper__frontpage_live_event_footer__required_keys() {
  return array(
    'nid',  // day nid
    'day_number', // day number
  );
}
