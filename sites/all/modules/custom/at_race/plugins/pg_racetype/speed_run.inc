<?php

$plugin = array(
  'pg_racetype' => AT_RACE_RACETYPE_SPEED_RUN,
  'validate_callback' => 'at_race_racetype_speed_run_validate',
  'add_new_validate_callback' => 'at_race_racetype_speed_run_add_new_validate',
  'remove_point_validate_callback' => 'at_race_racetype_speed_run_remove_point_validate',
);

function at_race_racetype_speed_run_add_new_validate($form, &$form_state) {
  // TODO:
}

function at_race_racetype_speed_run_remove_point_validate($form, &$form_state) {
  // TODO:
}
