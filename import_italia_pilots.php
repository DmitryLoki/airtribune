<?php

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// for debug.
$user_with_filled_data = profile2_load_by_user(user_load(6));
$processed_pilots = array();
//dpm(json_decode(file_get_contents('debug.json'), true));
//die();

/*
 * Init
 */
$roles = array(
  2 => 'authenticated user',
  6 => 'pilot',
);

$country = 'it'; // Italy
$country_phone_code = '+39'; // Italy

$groups_to_join = array(6639, 6645, 6650, 6655);
$groups_to_join = array(5438, 5718, 5452);

$fields = array(
//  'id'       => 'user_id',
  'email'    => 'email',

//  'field_full_name' => 'name',
  'name'     => 'firstname',
  'surname'  => 'lastname',
  'field_birthdate' => 'cb_datadinascita',

//  'province'    => 'cb_provincia',
  'postal_code' => 'cb_cap',
  'city'        => 'cb_cittdiresidenza',
  'address'     => 'cb_indiirizzo',

  'field_phone'       => 'cb_cellulare',

  'field_fai_license_number'      => 'cb_licenzafai',
  'field_civl_id'     => 'cb_numerocivl',
  'field_nat_license_id' => 'cb_ntesserafivl',
  'field_team'             => 'cb_clubfivl',

  'field_gender'            => 'cb_sesso',
  'field_t_shirt_size'        => 'cb_cdshirtsize',
  'field_paraglider_manufacturer' => 'cb_marcavela',
  'field_paraglider_model'      => 'cb_modellovela',
  'field_paraglider_color'      => 'cb_colorevela',

  'field_insurance_company' => 'cb_compagniarct',
  'field_insurance_policy_number'  => 'cb_ndocumento',
);
$fields = array_flip($fields);

$required_fields = array (
  'name',
  'surname',
  'field_birthdate',
  'postal_code',
  'city',
  'address',
  'field_fai_license_number',
  'field_civl_id',
  'field_nat_license_id',
  'field_team',
  'field_gender',
  'field_t_shirt_size',
  'field_paraglider_manufacturer',
  'field_paraglider_model',
  'field_paraglider_color',
  'field_insurance_company',
  'field_insurance_policy_number',
);

/*
 * Load data.
 */
// For speed-up at debbuging, instead load from csv and processing with non-english fields
if (file_exists('parsed_pilots.json')) {
  $pilots = json_decode(file_get_contents('parsed_pilots.json'), true);
} else {
  $csv_pilots = csv_to_array('pilots.csv');
  foreach ($csv_pilots as $number => $pilot) {
    foreach ($pilot as $field_name => $value) {
      if ($eng_field_name = $fields[$field_name]) {
        $pilots[$number][$eng_field_name] = trim($value);
      }
    }
  }
  file_put_contents('parsed_pilots.json', json_encode($pilots));
}

/*
 * Main processing.
 */
