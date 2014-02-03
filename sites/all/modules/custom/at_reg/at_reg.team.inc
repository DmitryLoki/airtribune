<?php

// @todo

/**
 * Team registration page callback.
 * 
 * @todo: Remove hardcode
 */
function at_reg_team_page_callback($node) {
  
  //~ module_load_include('inc', 'eck', 'eck.entity');
  //~ return eck__entity__add('ent_team', 'pg_nation_team');
  
  return drupal_get_form('at_reg_team_form', $node);
}


function at_reg_team_form($form, $form_state) {
  global $user;
  if (!$user->uid) {
    return;
  }
  
  $settings = field_info_instance(AIRTRIBUNE_TEAM_TYPE, AIRTRIBUNE_COUNTRY_FIELD, AIRTRIBUNE_PG_NATION_TEAM_TYPE);
  //~ dsm($settings);
  //~ dsm(countries_load_multiple());
  //~ dsm(field_info_field('field_country'));
  
  // @todo: maybe filter countries by field settings? See countries.elements.inc
  
  $form['caption'] = array(
    '#markup' => t('FAI Category 1 <br />Team Leader Registration'),
    '#prefix' => '<div class="at-reg-team-caption">',
    '#suffix' => '</div>',
  );
  
  $user_full_name = _at_reg_team_user_name($user);
  $countries = countries_get_countries('name');
  $options = array('' => t('Select country'));
  $options += $countries;
  $form['county'] = array(
    '#type' => 'select',
    '#title' => t('I, <em>!full_name</em>, declare myself as a team leader of', array('!full_name' => $user_full_name)),
    '#options' =>  $options,
    '#default_value' => ($user_country = _at_reg_team_user_country_default($user)) ? $user_country : '',
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' =>  t('Send request'),
    '#prefix'  => '<div class="form-actions">',
    '#suffix' => '</div>',
  );
  return $form;
}

// @todo
function at_reg_team_form_submit($form, &$form_state) {
  $node = $form_state['build_info']['args'][0];
  $gid = $node->nid;
  $country_code = $form_state['values']['county'];
  
  $entity = _at_reg_team_get_team_entity($gid, $country_code);
  drupal_set_message(t('Your application as a team leader was sent.'));
  drupal_set_message(t('After you are approved by organizer you will be able to continue with team registration.'));
  $form_state['redirect'] = "event/{$node->nid}/register";
}

/**
 * Get Team entity (for current event and country) if exists
 * else create a new one.
 * Add current user as candidate if not yet.
 */
function _at_reg_team_get_team_entity($gid, $country_code) {
  global $user;
  
  // Search team entitiy
  $query = db_select("og_membership", "ogm");
  $query->condition("ogm.gid", $gid, "=");
  $query->condition("ogm.entity_type", AIRTRIBUNE_TEAM_TYPE, "=");
  $query->fields("ogm", array("entity_type", "etid"));
  
  $query->join('field_data_' . AIRTRIBUNE_COUNTRY_FIELD, 'fc', 'ogm.etid = fc.entity_id');
  $query->condition('fc.entity_type', AIRTRIBUNE_TEAM_TYPE, '=');
  $query->condition('fc.' . AIRTRIBUNE_COUNTRY_ISO2_FIELD, $country_code, '=');
  
  $result = $query->execute();
  $rows = $result->fetchAll();
  
  $team_exists = !empty($rows);
  
  // Check if team exists
  if ($team_exists) {
    $row = array_shift($rows);
    $entities = entity_load(AIRTRIBUNE_TEAM_TYPE, array($row->etid));
    $entity = array_shift($entities);
    
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_TEAM_TYPE, $entity);
    //~ $value = $wrapper->{AIRTRIBUNE_TEAM_MEMBER_FIELD}->value();
    $value = $wrapper->{AIRTRIBUNE_USERS_REF_FIELD}->value();
    
    $is_candidate = FALSE;
    foreach ($value as $candidate) {
      if ($candidate->uid == $user->uid) {
        $is_candidate = TRUE;
      }
    }
    if (!$is_candidate) {
      //~ $wrapper->{AIRTRIBUNE_TEAM_MEMBER_FIELD}[count($value)]->set($user);
      $wrapper->{AIRTRIBUNE_USERS_REF_FIELD}[count($value)]->set($user);
      $wrapper->save();
    }
  }
  // Else create and populate new team entity
  else {
    // Do not translate country name for title.
    $countries = countries_get_countries('name');
    $country_name = isset($countries[$country_code]) ? $countries[$country_code] : '';
    $title = strtr('Team :country_name', array(':country_name' => $country_name));
    
    $entity = entity_create(AIRTRIBUNE_TEAM_TYPE, array('type' => AIRTRIBUNE_PG_NATION_TEAM_TYPE));
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_TEAM_TYPE, $entity);
    //~ $wrapper->uid = $user->uid;
    $wrapper->uid = 1;
    $wrapper->title = $title;
    $wrapper->{OG_AUDIENCE_FIELD}->set(array('target_id' => $gid));
    $wrapper->{AIRTRIBUNE_COUNTRY_FIELD}->set(array('iso2' => $country_code));
    //~ $wrapper->{AIRTRIBUNE_TEAM_MEMBER_FIELD}[0]->set($user);
    $wrapper->{AIRTRIBUNE_USERS_REF_FIELD}[0]->set($user);
    
    $wrapper->save();
  }
  return $entity;
}

