<?php

$plugin = array(
  'pg_racetype' => AT_RACE_RACETYPE_OPEN_DISTANCE,
  'validate_callback' => 'at_race_racetype_open_distance_validate',
  'add_new_validate_callback' => 'at_race_racetype_open_distance_add_new_validate',
  'remove_point_validate_callback' => 'at_race_racetype_open_distance_remove_point_validate',
);

function at_race_racetype_open_distance_add_new_validate($form, &$form_state) {
  // TODO:
}

function at_race_racetype_open_distance_remove_point_validate($form, &$form_state) {
  // TODO:
}
