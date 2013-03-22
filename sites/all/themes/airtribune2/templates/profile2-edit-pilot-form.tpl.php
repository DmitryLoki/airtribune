<?php

$pilot_uid = arg(1);
drupal_set_title(at_user_get_full_name($pilot_uid));

drupal_add_js(drupal_get_path('module', 'at_validation') . '/js/user-event-registration.js');
// Pilot profile
// =====================
// Address field
print drupal_render($form['profile_pilot']['field_address']);

// Mobile phone
print drupal_render($form['profile_pilot']['field_phone']);


// FAI license
print drupal_render($form['profile_pilot']['field_fai_license_number']);

// CIVIL ID
print drupal_render($form['profile_pilot']['field_civl_id']);

// Pilot's number
// print drupal_render($og_form['field_contestant_number']);

// T-shirt.
print drupal_render($form['profile_pilot']['field_t_shirt_size']);

// Paraglider manufacturer
print drupal_render($form['profile_pilot']['field_paraglider_manufacturer']);

// Paraglider model
print drupal_render($form['profile_pilot']['field_paraglider_model']);

// Paraglider color
print drupal_render($form['profile_pilot']['field_paraglider_color']);

// Sponsors
print drupal_render($form['profile_pilot']['field_sponsors']);

// Insurance company
print drupal_render($form['profile_pilot']['field_insurance_company']);

// Insurance policy number
print drupal_render($form['profile_pilot']['field_insurance_policy_number']);

// Name in national alphabet.
print drupal_render($form['profile_pilot']['field_name_in_national_alphabet']);

// Person to contact in case of emergency
print drupal_render($form['profile_pilot']['field_person_name']);

// Contact phone number in case of emergency
print drupal_render($form['profile_pilot']['field_person_phone']);

// Blood type
print drupal_render($form['profile_pilot']['field_blood_type']);

// Hide profile fieldsets
drupal_render($form['profile_pilot']);

print drupal_render_children($form);