/**
 * Get user Country from pilot profile.
 */
function _at_reg_team_user_country_default($user) {
  $profile = profile2_by_uid_load($user->uid, AIRTRIBUNE_USER_PILOT_PROFILE);
  if (empty($profile)) {
    return FALSE;
  }
  $wrapper = entity_metadata_wrapper('profile2', $profile);
  $value = $wrapper->{AIRTRIBUNE_ADDRESS_FIELD}->value();
  return !empty($value['country']) ? $value['country'] : FALSE;
}

/**
 * Get user Name/Surname from main profile.
 */
function _at_reg_team_user_name($user) {
  $profile = profile2_by_uid_load($user->uid, AIRTRIBUNE_USER_MAIN_PROFILE);
  if (empty($profile)) {
    return FALSE;
  }
  $wrapper = entity_metadata_wrapper('profile2', $profile);
  $value = $wrapper->{AIRTRIBUNE_USER_FULLNAME_FIELD}->value();
  return implode(' ', array($value['given'], $value['family']));
}


/**
 * Get category of the event.
 * @return string AIRTRIBUNE_FAI_CATEGORY_1, AIRTRIBUNE_FAI_CATEGORY_2, AIRTRIBUNE_FAI_CATEGORY_NONE
 */
function _at_reg_get_fai_type($node) {
  $wrapper = entity_metadata_wrapper('node', $node);
  $value = $wrapper->{AIRTRIBUNE_FAI_CATEGORY_FIELD}->value();
  $fai_category = !empty($value) ? $value : AIRTRIBUNE_FAI_CATEGORY_NONE;
  return $fai_category;
}

/**
 * Check if the use has already asked for team leadership.
 */
function _at_reg_team_leadership_pledged($gid, $uid, $type = 'pledged') {
  $query = db_select("og_membership", "ogm");
  $query->condition("ogm.gid", $gid, "=");
  $query->condition("ogm.entity_type", AIRTRIBUNE_TEAM_TYPE, "=");
  $query->fields("ogm", array("entity_type", "etid"));

  $query->join('eck_' . AIRTRIBUNE_TEAM_TYPE, 't', 'ogm.etid = t.id');
  
  
  // @todo
  if ($type == 'pledged') {
    //~ $query->join('field_data_' . AIRTRIBUNE_TEAM_MEMBER_FIELD, 'ftm', 't.id = ftm.entity_id');
    $query->join('field_data_' . AIRTRIBUNE_USERS_REF_FIELD, 'ftm', 't.id = ftm.entity_id');
    $query->condition("ftm.entity_type", AIRTRIBUNE_TEAM_TYPE, "=");
    //~ $query->condition("ftm." . AIRTRIBUNE_TEAM_MEMBER_FIELD . "_target_id", $uid, "=");
    $query->condition("ftm." . AIRTRIBUNE_USERS_REF_FIELD . "_target_id", $uid, "=");
    //~ 
  }
  elseif ($type == 'approved') {
    $query->condition('t.uid', $uid, '=');
  }

  $result = $query->execute();
  $rows = $result->fetchAll();
  
  return !empty($rows) ? $rows[0]->etid : FALSE;
}
