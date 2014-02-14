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
 * Returns Contest for entity
 */
function get_contest_for_entity($entity) {
  if (get_class($entity) == 'OgMembership') {
    return node_load($entity->gid);
  }
  return node_load($entity->og_group_ref[LANGUAGE_NONE][0]['target_id']);
}

/**
 * Returns Core ID from entity.
 * Returns Core ID of referenced entity for og_membership.
 */
function get_core_id_from_entity($entity_type, $entity) {
  $origin_entity = NULL;
  $etype = NULL;
  $etid = NULL;
  $core_id = FALSE;
  if ($entity_type == 'og_membership') {
    $etype = $entity->entity_type;
    $etid = $entity->etid;
  } else {
    $etype = $entity_type;
    $etid = $entity->id ? $entity->id : $entity->nid;
  }
  $origin_entity = entity_load($etype, array($etid));
  $origin_entity = $origin_entity[$etid];
  // Get core ID from entity
  if (isset($origin_entity->{AIRTRIBUNE_CORE_ID_FIELD})) {
    $wrapper = entity_metadata_wrapper($etype, $origin_entity);
    $core_id = $wrapper->{AIRTRIBUNE_CORE_ID_FIELD}->value();
  }

  return $core_id;
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