foreach ($pilots as $key => $pilot) {
  echo $key . ", ";

  if ($user = user_load_by_mail($pilot['email'])) {
    $profile = profile2_load_by_user($user);
    // This pilot already registered at AirTribune, and have filled profiles, skip him.
    if (count($profile) == 2) {
      debug_out('exist', $user, profile2_load_by_user($user), $pilot);
      continue;
    } else {
      // delete prof
      if ($profile['main']) profile2_delete($profile['main']);
      if ($profile['pilot']) profile2_delete($profile['pilot']);
    }
  }

  // Create new drupal user.
  $pilot['email'] = substr(md5(time()),0,7).$pilot['email'];
  $new_user = array(
    'name' => $pilot['email'],
    'pass' => user_password(),
    'mail' => $pilot['email'],
    'init' => $pilot['email'],
    'status' => 1,
    'roles' => $roles,
    'access' => REQUEST_TIME,
  );
  $user = user_save(null, $new_user);

  // Remove country phone code and spaces from raw phone number.
  $pilot['field_phone'] = str_replace(array(' ', $country_phone_code), '', $pilot['field_phone']);

  // If required fields is empty values, fill by '-'.
  foreach ($required_fields as $field) {
    $pilot[$field] = check_for_empty($pilot[$field]);
  }

  // Prepare complex fields.
  $field_birthdate = intval(strtotime($pilot['field_birthdate']));
  $field_gender = get_gender_italian($pilot['gender']);
  $field_full_name = array (
    'family' => $pilot['name'],
    'given'  => $pilot['surname'],
  );
  $field_address = array(
    'country' => $country,
    'locality' => $pilot['city'],
    'postal_code' => $pilot['postal_code'],
    'thoroughfare' => $pilot['address'],
  );
  $field_phone = array(
    'extension' => null,
    'country_codes' => $country,
    'number' => $pilot['field_phone'],
//    'phone_number' => $pilot['field_phone'],
  );

  // Create new 'main' & 'pilot' profiles.
  $profile_main = profile2_create(array('type' => 'main', 'uid' => $user->uid));
  $profile_w = entity_metadata_wrapper('profile2', $profile_main);
  $profile_w->field_birthdate->set($field_birthdate);
  $profile_w->field_full_name->set($field_full_name);
  $profile_w->field_gender->set($field_gender);
  profile2_save($profile_main);

  $profile_pilot = profile2_create(array('type' => 'pilot', 'uid' => $user->uid));
  $profile_w = entity_metadata_wrapper('profile2', $profile_pilot);
  $profile_w->field_address->set($field_address);
//  $profile_w->field_phone->set($field_phone);
  $profile_pilot->field_phone['und']['0'] = $field_phone;
  $profile_w->field_fai_license_number->set($pilot['field_fai_license_number']);
  $profile_w->field_civl_id->set(intval($pilot['field_civl_id']));
  $profile_w->field_nat_license_id->set($pilot['field_nat_license_id']);
  $profile_w->field_team->set($pilot['field_team']);
  $profile_w->field_t_shirt_size->set($pilot['field_t_shirt_size']);
  $profile_w->field_paraglider_manufacturer->set($pilot['field_paraglider_manufacturer']);
  $profile_w->field_paraglider_model->set($pilot['field_paraglider_model']);
  $profile_w->field_paraglider_color->set($pilot['field_paraglider_color']);
  $profile_w->field_insurance_company->set($pilot['field_insurance_company']);
  $profile_w->field_insurance_policy_number->set($pilot['field_insurance_policy_number']);
  // Fill fields, for which we haven't data.
  $profile_w->field_name_in_national_alphabet->set('–');
  //$profile_w->field_name_in_national_alphabet->set($field_full_name);
  $profile_w->field_person_name->set('–');
//  $profile_w->field_person_phone->set(array('country_codes' => $country, 'number' => '000000000'));
  $profile->field_person_phone['und']['0'] = array('country_codes' => $country, 'number' => '000000000');
  $profile_w->field_blood_type->set('unknown');
  profile2_save($profile_pilot);

  // Add the user to the groups.
  foreach ($groups_to_join as $group_id) {
    $group = node_load($group_id);
    $ogm = og_membership_create('node', $group_id, 'user', $user->uid, 'og_user_node', array('type' => AIRTRIBUNE_MEMBERSHIP_CONTESTANT));
    $ogm_w = entity_metadata_wrapper('og_membership', $ogm);
    $ogm->field_phone['und']['0'] = $field_phone;
    $ogm_w->field_team->set($pilot['field_team']);
    $ogm_w->field_paraglider_manufacturer->set($pilot['field_paraglider_manufacturer']);
    $ogm_w->field_paraglider_model->set($pilot['field_paraglider_model']);
    $ogm_w->field_paraglider_color->set($pilot['field_paraglider_color']);
    $ogm_w->field_contestant_number->set(rand(9000,9999));
    $ogm_w->field_pg_contestant_status->set(1); // 1|Waiting list, 4|Confirmed
    og_membership_save($ogm);

    // Optional - changes the users role in the group. 
    // og_role_grant('node', $group->gid, $user->uid, $role_id);
  }

  debug_out('created', $user, profile2_load_by_user($user));
  unset($user);
}


/*
 * Debug
 */
file_put_contents('debug.json', json_encode($processed_pilots));
dpm($processed_pilots);


/*
 * Helpers
 */
function get_gender_italian($gender) {
  return ($gender == 'Femmina') ? 1 : 0; // male = 0, female = 1
}

function check_for_empty($field) {
  return empty($field) ? '-' : $field;
}
function debug_out($type, $user, $profile, $new=null) {
  global $processed_pilots;
  $processed_pilots[$type][] = array(
    'user' => $user,
    'profile' => $profile,
    'new' => $new,
  );
}

function csv_to_array($filename = '', $delimiter = ',') {
  if (!file_exists($filename) || !is_readable($filename)) {
    return FALSE;
  }

  $header = NULL;
  $data = array();
  if (($handle = fopen($filename, 'r')) !== FALSE) {
    while (($row = fgetcsv($handle, 1000, $delimiter)) !== FALSE) {
      if (!$header) {
        $header = $row;
      }
      else {
        $data[] = array_combine($header, $row);
      }
    }
    fclose($handle);
  }
  return $data;
}
