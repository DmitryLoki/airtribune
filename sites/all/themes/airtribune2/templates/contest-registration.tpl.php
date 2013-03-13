<?php

global $user;

//print $user->mail;
print drupal_render($form['user_mail']);

// Main profile
// =====================
if (!empty($form['profile_main'])) {
  $lang = $form['profile_main']['field_full_name']['#language'];
  // Name.
  $form['profile_main']['field_full_name'][$lang][0]['given']['#prefix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#suffix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#prefix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#suffix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#title_display'] = 'before';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#title_display'] = 'before';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#description'] = t('Your name in English transcription.');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#description'] = t('Your surname in English transcription.');
  $form['profile_main']['field_full_name'][$lang][0]['given']['#attributes']['rel'] = t('Enter your name');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#attributes']['rel'] = t('Enter your surname');
  // print components
  print drupal_render($form['profile_main']['field_full_name'][$lang][0]['given']);
  print drupal_render($form['profile_main']['field_full_name'][$lang][0]['family']);
  drupal_render($form['profile_main']['field_full_name']);

  // Gender.
  print drupal_render($form['profile_main']['field_gender']);

  // Birthdate
  $lang = $form['profile_main']['field_birthdate']['#language'];
  $form['profile_main']['field_birthdate'][$lang][0]['value']['month']['#title'] = $form['profile_main']['field_birthdate'][$lang][0]['#title'];
  $form['profile_main']['field_birthdate'][$lang][0]['#title'] = '';
  print drupal_render($form['profile_main']['field_birthdate']);

  // Hide wrapping fieldsets.
  drupal_render($form['profile_main']);
}

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
print drupal_render($og_form['field_contestant_number']);

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
