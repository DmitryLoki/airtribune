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

function is_membership_contestant($og_membership) {
  $contestants = array(
    AIRTRIBUNE_MEMBERSHIP_CONTESTANT,
    AIRTRIBUNE_MEMBERSHIP_WINDDUMMY,
    AT_MEMBERSHIP_HG_CONTESTANT,
  );
  return in_array($og_membership->type, $contestants);
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

function get_phone($entity) {
  if (!empty($entity->field_phone)) {
    $field = $entity->field_phone[LANGUAGE_NONE][0];
  } else {
    return NULL;
  }

  if (isset($field['full_number'])) {
    return $field['full_number'];
  }
  else {
    $country_code = cck_phone_countrycodes($field['country_codes']);
    return $country_code['code'] . $field['number'];
  }
}

function get_tracker($entity_type, $entity) {
  $core_id = NULL;
  if (module_exists('at_tracker')) {
    $entity_fields = field_info_instances($entity_type, $entity->type);
    foreach ($entity_fields as $field_name => $field_instance) {
      $field_info = field_info_field($field_name);
      $type = $field_info['type'];
      if ($type == 'at_tracker') {
        if (!empty($entity->{$field_name}[LANGUAGE_NONE][0]['value'])) {
          $core_id = $entity->{$field_name}[LANGUAGE_NONE][0]['value'];
        }
      }
    }
  } 

  if (empty($core_id)) {
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    $tracker = $entity_wrapper->field_tracker->value();
    $core_id = get_core_id_from_entity(AIRTRIBUNE_TRACKER_TYPE, $tracker);
  }

  return $core_id;
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
function get_contest_for_entity($entity_type, $entity) {
  $contest = FALSE;
  if (get_class($entity) == 'OgMembership') {
    return node_load($entity->gid);
  } else if (isset($entity->group_group) && $entity->group_group['und'][0]['value'] == 1){
    return $entity;
  }
  if (isset($entity->og_group_ref[LANGUAGE_NONE][0]['target_id'])){
    $contest = node_load($entity->og_group_ref[LANGUAGE_NONE][0]['target_id']);
  }
  return $contest ;
}

/**
 * Returns Core ID from entity.
 * Returns Core ID of referenced entity for og_membership.
 */
function get_core_id_from_entity($entity_type, $entity) {
  if ($entity_type == 'og_membership') {
    $entity_type = $entity->entity_type;
    $entity = entity_load_single($entity->entity_type, $entity->etid);
  }
  // Get core ID from entity
  if (!empty($entity->{AIRTRIBUNE_CORE_ID_FIELD})) {
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    return $wrapper->{AIRTRIBUNE_CORE_ID_FIELD}->value();
  }
  return NULL;
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

function generate_person_id() {
  // pers-YYMMDD-random, random = first 32bits from UUID4
  return 'pers-' . date('ymd') . '-' . sprintf('%d%d', mt_rand(0, 0xffff), mt_rand(0, 0xffff));
}