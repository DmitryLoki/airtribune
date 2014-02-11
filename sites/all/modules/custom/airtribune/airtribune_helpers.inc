<?php

/**
* @file
* Helpers functions for AirTribune.
*/

function is_user_entity_author($entity) {
  global $user;
  if ($user->uid == $entity->uid || $user->uid == 1) {
    return TRUE;
  }
  return FALSE;
}

function is_user_contest_org($contest) {
  return is_user_entity_author($contest);
}

function is_user_team_leader($team) {
  return is_user_entity_author($team);
}

/**
 * Detect contest nodes
 * @see #4323
 */
function is_contest($node) {
  $contest_node_types = array (AIRTRIBUNE_PG_CONTEST_TYPE, AIRTRIBUNE_HG_CONTEST_TYPE);
  if (in_array($node->type, $contest_node_types)) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Definition of solutions pages
 * @see #3796 #4341
 */
function is_solutions(){
  $path = request_uri();
  $pattern = SOLUTIONS_REGEXT_PATTERN;
  preg_match($pattern, $path, $matches);
  $part = isset($matches[0]) ? $matches[0] : NULL;
  switch($part) {
    case 'privacy':
    case 'terms':
    case 'organizers':
    case 'pilots':
    case 'viewers':
      return $part;
      break;
  }

  return FALSE;
}


function get_country_name($iso2) {
  $country = country_load($iso2);
  return $country->name;
}

function get_pilot_profile($user) {
  return profile2_load_by_user($user, AIRTRIBUNE_USER_PILOT_PROFILE);
}

function get_main_profile($user) {
  return profile2_load_by_user($user, AIRTRIBUNE_USER_MAIN_PROFILE);
}

/**
 * Alias for at_user_get_full_name()
 * @param $user
 */
function get_full_name($user) {
  return at_user_get_full_name($user);
}

/**
 * Returns Contest Core ID from race entity
 */
function get_contest_id_for_entity($entity) {
  $contest_id = $entity->og_group_ref[LANGUAGE_NONE][0]['target_id'];
  $contest = node_load($contest_id);
  $field_core_id = field_get_items('node', $contest, AIRTRIBUNE_CORE_ID_FIELD);
  if (!empty($field_core_id[0]['value'])) {
    return $field_core_id[0]['value'];
  }
  else {
    return FALSE;
  }
}

function get_contest_trackers($contest_id = NULL, $contestant_id = NULL) {
  $view = views_get_view('contest_trackers');
  $view->set_arguments(array($contest_id, $contestant_id));
  $view->query->where[0]['type'] = 'OR';
  $view->execute();
  $response = $view->result;
  $ids = array();
  foreach ($response as $tracker) {
    $ids[] = $tracker->id;
  }
  return implode('+', $ids);
}